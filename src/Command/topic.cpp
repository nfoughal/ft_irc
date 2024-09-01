/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:47:16 by nfoughal          #+#    #+#             */
/*   Updated: 2023/10/10 18:40:56 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::TOPIC(Client &client, std::vector<std::string> &args)
{
    if(args.size() < 1)
    {
        sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "TOPIC"));
        return ;
    }
        
    Channel *channel = getChannel(args[0]);
    
    if(!channel)
    {
        sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, args[0]));
        return ;
    }
    
    if(!channel->isClientUser(client))
    {
        sendTo_H(client.socketFd, ERR_NOTONCHANNEL(client.nickname, args[0]));
        return ;   
    }
    
    if(channel->isTopicModeSet() && !channel->isClientOperator(client)) {
        sendTo_H(client.socketFd, ERR_CHANOPRIVSNEEDED(client.nickname, args[0]));
        return ;
    }
    
    if (args.size() == 1) {
        if(channel->getTopic().empty())
            sendTo_H(client.socketFd, RPL_NOTOPIC(client.nickname, args[0]));
        else
            sendTo_H(client.socketFd, RPL_TOPIC(client.nickname, args[0], channel->getTopic()));
        return ;
    }
    
    if (args[1] == ":"){
        channel->setTopic("");
        channel->sendToAllMembers(":" + IrcServer::HostName + " " + "TOPIC"
        + " " + args[0] + " :", client);
        return ;
    }
    
    std::string tpc;
    if (args.size() > 1)
    {
        tpc = args[1];
        for (size_t i = 2; i < args.size(); i++)
            tpc += " " + args[i];
        if (tpc[0] == ':')
            tpc.erase(0, 1);
        channel->setTopic(tpc);
    }
    channel->sendToAllMembers(":" + IrcServer::HostName + " " + "TOPIC"
        + " " + args[0] + " :" + tpc, client);
}