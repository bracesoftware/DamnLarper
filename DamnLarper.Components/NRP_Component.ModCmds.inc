// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - mod commands

@discord() command:moderation(@discord() cmd_params)
{
	new DCC_Channel:channel;
	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	/*@discord() SendMsg(channel, "**__Bot settings__**\n\n\
		"d_arrow"**`"BOT_PREFIX"logs`**\n"d_reply"Enable or disable the log system.\n\
		"d_arrow"**`"BOT_PREFIX"gmc`**\n"d_reply"Activate or deactivate GM counting.\n\
		"d_arrow"**`"BOT_PREFIX"eco`**\n"d_reply"Toggle economy commands on or off.");*/

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__MODERATION COMMANDS FOR RON__**", ""delimiterlol" Available moderation commands:\n\n\
		"d_arrow"**`"BOT_PREFIX"gmtemp`**\n"d_reply"View the GM template to use in `#gm-output`!\n\
		"d_arrow"**`"BOT_PREFIX"warn`**\n"d_reply"Permanently warns a member.\n\
		"d_arrow"**`"BOT_PREFIX"warns`**\n"d_reply"View all user's warnings.\n\
		"d_arrow"**`"BOT_PREFIX"annc`**\n"d_reply"Post an announcement.\n\
		"d_arrow"**`"BOT_PREFIX"mute`**\n"d_reply"Mute a member.\n\
		"d_arrow"**`"BOT_PREFIX"unmute`**\n"d_reply"Unmute a member.\n\
		"d_arrow"**`"BOT_PREFIX"setgmc`**\n"d_reply"Set GM count for a member.\n\
		"d_arrow"**`"BOT_PREFIX"getgmc`**\n"d_reply"Get GM count of a member.\n\
		"d_arrow"**`"BOT_PREFIX"poll`**\n"d_reply"Create a poll.\n\
		"d_arrow"**`"BOT_PREFIX"profile`**\n"d_reply"View the overall Game Master statistics.\n\
		"d_arrow"**`"BOT_PREFIX"setgmcc`**\n"d_reply"Customized `"BOT_PREFIX"setgmc` built for each department.\n\
		"d_arrow"**`"BOT_PREFIX"setgmclvl`**\n"d_reply"Another custom `"BOT_PREFIX"setgmc` to set leveled GM count.\n\
		"d_arrow"**`"BOT_PREFIX"top`**\n"d_reply"View a leaderboard.\n\
		"d_arrow"**`"BOT_PREFIX"sprofile`**\n"d_reply"View the support staff profile.\n\
		"d_arrow"**`"BOT_PREFIX"resetprofile`**\n"d_reply"Reset a GM/support staff profile of a certain user to 0.\n\
		"d_arrow"**`"BOT_PREFIX"rprole`**\n"d_reply"Assign a role-play role to an user.", "","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
	return 1;
}


//gmtemp
@discord() command:gmtemp(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	
	@discord() SendMsg(channel, "**__GM Template__**\n\n\
		**[`department label [pol/eco/mil]`]**\n\
		**Message link:**\n\
		**Provided WIWTK:**\n\
		**GM Content:**\n\
		**Tags:**");

	@discord() SendMsg(channel, ":information_source: • Using a valid template is really important, as if you don't, your GM will not be count in activity logs.\n\
		"delimiterlol" • Use "d_arrow"**`"BOT_PREFIX"gmexample`** to view the example of template usage.");

	return 1;
}
//warn

