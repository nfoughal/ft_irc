/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:48:34 by nfoughal          #+#    #+#             */
/*   Updated: 2023/10/10 17:28:38 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void	IrcServer::INVITE(Client &client, std::vector<std::string> &args) {
    if (args.size() != 2)
        sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "INVITE"));
    else {
        Channel *channel = getChannel(args[1]);
        Client *cl = getClient(args[0]);
        if (!channel)
            sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, args[1]));
        else if (!channel->isClientUser(client))
            sendTo_H(client.socketFd, ERR_NOTONCHANNEL(client.nickname, args[1]));
        else if (channel->isInviteOnlySet() && !channel->isClientOperator(client))
            sendTo_H(client.socketFd, ERR_CHANOPRIVSNEEDED(client.nickname, args[1]));
        else if (channel->getClientByName(args[0]))
            sendTo_H(client.socketFd, ERR_USERONCHANNEL(client.nickname, args[0], args[1]));
        else {
            channel->makeClientInvited(*cl);
            sendTo_H(client.socketFd, RPL_INVITING(client.nickname, args[0], args[1]));
            sendTo(cl->socketFd, ":" + client.nickname + "!" + client.username
                + "@" + IrcServer::HostName + " INVITE " + args[0] + " " + args[1]);
        }
    }
}