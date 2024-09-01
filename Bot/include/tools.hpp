/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:37:20 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/12 15:38:29 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef TOOLS_HPP
# define TOOLS_HPP

#include "Bot.hpp"

typedef struct sockaddr_in t_sockaddr_in;

class Error : public std::runtime_error
{
	public:
		Error() : std::runtime_error(strerror(errno)) {errno = 0;}
		Error(std::string _error) : std::runtime_error(_error) {}
};

bool		isNb(std::string nb);
bool		isValidPort(std::string port_s, int &port);

std::string	&trim(std::string &str);
void		split(std::string &Buffer, char c, std::vector<std::string> &vec);

std::string	host_name();
ssize_t		sendTo(int socketFd, std::string message);
ssize_t		sendTo_H(int socketFd, std::string message);
ssize_t		reciveFrom(int socketFd, std::string &recv_msg);

void	genSockaddr(t_sockaddr_in &servaddr, int port);

#endif
