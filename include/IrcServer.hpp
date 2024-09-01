/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:30:46 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/20 16:06:39 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "irc.hpp"
#include "Channel.hpp"
#include "Client.hpp"

typedef struct sockaddr_in t_sockaddr_in;

class IrcServer;
typedef void (IrcServer::*func_command)(Client &, std::vector<std::string> &);
struct	Command
{
	std::string					cmd;
	std::vector<std::string>	args;
};

class Channel;

class IrcServer
{
    public:
		static std::string	HostName;
    private:
		std::vector<Client>					Clients;
		std::map<std::string, Channel>		Channels;
		std::vector<struct pollfd>			pollFds;
		std::map<std::string, func_command>	commandMap;
		std::string							password;
		int									port;
		int									socketFd;
		bool								BotExist;
		Client								*Bot;
    public:
		IrcServer(std::string &_port, std::string &_password);
        ~IrcServer();

		Client	*getClient(std::string &name);
		Channel	*getChannel(std::string &name);

		void		Setup();
		void		EventLoop();
		void		Monitoring();
		static void genSockaddr(t_sockaddr_in &servaddr, int port);

		void	newClient();
		bool	authentication(Client &Client, Command &command);
		void	handleClient(Client &client, int indexToRemove);
		void	handleClient(Client &client);
		void	Delete_Client_PollFd(size_t indexToRemove);

		void	InitCommandMap();
		bool	getRequest(std::string &RequestToHandle, std::string &buffer);
		void	readCommand(std::string &Buffer, Command &command);
		void	handleCommands(Client &client, Command &command);

    public:
		void	QUIT(Client &client, std::vector<std::string> &args);
		void	BOT(Client &client, std::vector<std::string> &args);
		void	JOIN(Client &client, std::vector<std::string> &args);
		void	MODE(Client &client, std::vector<std::string> &args);
		void	INVITE(Client &client, std::vector<std::string> &args);
		void	PART(Client &client, std::vector<std::string> &args);
		void	KICK(Client &client, std::vector<std::string> &args);
		void	TOPIC(Client &client, std::vector<std::string> &args);
		void	PASS(Client &client, std::vector<std::string> &args);
		void	USER(Client &client, std::vector<std::string> &args);
		void	NICK(Client &client, std::vector<std::string> &args);
		void	PRIVMSG(Client &client, std::vector<std::string> &args);
		void	PONG(Client &client, std::vector<std::string> &args) {(void)client;(void)args;}
};

#endif