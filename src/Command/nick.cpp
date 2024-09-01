/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:55:31 by orakib            #+#    #+#             */
/*   Updated: 2023/10/16 18:22:58 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

bool isValidNickname(std::string &nickname)
{
    if (nickname.empty())
        return false;
    std::string validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}-_\\|";
    if(nickname.find_first_not_of(validCharacters) != std::string::npos)
        return false;
    return true;
}

void IrcServer::NICK(Client &client, std::vector<std::string> &args) {
	if (args.size() == 0)
		sendTo_H(client.socketFd, ERR_NONICKNAMEGIVEN(client.nickname));
	else if (!isValidNickname(args[0]))
		sendTo_H(client.socketFd, ERR_ERRONEUSNICKNAME(client.nickname, args[0]));
	else if (getClient(args[0]) && getClient(args[0]) != &client)
		sendTo_H(client.socketFd, ERR_NICKNAMEINUSE(client.nickname, args[0]));
	else {
		if (client.isLogged()) {
			std::map<std::string, Channel>::iterator it = Channels.begin();
			while (it != Channels.end()) {
				if (it->second.isClientUser(client))
					ChangeMapKey<std::string, Member>(it->second._members, client.nickname, args[0]);
				if (it->second.isClientInvited(client)) {
					it->second.removeInvite(client);
					it->second._invited.push_back(args[0]);
				}
				it++;
			}
			std::vector<Client>::iterator cl = Clients.begin();
			while (cl != Clients.end()) {
				if (cl->isLogged())
					sendTo(cl->socketFd, ":" + client.nickname + "!" + client.username + "@" + IrcServer::HostName + " NICK " + args[0]);
				cl++;
			}
		}
		client.nickname = args[0];
	}
}