@discord() command:warn(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	SettingsCheck(mod);

	modcheck;

	new user[DCC_ID_SIZE + 10], reason[100];

	if(sscanf(params, "s[40]s[100]", user, reason))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"warn [user ID or user mention] [reason]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	if(!strcmp(user, "617419819108663296"))
	{
		@discord() SendMsg(channel, ""d_reply" • This user can't be warned as the user is a bot owner!");
		return 1;
	}

	if(!strcmp(user, "888667418904363078"))
	{
		@discord() SendMsg(channel, ""d_reply" • This user can't be warned as the user is a website maintainer!");
		return 1;
	}

	new filename[100];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	SaveLogIntoFile(filename, reason);

	new msg[512];
	format(msg, sizeof msg, ""d_reply" • User <@%s> was warned successfully.\n**REASON** • `%s`", user, reason);
	@discord() SendMsg(channel, msg);
	return 1;
}
//warns
@discord() command:warns(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	SettingsCheck(mod);

	modcheck;

	new user[100];

	if(sscanf(params, "s[100]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"warns [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	/*new parameters[128], idx;

	parameters = strtok(params, idx);

	if(strlen(parameters) == 0) return @discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"warns [user ID or user mention]`");

	format(user, sizeof user, "%s", parameters);*/

	if(!strcmp(user, "617419819108663296"))
	{
		@discord() SendMsg(channel, ""d_reply" • Operation failed!");
		return 1;
	}

	new filename[100], content[1024];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	if(!fexist(filename))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This user has no warnings.");
		return 1;
	}

	new File: file = fopen(filename, io_read);
	if (file)
	{
		fread(file, content);

		for(new i; i < strlen(content); i++)
		{
			if(content[i] == '*') content[i] = '\n';
		}

		fclose(file);
	}

	new msg[1024 + 100];

	format(msg, sizeof msg, "**__List of <@%s>'s warnings__**\n\n%s", user, content);

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__WARN LIST__**", msg, "","", col_embed, datetimelog, 
		"","","");

	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2);

	return 1;
}


//annc

@discord() command:annc(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new string[512], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[512]", string))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"annc [announcement text]`\n\
			"delimiterlol" **TIP** • In order to strip to a new line, at the point you want to add a new line add `\\` symbol.\n\
			**Example:** `"BOT_PREFIX"annc Funny\\text.`");
		return 1;
	}

	for(new i; i < strlen(string); i++)
	{
		if(string[i] == '\\') string[i] = '\n';
	}

	new msg[1024];
	
	format(msg, sizeof msg, ""botpfp" Announcement posted by <@%s>.\n\n\
		`%s`", id, string);

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__"SERVER_RISE_OF_NATIONS"__** Announcement", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"","");

	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(announcements, msg2, ""delimiterlol" **INFO** • This is an announcement repost made with `"BOT_PREFIX"annc` mod command.");

	@discord() SendMsg(channel, ""d_reply" • Announcement was posted successfully.");
	return 1;
}

//mute
@discord() command:mute(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	SettingsCheck(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"mute [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	if(!strcmp(user, "617419819108663296"))
	{
		@discord() SendMsg(channel, ""d_reply" • This user can't be removed as the user is a bot owner!");
		return 1;
	}


	if(muted == DCC_INVALID_ROLE)
	{
		@discord() SendMsg(channel,""d_reply" **ROLE ERROR** • There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), muted);

	@discord() SendMsg(channel, ""d_reply" **MUTED** • <@%s> was muted successfully.", user);

	return 1;
}
//unmute
@discord() command:unmute(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	servercheck(RiseOfNations);
	SettingsCheck(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"unmute [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	if(!strcmp(user, "617419819108663296"))
	{
		@discord() SendMsg(channel, ""d_reply" • This member wasn't muted!");
		return 1;
	}

	if(muted == DCC_INVALID_ROLE)
	{
		@discord() SendMsg(channel,""d_reply" **ROLE ERROR** • There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_RemoveGuildMemberRole(RiseOfNations, DCC_FindUserById(user), muted);

	@discord() SendMsg(channel, ""d_reply" **UNMUTED** • <@%s> was unmuted successfully.", user);

	return 1;
}



//setgmc

@discord() command:setgmc(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], gmcount;

	if(sscanf(params, "s[40]i", user, gmcount))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"setgmc [user ID or user mention] [GM count]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	SaveGMCount(user, gmcount);

	@discord() SendMsg(channel, ""d_reply" **GM COUNT SET** • <@%s>'s GM count was modified successfully. New GM count: `%i`", user, gmcount);

	return 1;
}

//getgmc


@discord() command:getgmc(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"getgmc [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	@discord() SendMsg(channel, ""d_reply" **MEMBER'S GM COUNT** • <@%s> did `%i` GMs since the last reset.", user, GetGMCount(user));

	return 1;
}


//poll


@discord() command:poll(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new text[512];

	if(sscanf(params, "s[512]", text))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"poll [poll name]*[poll text]`\n\
			"delimiterlol" **TIP** • Command usage example: `"BOT_PREFIX"poll Void an action*I vote to void this and this, bla bla...`");
		return 1;
	}

	new strip[2][512];

	split(text, strip, '*');

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	format(RISE_OF_NATIONS_GLOBALSTRING,sizeof RISE_OF_NATIONS_GLOBALSTRING, "**__%s__**\n"d_reply" *%s*\n\n:dizzy: • \
		Poll was posted by: <@%s>\nReact with "d_yes" or "d_reply" below.", strip[0], strip[1], id);
	
	new DCC_Embed:msg2 = DCC_CreateEmbed(
		":newspaper: **__POLL__**", RISE_OF_NATIONS_GLOBALSTRING, "","", col_embed, datetimelog, 
		"","","");

	DCC_SendChannelEmbedMessage(channel, msg2, ""delimiterlol" **INFO** • A new poll has been posted!");

	new DCC_Message:msg3 = DCC_GetCreatedMessage();

	AddReaction(msg3, DCC_CreateEmoji("☑️"));

	AddReaction(msg3, DCC_CreateEmoji("❌"));

	return 1;
}


