/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orakib <orakib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:42:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/08 22:08:28 by orakib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef NUMERICS_H
# define NUMERICS_H

#define RPL_WELCOME(nickname) "001 " + nickname + " :Welcome to the IRC server"
#define RPL_HOST(nickname, host) "002 " + nickname + " :Your host is " + host
#define RPL_TOPIC(nickname , ch, topic) "332 " + nickname + " " + ch + " :" + topic
#define RPL_NAMREPLY(nickname, ch, members) "353 " + nickname + " = " + ch + " :" + members
#define RPL_ENDOFNAMES(nickname, ch) "366 " + nickname + " " + ch + " :End of /NAMES list"
#define ERR_NEEDMOREPARAMS(nickname, cmd) "461 " + nickname + " " + cmd + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(nickname, ch) "403 " + nickname + " " + ch + " :No such channel"
#define ERR_CHANNELISFULL(nickname, ch) "471 " + nickname + " " + ch + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(nickname, ch) "473 " + nickname + " " + ch + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(nickname, ch) "475 " + nickname + " " + ch + " :Cannot join channel (+k)"

#endif