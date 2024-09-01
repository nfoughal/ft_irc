/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:00:17 by nfoughal          #+#    #+#             */
/*   Updated: 2023/10/10 17:45:03 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::KICK(Client &client, std::vector<std::string> &args) {
    if (args.size() < 2)
    {
        sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "KICK"));
        return ;
    }

    std::string channelName = args[0];
    std::string user = args[1];
    std::string cmt;

    if (args.size() > 2)
    {
        cmt = args[2];
        for (size_t i = 3; i < args.size(); i++)
            cmt += " " + args[i];
    }
    else
        cmt = "Kicked by " + client.nickname;
    
    Channel *channel = getChannel(channelName);
    
    if(!channel)
    {
        sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, channelName));
        return ;
    }
    
    if (!channel->isClientUser(client)) {
        sendTo_H(client.socketFd, ERR_NOTONCHANNEL(client.nickname, channelName));
        return ;
    }
    
    if(!channel->isClientOperator(client))
    {
        sendTo_H(client.socketFd, ERR_CHANOPRIVSNEEDED(client.nickname, channelName));
        return ;
    }
    
    if (!channel->getClientByName(user))
    {
        sendTo_H(client.socketFd, ERR_USERNOTINCHANNEL(client.nickname, user, channelName));
        return ;
    }

    Client *targetClient = getClient(user);
    
    if(targetClient)
    {
        channel->removeMember(*targetClient);
        sendTo(targetClient->socketFd, ":" + client.nickname + "!" + client.username
            + "@" + IrcServer::HostName + " KICK " + channelName + " " + user + " :" + cmt);
        channel->sendToAllMembers(":" + client.nickname + "!" + client.username
            + "@" + IrcServer::HostName + " KICK " + channelName + " " + user + " :" + cmt, client);
    }
}