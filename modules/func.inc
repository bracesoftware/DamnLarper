// Module written by DEntisT, © & ® BRACE™.

forward OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success);


public DCC_OnMessageCreate(DCC_Message: message) 
{
	new
		DCC_User: author,
		bool: is_bot = false,
		content[256 + MAX_CMD_NAME + 2],
		command[MAX_CMD_NAME],
		params[256],
		discord[MAX_CMD_LEN] = "discord_"
	;

	new msg[1024];
	DCC_GetMessageContent(message, msg);
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	DCC_GetMessageAuthor(message, author);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	/*#if SLASH_COMMANDS == 1
	CreateCommands(guild);
	#endif*/

	DCC_IsUserBot(author, is_bot);

	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);

	new mention[128];

	format(mention, sizeof mention, ""d_reply" <@%s>", id);

	SetMention(id, mention);

	if(is_bot == false && author != bot && GetGuildVerification(guild) == 1 && GetUserVerification(guild, id) == 0)
	{
		if(channel != DCC_FindChannelById(GetGuildVerificationChannel(guild)))
		{
			if(DCC_FindUserById(id) != DCC_INVALID_USER)
			{
				DCC_DeleteMessage(message);
				@discord() SendInfo(DCC_FindChannelById(GetGuildVerificationChannel(guild)), "<@%s>\n\n"d_reply" **UNVERIFIED!** • You aren't verified in this guild so your message was deleted! You can use commands and chat **only** in this channel. You can use `"BOT_PREFIX"newverifycode` to generate a new verification code for this guild in case you lost yours or didn't even get it.", id);
			}
			return 1;
		}
	}


	if(GetReportQuestion(id) != 0 && (channel == DCC_FindChannelById(GetUserReportChannel(id))))
	{
		if(GetReportQuestion(id) == 1)
		{
			SetReportQuestion(id, "2");
			SetReportAnswer(id, 1, msg);

			AddReaction(message, DCC_CreateEmoji(d_yes));

			@discord() SendMsg(channel, "**__REPORT PANEL__**\n**Question 2** • <@%s>\n\n"d_arrow"*`Please describe your reported subject in short words!`*\n\n", id);
			@discord() SendInfo(channel, "Please reply to the question above with the proper answer.");
			return 1;
		}
		if(GetReportQuestion(id) == 2)
		{
			SetReportQuestion(id, "3");
			SetReportAnswer(id, 2, msg);

			AddReaction(message, DCC_CreateEmoji(d_yes));

			@discord() SendMsg(channel, "**__REPORT PANEL__**\n**Question 3** • <@%s>\n\n"d_arrow"*`Please write a description of a problem in details!`*\n\n", id);
			@discord() SendInfo(channel, "Please reply to the question above with the proper answer.");
			return 1;
		}
		if(GetReportQuestion(id) == 3)
		{
			SetReportQuestion(id, "0");
			SetReportAnswer(id, 3, msg);

			AddReaction(message, DCC_CreateEmoji(d_yes));

			new reportstring[1024];
	
			format(reportstring, sizeof reportstring, "**<@%s>**\n\n\
				"d_reply" • Your report was successfully sent to the support server, we'll start to investigate as soon as possible.\n\
				Thank you for helping us and our community to provide our users and you a better experience! "d_heart"\n\n\
				**Support Server**\n\
				"d_reply" If you wish, you can join our support server below.\n\n\
				["BOT_NAME" • Support](https://discord.gg/SEvCgZy27a)", id);

			new DCC_Embed:msg2 = DCC_CreateEmbed(
				"**__Report Response__**", reportstring, 
				"",
				"", 
				col_embed, datetimelog, 
				"",
				"",
				"");

			//@discord() SendMsg(channel, msg);

			DCC_SendChannelEmbedMessage(channel, msg2, ""delimiterlol" **SUCCESS** • Read the text below for more information!");
			@discord() SendMsg(reports, "__**Report Received**__\n\n"d_reply" • Report issued by: <@%s>\n\n**The Form**\n"d_arrow"Reported: `%s`\n"d_arrow"Subject: `%s`\n"d_arrow"Problem description: `%s`\n", id, GetReportAnswer(id, 1), GetReportAnswer(id, 2), GetReportAnswer(id, 3));
			return 1;
		}
	}
	

	new msgid[DCC_ID_SIZE], channelid[DCC_ID_SIZE];
	DCC_GetMessageId(message, msgid);
	DCC_GetChannelId(channel, channelid);

	if(author != bot)
	{
		if(settings[cnt] == 1)
		{	
			if(channel == DCC_FindChannelById(GetGuildCountChannel(guild)))
			{
				new count2;
				if(sscanf(msg, "i", count2))
				{
					@discord() SendMsg(channel, ""d_reply" **WARNING** • This is a counting channel. Don't chat here!");
					return 1;
				}
				if(count2 != GetGuildCountGame(guild)+1)
				{
					@discord() SendMsg(channel, "**__COUNT RUINED!__**\n"d_reply" • Unfortunately, <@%s> ruined the count at `%i`!\n\n"delimiterlol" • We'll go again! The next number is `1`.", id, GetGuildCountGame(guild)+1);
					SaveGuildCountGame(guild, 0);
					return 1;
				}
				if(count2 == GetGuildCountGame(guild)+1)
				{
					SaveGuildCountGame(guild, GetGuildCountGame(guild)+1);
					AddReaction(message, DCC_CreateEmoji("✅"));
					return 1;
				}
			}
		}
		new msglen = strlen(msg);
		for(new i; i < msglen; i++)
		{
			if(msg[i] == '\10') strdel(msg, i, i+1);
		}
		for(new i; i < msglen; i++)
		{
			if(tolower(msg[i]) == 'd' && 
				tolower(msg[i+1]) == 'a' && 
				tolower(msg[i+2]) == 'm' && 
				tolower(msg[i+3]) == 'n' &&
				tolower(msg[i+4]) == ' ' &&
				tolower(msg[i+5]) == 'l' &&
				tolower(msg[i+6]) == 'a' &&
				tolower(msg[i+7]) == 'r' &&
				tolower(msg[i+8]) == 'p' &&
				tolower(msg[i+9]) == 'e' &&
				tolower(msg[i+10]) == 'r' 
				)
			{
				DCC_SendChannelMessage(channel, DiplomyReplies[random(sizeof DiplomyReplies)]);
			}
		}
	}

	if(settings[ac] == 1 && GetGuildSecurity(guild) == 1)
	{
		if(author != bot)
		{
			new msglen = strlen(msg);
			for(new i; i < msglen; i++)
			{
				if(msg[i] == '\10') strdel(msg, i, i+1);
			}
			for(new i; i < msglen; i++)
			{
				if(msg[i] == 'n' && 
					msg[i+1] == 'i' && 
					msg[i+2] == 'g' && 
					msg[i+3] == 'g')
				{
					DCC_DeleteMessage(message);
					@discord() SendMsg(channel, ""d_protectiveshield" **SERVER SECURITY** • <@%s>'s message has been removed because it contains inappropriate words, slurs or threatens another user or a community.", id);
					return 1;
				}
				if(msg[i] == 'c' && 
					msg[i+1] == 'u' && 
					msg[i+2] == 'n' && 
					msg[i+3] == 't')
				{
					DCC_DeleteMessage(message);
					@discord() SendMsg(channel, ""d_protectiveshield" **SERVER SECURITY** • <@%s>'s message has been removed because it contains inappropriate words, slurs or threatens another user or a community.", id);
					return 1;
				}
				if(msg[i] == 'f' && 
					msg[i+1] == 'a' && 
					msg[i+2] == 'g' && 
					msg[i+3] == 'g')
				{
					DCC_DeleteMessage(message);
					@discord() SendMsg(channel, ""d_protectiveshield" **SERVER SECURITY** • <@%s>'s message has been removed because it contains inappropriate words, slurs or threatens another user or a community.", id);
					return 1;
				}
			}
		}
	}

	// Other features

	SaveMessageCount(id, GetMessageCount(id) + 1);

	if(is_bot == false && (GetMessageCount(id) / 100 + 1) > GetData(id, "Level"))
	{
		@discord() SendMsg(DCC_FindChannelById(GetGuildLevelChannel(guild)), ""d_reply" **LEVEL-UP** • Congratulations <@%s>, you've advanced to level `%i`!", id, GetMessageCount(id) / 100 + 1);
	}

	SetData(id, "Level", GetMessageCount(id) / 100 + 1);

	if(!strfind(msg, "<@!"BOT_USER_ID">") || !strfind(msg, "<@"BOT_USER_ID">")) //if bot is tagged
	{
		new response [364];
		format(response, sizeof response, 
			""botpfp" • Hi, <@%s> - please use **`"BOT_PREFIX"help`** to interact with **"BOT_NAME"**.", id);

		new DCC_Embed:msg2 = DCC_CreateEmbed(
			"**__"BOT_NAME"__**", response, "","", col_embed, datetimelog, 
			"","","");

		//@discord() SendMsg(channel, msg);

		DCC_SendChannelEmbedMessage(channel, msg2, ""botpfp" • My prefix is `damn`.");
		return 1;
	}


	if(author != bot)
	{
		for(new i; i < strlen(msg); i++)
		{
			if(msg[i] == '<' &&
				msg[i+1] == '@'
				||
				msg[i] == '<' &&
				msg[i+1] == '@' &&
				msg[i+2] == '!' )
			{
				new closepoint;
				for(new x; x < strlen(msg); x++)
				{
					if(msg[x] == '>')
					{
						closepoint = x + 1;
					}
				}
				new user[DCC_ID_SIZE+10];
				strmid(user, msg, i, closepoint);
				for(new ii; ii < strlen(user); ii++)
				{
					if(user[ii] == '<') strdel(user, ii, ii+1);
					if(user[ii] == '@') strdel(user, ii, ii+1);
					if(user[ii] == '>') strdel(user, ii, ii+1);
					if(user[ii] == '!') strdel(user, ii, ii+1);
					if(user[ii] == '\32') strdel(user, ii, ii+1);
				}

				if(IsAFK(user))
				{
					@discord() SendMsg(channel, ""d_reply" • This user (<@%s>) is now AFK. Reason: `%s`", user, GetAFK(user));
				}
				break;
			}
		}
	}

	if(IsAFK(id))
	{
		DeleteAFK(id);

		@discord() SendMsg(channel, ""botpfp" **Welcome back,** <@%s> - I've removed your AFK status!", id);
	}
	

	if (!DCC_GetMessageAuthor(message, author) || author == DCC_INVALID_USER) { // The message author is invalid
		#if defined discdcmd_DCC_OnMessageCreate
			return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
		#else
			return 0;
		#endif
	}

	DCC_GetMessageContent(message, content);

	if((content[0] == 'd' || content[0] == 'D') && 
		(content[1] == 'a' || content[1] == 'A') && 
		(content[2] == 'm' || content[2] == 'M') &&
		(content[3] == 'n' || content[3] == 'N') && 
		content[4] == ' ' )
	{
		content[0] = CMD_PREFIX;
		strdel(content, 1, 2);
		strdel(content, 1, 2);
		strdel(content, 1, 2);
		strdel(content, 1, 2);
	}

	if(content[0] == '!') // custom command
	{
		SettingsCheck(ccmd);
		strdel(content, 0, 1);
		for(new i; i < strlen(content); i++)
		{
			if(content[i] == ' ')
			{
				strdel(content, i, strlen(content));
			}
		}
		ProcessCommand(content, channel);
		return 1;
	}

	CallLocalFunction("NRP_MSG_COMPONENT", "i", _:message);

	if (is_bot || content[0] != CMD_PREFIX) //|| content[0] != 'p' && content[1] != 'o' && content[2] != 'd'
	{ // Skip if the message author is a bot or is not a command
		#if defined discdcmd_DCC_OnMessageCreate
			return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
		#else
			return 0;
		#endif
	}


	if (sscanf(content, "s["#MAX_CMD_NAME"]S()[256]", command, params)) {
		#if defined discdcmd_DCC_OnMessageCreate
			return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
		#else
			return 0;
		#endif
	}

	for (new i = strlen(command) - 1; i != 0; i --) {
		command[i] |= 0x20; // lower case using bitwise OR operator
	}

	strcat(discord, command[1]);

	if (isnull(params)) {
		params = "\1";
	}

	//Hooks

	DCC_TriggerBotTypingIndicator(channel);

	new cmdcontinue = CallLocalFunction("OnDiscordCommandReceived", "iis", _: message, _: author, params);

	if(cmdcontinue != 1)
	{
		return 0;
	}

	#if defined OnDiscordCommandPerformed
		OnDiscordCommandPerformed(message, author, bool: CallLocalFunction(discord, "iis", _: message, _: author, params, _:channel));
	#else
		CallLocalFunction(discord, "iis", _: message, _: author, params, _:channel);
	#endif
	
	#if defined discdcmd_DCC_OnMessageCreate
		return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
	#else
		return 1;
	#endif
}

