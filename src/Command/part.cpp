/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:51:40 by nfoughal          #+#    #+#             */
/*   Updated: 2023/10/19 14:29:36 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::PART(Client &client, std::vector<std::string> &args)
{
    if(args.empty())
    {
        sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "PART"));
        return ;
    }
    std::string reason = "";
    std::vector<std::string> channels;
    
    if (args.size() > 1)
    {
        if(args.back()[0] != '#')
        {
            reason = args.back();
            args.pop_back();
            
        }
    }
    
    channels = args;
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel *channel = getChannel(args[i]);
        
        if(!channel)
            sendTo_H(client.socketFd, ERR_NOSUCHCHANNEL(client.nickname, args[i]));
        else if(!channel->isClientUser(client))
            sendTo_H(client.socketFd, ERR_NOTONCHANNEL(client.nickname, args[i]));
        else 
        {
            channel->removeMember(client);
            std::string msg = ":" + client.nickname + "!" + client.username
		        + "@" + host_name() + " " + "PART " + args[i];
            if(!reason.empty())
                msg += " :" + reason;
            channel->sendToAllMembers(msg, client);
            sendTo(client.socketFd, ":" + client.nickname + "!" + client.username
                + "@" + IrcServer::HostName + " PART " + args[i] + " :" + reason);
        }
    }
    
    
}