/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:54:55 by nfoughal          #+#    #+#             */
/*   Updated: 2023/10/10 20:04:45 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::PASS(Client &client, std::vector<std::string> &args)
{
    if(!client.isLogged())
    {
        if (args.size() != 1)
            sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "PASS"));
        else if (args[0] != password)
            sendTo_H(client.socketFd, ERR_PASSWDMISMATCH(client.nickname));
        else
            client.password = password;
    }
    else
        sendTo_H(client.socketFd, ERR_ALREADYREGISTERED(client.nickname));
}