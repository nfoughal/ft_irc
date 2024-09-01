/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:55:17 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 14:23:55 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

void	DisplayBotHelp(Client &client, std::vector<std::string> &args)
{
	(void)args;
	sendTo(client.socketFd, NOTICE_DISPLAY(client.nickname, "======= Options ======="));
	sendTo(client.socketFd, NOTICE_DISPLAY(client.nickname, "Ft_irc team:  show github page"));
	sendTo(client.socketFd, NOTICE_DISPLAY(client.nickname, "Random song:  Listen to random song"));
	sendTo(client.socketFd, NOTICE_DISPLAY(client.nickname, "New Version:  run new version of irc"));
}

void	IrcServer::BOT(Client &client, std::vector<std::string> &args)
{
	if (this->BotExist)
	{
		if (args.size() == 0)
			DisplayBotHelp(client, args);
		else
		{
			std::string buffer;
			for (size_t i = 0; i < args.size(); i++)
			{
				buffer += args[i];
				buffer += ' ';
			}
			sendTo(Bot->socketFd, buffer);
		}
	}
}
