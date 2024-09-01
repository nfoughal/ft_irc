/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:27:22 by orakib            #+#    #+#             */
/*   Updated: 2023/10/19 14:29:12 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

bool	isNumber(std::string str) {
	size_t i = -1;

	while (++i < str.size()) {
		if (!std::isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool	isModestringValid(std::string mstr) {
	if (mstr.size() < 2)
		return (false);
	if (mstr[0] != '+' && mstr[0] != '-')
		return (false);
	std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size_t i = 0;
	while (++i < mstr.size())
		if (alpha.find(mstr[i]) == std::string::npos)
			return (false);
	return (true);
}

void	modePlus(Client &client, Channel &ch, std::string mstr, std::vector<std::string> &args) {
	size_t	i = 0;

	if (mstr[1] == 'k') {
		if (args.size() < 3)
			sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "MODE"));
		else if (args[2].find(' ') != std::string::npos)
			sendTo_H(client.socketFd, ERR_INVALIDKEY(client.nickname, ch.getName()));
		else {
			ch.setKeyBool(true);
			ch.setKey(args[2]);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "+k"), client);
		}
		return ;
	}
	if (mstr[1] == 'l') {
		if (args.size() < 3)
			sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "MODE"));
		else if (!isNumber(args[2]))
			sendTo_H(client.socketFd, ERR_INVALIDMODEPARAM(client.nickname, ch.getName(), "l", args[2], "Not a number"));
		else {
			ch.setLimit(std::atoi(args[2].c_str()));
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "+l"), client);
		}
		return ;
	}
	if (mstr[1] == 'o') {
		if (args.size() < 3)
			sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "MODE"));
		else if (args[2].find(' ') != std::string::npos)
			sendTo_H(client.socketFd, ERR_INVALIDMODEPARAM(client.nickname, ch.getName(), "o", args[2], "Invalid param"));
		else {
			Client *target = ch.getClientByName(args[2]);
			if (!target)
				sendTo_H(client.socketFd, ERR_INVALIDMODEPARAM(client.nickname, ch.getName(), "o", args[2], "Client is not a channel member"));
			else {
				ch.makeClientOperator(*target);
				ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "+o " + target->nickname), client);
			}
		}
		return ;
	}
	while (++i < mstr.size()) {
		if (mstr[i] == 'i') {
			ch.setInviteBool(true);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "+i"), client);
		}
		else if (mstr[i] == 't'){
			ch.setTopicBool(true);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "+t"), client);
		}
	}
}

void	modeMinus(Client &client, Channel &ch, std::string mstr, std::vector<std::string> &args) {
	size_t i = 0;

	while (++i < mstr.size()) {
		if (mstr[i] == 'i') {
			ch.setInviteBool(false);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "-i"), client);
		}
		else if (mstr[i] == 't') {
			ch.setTopicBool(false);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "-t"), client);
		}
		else if (mstr[i] == 'l') {
			ch.setLimit(0);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "-l"), client);
		}
		else if (mstr[i] == 'k') {
			ch.setKeyBool(false);
			ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "-k"), client);
		}
		else if (mstr[i] == 'o') {
			if (args.size() < 3)
				sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "MODE"));
			else if (args[2].find(' ') != std::string::npos)
				sendTo_H(client.socketFd, ERR_INVALIDMODEPARAM(client.nickname, ch.getName(), "o", args[2], "Invalid param"));
			else {
				Client *target = ch.getClientByName(args[2]);
				if (!target)
					sendTo_H(client.socketFd, ERR_INVALIDMODEPARAM(client.nickname, ch.getName(), "o", args[2], "Client is not a channel member"));
				else {
					ch.removeOperatorRole(*target);
					ch.sendToAllMembers((':' + IrcServer::HostName + ' ') + RPL_CHANNELMODEIS(client.nickname, args[0], "-o " + target->nickname), client);
				}
			}
		}
	}
}

void	IrcServer::MODE(Client &client, std::vector<std::string> &args) {
	if (args.size() < 1)
		sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "MODE"));
	else if (Channels.find(args[0]) == Channels.end()) {
		sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, args[0]));
	}
	else if (args.size() == 1) {
		std::string modestring = "+";
		if (Channels[args[0]].isInviteOnlySet())
			modestring += "i";
		if (Channels[args[0]].isKeySet())
			modestring += "k";
		if (Channels[args[0]].isTopicModeSet())
			modestring += "t";
		if (Channels[args[0]].getLimit())
			modestring += "l";
		sendTo_H(client.socketFd, RPL_CHANNELMODEIS(client.nickname, args[0], modestring));
	}
	else if (Channels[args[0]].isClientOperator(client) == false)
		sendTo_H(client.socketFd, ERR_CHANOPRIVSNEEDED(client.nickname, args[0]));
	else if (isModestringValid(args[1])) {
		if (args[1][0] == '+'){
			modePlus(client, Channels[args[0]], args[1], args);
		}
		else if (args[1][0] == '-') {
			modeMinus(client, Channels[args[0]], args[1], args);
		}
	}
}