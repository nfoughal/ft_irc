/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:35:46 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 21:25:01 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef BOT_HPP
# define BOT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <algorithm>
#include <map>

#include "BotToken.hpp"
#include "Numerics.hpp"
#include "tools.hpp"

class Bot
{
	private:
		std::string	Name;
		std::string	password;
		int			port;
		int			socketFd;
	public:
		Bot(std::string _Name, std::string _port, std::string _password);
		~Bot();

		void	Setup();
		void	EventLoop();

		void	DisplayHelp();
		void	HandleRequest(std::string &cmd);
};

void	random_song();

#endif