forward OnDiscordCommandReceived(DCC_Message:message, DCC_User:author, params[]);
public OnDiscordCommandReceived(DCC_Message:message, DCC_User:author, params[])
{
	new id[DCC_ID_SIZE], DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_GetUserId(author, id);

	new DCC_Guild:guild;
	new DCC_ChannelType:channeltype;

	DCC_GetChannelType(channel, channeltype);

	DCC_GetChannelGuild(channel, guild);

	if(channeltype == DM || channeltype == GROUP_DM)
	{
		@discord() SendMsg(channel, "> "d_reply" **WRONG TIME, WRONG PLACE!** • You can't use me here, mate!");
		return 0;
	}

	if(IsBlacklisted(id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You're blacklisted from using bot commands.");
		return 0;
	}

	return 1;
}


public DCC_OnGuildMemberAdd(DCC_Guild:guild, DCC_User:user)
{
	/*if(guild == RiseOfNations)
	{
		new id[DCC_ID_SIZE];

		DCC_GetUserId(user, id);

		@discord() SendMsg(lounge, ""botpfp" • Hello, <@%s>! First of all, we would like to welcome you and thank you for joining our community **"SERVER_RISE_OF_NATIONS"**. To get started with roleplay, read <#965523854988570644> and <#965523792405352458>. In case you are interested in something, look at <#965523810524753930> - you may find what you are looking for. If you are interested in roles, take a look at <#968181829473554452>! When everything is ready, without hesitation apply for the desired entity (state, union, co-op, organization or sports club) in <#965490451333402644> using a specific template in <#965490312246095872>. If you need any other help, feel free to contact us via the ticket in <#965529291599269898>. That would be it! Thanks again - see you later!", id);
		
		DCC_AddGuildMemberRole(guild, user, standardrole1);
		DCC_AddGuildMemberRole(guild, user, standardrole2);
		DCC_AddGuildMemberRole(guild, user, standardrole3);
		DCC_AddGuildMemberRole(guild, user, standardrole4);
		DCC_AddGuildMemberRole(guild, user, unverified);
	}*/
	new id[DCC_ID_SIZE];

	DCC_GetUserId(user, id);

	if(!strcmp(id, BOT_USER_ID)) 
	{
		SetServers(GetServers() + 1);
	}

	@discord() SendMsg(DCC_FindChannelById(GetGuildAirportChannel(guild)), ""d_reply"**JOIN** • <@%s> joined the guild!", id);

	if(!IsUserABot(id))
	{
		if(GetGuildVerification(guild) == 1)
		{
			new code[10];

			format(code, sizeof code, "%i", random(100000));

			SetVerifyCode(guild, id, code);

			@discord() SendMsg(DCC_FindChannelById(GetGuildVerificationChannel(guild)), ""botpfp" **WELCOME TO THE GUILD** • Hello <@%s>! Thanks for choosing this guild to join! But in order to send messages here, please use a `"BOT_PREFIX"verify` command.\n\nYour verification code **for this guild** is: `%s`", id, code);
		}
	}
	if(user == bot)
	{
		new channelcount;
		DCC_GetGuildChannelCount(guild, channelcount);
		for (new i; i != channelcount; i++)
		{
		    new DCC_Channel:channel;
		    if (!DCC_GetGuildChannel(guild, i, channel))
		    {
		        // error
		        continue;
		    }

		    new DCC_ChannelType:type;

		    DCC_GetChannelType(channel, type);

		    if(type == GUILD_TEXT)
		    {
		    	@discord() SendMsg(channel, ""botpfp" **BOT INVITED** • Hello to everyone! I am **"BOT_NAME"** and I am glad to be in this __damn__ cool server. To view all of my commands, use `"BOT_PREFIX"help`. If you want to setup me, you can use `"BOT_PREFIX"serverconfig`");
		    	break;
		    }
		}
	}
	return 1;
}

public DCC_OnGuildMemberRemove(DCC_Guild:guild, DCC_User:user)
{
	new id[DCC_ID_SIZE];

	DCC_GetUserId(user, id);

	@discord() SendMsg(DCC_FindChannelById(GetGuildAirportChannel(guild)), ""d_reply"**LEAVE** • <@%s> left the guild!", id);

	if(!strcmp(id, BOT_USER_ID)) 
	{
		SetServers(GetServers() - 1);
	}
	return 1;
}



forward ActivityChange();
public ActivityChange()
{
	format(activity, sizeof activity, "/damn • damn help");
	DCC_SetBotActivity(activity);
	return 1;
}


public OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success) 
{
	new DCC_Channel: channel;

	DCC_GetMessageChannel(message, channel);
	
	new DCC_Guild:guild;

	DCC_GetChannelGuild(channel, guild);

	new betasent = 0;

	if (!success) 
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • I don't know what that command is, try using `"BOT_PREFIX"help` to see a list of available commands.");
		return 1;
	}
	else if(success)
	{
		if(settings[log] == 0) return 1;
		new content[512], id[DCC_ID_SIZE];
		DCC_GetMessageContent(message, content);
		DCC_GetUserId(author, id);
		new logmsg[512];
		if(IsUserMod(author) == 1)
		{
			format(logmsg, sizeof logmsg, 
				"**__Command used__**\n\n"delimiterlol" User: <@%s>\nCommand text: `%s`\n"botpfp" User is a moderator.",
			id, content);
		}
		else
		{
			format(logmsg, sizeof logmsg, "**__Command used__**\n\n"delimiterlol" User: <@%s>\nCommand text: `%s`",
			id, content);
		}
		DCC_SendChannelEmbedMessage(DCC_FindChannelById(GetGuildLogChannel(guild)), DCC_CreateEmbed(
		"**__"BOT_NAME" Logs__**", 
		logmsg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), ""delimiterlol" **INFO** • Mention me for more information!");

		CallLocalFunction("TurnInteractionOff", "i", _:author);
	}
	if(BOT_BETA_PHASE == 1)
	{
		if(random(10) == 5)
		{
			@discord() SendInfo(channel, ""d_beta" "BOT_NAME" achieved the **Beta Test** phase of development, help us in the development process by reporting all the bugs and issues using the `"BOT_PREFIX"report` command!");
			betasent = 1;
		}
	}
	if(random(100) < 10 && betasent == 0 && GetUserConfigTips(author) == 1)
	{
		@discord() SendInfo(channel, "**TIP** "d_star" %s", BotTips[random(sizeof BotTips)]);
	}
	return 1;
}

