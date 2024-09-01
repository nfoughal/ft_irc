/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringTools.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:47:14 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/19 21:44:04 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

std::string	&trim(std::string &str)
{
	size_t	fIndex = str.find_first_not_of(" \n\r\t\f\v");
	size_t	lIndex = str.find_last_not_of(" \n\r\t\f\v");

	if (fIndex == std::string::npos)
		fIndex = str.size();
	if (lIndex == std::string::npos)
		lIndex = 0;
	str = str.substr(fIndex, lIndex - fIndex + 1);
	return str;
}

void	split(std::string &Buffer, char c, std::vector<std::string> &vec)
{
	std::istringstream	args_buff(Buffer);
	std::string			readline;

	while (std::getline(args_buff, readline, c))
	{
		if (!readline.empty())
			vec.push_back(readline);
	}
}
