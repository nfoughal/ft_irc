/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communicate_tools.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:25:44 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/12 20:48:49 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::string	host_name()
{
	char buffer[253];

	memset(buffer, 0, sizeof(buffer));
	if (gethostname(buffer, sizeof(buffer)) < 0)
		throw Error("Can't get hostname");	
	return std::string(buffer);
}

ssize_t	sendTo_H(int socketFd, std::string message)
{
	message = (':' + host_name() + ' ') + message + "\r\n";
	return send(socketFd, message.c_str(), message.size(), 0);
}

ssize_t	sendTo(int socketFd, std::string message)
{
	message += "\r\n";
	return send(socketFd, message.c_str(), message.size(), 0);
}

ssize_t	reciveFrom(int socketFd, std::string &recv_msg)
{
	char	buffer[1024];
	ssize_t	readBytes;

	memset(buffer, 0, sizeof(buffer));
	readBytes = recv(socketFd, buffer, sizeof(buffer), 0);
	if (readBytes > 0)
		recv_msg = buffer;
	return (readBytes);
}

void	genSockaddr(t_sockaddr_in &sockaddr, int port)
{
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	if (inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr) <= 0)
		throw Error();
}