//profile


@discord() command:profile(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"profile [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	new msg[1024];
	
	format(msg, sizeof msg, ":speaking_head: <@%s>'s Statistics\n\n\
		Total GMs: `%i`\n\n\
		:newspaper: **Departments**\n\
		Politics GMs: `%i`\n\
		Economics GMs: `%i`\n\
		Military GMs: `%i`\n\
		War GMs: `%i`\n\n\
		:newspaper: **Multiple Labels/Departments**\n\
		Politics & Economics GMs: `%i`\n\
		Economics & Military: `%i`\n\
		Military & Politics: `%i`\n\n\
		:crown: **Accuracy levels**\n\
		Easy GMs: `%i`\n\
		Subnormal GMs: `%i`\n\
		Normal GMs: `%i`\n\
		Medium GMs: `%i`\n\
		Hard GMs: `%i`\n", user, 
		GetGMCount(user),
		GetPolGMCount(user),
		GetEcoGMCount(user),
		GetMilGMCount(user),
		GetWarGMCount(user),
		GetPolEcoGMCount(user),GetEcoMilGMCount(user),GetMilPolGMCount(user),
		GetEasyGMCount(user),
		GetSubnormalGMCount(user),
		GetNormalGMCount(user),
		GetMediumGMCount(user),
		GetHardGMCount(user));

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__Game Master Profile__**", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"","");

	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, GetMention(useridmention));
	return 1;
}


//setgmcc