public OnGameModeInit()
{
	d_sqlconnect();
	printf("OnGameModeInit called");
	new y,m,d,h,n,s;
	getdate(y,m,d);
	gettime(h,n,s);
	format(datetimelog, sizeof datetimelog, 
		""BOT_NAME" • %i/%i/%i • %i:%i:%i | v%s.%s-R%s",
		d,m,y,h,n,s,
		DAMN_LARPER_MAJOR,
		DAMN_LARPER_MINOR,
		DAMN_LARPER_RELEASE);

	LoadSettings();
	DCC_SetBotPresenceStatus(IDLE);
	SetTimer("ActivityChange", 2000, true);
	SetTimer("InactivityPurge", 3600000, true);
	SetTimer("DateUpdate", 10000, true);
	SetTimer("DateTimeLog", 1000, true);

	LoadChannels();
	LoadCommands();
	CallLocalFunction("NRP_SETDATE", "");
	printf("OnGameModeInit performed");
	return 1;
}

forward DateTimeLog();
public DateTimeLog()
{
	new y,m,d,h,n,s;
	getdate(y,m,d);
	gettime(h,n,s);
	format(datetimelog, sizeof datetimelog, 
		""BOT_NAME" • %i/%i/%i • %i:%i:%i | v%s.%s-R%s",
		d,m,y,h,n,s,
		DAMN_LARPER_MAJOR,
		DAMN_LARPER_MINOR,
		DAMN_LARPER_RELEASE);
	return 1;
}

public OnGameModeExit()
{
	DCC_SetBotPresenceStatus(DO_NOT_DISTURB);
	DCC_SetBotActivity("System is restarting...");
	SaveSettings();
	return 1;
}