/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:43:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 21:39:03 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef IRC_HPP
# define IRC_HPP

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

#include "Numerics.hpp"
#include "IrcServer.hpp"
#include "tools.hpp"

#define C_BLK "\e[1;90m"
#define C_RED "\e[1;91m"
#define C_GRN "\e[1;92m"
#define C_YEL "\e[1;93m"
#define C_BLU "\e[1;94m"
#define C_MAG "\e[1;95m"
#define C_CYN "\e[1;96m"
#define C_WHT "\e[1;97m"
#define C_RESET "\e[0m"

template<typename K, typename V>
void	ChangeMapKey(std::map<K, V> &map, const K &oldKey, const K &newKey)
{
	V	value;
	typename std::map<K, V>::iterator	iter;

	iter = map.find(oldKey);
	if (iter != map.end())
	{
		value = iter->second;
		map.erase(oldKey);
		map[newKey] = value;
	}
}

#endif