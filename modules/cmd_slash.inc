// Script written by DEntisT, © & ® BRACE™.


new DCC_Command:DAMNLARPER_CMD;
#pragma unused DAMNLARPER_CMD

stock LoadCommands()
{
	DAMNLARPER_CMD = DCC_CreateCommand("damn", "One command to use the bot!", "INTERACTION_RECEIVED", true);
	return 1;
}

forward INTERACTION_RECEIVED(DCC_Interaction:interaction, DCC_User:DAMN_LARPER_USER);
public INTERACTION_RECEIVED(DCC_Interaction:interaction, DCC_User:DAMN_LARPER_USER)
{
	print("INTERACTION_RECEIVED called.");
	new 
		DCC_Channel:DAMN_LARPER_CHANNEL, 
		DAMN_LARPER_CONTENT[1000];

	DCC_GetInteractionChannel(interaction, DAMN_LARPER_CHANNEL);
	new channelid[DCC_ID_SIZE];
	DCC_GetChannelId(DAMN_LARPER_CHANNEL,channelid);
	DCC_GetInteractionContent(interaction, DAMN_LARPER_CONTENT);
	
	printf("channelid : '%s'\nDAMN_LARPER_CONTENT : '%s'",channelid,DAMN_LARPER_CONTENT);
	// cmd args:msg,author,args
	new 
		cmdname[32],
		arguments[1024];

	sscanf(DAMN_LARPER_CONTENT, "s[32]s[1024]", cmdname,arguments);

	if(strlen(cmdname) < 1)
	{
		DCC_SendInteractionMessage(interaction, 
		""d_reply""damn_larper_text" **OOPS** • You need to use it like this:\n`"BOT_PREFIX" [command] [arguments]`");
		return 1;
	}
	printf("cmdname : '%s'\narguments : '%s'", cmdname,arguments);

	new cmdfuncname[64];
	format(cmdfuncname, sizeof cmdfuncname, "discord_%s", cmdname);

	printf("cmdfuncname : '%s'", cmdfuncname);

	new DCC_ChannelType:channeltype;

	DCC_GetChannelType(DAMN_LARPER_CHANNEL, channeltype);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(DAMN_LARPER_USER,id);

	if(channeltype == DM || channeltype == GROUP_DM)
	{
		DCC_SendInteractionMessage(interaction, "> "d_reply" **WRONG TIME, WRONG PLACE!** • You may not use **"BOT_NAME"** commands in group or DM chats!");
		return 1;
	}

	if(IsBlacklisted(id))
	{
		DCC_SendInteractionMessage(interaction,  "> "d_reply" **ERROR** • You're blacklisted from using bot commands.");
		return 1;
	}

	new returned = CallLocalFunction(cmdfuncname, "iisi", 0, _:DAMN_LARPER_USER,arguments,_:DAMN_LARPER_CHANNEL);
	
	printf("returned : %i", returned);

	if(returned == 0)
	{
		DCC_SendInteractionMessage(interaction, 
		""d_reply""damn_larper_text" **UNKNOWN COMMAND** • I don't know what that is!");
		return 1;
	}

	if(returned == 1)
	{
		DCC_SendInteractionMessage(interaction, 
		""d_reply""damn_larper_text" Slash commands are the new "d_beta" feature!\n\nReport everything using `"BOT_PREFIX" report`.");
		
		CallLocalFunction("OnSlashCommandReceived", "iis", 
			_:DAMN_LARPER_CHANNEL, 
			_:DAMN_LARPER_USER, 
			DAMN_LARPER_CONTENT);
		return 1;
	}


	//DCC_SendInteractionMessage(interaction, ""d_reply""damn_larper_text" **OOPS** • I am not smart enough for slash commands yet! Try `damn help`.");
	return 1;
}

OnSlashCommandReceived(DCC_Channel:channel, DCC_User:user, content[]);
public OnSlashCommandReceived(DCC_Channel:channel, DCC_User:user, content[])
{
	new betasent;
	if(BOT_BETA_PHASE == 1)
	{
		if(random(10) == 5 && GetUserConfigBetaAnnc(user) == 1)
		{
			@discord() SendInfo(channel, ""d_beta" "BOT_NAME" achieved the **Beta Test** phase of development, help us in the development process by reporting all the bugs and issues using the `"BOT_PREFIX"report` command!");
			betasent = 1;
		}
	}
	if(random(100) < 10 && betasent == 0 && GetUserConfigTips(user) == 1)
	{
		@discord() SendInfo(channel, "**TIP** "d_star" %s", BotTips[random(sizeof BotTips)]);
	}
	return 1;
}
