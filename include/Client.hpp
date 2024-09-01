/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 03:41:23 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 15:50:10 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef CLIENT_H
# define CLIENT_H

#include <string>
#include <iostream>

class Client
{
	public:
		int			socketFd;
		std::string	password;
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string	buffer;
		std::string	RequestToHandle;
		bool		isQuit;
	private:
		bool		logged;
	public:
		Client();
		Client(int &_socketFd);

		bool	isLogged() const;
		void	setLogged();
};

#endif