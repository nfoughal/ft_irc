/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:28:42 by orakib            #+#    #+#             */
/*   Updated: 2023/10/19 15:53:58 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void	afterjoin_replies(Client &client, std::vector<std::string> &args,
		Channel &ch) {
	(void)args;
	ch.sendToAllMembers(":" + client.nickname + "!" + client.username
		+ "@" + host_name() + " " + "JOIN " + ch.getName(), client);
	if (!ch.getTopic().empty())
		sendTo_H(client.socketFd, RPL_TOPIC(client.nickname, ch.getName(), ch.getTopic()));
	sendTo_H(client.socketFd, RPL_NAMREPLY(client.nickname, ch.getName(), ch.getAllClientsName()));
	sendTo_H(client.socketFd, RPL_ENDOFNAMES(client.nickname, ch.getName()));
}

bool	isChannelNameValid(std::string &name) {
	if (name.size() < 2)
		return (false);
	if (name[0] != '#' || name.find(' ') != std::string::npos
		|| name.find(',') != std::string::npos || name.find(7) != std::string::npos)
		return (false);
	return (true);
}

void	IrcServer::JOIN(Client &client, std::vector<std::string> &args) {
	if (args.size() < 1) {
		sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "JOIN"));
	}
	else if (args[0] == "0"){
        std::map<std::string, Channel>::iterator it1 = Channels.begin();
        while (it1 != Channels.end()) {
            if (it1->second.isClientUser(client)) {
                std::vector<std::string> ch1;
                ch1.push_back(it1->second.getName());
                ch1.push_back("Disconnected");
                PART(client, ch1);
            }
            if (it1->second.isClientInvited(client))
                it1->second.removeInvite(client);
            it1++;
        }
    }
	else if (!isChannelNameValid(args[0])) {
		sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, args[0]));
	}
	else {
		std::map<std::string, Channel>::iterator it = Channels.find(args[0]);
		if (it == Channels.end()) {
			if (args.size() == 1) {
				Channels[args[0]] = Channel(args[0], client);
				afterjoin_replies(client, args, Channels[args[0]]);
			}
			else if (args.size() > 1) {
				Channels[args[0]] = Channel(args[0], client, args[1]);
				afterjoin_replies(client, args, Channels[args[0]]);
			}
		}
		else {
			if (!it->second.isInviteOnlySet() && !it->second.isKeySet() && !it->second.getLimit()) {
				if (it->second.isClientUser(client)) {
					sendTo_H(client.socketFd, ERR_USERONCHANNEL(client.nickname, "", args[0]));
					return ;
				}
				it->second.addMember(client);
				afterjoin_replies(client, args, it->second);
				return ;
			}
			else if (it->second.getLimit()) {
				if (it->second.getCount() >= it->second.getLimit()) {
					sendTo_H(client.socketFd, ERR_CHANNELISFULL(client.nickname, it->first));
					return ;
				}
			}
			else if (it->second.isInviteOnlySet()) {
				if (!it->second.isClientInvited(client)) {
					sendTo_H(client.socketFd, ERR_INVITEONLYCHAN(client.nickname, it->first));
					return ;
				}
			}
			else if(it->second.isKeySet()) {
				if (args.size() <= 1 || args[1] != it->second.getKey()) {
					sendTo_H(client.socketFd, ERR_BADCHANNELKEY(client.nickname, it->first));
					return ;
				}
			}
			if (it->second.isClientUser(client)) {
				sendTo_H(client.socketFd, ERR_USERONCHANNEL(client.nickname, "", args[0]));
				return ;
			}
			it->second.addMember(client);
			afterjoin_replies(client, args, it->second);
		}
	}
}