/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orakib <orakib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:34:26 by orakib            #+#    #+#             */
/*   Updated: 2023/10/13 17:22:32 by orakib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::PRIVMSG(Client &client, std::vector<std::string> &args) {
	if (args.size() == 0)
		sendTo_H(client.socketFd, ERR_NORECIPIENT(client.nickname, "PRIVMSG"));
	else if (args.size() == 1)
		sendTo_H(client.socketFd, ERR_NOTEXTTOSEND(client.nickname));
	else {
		std::string msg;
		msg = args[1];
		for (size_t i = 2; i < args.size(); i++)
			msg += " " + args[i];
		if (msg[0] == ':')
            msg.erase(0, 1);
		if (args[0][0] == '#') {
			if (Channels.find(args[0]) == Channels.end())
				sendTo_H(client.socketFd, ERR_NOSUCHNICK(client.nickname, args[0]));
			else if (!Channels[args[0]].isClientUser(client))
				sendTo_H(client.socketFd, ERR_CANNOTSENDTOCHAN(client.nickname, args[0]));
			else {
				std::map<std::string, Member>::iterator cl = Channels[args[0]]._members.begin();
				while (cl != Channels[args[0]]._members.end()) {
					if (cl->second.client == &client){
						cl++;
						continue;
					}
					sendTo(cl->second.client->socketFd, ":" + client.nickname + " PRIVMSG " + args[0] + " :" + msg);
					cl++;
				}
			}
		}
		else {
			Client *target = getClient(args[0]);
			if (!target)
				sendTo_H(client.socketFd, ERR_NOSUCHNICK(client.nickname, args[0]));
			else
				sendTo(target->socketFd, ":" + client.nickname +  " PRIVMSG " + args[0] + " :" + msg);
		}
	}
}