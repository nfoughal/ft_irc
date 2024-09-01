/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:10:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 21:18:39 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	ShutDown(int i)
{
	(void)i;
	std::cout << C_RED
			"\n-------------------------------------\n"
			"-------- Server is ShutDown ---------\n"
			"-------------------------------------\n"
			<< C_RESET << std::endl;
	exit(EXIT_SUCCESS);
}

int	irc(std::string port, std::string password)
{
	try
	{
		IrcServer	ircserver(port, password);

		ircserver.Setup();
		std::cout << C_GRN << "-------------------------------------\n"
							<< "---- Server running successfully ----\n"
							<< "-------------------------------------\n" << C_RESET << std::endl;
		signal(SIGINT, ShutDown);
		ircserver.EventLoop();
	}
	catch(const std::exception &error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage:\n"
				<< "\tPort: The port number to listen on.\n"
				<< "\tPassword: The password that clients must use to connect to the server." << std::endl;
		return EXIT_FAILURE;
	}
	return irc(argv[1], argv[2]);
}
