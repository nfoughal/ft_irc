/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:47:23 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/20 16:18:51 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"

Bot::Bot(std::string _Name, std::string _port, std::string _password)
	: Name(_Name), socketFd(socket(AF_INET, SOCK_STREAM, 0))
{
	if (this->socketFd < 0)
		throw Error();
	if (_password.empty())
		throw Error("Invalid Password");
	if (!isValidPort(_port, this->port))
		throw Error("Invalid Port");
	this->password = _password;
}

Bot::~Bot()
{
	close(this->socketFd);
}

void	Bot::Setup()
{
	t_sockaddr_in	sockaddr;
	int 			enable = 1;

	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		throw Error();
	genSockaddr(sockaddr, this->port);
	if (connect(socketFd, (struct sockaddr *)&sockaddr, sizeof(t_sockaddr_in)))
		throw Error();
	if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0)
		throw Error();
	sendTo(socketFd, "PASS " + this->password);
	sendTo(socketFd, "NICK " + this->Name);
	sendTo(socketFd, "USER BOT 0 * BOT");
}

void	Bot::HandleRequest(std::string &cmd)
{
	if (cmd == "ft_irc team")
		std::system("open -a '/Applications/Google Chrome.app' 'https://github.com/Alien-MEGA/'");
	else if (cmd == "new version")
		std::system("open -a /Applications/Discord.app");
	else if (cmd == "random song")
		random_song();
}

void	Bot::EventLoop()
{
	std::string		Request;
	struct pollfd	pollFd;
	int 			status;

	pollFd.fd = socketFd;
	pollFd.events = POLLIN;
	while (true)
	{
		status = poll(&pollFd, 1, -1) < 0;
		if (status < 0)
			throw Error();
		if (pollFd.revents & POLLIN)
		{
			status = reciveFrom(socketFd, Request);
			if (status < 0)
				throw Error();
			else if (status == 0)
				exit(0);
			else
			{
				std::vector<std::string>	cmd;

				split(trim(Request), ' ', cmd);
				if (cmd[1] == "433")
				{
					std::cerr << "Bot already in use" << std::endl;
					exit(1);
				}
				for (size_t i = 0; i < Request.size(); i++)
					Request[i] = std::tolower(Request[i]);
				HandleRequest(Request);
			}
		}
	}
}

void	random_song()
{
	int rNb;
	std::string	song_list[] = {
			"'https://www.youtube.com/watch?v=RUmasKuqag0'",
			"'https://www.youtube.com/watch?v=7PZM--Em9G8'",
			"'https://www.youtube.com/watch?v=qZuxPKUVGiw'",
			"'https://www.youtube.com/watch?v=tyYEh7lK-s8'",
			"'https://www.youtube.com/watch?v=2_gLD1jarfU'",
			"'https://www.youtube.com/watch?v=CTFtOOh47oo'",
			"'https://www.youtube.com/watch?v=VDo2Bo10PQY&t=6s'",
			"'https://www.youtube.com/watch?v=S2ujotDMluo&t=50s'",
			"'https://www.youtube.com/watch?v=SsdBNuxcdlo&t=65s'",
		};
	srand(time(NULL));
	rNb = rand() % 9;
	std::system(("open -a '/Applications/Google Chrome.app' " + song_list[rNb]).c_str());
}
