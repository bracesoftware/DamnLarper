// Module written by DEntisT, © & ® BRACE™.

stock GetUserConfigTips(DCC_User:user)
{
	new id[DCC_ID_SIZE];
	DCC_GetUserId(user, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"usercfg/tips_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);

		return strval(strFromFile2);
	}
	return strval(strFromFile2);
}

stock SetUserConfigTips(DCC_User:user, value)
{
	new id[DCC_ID_SIZE];
	DCC_GetUserId(user, id);
	new file_name[150], string[10];

	format(file_name, sizeof file_name,"usercfg/tips_%s.ini",id);
	format(string, sizeof(string), "%i", value);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

@discord() command:userconfig(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);


	new option[30],value[DCC_ID_SIZE+10];

	if(sscanf(params, "s[30]s[50]", option, value))
	{
		//@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"serverconfig [option]`");
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__User Configuration__**", ""delimiterlol" • Setup how "BOT_NAME" will work for you!\n\
		Usage: `"BOT_PREFIX"userconfig [option] [value]`\n\
		Use `"BOT_PREFIX"userconfig view cfg` to view current configuration.\n\n\
		**__Options__**\n\
		**`tips`**\n"d_reply"Toggle the "BOT_NAME" Tips system on or of!\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));

		return 1;
	}

	for(new i; i <= strlen(value); i++)
	{
		if(value[i] == '<') strdel(value, i, i+1);
		if(value[i] == '@') strdel(value, i, i+1);
		if(value[i] == '>') strdel(value, i, i+1);
		if(value[i] == '!') strdel(value, i, i+1);
		if(value[i] == '\32') strdel(value, i, i+1);
		if(value[i] == '#') strdel(value, i, i+1);
	}
	if(!strcmp(option, "view") && !strcmp(value, "cfg"))
	{
		@discord() SendMsg(channel, "**<@%s>'s Current Configuration**\n\n`tips` • `%s`\n",id,GetUserConfigTips(author) ? "true" : "false");
		return 1;
	}

	if(!strcmp(option, "tips"))
	{
		if(!strcmp(value, "true"))
		{
			SetUserConfigTips(author, 1);

			@discord() SendMsg(channel, ""d_reply" **USER CONFIG UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		if(!strcmp(value, "false"))
		{
			SetUserConfigTips(author, 0);

			@discord() SendMsg(channel, ""d_reply" **USER CONFIG UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		@discord() SendMsg(channel, ""d_reply" **WRONG VALUE** • Wrong value for option `%s` was given!\nPlease try again with either `true` or `false`!\n\nGiven value: `%s`.", option, value);
		return 1;
	}
	
	@discord() SendInfo(channel, "Something went wrong! Try again.");
	return 1;
}


#endinput

stock GetGuildLogChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/lgc_%s.ini", id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Unknown");
	if(!fexist(file_name)) return strFromFile2;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);

		return strFromFile2;
	}
	return strFromFile2;
}

stock SetGuildLogChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/lgc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

