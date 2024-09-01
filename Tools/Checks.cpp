/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checks.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:18 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/29 21:52:14 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

bool	isNb(std::string nb)
{
	for (size_t i = 0; i < nb.length(); i++)
		if (!isdigit(nb[i]))
			return false;
	return true;
}

bool	isValidPort(std::string port_s, int &port)
{
	if (port_s.empty() || !isNb(port_s))
		return false;
	port = atoi(port_s.c_str());
	if (!(port >= 0 && port <= 65535))
		return false;
	return true;
}
