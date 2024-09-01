/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 03:41:47 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 17:04:35 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
	: socketFd(-1), isQuit(false), logged(false)
{
}

Client::Client(int &_socketFd)
	: socketFd(_socketFd), isQuit(false), logged(false)
{
}

bool	Client::isLogged() const
{
	return this->logged;
}

void	Client::setLogged()
{
	this->logged = true;
}
