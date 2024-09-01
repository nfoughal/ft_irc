/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:31:20 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/20 16:26:20 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"
#include "../Bot/include/BotToken.hpp"

std::string	IrcServer::HostName = host_name();

IrcServer::IrcServer(std::string &_port, std::string &_password)
		: BotExist(false), Bot(NULL)
{
	if (_password.empty())
		throw Error("Invalid Password");
	if (!isValidPort(_port, this->port))
		throw Error("Invalid Port");
	this->password = _password;
	this->Clients.reserve(10);
	this->pollFds.reserve(10);
	this->InitCommandMap();
}

IrcServer::~IrcServer()
{
	for (std::vector<Client>::iterator iter = Clients.begin(); iter != Clients.end(); iter++)
		close(iter->socketFd);
	close(socketFd);
}

Client	*IrcServer::getClient(std::string &name)
{
	for (std::vector<Client>::iterator iter = Clients.begin();
			iter != Clients.end(); iter++)
		if (name == iter->nickname)
			return &(*iter);
	return NULL;
}

Channel	*IrcServer::getChannel(std::string &name)
{
	std::map<std::string, Channel>::iterator iter = Channels.find(name);
	if (iter != Channels.end())
		return &(iter->second);
	return NULL;
}

void	IrcServer::genSockaddr(t_sockaddr_in &servaddr, int port)
{
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);
}

void	IrcServer::Setup()
{
	t_sockaddr_in	sockaddr;
	int				enable = 1;

	this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketFd < 0)
		throw Error();
	if (setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		throw Error();
	if (fcntl(this->socketFd, F_SETFL, O_NONBLOCK) < 0)
		throw Error();
	IrcServer::genSockaddr(sockaddr, this->port);
	if (bind(this->socketFd, (const struct sockaddr *)&sockaddr, sizeof(t_sockaddr_in)) < 0)
		throw Error();
	if (listen(this->socketFd, 127) < 0)
		throw Error();
}

void	IrcServer::InitCommandMap()
{
	this->commandMap["BOT"] = &IrcServer::BOT;
	this->commandMap["JOIN"] = &IrcServer::JOIN;
	this->commandMap["MODE"] = &IrcServer::MODE;
	this->commandMap["INVITE"] = &IrcServer::INVITE;
	this->commandMap["PART"] = &IrcServer::PART;
	this->commandMap["KICK"] = &IrcServer::KICK;
	this->commandMap["TOPIC"] = &IrcServer::TOPIC;
	this->commandMap["PASS"] = &IrcServer::PASS;
	this->commandMap["USER"] = &IrcServer::USER;
	this->commandMap["NICK"] = &IrcServer::NICK;
	this->commandMap["PRIVMSG"] = &IrcServer::PRIVMSG;
	this->commandMap["PONG"] = &IrcServer::PONG;
	this->commandMap["QUIT"] = &IrcServer::QUIT;
}

void	IrcServer::readCommand(std::string &Buffer, Command &command)
{
	std::string		args_buff;
	size_t			fIndex;

	fIndex = Buffer.find_first_of(' ');
	if (fIndex == std::string::npos)
	{
		command.cmd = Buffer;
		return ;
	}
	command.cmd = Buffer.substr(0, fIndex);
	args_buff = Buffer.substr(fIndex, Buffer.size());
	split(trim(args_buff), ' ', command.args);
}

bool	IrcServer::authentication(Client &client, Command &command)
{
	if (client.password.empty())
	{
		if (command.cmd == "PASS")
			PASS(client, command.args);
		else
			sendTo(client.socketFd, NOTICE_AUTH);
	}
	else if (client.nickname.empty() || client.username.empty())
	{
		if (command.cmd == "NICK")
			NICK(client, command.args);
		else if (command.cmd == "USER")
			USER(client, command.args);
		else
			sendTo(client.socketFd, NOTICE_AUTH);
	}
	if (!client.password.empty() && !client.nickname.empty() && !client.username.empty())
	{
		std::string token = BOT_TOKEN;

		if (client.nickname == ("BOT-" + token))
		{
			BotExist = true;
			Bot = &client;
		}
		client.setLogged();
		sendTo_H(client.socketFd, RPL_WELCOME(client.nickname));
		sendTo_H(client.socketFd, RPL_HOST(client.nickname, IrcServer::HostName));
		return true;
	}
	return false;
}

