/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orakib <orakib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:18:53 by orakib            #+#    #+#             */
/*   Updated: 2023/10/11 20:44:04 by orakib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <string>
#include <map>
#include "Client.hpp"
#include "tools.hpp"

enum PRIVILEGE
{
	MEMBER,
	ADMIN
};

struct Member
{
	PRIVILEGE	privilege;
	Client		*client;

	Member() : privilege(MEMBER), client(NULL) {}
	Member(PRIVILEGE _privilege, Client &_client)
		: privilege(_privilege), client(&_client) {}
};

class	Channel {
	private:
		std::string						_name;
		std::string						_topic;
		std::string						_key;
		bool							_keylocked;
		bool							_inviteonly;
		bool							_istopic_set;
		int								_limit;
		int								_count;
	public:
		std::map<std::string, Member>	_members;
		std::vector<std::string>		_invited;
		Channel() {}
		Channel(std::string name, Client &owner);
		Channel(std::string name, Client &owner, std::string key);
		void	setName(std::string name);
		void	setTopic(std::string topic);
		void	setKey(std::string key);
		void	setLimit(int limit);
		void	setKeyBool(bool state);
		void	setInviteBool(bool state);
		void	setTopicBool(bool state);
		
		const std::string	&getName();
		const std::string	&getTopic();
		const std::string	&getKey();
		int	getLimit();
		int	getCount();
		Client	*getClientByName(std::string name);
		bool	isKeySet();
		bool	isInviteOnlySet();
		bool	isTopicModeSet();
		bool	isClientInvited(const Client &user);
		bool	isClientUser(const Client &user);
		bool	isClientOperator(const Client &user);
		void	makeClientOperator(const Client &user);
		void	makeClientInvited(const Client &user);
		void	removeOperatorRole(const Client &user);
		void	removeInvite(const Client &user);
		void	addMember(Client &user);
		void	removeMember(const Client &user);
		void	sendToAllMembers(std::string message, Client &client);
		std::string	getAllClientsName();
		~Channel();
};

#endif