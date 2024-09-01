/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:32:57 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/18 22:32:31 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage:\n"
				<< "\tPort: The port number to listen on.\n"
				<< "\tPassword: The password that clients must use to connect to the server." << std::endl;
		return EXIT_FAILURE;
	}
	std::string	token = BOT_TOKEN;
	try
	{
		Bot bot("BOT-" + token, argv[1], argv[2]);

		bot.Setup();
		bot.EventLoop();
	}
	catch(const std::exception &error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
		return 1;
	}
	return 0;
}