void	IrcServer::handleCommands(Client &client, Command &command)
{
	std::map<std::string, func_command>::iterator	iter;
	func_command									func;

	iter = this->commandMap.find(command.cmd);
	if (iter != commandMap.end())
	{
		func = iter->second;
		(this->*func)(client, command.args);
	}
	else
		throw Error(NOTICE_CMDNOTFOUND(client.nickname, command.cmd));
}

void	IrcServer::newClient()
{
	int				newClientSocket;
	struct pollfd	new_pollFd;
	struct sockaddr	clientAddr;
	socklen_t		socklen = sizeof(clientAddr);

	newClientSocket = accept(this->socketFd, &clientAddr, &socklen);
	if (newClientSocket < 0)
		return ;
	else if (fcntl(newClientSocket, F_SETFL, O_NONBLOCK) >= 0)
	{
		Client	newClient(newClientSocket);

		this->Clients.push_back(newClient);
		new_pollFd.fd = newClientSocket;
		new_pollFd.events = POLLIN;
		new_pollFd.revents = 0;
		this->pollFds.push_back(new_pollFd);
		std::cout << C_GRN << "• Connected" << C_RESET << std::endl;
	}
	else
		close(newClientSocket);
}

void	IrcServer::Delete_Client_PollFd(size_t indexToRemove)
{
	if (indexToRemove >= 0 && indexToRemove < pollFds.size())
		pollFds.erase(pollFds.begin() + indexToRemove);
	indexToRemove--;
	std::cout << C_RED << "○ Disconnected - " << Clients[indexToRemove].nickname << C_RESET << std::endl;
	if (Clients[indexToRemove].nickname == ("BOT-" + std::string(BOT_TOKEN)))
	{
		BotExist = false;
		Bot = NULL;
	}
	if (indexToRemove >= 0 && indexToRemove < Clients.size())
	{
		std::vector<std::string> zero;
		zero.push_back("0");
		JOIN(Clients[indexToRemove], zero);
		close(Clients[indexToRemove].socketFd);
		Clients.erase(Clients.begin() + indexToRemove);
	}
}

bool	IrcServer::getRequest(std::string &RequestToHandle, std::string &buffer)
{
	size_t	index;

	RequestToHandle += buffer;
	index = RequestToHandle.find("\r\n");
	if (index == std::string::npos)
		return false;
	index += 2;
	buffer = RequestToHandle.substr(0, index);
	RequestToHandle = RequestToHandle.substr(index);
	return true;
}

void	IrcServer::handleClient(Client &client, int indexToRemove)
{
	Command		command;
	std::string	buffer;
	ssize_t		bytes_size;

	if (client.isQuit)
	{
		this->Delete_Client_PollFd(indexToRemove);
		return ;
	}
	bytes_size = reciveFrom(client.socketFd, buffer);
	if (bytes_size < 0)
		this->Delete_Client_PollFd(indexToRemove);
	else if (bytes_size == 0)
		this->Delete_Client_PollFd(indexToRemove);
	else
	{
		if (!getRequest(client.RequestToHandle, buffer))
			return ;
		try
		{
			readCommand(trim(buffer), command);
			if (!client.isLogged())
				authentication(client, command);
			else
				handleCommands(client, command);
		}
		catch(const std::exception &e)
		{
			sendTo(client.socketFd, e.what());
		}
	}
}

void	IrcServer::handleClient(Client &client)
{
	Command		command;
	std::string	buffer;

	if (!getRequest(client.RequestToHandle, buffer))
		return ;
	try
	{
		readCommand(trim(buffer), command);
		if (!client.isLogged())
			authentication(client, command);
		else
			handleCommands(client, command);
	}
	catch(const std::exception &e)
	{
		sendTo(client.socketFd, e.what());
	}
}

void	IrcServer::Monitoring()
{
	for (size_t i = 0; i < this->pollFds.size(); i++)
	{
		if (pollFds[i].revents & POLLIN
			|| (i > 0 && Clients[i-1].isQuit))
		{
			if (pollFds[i].fd == this->socketFd)
				newClient();
			else
				handleClient(this->Clients[i-1], i);
		}
		else if (i > 0 && !Clients[i-1].RequestToHandle.empty())
			handleClient(this->Clients[i-1]);
	}
}

void	IrcServer::EventLoop()
{
	int		status;

	pollFds.push_back(pollfd());
	pollFds[0].fd = this->socketFd;
	pollFds[0].events = POLLIN;
	while (true)
	{
		status = poll(&pollFds[0], pollFds.size(), 0);
		if (status < 0)
			throw Error();
		if (status > 0)
			Monitoring();
	}
}
