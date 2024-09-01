/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orakib <orakib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:14:35 by orakib            #+#    #+#             */
/*   Updated: 2023/10/11 19:35:41 by orakib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void IrcServer::USER(Client &client, std::vector<std::string> &args) {
	if (client.isLogged())
		sendTo_H(client.socketFd, ERR_ALREADYREGISTERED(client.nickname));
	else if (args.size() < 4)
		sendTo_H(client.socketFd, ERR_NEEDMOREPARAMS(client.nickname, "USER"));
	else if (args[1] == "0" && args[2] == "*") {
		client.username = args[0];
		std::string str;
		str = args[3];
		for (size_t i = 4; i < args.size(); i++)
			str += " " + args[i];
		client.realname = str;
	}
}

