/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numerics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:42:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/10/17 13:41:17 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef NUMERICS_H
# define NUMERICS_H

#define RPL_WELCOME(nickname) "001 " + nickname + " :Welcome to the IRC server"
#define RPL_HOST(nickname, host) "002 " + nickname + " :Your host is " + host
#define NOTICE_CMDNOTFOUND(nickname, command) "NOTICE " + nickname + " :Command not found: " + command
#define NOTICE_AUTH "NOTICE AUTH :Authentication required"
#define NOTICE_DISPLAY(nickname, message) "NOTICE " + nickname + " :" + message
#define RPL_TOPIC(nickname , ch, topic) "332 " + nickname + " " + ch + " :" + topic
#define RPL_NAMREPLY(nickname, ch, members) "353 " + nickname + " = " + ch + " :" + members
#define RPL_ENDOFNAMES(nickname, ch) "366 " + nickname + " " + ch + " :End of /NAMES list"
#define ERR_NEEDMOREPARAMS(nickname, cmd) "461 " + nickname + " " + cmd + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(nickname, ch) "403 " + nickname + " " + ch + " :No such channel"
#define ERR_CHANNELISFULL(nickname, ch) "471 " + nickname + " " + ch + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(nickname, ch) "473 " + nickname + " " + ch + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(nickname, ch) "475 " + nickname + " " + ch + " :Cannot join channel (+k)"
#define RPL_CHANNELMODEIS(nickname, ch, mstr) "324 " + nickname + " " + ch + " " + mstr
#define ERR_CHANOPRIVSNEEDED(nickname, ch) "482 " + nickname + " " + ch + " :You're not channel operator"
#define ERR_INVALIDKEY(nickname, ch) "525 " + nickname + " " + ch + " :Key is not well-formed"
#define ERR_INVALIDMODEPARAM(nickname, ch, mode, param, desc) "696 " + nickname + " " + ch + mode + param + " :" + desc
#define ERR_NOTONCHANNEL(nickname, ch) "442 " + nickname + " " + ch + " :You're not on that channel"
#define ERR_USERONCHANNEL(nickname, target, ch) "443 "  + nickname + " " + target + " " + ch + " :is already on channel"
#define RPL_INVITING(nickname, target, ch) "341 " + nickname + " " + target + " " + ch
#define ERR_USERNOTINCHANNEL(nickname, target, ch) "441 " + nickname + " " + target + " " + ch + " :They aren't on that channel"
#define RPL_NOTOPIC(nickname , ch) "331 " + nickname + " " + ch + " :No topic is set"
#define ERR_PASSWDMISMATCH(nickname) "464 " + nickname + " :Password incorrect"
#define ERR_ALREADYREGISTERED(nickname) "462 " + nickname + " :You may not reregister"
#define ERR_NORECIPIENT(nickname, cmd) "411 " + nickname + " :No recipient given (" + cmd + ")"
#define ERR_NOTEXTTOSEND(nickname) "412 " + nickname + " :No text to send"
#define ERR_NOSUCHNICK(nickname, target) "401 " + nickname + " " + target + " :No such nick/channel"
#define ERR_CANNOTSENDTOCHAN(nickname, ch) "404 " + nickname + " " + ch + " :Cannot send to channel"
#define ERR_ALREADYREGISTERED(nickname) "462 " + nickname + " :You may not reregister"
#define ERR_NONICKNAMEGIVEN(nickname) "431 " + nickname + " :No nickname given"
#define ERR_NICKNAMEINUSE(nickname, nick) "433 " + nickname + " " + nick + " :Nickname is already in use"
#define ERR_ERRONEUSNICKNAME(nickname, nick) "432 " + nickname + " " + nick + " :Erroneus nickname"

#endif