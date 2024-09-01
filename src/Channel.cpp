/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:18 by orakib            #+#    #+#             */
/*   Updated: 2023/10/19 14:22:48 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, Client &owner) : _name(name), _key("") {

	_members[owner.nickname] = Member(ADMIN, owner);
	_topic = "";
	_keylocked = false;
	_inviteonly = false;
	_istopic_set = false;
	_limit = 0;
	_count = 1;
}

Channel::Channel(std::string name, Client &owner, std::string key) : _name(name), _key(key) {
	_members[owner.nickname] = Member(ADMIN, owner);
	_topic = "";
	_keylocked = true;
	_inviteonly = false;
	_istopic_set = false;
	_limit = 0;
	_count = 1;
}

Channel::~Channel() {}

void	Channel::setName(std::string name) {
	if (name == "") {
		std::cerr << "Cannot set an empty name" << std::endl;
		return ;
	}
	_name = name;
}

void	Channel::setTopic(std::string topic) {
	_topic = topic;
}

void	Channel::setKey(std::string key) {
	if (key == "") {
		std::cerr << "Cannot set an empty key" << std::endl;
		return ;
	}
	_key = key;
	_keylocked = true;
}

void	Channel::setLimit(int limit) {
	if (limit < 0) {
		std::cerr << "Cannot set limit to a negative value" << std::endl;
		return ;
	}
}

void	Channel::setKeyBool(bool state) {
	_keylocked = state;
}

void	Channel::setInviteBool(bool state) {
	_inviteonly = state;
}
void	Channel::setTopicBool(bool state) {
	_istopic_set = state;
}

const std::string	&Channel::getName() {
	return (_name);
}

const std::string	&Channel::getTopic() {
	return (_topic);
}

const std::string	&Channel::getKey() {
	return (_key);
}

int	Channel::getLimit() {
	return (_limit);
}

int	Channel::getCount() {
	return (_count);
}

bool	Channel::isKeySet() {
	return (_keylocked);
}

bool	Channel::isInviteOnlySet() {
	return (_inviteonly);
}

bool	Channel::isTopicModeSet() {
	return (_istopic_set);
}

bool	Channel::isClientInvited(const Client &user) {
	for (std::vector<std::string>::iterator iter =  this->_invited.begin(); iter != _invited.end(); iter++)
	{
		if (*iter == user.nickname)
			return (true);
	}
	return (false);
}

bool	Channel::isClientUser(const Client &user) {
	std::map<std::string, Member>::iterator	iter = _members.find(user.nickname);
	
	if (iter != _members.end())
		return (true);
	return (false);
}

bool	Channel::isClientOperator(const Client &user) {
	std::map<std::string, Member>::iterator	iter = _members.find(user.nickname);
	
	if (iter != _members.end() && iter->second.privilege == ADMIN)
		return (true);
	return (false);
}

void	Channel::addMember(Client &user) {
		_members[user.nickname] = Member(MEMBER, user);
		_count++;
}

void	Channel::removeMember(const Client &user) {
		_members.erase(user.nickname);
		_count--;
}

void	Channel::sendToAllMembers(std::string message, Client &client) {
	(void)client;
	std::map<std::string, Member>::iterator	it = _members.begin();
	while (it != _members.end()) {
		sendTo(it->second.client->socketFd, message);
		it++;
	}
}

std::string	Channel::getAllClientsName() {
	std::map<std::string, Member>::iterator it = _members.begin();
	std::string str = "";
	while (it != _members.end()) {
		if (it->second.privilege == ADMIN)
			str += "@";
		str += it->first;
		str += " ";
		it++;
	}
	return(str);
}

void	Channel::makeClientOperator(const Client &user) {
	_members[user.nickname].privilege = ADMIN;
}

void	Channel::makeClientInvited(const Client &user) {
	_invited.push_back(user.nickname);
}

void	Channel::removeOperatorRole(const Client &user) {
	_members[user.nickname].privilege = MEMBER;
}

void	Channel::removeInvite(const Client &user) {
	std::vector<std::string>::iterator it = std::find(_invited.begin(), _invited.end(), user.nickname);
	if (it != _invited.end())
		_invited.erase(it);
}

Client	*Channel::getClientByName(std::string name) {
	std::map<std::string, Member>::iterator it = _members.find(name);
	if (it != _members.end())
		return (it->second.client);
	return (NULL);
}