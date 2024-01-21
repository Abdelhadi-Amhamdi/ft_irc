/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:20:34 by kben-ham          #+#    #+#             */
/*   Updated: 2024/01/21 11:56:35 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


TOPIC :(Change the channel topic in a mode +t channel)
-------

TOPIC #channel :New topic text goes here
TOPIC #channel :
TOPIC #channel // getter 
:nickname TOPIC #channel :New topic
:nickname!hostname TOPIC #channel :New topic
//exemple(:WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic)

If a channel does not have the +t mode set, it means that any user,
 including those without operator status
if (!operator)//operator means(@user) == "+o" as a mode
	you are not a channel operator.


A message is typically broadcast to all users in the channel:
[User] sets topic: New topic text goes here

______________________________________________________________

QUIT :(quit the server)
------

QUIT
QUIT :quit message 
:nickname QUIT :New QUIT
:nickname!hostname QUIT :New QUIT
//exemple(syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch)
:alice!~a@localhost JOIN #test

the IRC server broadcasts a quit message to all the channels the user is currently in.

-!- nickname has quit (quit message)

____________________________________________________________

KICK :(to remove a user from a channel)is used by channel operators 
------

if (!operator)//operator means(@user) == "+t" as a mode
	you are not a channel operator.

KICK #channel nickname :reason
KICK #channel nickname
:nickname!hostname KICK #channel nickname

A message is typically broadcast to all users in the channel:
-!- Operator1 kicked nickname from #channel(reason)

____________________________________________________________

JOIN : (join a specific channel)
------

JOIN #channel key
JOIN #channel (public channel) !!! if there isn't a channe you should create one and you became the admin
JOIN #channel,#channel,#channel,#channel key(optional) (this key is jut for the first channel) 
JOIN 0 (Leave all currently joined channels)
:nickname!hostname JOIN #channel

A message is typically broadcast to all users in the channel:
-!- nickname joined #channel

____________________________________________________________

INVITE : (to invite a user to join a specific channel)
--------


!!!!!if the channel exists, only members of the channel
are allowed to invite other users.  When the channel has invite-only
flag set, only channel operators may issue INVITE command.


INVITE nickname #channel
:nickname!hostname INVITE nickname #channel
   
The user who receives the invitation can choose whether to accept or decline it.

the invited user typically receives a notice or message indicating the invitation
-!- You have been invited by <inviter> to join #channel

Invite list (refers to a list of users who are allowed to join an invite-only channel without explicitly requiring an invitation each time.)

____________________________________________________________

NOTICE : (is used similarly to PRIVMSG)
--------
The difference between NOTICE and PRIVMSG
	is that automatic replies MUST NEVER be
	sent in response to a NOTICE message

NOTICE nickname :message
NOTICE #channel :message

-!- nickname :message.

____________________________________________________________

PART : (to leave a channel)
--------
PART #channel,#channel
PART #channel
PART #channel :reason
:nickname!hostname PART #channel :reason

!!!!!Servers SHOULD NOT send multiple channels in this message to clients,
and SHOULD distribute these multiple-channel PART messages
as a series of messages with a single channel name on each.

all clients in the channel also receive a
PART message(include the one who has part the channel)
Once all users in a channel have left that channel, the channel must be destroyed.

____________________________________________________________

PRIVMSG : (to send private messages)
--------

PRIVMSG nickname :message
PRIVMSG #channel :message
:nickname!hostname PRIVMSG #channel :message

New private message from nickname :message


____________________________________________________________

MODE : (to set modes to channel)
-------

MODE #channel key parameters(example of parameters is pass)


****i****(Set/remove Invite-only channel)



****o****( Give/take channel operator privilege)(just operators can do this)

MODE #channel +o nickname 





Channel lifetime

   In regard to the lifetime of a channel, there are typically two
   groups of channels: standard channels which prefix is either '&', '#'
   or '+', and "safe channels" which prefix is '!'.


(momkin channel maykonch 3ndha ta chi operator)

Since channels starting with the character '+' as prefix do not
   support channel modes, no member can therefore have the status of
   channel operator.













#include "Server.hpp"

std::vector<std::string> tokens;

void splt(const std::string& input, char delimiter, std::vector<std::string>& result)
{
	std::string token;
	
	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] != delimiter)
		{
			token += input[i];
		} 
		else
		{
			result.push_back(token);
			token.clear();
		}
	}
	// Add the last token (if any)
	if (!token.empty())
		result.push_back(token);
}