@discord() command:setgmcc(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], label[15], gmcount;

	if(sscanf(params, "s[31]s[15]i", user, label, gmcount))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"setgmcc [user ID or user mention] [department label(s)] [GM count]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	new dept;

	for(new i; i < strlen(label); i++)
	{
		if(label[i] == '[' && 
			label[i+1] == 'p' && 
			label[i+2] == 'o' && 
			label[i+3] == 'l' && 
			label[i+4] == ']')
		{
			dept = dept + 1;
		}

		if(label[i] == '[' && 
			label[i+1] == 'e' && 
			label[i+2] == 'c' && 
			label[i+3] == 'o' && 
			label[i+4] == ']')
		{
			dept = dept + 3;
		}

		if(label[i] == '[' && 
			label[i+1] == 'm' && 
			label[i+2] == 'i' && 
			label[i+3] == 'l' && 
			label[i+4] == ']')
		{
			dept = dept + 8;
		}
	}

	if(dept == 1) // Politics department solo
	{
		@discord() SendMsg(channel, ""d_reply" **POLITICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SavePolGMCount(user,gmcount);
		return 1;
	}

	if(dept == 3) // Economics solo
	{
		@discord() SendMsg(channel, ""d_reply" **ECONOMICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SaveEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 8) // Military solo
	{
		@discord() SendMsg(channel, ""d_reply" **MILITARY GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SaveMilGMCount(user,gmcount);
		return 1;
	}

	// Mixed labels:
	
	if(dept == 4) // pol eco
	{
		@discord() SendMsg(channel, ""d_reply" **POLITICS & ECONOMICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SavePolEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 11) // eco mil
	{
		@discord() SendMsg(channel, ""d_reply" **ECONOMICS & MILITARY GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SaveEcoMilGMCount(user,gmcount);
		return 1;
	}

	if(dept == 9) // mil pol
	{
		@discord() SendMsg(channel, ""d_reply" **MILITARY & POLITICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `"BOT_PREFIX"profile`.", user);
		SaveMilPolGMCount(user,gmcount);
		return 1;
	}

	if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9)
	{
		@discord() SendMsg(channel, ""d_reply" **GM COUNT MODIFICATION** • Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`\n\n"delimiterlol" • Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}

	return 1;
}

//setgmclvl


@discord() command:setgmclvl(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], lvl, gmcount;

	if(sscanf(params, "s[31]ii", user, lvl, gmcount))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"setgmclvl [user ID or user mention] [level ID] [GM count]`\n\
			"delimiterlol" **LEVEL IDs** • These are the current GM levels: easy - `1`, subnormal - `2`, normal - `3`, medium - `4`, hard - `5`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	if(lvl == 1)
	{
		@discord() SendMsg(channel, ""d_reply" **MODIFICATION SUCCESS** • GM count modification on level **Easy** for <@%s> was successful. Check it using `"BOT_PREFIX"profile`.", user);
		SaveEasyGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 2)
	{
		@discord() SendMsg(channel, ""d_reply" **MODIFICATION SUCCESS** • GM count modification on level **Subnormal** for <@%s> was successful. Check it using `"BOT_PREFIX"profile`.", user);
		SaveSubnormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 3)
	{
		@discord() SendMsg(channel, ""d_reply" **MODIFICATION SUCCESS** • GM count modification on level **Normal** for <@%s> was successful. Check it using `"BOT_PREFIX"profile`.", user);
		SaveNormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 4)
	{
		@discord() SendMsg(channel, ""d_reply" **MODIFICATION SUCCESS** • GM count modification on level **Medium** for <@%s> was successful. Check it using `"BOT_PREFIX"profile`.", user);
		SaveMediumGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 5)
	{
		@discord() SendMsg(channel, ""d_reply" **MODIFICATION SUCCESS** • GM count modification on level **Hard** for <@%s> was successful. Check it using `"BOT_PREFIX"profile`.", user);
		SaveHardGMCount(user, gmcount);
		return 1;
	}
	@discord() SendMsg(channel, "> "d_reply" **ERROR** • Invalid level ID provided.");
	return 1;
}

//top


@discord() command:top(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

  	new label[20];

  	new dept, 
    	slot1[DCC_ID_SIZE], 
    	slot2[DCC_ID_SIZE], 
    	slot3[DCC_ID_SIZE], 
    	slot4[DCC_ID_SIZE], 
    	slot5[DCC_ID_SIZE], gmrate_highest = 0;

   	GetStaffString();

    split(staffstring, staffid, '*');

	if(sscanf(params, "s[20]", label))
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the overall GM count:\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n\n\
	    	"d_reply" If you want to view a leaderboard for each department, provide a department label after the command trigger:\n`"BOT_PREFIX"top [department]`", 
	    	slot1, GetGMCount(slot1),
	    	slot2, GetGMCount(slot2),
	    	slot3, GetGMCount(slot3),
	    	slot4, GetGMCount(slot4),
	    	slot5, GetGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

    for(new i; i < strlen(label); i++)
	{
		if(label[i] == '[' && 
			label[i+1] == 'p' && 
			label[i+2] == 'o' && 
			label[i+3] == 'l' && 
			label[i+4] == ']')
		{
			dept = dept + 1;
		}

		if(label[i] == '[' && 
			label[i+1] == 'e' && 
			label[i+2] == 'c' && 
			label[i+3] == 'o' && 
			label[i+4] == ']')
		{
			dept = dept + 3;
		}

		if(label[i] == '[' && 
			label[i+1] == 'm' && 
			label[i+2] == 'i' && 
			label[i+3] == 'l' && 
			label[i+4] == ']')
		{
			dept = dept + 8;
		}

		if(label[i] == '[' && 
			label[i+1] == 'w' && 
			label[i+2] == 'a' && 
			label[i+3] == 'r' && 
			label[i+4] == ']')
		{
			dept = dept + 12;
		}
	}

	if(dept == 1) // Politics department solo
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetPolGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetPolGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Politics** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetPolGMCount(slot1),
	    	slot2, GetPolGMCount(slot2),
	    	slot3, GetPolGMCount(slot3),
	    	slot4, GetPolGMCount(slot4),
	    	slot5, GetPolGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	if(dept == 3) // Economics solo
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetEcoGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetEcoGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Economics** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetEcoGMCount(slot1),
	    	slot2, GetEcoGMCount(slot2),
	    	slot3, GetEcoGMCount(slot3),
	    	slot4, GetEcoGMCount(slot4),
	    	slot5, GetEcoGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	if(dept == 8) // Military solo
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetMilGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetMilGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Military** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetMilGMCount(slot1),
	    	slot2, GetMilGMCount(slot2),
	    	slot3, GetMilGMCount(slot3),
	    	slot4, GetMilGMCount(slot4),
	    	slot5, GetMilGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	// Mixed labels:
	
	if(dept == 4) // pol eco
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetPolEcoGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetPolEcoGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetPolEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolEcoGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetPolEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolEcoGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetPolEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolEcoGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetPolEcoGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetPolEcoGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Politics & Economics** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetPolEcoGMCount(slot1),
	    	slot2, GetPolEcoGMCount(slot2),
	    	slot3, GetPolEcoGMCount(slot3),
	    	slot4, GetPolEcoGMCount(slot4),
	    	slot5, GetPolEcoGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	if(dept == 11) // eco mil
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetEcoMilGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetEcoMilGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetEcoMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoMilGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetEcoMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoMilGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetEcoMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoMilGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetEcoMilGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetEcoMilGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Economics & Military** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetEcoMilGMCount(slot1),
	    	slot2, GetEcoMilGMCount(slot2),
	    	slot3, GetEcoMilGMCount(slot3),
	    	slot4, GetEcoMilGMCount(slot4),
	    	slot5, GetEcoMilGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));

		return 1;
	}

	if(dept == 9) // mil pol
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetMilPolGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetMilPolGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetMilPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilPolGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetMilPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilPolGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetMilPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilPolGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetMilPolGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetMilPolGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **Military & Politics** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetMilPolGMCount(slot1),
	    	slot2, GetMilPolGMCount(slot2),
	    	slot3, GetMilPolGMCount(slot3),
	    	slot4, GetMilPolGMCount(slot4),
	    	slot5, GetMilPolGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	if(dept == 12) // war
	{
		for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(GetWarGMCount(staffid[x]) >= gmrate_highest)
	        {
	            gmrate_highest = GetWarGMCount(staffid[x]);
	            strmid(slot1, staffid[x], 0, strlen(staffid[x]));
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]))
	        {
	            if(GetWarGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetWarGMCount(staffid[x]);
	                strmid(slot2, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && strcmp(slot2, staffid[x]))
	        {
	            if(GetWarGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetWarGMCount(staffid[x]);
	                strmid(slot3, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x]) && 
	        	strcmp(slot2, staffid[x]) && 
	        	strcmp(slot3, staffid[x]))
	        {
	            if(GetWarGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetWarGMCount(staffid[x]);
	                strmid(slot4, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    for(new x = 0; x < MAX_STAFF_MEMBERS; x++)
	    {
	        if(strcmp(slot1, staffid[x])
	        	&& strcmp(slot2, staffid[x])
	        	&& strcmp(slot3, staffid[x])
	        	&& strcmp(slot4, staffid[x]))
	        {
	            if(GetWarGMCount(staffid[x]) >= gmrate_highest)
	            {
	                gmrate_highest = GetWarGMCount(staffid[x]);
	                strmid(slot5, staffid[x], 0, strlen(staffid[x]));
	            }
	        }
	    }

	    gmrate_highest = 0;

	    format(RISE_OF_NATIONS_GLOBALSTRING, sizeof RISE_OF_NATIONS_GLOBALSTRING, 
	    	":newspaper: Leaderboard for the **War** department(s):\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n", 
	    	slot1, GetWarGMCount(slot1),
	    	slot2, GetWarGMCount(slot2),
	    	slot3, GetWarGMCount(slot3),
	    	slot4, GetWarGMCount(slot4),
	    	slot5, GetWarGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", RISE_OF_NATIONS_GLOBALSTRING, 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""));
		return 1;
	}

	if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9 && dept != 12)
	{
		@discord() SendMsg(channel, ""d_reply" **GM COUNT LEADERBOARD** • Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`, `[war]`\n\n"delimiterlol" • Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}
	printf("gmrate_highest : %i", gmrate_highest);
    return 1;
}


//sprofile
@discord() command:sprofile(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"sprofile [user ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	new msg[1024];
	
	format(msg, sizeof msg, ":speaking_head: <@%s>'s Statistics\n\n\
		:newspaper: **Messages**\n\
		Total message count: `%i`\n\n\
		:newspaper: **Submission**\n\
		Submission approvals: `%i`\n\n\
		:newspaper: **Support**\n\
		Support points: `%i`", 
		user, GetMessageCount(user), GetApprovalCount(user), GetSupportPoints(user));

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__Support Staff Profile__**", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"","");

	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, GetMention(useridmention));
	return 1;
}


//resetprofile



@discord() command:resetprofile(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], type;

	if(sscanf(params, "s[31]i", user, type))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"resetprofile [user ID or user mention] [type of a reset]`\n\nIf you want to reset GM profile of an user, use `0` as the type ID - if you want to reset a supporter profile, use `1` as the type ID.");
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);
	
	if(type == 0)
	{
		SaveGMCount(user,0);
		SavePolGMCount(user,0);
		SaveEcoGMCount(user,0);
		SaveMilGMCount(user,0);
		SaveWarGMCount(user,0);
		SavePolEcoGMCount(user,0);
		SaveEcoMilGMCount(user,0);
		SaveMilPolGMCount(user,0);
		SaveEasyGMCount(user,0);
		SaveSubnormalGMCount(user,0);
		SaveNormalGMCount(user,0);
		SaveMediumGMCount(user,0);
		SaveHardGMCount(user,0);

		@discord() SendMsg(channel, "<@%s>'s GM profile has been cleared.", user);
	}
	if(type == 1)
	{
		SaveApprovalCount(user,0); 
		SaveSupportPoints(user,0);

		@discord() SendMsg(channel, "<@%s>'s support profile has been cleared.", user);
	}
	if(type != 0 && type != 1)
	{
		@discord() SendMsg(channel, ""d_reply" **ERROR** • Invalid reset type ID provided, it can be either `0` or `1`.");
	}
	return 1;
}


//rprole





@discord() command:rprole(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new user[DCC_ID_SIZE], option[30];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	if(sscanf(params, "s[50]s[30]", user, option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Submission Approval Setup__**", ""delimiterlol" These are the options used to manipulate with user RP role statistics.\n\
		Usage: `"BOT_PREFIX"rprole [user] [option]`\n\n\
		**__Options__**\n\n\
		**`nation`**\n"d_reply"Give a nation role to user.\n\
		**`rebelorg`**\n"d_reply"Give a rebellion organization role to user.\n\
		**`politicalorg`**\n"d_reply"Give a political organization role to user.\n\
		**`corporation`**\n"d_reply"Give a corporation role to user.\n\
		**`acoop`**\n"d_reply"Give an administrative cooperator role to user.\n\
		**`pcoop`**\n"d_reply"Give a provincial cooperator role to user.\n\
		**`civilian`**\n"d_reply"Give a civilian role to user.\n\
		**`unsec`**\n"d_reply"Give an UN secretariat role to user.\n\
		**`spectator`**\n"d_reply"Give a spectator role to user.\n\
		**`player`**\n"d_reply"Give a player role to user.",
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	for(new i; i <= strlen(user); i++)
	{
		if(user[i] == '<') strdel(user, i, i+1);
		if(user[i] == '@') strdel(user, i, i+1);
		if(user[i] == '>') strdel(user, i, i+1);
		if(user[i] == '!') strdel(user, i, i+1);
		if(user[i] == '\32') strdel(user, i, i+1);
	}

	usercheck(user);

	//options
	if(!strcmp(option, "nation"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), nation);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Nation`* role.", user);

		return 1;
	}
	if(!strcmp(option, "rebelorg"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), rebelorg);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Rebellion Organization`* role.", user);

		return 1;
	}
	if(!strcmp(option, "politicalorg"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), politicalorg);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Political Organization`* role.", user);

		return 1;
	}
	if(!strcmp(option, "corporation"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), corporation);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Corporation`* role.", user);

		return 1;
	}
	if(!strcmp(option, "acoop"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), acoop);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Administrative Cooperator`* role.", user);

		return 1;
	}
	if(!strcmp(option, "pcoop"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), pcoop);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Provincial Cooperator`* role.", user);

		return 1;
	}
	if(!strcmp(option, "civilian"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), civilian);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Civilian`* role.", user);

		return 1;
	}
	if(!strcmp(option, "unsec"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), unsec);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`UN Secretariat`* role.", user);

		return 1;
	}
	if(!strcmp(option, "player"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), playerrole);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Player`* role.", user);

		return 1;
	}
	if(!strcmp(option, "spectator"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), spectator);

		@discord() SendMsg(channel, ""d_reply" **USER ROLED** • <@%s> was successfully given the *`Spectator`* role.", user);

		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN OPTION** • Invalid role option provided, use `"BOT_PREFIX"rprole` to view a list of available options.");
	}
	return 1;
}
