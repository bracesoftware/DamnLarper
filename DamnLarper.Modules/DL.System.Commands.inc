// Module written by DEntisT, © & ® BRACE™.

@discord() command:verify(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	if(GetGuildVerification(guild) == 0)
	{
		@discord() SendInfo(channel, "This guild does not require verification of the users!");
		return 1;
	}

	new code[10];

	if(sscanf(params, "s[10]", code))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"verify [your verify code]`");
		return 1;
	}

	if(!strcmp(code, GetVerifyCode(guild, user)))
	{
		SetUserVerification(guild, user, 1);
		@discord() SendMsg(channel, ""d_reply" **VERIFICATION WAS SUCCESSFUL** • You were successfully verified!");
		return 1;
	}

	@discord() SendMsg(channel, ""d_reply" **VERIFICATION WAS UNSUCCESSFUL** • Your verification code wasn't correct! Please try again.");
	@discord() SendInfo(channel, "Use `"BOT_PREFIX"newverifycode` to generate a new verification code for this guild.");
	return 1;
}

@discord() command:newverifycode(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	if(GetGuildVerification(guild) == 0)
	{
		@discord() SendInfo(channel, "This guild does not require verification of the users!");
		return 1;
	}
	@discord() SendInfo(channel, "New verification code is being generated...");
	new code[10];
	format(code, sizeof code, "%i", random(100000));

	SetVerifyCode(guild, id, code);

	@discord() SendMsg(DCC_FindChannelById(GetGuildVerificationChannel(guild)), ""botpfp" **WELCOME TO THE GUILD** • Hello <@%s>! Thanks for choosing this guild to join! But in order to send messages here, please use a `"BOT_PREFIX"verify` command.\n\nYour verification code **for this guild** is: `%s`", id, code);
	@discord() SendInfo(DCC_FindChannelById(GetGuildVerificationChannel(guild)), "<@%s>\n\nPlease make sure to verify as fast as possible to be able to chat, use commands and more!", id);
	return 1;
}


@discord() command:addmod(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"addmod [user ID or user mention]`");
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

	new file_name[150];
	format(file_name, sizeof file_name,"mods/mod_%s.ini",user);

	if(fexist(file_name))
	{
		@discord() SendMsg(channel, ""d_reply" • This user is already a moderator!");
		return 1;
	}

	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "");
	fclose(file2);

	@discord() SendMsg(channel, ""d_reply" • User <@%s> added to the moderator team successfully.", user);

	return 1;
}

@discord() command:addpremium(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"addpremium [user ID or user mention]`");
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

	SetPremium(user, 1);
	
	@discord() SendMsg(channel, ""d_reply" **PREMIUM PERKS GIVEN** • <@%s> was given the "BOT_NAME" Premium membership.", user);

	@discord() SendDM(DCC_FindUserById(user), "**GREAT NEWS!** • You were given "d_premium" | `"BOT_NAME" Premium` perks by a global moderator.");

	return 1;
}

@discord() command:delpremium(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"delpremium [user ID or user mention]`");
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

	SetPremium(user, 0);
	
	@discord() SendMsg(channel, ""d_reply" **PREMIUM PERKS REMOVED** • <@%s> was removed from the "BOT_NAME" Premium membership.", user);

	@discord() SendDM(DCC_FindUserById(user), "**UNFORTUNATE NEWS** • Your "d_premium" | `"BOT_NAME" Premium` perks were taken away by a global moderator.");

	return 1;
}


@discord() command:delmod(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"delmod [user ID or user mention]`");
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

	new file_name[150];
	format(file_name, sizeof file_name,"mods/mod_%s.ini",user);
	
	if(!fexist(file_name))
	{
		@discord() SendMsg(channel, ""d_reply" • This user is not a moderator!");
		return 1;
	}

	fremove(file_name);
	@discord() SendMsg(channel, ""d_reply" • User <@%s> removed from the moderator team successfully.", user);

	return 1;
}
/*"d_arrow"**`"BOT_PREFIX"moderation`**\n"d_reply"Help about server moderation.\n\
	"d_arrow"**`"BOT_PREFIX"version`**\n"d_reply"Last bot update.\n\*/
@discord() command:help(@discord() cmd_params)
{

	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);
    new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
    
    new option[30];

    if(sscanf(params, "s[30]", option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Main Bot Panel__**", "\n\n\
		"delimiterlol" • __List of Informational & Pinned Commands__\n\
		"d_arrow"**`"BOT_PREFIX"help bracetm`**\n"d_reply"Exclusive commands for the "BRACE_TEAM" team!\n\
		"d_arrow"**`"BOT_PREFIX"help premium`**\n"d_reply"Exclusive commands for the "BOT_NAME" Premium users!\n\
		"d_arrow"**`"BOT_PREFIX"help custom`**\n"d_reply"View help panel for custom server features.\n\
		"d_arrow"**`"BOT_PREFIX"version`**\n"d_reply"Last bot update.\n\
		"d_arrow"**`"BOT_PREFIX"website`**\n"d_reply"Link to our website where you can find various information and other links.\n\
		"d_arrow"**`"BOT_PREFIX"errors`**\n"d_reply"Check for the bot errors.\n\
		"d_arrow"**`"BOT_PREFIX"report`**\n"d_reply"Report a bug, error and such exploits.\n\
		"d_arrow"**`"BOT_PREFIX"tos`**\n"d_reply"Read our application's Terms of Service.\n\
		"d_arrow"**`"BOT_PREFIX"pp`**\n"d_reply"Read our Privacy Policy.\n\n\
		"delimiterlol" • __List of Main Commands__\n\
		"d_arrow"**`"BOT_PREFIX"help verification`** "d_beta"\n"d_reply"Help about verification system.\n\
		"d_arrow"**`"BOT_PREFIX"help moderation`**\n"d_reply"Help about moderation commands.\n\
		"d_arrow"**`"BOT_PREFIX"help economy`**\n"d_reply"Help about economy commands.\n\
		"d_arrow"**`"BOT_PREFIX"help afk`**\n"d_reply"Help about AFK system.\n\
		"d_arrow"**`"BOT_PREFIX"help customcmd`**\n"d_reply"Help with your own custom commands!\n\
		"d_arrow"**`"BOT_PREFIX"help fun`**\n"d_reply"Other miscellaneous panel - contains a big variety of other types of commands!\n\
		"d_arrow"**`"BOT_PREFIX"help levels`**\n"d_reply"Help about leveling system.\n\
		"d_arrow"**`"BOT_PREFIX"help bump`**\n"d_reply"Help about server bumping and leaderboard.\n\
		"d_arrow"**`"BOT_PREFIX"help lists`**\n"d_reply"Lists system help.\n\
		"d_arrow"**`"BOT_PREFIX"help pets`**\n"d_reply"Help with pet system!\n\
		"d_arrow"**`"BOT_PREFIX"help roleplay`**\n"d_reply"Bot's role-play system help.\n\
		"d_arrow"**`"BOT_PREFIX"help security`**\n"d_reply"Anti-raid and security system help.\n\
		"d_arrow"**`"BOT_PREFIX"help achievements`**\n"d_reply"Achievement system help.\n\
		"d_arrow"**`"BOT_PREFIX"help socialmedia`**\n"d_reply"Social media system help.\n\n\
		"delimiterlol" • __Other Information__\n\
		"d_reply" To learn more about "BOT_NAME", use `"BOT_PREFIX"features`.\n\n\
		"d_reply" • You can [invite me]("BOT_AUTH_LINK") on your server too! Use `"BOT_PREFIX"botsetup` to learn about everything you need to know before inviting me.\n\n\
		"d_heart" Thanks for choosing **"BOT_NAME"**!\n", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "bracetm"))
	{
		modcheck;
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BRACE_TEAM" Dev Team Commands__**", "\n\n\
		"d_arrow"**`"BOT_PREFIX"settings`**\n"d_reply"Manage the "BOT_NAME"'s settings!\n\
		"d_arrow"**`"BOT_PREFIX"saveset`**\n"d_reply"Save the current settings configuration.\n\
		"d_arrow"**`"BOT_PREFIX"setaccdata`**\n"d_reply"Manage another "BRACE_TEAM" account.\n\
		"d_arrow"**`"BOT_PREFIX"blacklist`**\n"d_reply"Blacklist someone from using "BOT_NAME" commands!\n\
		"d_arrow"**`"BOT_PREFIX"addmod`**\n"d_reply"Add someone to the "BOT_NAME" moderation team!\n\
		"d_arrow"**`"BOT_PREFIX"delmod`**\n"d_reply"Remove someone from the "BOT_NAME" moderation team!\n\
		"d_arrow"**`"BOT_PREFIX"addpremium`**\n"d_reply"Give someone the "BOT_NAME" Premium perks!\n\
		"d_arrow"**`"BOT_PREFIX"delpremium`**\n"d_reply"Take "BOT_NAME" Premium perks from someone and make them mad!\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "premium"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Premium Information__**", "If you have any related questions about premium or how can you get it, contact us @ **"BOT_SUPPORT_MAIL"**.\n\n\
		**Commands**\n\n\
		"d_premium" **`"BOT_PREFIX"premiumdaily`**\n"d_reply"Claim your daily!\n\
		\n**Other Features**\n\n\
		"d_premium" **Skip Command Cooldown**\n"d_reply"Mine, beg, chop and do other stuff without being disturbed by that annoying command cooldown!\n\n\
		"d_premium" **Access Special Pets**\n"d_reply"With premium perks, you can access special pets in the pet shop such as "d_pepefrog" | `Pepe Frog`!\n\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "verification"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Verification System Commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"verify`**\n"d_reply"Verify yourself!\n\
		"d_arrow"**`"BOT_PREFIX"newverifycode`**\n"d_reply"Get a new verification code in case of anything!\n\
		\n", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	//other systems
	if(!strcmp(option, "custom"))
	{
		if(DAMN_LARPER_REWRITE == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **UH OH!** • This help panel is currently deprecated! Try seeing another topic.");
			return 1;
		}
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Custom Features Help Panel__**", "\n\n\
		"delimiterlol" __List of Commands available for **"SERVER_RISE_OF_NATIONS"**__\n\
		"d_arrow"**`"BOT_PREFIX"moderation`**\n"d_reply"Help about server moderation.\n\
		"d_arrow"**`"BOT_PREFIX"nrphelp`**\n"d_reply"Nation role-play system help.\n\n", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "moderation"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Moderation Commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"serverconfig`**\n"d_reply"Setup "BOT_NAME" in your server!\n\
		"d_arrow"**`"BOT_PREFIX"ban`**\n"d_reply"Bans an user from a certain server.\n\
		"d_arrow"**`"BOT_PREFIX"unban`**\n"d_reply"Revokes an user ban in a certain server.\n\
		"d_arrow"**`"BOT_PREFIX"kick`**\n"d_reply"Kicks an user from a certain server.\n\
		"d_arrow"**`"BOT_PREFIX"roleall`**\n"d_reply"Give everyone a role.\n\
		"d_arrow"**`"BOT_PREFIX"deroleall`**\n"d_reply"Take a role from everyone.\n\n", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "economy"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Economy commands__**\n\n\
		"d_arrow"**`"BOT_PREFIX"bal` `"BOT_PREFIX"balance`**\n"d_reply"View your balance.\n\
		"d_arrow"**`"BOT_PREFIX"work`**\n"d_reply"Work and earn money.\n\
		"d_arrow"**`"BOT_PREFIX"dep` `"BOT_PREFIX"deposit`**\n"d_reply"Deposit money.\n\
		"d_arrow"**`"BOT_PREFIX"bankacc`**\n"d_reply"Open a bank account.\n\
		"d_arrow"**`"BOT_PREFIX"with` `"BOT_PREFIX"withdraw`**\n"d_reply"Withdraw money.\n\
		"d_arrow"**`"BOT_PREFIX"rob`**\n"d_reply"Rob a member.\n\
		"d_arrow"**`"BOT_PREFIX"shop`**\n"d_reply"Open a "BOT_NAME" shop.\n\
		"d_arrow"**`"BOT_PREFIX"buy`**\n"d_reply"Buy something from a "BOT_NAME" shop.\n\
		"d_arrow"**`"BOT_PREFIX"inv` `"BOT_PREFIX"inventory`**\n"d_reply"View your inventory.\n\
		"d_arrow"**`"BOT_PREFIX"daily`**\n"d_reply"Claim your daily money.\n\
		"d_arrow"**`"BOT_PREFIX"beg`**\n"d_reply"Beg for money on the streets!\n\
		"d_arrow"**`"BOT_PREFIX"heist`**\n"d_reply"Rob someone's bank balance!\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "afk"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__AFK commands__**\n\n\
		"d_arrow"**`"BOT_PREFIX"afk`**\n"d_reply"Set your AFK status.\n\
		"delimiterlol" **TIP** • Your AFK status gets removed once you send a message into any channel of a server.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "customcmd"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Custom Command help__**\n\n\
		"d_arrow"**`"BOT_PREFIX"declcmd`**\n"d_reply"Declare (create) a custom command.\n\
		"d_arrow"**`"BOT_PREFIX"delcmd`**\n"d_reply"Delete a custom command.\n\n\
		"delimiterlol" **TIP** • Bot responds to these commands only when they have a `!` prefix.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "fun"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Miscellaneous commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"search`**\n"d_reply"Let me Google stuff for you!\n\
		"d_arrow"**`"BOT_PREFIX"say`**\n"d_reply"Say something anonymously.\n\
		"d_arrow"**`"BOT_PREFIX"joke`**\n"d_reply"Get a joke.\n\
		"d_arrow"**`"BOT_PREFIX"qna`**\n"d_reply"Ask us a question!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "levels"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Leveling system help__**\n\n\
		"delimiterlol" This is a message-based leveling system. Statistics and rewards \
		gained in it is stored in multi-server storage, which means, if you achieved \
		level 2 on one server, on all other servers this bot is in, you will be level 2.\n\n\
		**Leveling Policy**\n\
		"delimiterlol" Every 100 messages you send, you climb up by one level! \
		You can check your level using `"BOT_PREFIX"level` command.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "bump"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ""d_reply" This system is under heavily development.\n\n\
		"d_arrow"**`"BOT_PREFIX"bump`**\n"d_reply"Bump your server!\n\
		"d_arrow"**`"BOT_PREFIX"servers`**\n"d_reply"View the server leaderboards.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "lists"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**List System commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"createlist`**\n"d_reply"Create a list!\n\
		"d_arrow"**`"BOT_PREFIX"addelement`**\n"d_reply"Add a list element (an user for example).\n\
		"d_arrow"**`"BOT_PREFIX"delelement`**\n"d_reply"Delete a list element.\n\
		"d_arrow"**`"BOT_PREFIX"viewlist`**\n"d_reply"View a list.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "pets"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Pet System commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"petshop`**\n"d_reply"List of pets you can buy!\n\
		"d_arrow"**`"BOT_PREFIX"buypet`**\n"d_reply"Buy a pet!\n\
		"d_arrow"**`"BOT_PREFIX"petstats`**\n"d_reply"View your pet statistics!\n\
		"d_arrow"**`"BOT_PREFIX"namepet`**\n"d_reply"Give your pet a new name!\n\
		"d_arrow"**`"BOT_PREFIX"feedpet`**\n"d_reply"Give your pet some food!\n\
		"d_arrow"**`"BOT_PREFIX"sellpet`**\n"d_reply"Sell your pet and make it cry!\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "roleplay"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**RolePlay System commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"mystats`**\n"d_reply"View your statistics!\n\
		"d_arrow"**`"BOT_PREFIX"mine`**\n"d_reply"Go mining and find something valuable!\n\
		"d_arrow"**`"BOT_PREFIX"melt`**\n"d_reply"Melt stuff to get other stuff!\n\
		"d_arrow"**`"BOT_PREFIX"hunt`**\n"d_reply"Go hunting and find stuff!\n\
		"d_arrow"**`"BOT_PREFIX"eat`**\n"d_reply"Consume stuff and max out your energy!\n\
		"d_arrow"**`"BOT_PREFIX"fish`**\n"d_reply"Go fishing and get fish or something else!\n\
		"d_arrow"**`"BOT_PREFIX"chop`**\n"d_reply"Go chopping and get planks!\n\
		"d_arrow"**`"BOT_PREFIX"make`**\n"d_reply"Make items out of other items!\n\
		"d_arrow"**`"BOT_PREFIX"openchest`**\n"d_reply"Open a chest!\n\
		"d_arrow"**`"BOT_PREFIX"dig`**\n"d_reply"Go digging into the dirt and hopefully find something!\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "security"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Anti-raid System commands**\n\n\
		"d_arrow" Nothing to see here yet!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "socialmedia"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Social Media System**\n\n\
		"d_arrow"**`"BOT_PREFIX"smregister`**\n"d_reply"Register an account on social media or change a current account's nickname.\n\
		"d_arrow"**`"BOT_PREFIX"smprofile`**\n"d_reply"View your "BRACE_TEAM" account profile.\n\
		"d_arrow"**`"BOT_PREFIX"smaccname`**\n"d_reply"Set your account name.\n\
		"d_arrow"**`"BOT_PREFIX"smbio`**\n"d_reply"Update your account's bio.\n\
		"d_arrow"**`"BOT_PREFIX"smpfp`**\n"d_reply"Update your account's profile picture.\n\
		"d_arrow"**`"BOT_PREFIX"post`**\n"d_reply"Post a message on social media.\n\
		"d_arrow"**`"BOT_PREFIX"feed`**\n"d_reply"The latest social media posts.\n\
		"d_arrow"**`"BOT_PREFIX"smtos`**\n"d_reply"Terms of Use of "BRACE_TEAM" account.\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "achievements"))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Achievement System**\n\n\
		"d_arrow"**`"BOT_PREFIX"achievements`**\n"d_reply"View the list of all the achievements that can be unlocked!\n\
		"d_arrow"**`"BOT_PREFIX"myachievements`**\n"d_reply"View the achievements you've unlocked so far!\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
		return 1;
	}
	@discord() SendMsg(channel, ""d_reply" **UNKNOWN TOPIC** • Help panel with that name wasn't found!");
	return 1;
}

@discord() command:features(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ""delimiterlol" Below, there's a list of all the features included in the bot.\n\n\
		**Exclusive "SERVER_RISE_OF_NATIONS" Features**\n\
		**1.** GM counting\n\
		**2.** Number counting\n\
		**3.** Moderation logging\n\
		**4.** Moderation commands\n\
		**5.** Bot settings can be maintained only by a bot mods\n\n\
		**Features available for all servers**\n\
		**1.** Economy system\n\
		**2.** AFK system\n\
		**3.** Leveling system\n\
		**4.** Custom commands\n\
		**5.** Message management\n\
		**6.** Server bump and leaderboard\n\
		**7.** Create and manage lists themed on any topic you want!\n\
		**8.** Other funny commands displayed on the `"BOT_PREFIX"help` panel\n\
		**9.** Role-play system!\n\n\
		"delimiterlol" **NOTE** • Bot is regularly maintained and updated, a lot of interesting cross-server features are coming soon!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}



@discord() command:tos(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Terms of Service__**", "**Hello! It's mandatory for everyone to accept our Terms of Service in order to use the bot properly.**\n\n\
		**1.** Don't exploit bugs of the bot, doing so may result in a command blacklist.\n\
		\n**2.** Using custom commands to send explicit or forbidden content of a certain server may result in a command blacklist.\n\
		\n**3.** Putting bad words as an arguments in commands is a bannable offense.\n\
		\n**4.** Using bot's commands to share personal information is not allowed.\n\
		\n**5.** Sharing fake information about the bot community is bannable offense.\n\
		\n**6.** Using commands such as `"BOT_PREFIX"report` for fun or multiple times is not a thing you should really do. Multiple requests and reports will be ignored.\n\
		\n**7.** Noticing the bug and not reporting it is not a nice thing to do - whenever \
		you notice something unusual happening, you should use the `"BOT_PREFIX"report` command.\n\
		\n**8.** Redistributing the bot's resources (such as images, logos, text) is prohibited.\n\
		\n**9.** Read our Privacy Policy for more, use `"BOT_PREFIX"pp` command to do so.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

@discord() command:pp(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Privacy Policy__**", ""d_reply" Your information is safe!\n\n\
		> Hi! Please note that the bot doesn't store any of your personal information \
		or account information such as e-mails, passwords, nicknames or messages besides \
		the user ID, which is used to store the data such as your economy money, level, \
		message count and many more!\n\n\
		> We deeply care about your privacy and security online. But, we aren't responsible for \
		any data loss using the bot, you shouldn't use passwords, usernames and such information \
		as list names, custom command names or anything else requiring a text input! Thanks.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}


//------------------------

@discord() command:createlist(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE],listname[20];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]", listname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"createlist [list name]`");
		return 1;
	}

	if(IsValidList(listname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This list already has been created.");
		return 1;
	}

	CreateList(id, listname);

	@discord() SendMsg(channel, ""d_reply" **LIST CREATED** • Your list has been created successfully.");

	return 1;
}

@discord() command:addelement(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new listname[20], element[50], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]s[50]", listname, element))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"addelement [list name] [element]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You can only modify lists that you created!");
		return 1;
	}

	AddListElement(listname, element);

	@discord() SendMsg(channel, ""d_reply" **LIST MODIFIED** • Your list has been successfully modified.");
	return 1;
}

@discord() command:delelement(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new listname[20], element, id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]i", listname, element))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"delelement [list name] [element ID]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You can only modify lists that you created!");
		return 1;
	}

	RemoveListElement(listname, element-1);

	@discord() SendMsg(channel, ""d_reply" **LIST MODIFIED** • Your list has been successfully modified.");
	return 1;
}

@discord() command:viewlist(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new listname[20], element[150], el[50];

	if(sscanf(params, "s[20]", listname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"viewlist [list name]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This list doesn't exist.");
		return 1;
	}

	//GetElement(list, element, dest);

	format(listpreview, sizeof listpreview, ":newspaper: This is a preview of **%s** list.\n\
		`[element ID] • [element content]`\n\n", listname);

	for(new i; i < MAX_LIST_ELEMENTS; i++)
	{
		if(IsValidElement(listname, i))
		{
			GetElement(listname, i, el);
			format(element, sizeof element, "**%i.** %s\n", i+1,el);
			strcat(listpreview, element);
		}
	}

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__List Preview__**", listpreview, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}



@discord() command:bump(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);

    new id[DCC_ID_SIZE];

    DCC_GetGuildId(guild, id);

    SaveBumpCount(id, GetBumpCount(id) + 1);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bump Done!__**", ""d_reply" Your server successfully got bumped on the bot's global server leaderboard.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

@discord() command:servers(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Coming soon!__**", ""d_reply" This feature is currently unavailable, but don't give up with bumping - bump command works.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}


@discord() command:level(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new lvl[256];

	format(lvl, sizeof lvl, "<@%s>\n\n**Level**\n"d_reply" `%i`\n\n**Total messages**\n"d_reply" `%i`", id, GetMessageCount(id) / 100 + 1, GetMessageCount(id));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Level Statistics__**", lvl, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}


@discord() command:declcmd(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(ccmd);

	new cmdname[32], text[256], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[32]s[256]", cmdname, text))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"declcmd [command name] [text to respond with]`");
		return 1;
	}

	if(IsCommand(cmdname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This command is already registered!");
		return 1;
	}

	for(new i; i < strlen(text); i++)
	{
		if(text[i] == '<' && text[i+1] == '@')
		{
			@discord() SendMsg(channel, ""d_reply" **ERROR** • Invalid characters detected in the text response.");
			return 1;
		}
		if(text[i] == '<' && text[i+1] == '!' && text[i+2] == '@')
		{
			@discord() SendMsg(channel,""d_reply" **ERROR** • Invalid characters detected in the text response.");
			return 1;
		}
	}

	CreateCommand(cmdname, id, text);

	@discord() SendMsg(channel, ""d_reply" **COMMAND CREATED** • Your custom command is successfully registered!\n> "d_reply" Try using it now!");
	return 1;
}

@discord() command:delcmd(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(ccmd);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new cmdname[32];

	if(sscanf(params, "s[32]", cmdname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"delcmd [command name]`");
		return 1;
	}

	if(!IsCommand(cmdname))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This command doesn't exist!");
		return 1;
	}

	if(!IsUsersCommand(cmdname, id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You can only delete the commands that you created!");
		return 1;
	}

	DeleteCommand(cmdname);

	@discord() SendMsg(channel, ""d_reply" **COMMAND DELETED** • Your custom command is successfully deleted!");
	
	return 1;
}

@discord() command:botsetup(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bot Setup__**", "\
		"d_heart" __Welcome to a bot setup guide and FAQ-s.__\n\
		"d_reply" • This bot doesn't require many setup when it gets invited to the server, \
		in fact, all of the setup is optional. If you are interested setting up the bot, \
		you can use the `"BOT_PREFIX"serverconfig` command.\n\n\
		"d_reply" • You can modify your user settings with the `"BOT_PREFIX"userconfig` command.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), ""delimiterlol" **TIP** • Thanks for bothering inviting **"BOT_NAME"** to your server.");
	return 1;
}

@discord() command:report(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new cid[DCC_ID_SIZE];
	DCC_GetChannelId(channel, cid);

	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);
	SetUserReportChannel(id, cid);
	@discord() SendMsg(channel, ""d_reply" **REPORT FORM LOADED** • <@%s> successfully entered a report mode.", id);

	SetReportQuestion(id, "1");

	@discord() SendMsg(channel, "**__REPORT PANEL__**\n**Question 1** • <@%s>\n\n"d_arrow"*`What are you reporting? Please describe.`*\n\n", id);
	@discord() SendInfo(channel, "Please reply to the question above with the proper answer.");
	return 1;
}

@discord() command:errors(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	@discord() SendMsg(channel, ""delimiterlol" **INFO** • `No errors found.`\n"botpfp" **NOTE** • This system is currently under a beta phase!");
	return 1;
}

//https://www.google.com/search?q=KEYWORDS+OF+A+SEARCH
@discord() command:search(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new query[256];

	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetInvData(id, "Gamepad") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	if(sscanf(params, "s[256]", query))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"search [search text]`");
		return 1;
	}

	for(new i; i < strlen(query); i++)
	{
		if(query[i] == ' ') query[i] = '+';
	}

	@discord() SendMsg(channel, ""d_reply" **SEARCHING FINISHED** • Your search results: \nhttps://www.google.com/search?q=%s\n`%i results in 0,%is`", query, random(100000), random(10));
	return 1;
}

@discord() command:say(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new t[256];

	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetInvData(id, "Gamepad") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	if(sscanf(params, "s[256]", t))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"say [text]`");
		return 1;
	}

	DCC_DeleteMessage(message);

	@discord() SendMsg(channel, "%s", t);
	return 1;
}

@discord() command:joke(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);


	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetInvData(id, "Gamepad") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	DCC_SendChannelMessage(channel, DiplomyJokes[random(sizeof DiplomyJokes)]);
	return 1;
}

/*
@discord() command:juan(@discord() cmd_params)
{
	new DCC_Channel:c;
	DCC_GetMessageChannel(message,c);
	@discord() SendMsg(c,"https://cdn.discordapp.com/attachments/795025965985693716/959382383034007592/IMG_4433.jpg");
	return 1;
}
*/
@discord() command:website(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" • Website__**", "\
		"d_reply" • Visit our community on the web! Access our site by clicking this [link](https://bracetm.000webhostapp.com/d_damnlarper.html)!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));


	return 1;
}

@discord() command:version(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	@discord() SendMsg(channel, "• **Last Update**\n"d_reply"Script was (re)compiled last time at `%s-%s`.\n• **Script Version**\n"d_reply"Bot code version: `"BOT_VERSION"`",__date, __time);

	return 1;
}

@discord() command:bankacc(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(HasBankAccount(id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You already have opened a bank account.");
		return 1;
	}

	OpenBankAccount(id);

	@discord() SendMsg(channel, ""d_reply" **BANK** • You successfully opened a bank account.");

	return 1;
}



@discord() command:afk(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new afkstatus[256];

	if(sscanf(params, "s[256]", afkstatus))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"afk [AFK status text]`");
		return 1;
	}

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	SetAFK(id, afkstatus);

	@discord() SendMsg(channel, ""d_reply" • Alright, <@%s> - you're now AFK.", id);

	return 1;
}

@discord() command:settings(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new option[30];
	
	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	if(sscanf(params, "s[30]", option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bot Settings Panel__**", ""delimiterlol" • These are the options used to manipulate with bot settings.\n\
		Usage: `"BOT_PREFIX"settings [option]`\n\
		"delimiterlol" **NOTE** • If you want to see whose settings are on or off, please use `"BOT_PREFIX"settings view`.\n\n\
		**__Setting Options__**\n\
		**`logs`**\n"d_reply"Enable or disable the log system.\n\
		**`gmc`**\n"d_reply"Activate or deactivate GM counting.\n\
		**`eco`**\n"d_reply"Toggle economy commands on or off.\n\
		**`mod`**\n"d_reply"Toggle commands such as `"BOT_PREFIX"kick`, `"BOT_PREFIX"warn` on or off.\n\
		**`count`**\n"d_reply"Enable or disable the counting system.\n\
		**`ccmd`**\n"d_reply"Enable or disable custom commands.\n\
		**`ac`**\n"d_reply"Activate or deactivate anti-raid system.\n\
		**`rp`**\n"d_reply"Activate or deactivate a roleplay system.", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "view"))
	{
		@discord() SendMsg(channel, "**__Bot Settings Panel__**\n"delimiterlol" • This is settings configuration preview.\n\n\t**`logs`**\t\t• %s\n\t**`gmc`**\t\t• %s\n\t**`eco`**\t\t• %s\n\t**`mod`**\t\t• %s\n\t**`count`**\t\t• %s\n\t**`ccmd`**\t\t• %s\n\t**`ac`**\t\t• %s\n\t**`rp`**\t\t• %s", settings[log] ? d_yes : d_no, settings[gmc] ? d_yes : d_no, settings[eco] ? d_yes : d_no, settings[mod] ? d_yes : d_no, settings[cnt] ? d_yes : d_no, settings[ccmd] ? d_yes : d_no,settings[ac] ? d_yes : d_no,settings[rp] ? d_yes : d_no);
		return 1;
	}

	if(!strcmp(option, "ccmd"))
	{
		modcheck;

		if(settings[ccmd] == 1)
		{
			settings[ccmd] = 0;
			@discord() SendMsg(channel, ""d_reply" • Custom commands system has been disabled.");
			return 1;
		}
		if(settings[ccmd] == 0)
		{
			settings[ccmd] = 1;
			@discord() SendMsg(channel, ""d_reply" • Custom commands system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "logs"))
	{
		modcheck;

		if(settings[log] == 1)
		{
			settings[log] = 0;
			@discord() SendMsg(channel, ""d_reply" • Log system has been disabled.");
			return 1;
		}
		if(settings[log] == 0)
		{
			settings[log] = 1;
			@discord() SendMsg(channel, ""d_reply" • Log system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "eco"))
	{
		modcheck;

		if(settings[eco] == 1)
		{
			settings[eco] = 0;
			@discord() SendMsg(channel, ""d_reply" • Economy commands have been disabled.");
			return 1;
		}
		if(settings[eco] == 0)
		{
			settings[eco] = 1;
			@discord() SendMsg(channel, ""d_reply" • Economy commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "count"))
	{
		modcheck;

		if(settings[cnt] == 1)
		{
			settings[cnt] = 0;
			@discord() SendMsg(channel, ""d_reply" • Counting system has been disabled.");
			return 1;
		}
		if(settings[cnt] == 0)
		{
			settings[cnt] = 1;
			@discord() SendMsg(channel, ""d_reply" • Counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "gmc"))
	{
		modcheck;

		if(settings[gmc] == 1)
		{
			settings[gmc] = 0;
			@discord() SendMsg(channel, ""d_reply" • GM counting system has been disabled.");
			return 1;
		}
		if(settings[gmc] == 0)
		{
			settings[gmc] = 1;
			@discord() SendMsg(channel, ""d_reply" • GM counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "mod"))
	{
		modcheck;

		if(settings[mod] == 1)
		{
			settings[mod] = 0;
			@discord() SendMsg(channel, ""d_reply" • Moderation commands have been disabled.");
			return 1;
		}
		if(settings[mod] == 0)
		{
			settings[mod] = 1;
			@discord() SendMsg(channel, ""d_reply" • Moderation commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "ac"))
	{
		modcheck;

		if(settings[ac] == 1)
		{
			settings[ac] = 0;
			@discord() SendMsg(channel, ""d_reply" • Anti-raid has been disabled.");
			return 1;
		}
		if(settings[ac] == 0)
		{
			settings[ac] = 1;
			@discord() SendMsg(channel, ""d_reply" • Anti-raid has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "rp"))
	{
		modcheck;

		if(settings[rp] == 1)
		{
			settings[rp] = 0;
			@discord() SendMsg(channel, ""d_reply" • RolePlay system has been disabled.");
			return 1;
		}
		if(settings[rp] == 0)
		{
			settings[rp] = 1;
			@discord() SendMsg(channel, ""d_reply" • RolePlay system has been enabled.");
			return 1;
		}
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN OPTION** • Invalid option provided, use `"BOT_PREFIX"settings` to view a list of available options.");
	}
	return 1;
}

// Moderation:

@discord() command:saveset(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	SaveSettings();
	@discord() SendMsg(channel, ""d_reply" **SETTINGS SAVED** • Current bot settings saved successfully.");
	return 1;
}

@discord() command:serverconfig(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	if(IsUserGuildOwner(guild, id) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `SERVER_OWNER` permission!");
		return 1;
	}

	new option[30],value[DCC_ID_SIZE+10];

	if(sscanf(params, "s[30]s[50]", option, value))
	{
		//@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"serverconfig [option]`");
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Server Configuration__**", ""delimiterlol" • Setup how "BOT_NAME" will work in your server!\n\
		Usage: `"BOT_PREFIX"serverconfig [option] [value]`\n\
		Use `"BOT_PREFIX"serverconfig view cfg` to view current configuration.\n\n\
		**__Options__**\n\
		**`logchannel`**\n"d_reply"A channel in which "BOT_NAME" will log things!\n\
		**`countchannel`**\n"d_reply"A channel where "BOT_NAME" will do a counting game!\n\
		**`airportchannel`**\n"d_reply"A channel where "BOT_NAME" will log who joins and leaves this guild!\n\
		**`verification`**\n"d_reply"Enable the "BOT_NAME" verification system in this guild! Use `true` as a value to enable it, and `false` to disable it. It is recommended not to turn this on unless you've set the `verificationchannel` up.\n\
		**`verificationchannel`**\n"d_reply"A channel where "BOT_NAME" will verify people!\n\
		**`levelchannel`**\n"d_reply"A channel where "BOT_NAME" will log member level-ups!\n\
		**`botannouncements`** "d_beta"\n"d_reply"A channel where "BOT_NAME" will send announcements from the developer team!\n\
		**`securitysys`**\n"d_reply"Used to toggle the "BOT_NAME" security system! Use `true` to turn it on; and `false` to turn it off.\n\
		**`bumpchannel`** "d_beta"\n"d_reply"A channel where "BOT_NAME" will perform the bump system activites.\n\
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
		@discord() SendMsg(channel, "**Current Server Configuration**\n\n`logchannel` • <#%s>\n`countchannel` • <#%s>\n`airportchannel` • <#%s>\n`verification` • `%s`\n`verificationchannel` • <#%s>\n`levelchannel` • <#%s>\n`botannouncements` • <#%s>\n`securitysys` • `%s`\n`bumpchannel` • <#%s>\n",GetGuildLogChannel(guild),GetGuildCountChannel(guild),GetGuildAirportChannel(guild),GetGuildVerification(guild) ? "true" : "false",GetGuildVerificationChannel(guild),GetGuildLevelChannel(guild),GetGuildAnnouncementChannel(guild),GetGuildSecurity(guild) ? "true" : "false",GetGuildBumpChannel(guild));
		return 1;
	}

	if(!strcmp(option, "logchannel"))
	{
		channelcheck(value);

		SetGuildLogChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "countchannel"))
	{
		channelcheck(value);

		SetGuildCountChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "airportchannel"))
	{
		channelcheck(value);

		SetGuildAirportChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "verification"))
	{
		if(!strcmp(GetGuildVerificationChannel(guild), "Unknown"))
		{
			@discord() SendInfo(channel, "You need to setup the `verificationchannel` option first!");
			return 1;
		}
		if(!strcmp(value, "true"))
		{
			SetGuildVerification(guild, 1);

			@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		if(!strcmp(value, "false"))
		{
			SetGuildVerification(guild, 0);

			@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		@discord() SendMsg(channel, ""d_reply" **WRONG VALUE** • Wrong value for option `%s` was given!\nPlease try again with either `true` or `false`!\n\nGiven value: `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "verificationchannel"))
	{
		channelcheck(value);

		SetGuildVerificationChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "botannouncements"))
	{
		channelcheck(value);

		SetGuildAnnouncementChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "levelchannel"))
	{
		channelcheck(value);

		SetGuildLevelChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "securitysys"))
	{
		if(!strcmp(value, "true"))
		{
			SetGuildSecurity(guild, 1);

			@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		if(!strcmp(value, "false"))
		{
			SetGuildSecurity(guild, 0);

			@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
			return 1;
		}
		@discord() SendMsg(channel, ""d_reply" **WRONG VALUE** • Wrong value for option `%s` was given!\nPlease try again with either `true` or `false`!\n\nGiven value: `%s`.", option, value);
		return 1;
	}
	if(!strcmp(option, "bumpchannel"))
	{
		channelcheck(value);

		SetGuildBumpChannel(guild, value);

		@discord() SendMsg(channel, ""d_reply" **CONFIGURATION UPDATED** • Value for option `%s` was successfully changed to `%s`.", option, value);
		return 1;
	}
	
	@discord() SendInfo(channel, "Something went wrong! Try again.");
	return 1;
}

@discord() command:ban(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	if(DCC_HasGuildMemberPermission(guild, author, DCC_PERMISSION_BAN_MEMBERS) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `BAN_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[50]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"ban [user ID or user mention]`");
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


	DCC_CreateGuildMemberBan(guild, 
		DCC_FindUserById(user), 
		""BOT_NAME" • Banned with a ban command.");

	@discord() SendMsg(channel, ""d_reply" **BANNED** • <@%s> was banned successfully.\n\n"delimiterlol" **TIP** • If the ban didn't work, simply try again! Due to some Discord's limitations, you are unable to ban two users in a short period of time.", user);

	//@discord() SendMsg(bankicklog, "<@%s> was **banned** by <@%s>.\n\n"delimiterlol" **TIP** • If the ban didn't work, simply try again! Due to some Discord's limitations, you are unable to ban two users in a short period of time.", user, id);

	return 1;
}

@discord() command:unban(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	if(DCC_HasGuildMemberPermission(guild, author, DCC_PERMISSION_BAN_MEMBERS) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `BAN_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"unban [user ID or user mention]`");
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

	DCC_RemoveGuildMemberBan(guild, DCC_FindUserById(user));

	@discord() SendMsg(channel, ""d_reply" **UNBANNED** • <@%s> was unbanned successfully.", user);

	return 1;
}

@discord() command:roleall(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	if(DCC_HasGuildMemberPermission(guild, author, DCC_PERMISSION_MANAGE_ROLES) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `MANAGE_ROLES` permission!");
		return 1;
	}

	new roleid[DCC_ID_SIZE+10];

	if(sscanf(params, "s[50]", roleid))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"roleall [role ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(roleid); i++)
	{
		if(roleid[i] == '<') strdel(roleid, i, i+1);
		if(roleid[i] == '@') strdel(roleid, i, i+1);
		if(roleid[i] == '>') strdel(roleid, i, i+1);
		if(roleid[i] == '!') strdel(roleid, i, i+1);
		if(roleid[i] == '\32') strdel(roleid, i, i+1);
		if(roleid[i] == '&') strdel(roleid, i, i+1);
	}

	rolecheck(roleid);

	new membercount;
	DCC_GetGuildMemberCount(guild, membercount);

	@discord() SendMsg(channel, ""d_reply" **PROCCESS STARTED** • %i users will be given a <@&%s> role in `%i` seconds!", membercount, roleid, membercount);

	for (new i; i != membercount; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(guild, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    //DCC_GetUserId(user, id);

	   	DCC_AddGuildMemberRole(guild, user, DCC_FindRoleById(roleid));

	}
	@discord() SendMsg(channel, ""d_reply" **USERS ROLED** • %i users were given a <@&%s> role.", membercount, roleid);	
	return 1;
}

@discord() command:deroleall(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	if(DCC_HasGuildMemberPermission(guild, author, DCC_PERMISSION_MANAGE_ROLES) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `MANAGE_ROLES` permission!");
		return 1;
	}

	new roleid[DCC_ID_SIZE+10];

	if(sscanf(params, "s[50]", roleid))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"deroleall [role ID or user mention]`");
		return 1;
	}

	for(new i; i <= strlen(roleid); i++)
	{
		if(roleid[i] == '<') strdel(roleid, i, i+1);
		if(roleid[i] == '@') strdel(roleid, i, i+1);
		if(roleid[i] == '>') strdel(roleid, i, i+1);
		if(roleid[i] == '!') strdel(roleid, i, i+1);
		if(roleid[i] == '\32') strdel(roleid, i, i+1);
		if(roleid[i] == '&') strdel(roleid, i, i+1);
	}

	rolecheck(roleid);

	new membercount;
	DCC_GetGuildMemberCount(guild, membercount);

	@discord() SendMsg(channel, ""d_reply" **PROCCESS STARTED** • %i users will be removed from a <@&%s> role in `%i` seconds!", membercount, roleid, membercount);

	for (new i; i != membercount; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(guild, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    //DCC_GetUserId(user, id);

	   	DCC_RemoveGuildMemberRole(guild, user, DCC_FindRoleById(roleid));

	}
	@discord() SendMsg(channel, ""d_reply" **USERS DEROLED** • %i users were removed from a <@&%s> role.", membercount, roleid);	
	return 1;
}

@discord() command:kick(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SettingsCheck(mod);

	if(DCC_HasGuildMemberPermission(guild, author, DCC_PERMISSION_KICK_MEMBERS) == false)
	{
		@discord() SendMsg(channel, ""d_reply" **AUTHORIZATION ERROR** • You do not have a `KICK_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"kick [user ID or user mention]`");
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


	@discord() SendMsg(channel,""d_reply" **KICKED** • <@%s> was kicked successfully.", user);

	DCC_RemoveGuildMember(guild, DCC_FindUserById(user));

	//@discord() SendMsg(bankicklog, "<@%s> was **kicked** by <@%s>.", user, id);
	return 1;
}



@discord() command:gmexample(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	@discord() SendMsg(channel, ""d_reply" **__GM Example__**\n\
		```\n\
		[pol]\n\
		https://discord.com/32452353252345/2352345234523\n\
		WIWTK - What happened?\n\
		You successfully won the September elections!\n\
		@Requester\n```");

	return 1;
}

@discord() command:gmlvl(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	/*@discord() SendMsg(channel, "**__Bot settings__**\n\n\
		"d_arrow"**`"BOT_PREFIX"logs`**\n"d_reply"Enable or disable the log system.\n\
		"d_arrow"**`"BOT_PREFIX"gmc`**\n"d_reply"Activate or deactivate GM counting.\n\
		"d_arrow"**`"BOT_PREFIX"eco`**\n"d_reply"Toggle economy commands on or off.");*/

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__INFORMATION ABOUT GM LEVELS__**", "**__GM Levels__**\n\n\
		1. `Easy` - GM for 1 post\n\
		2. `Subnormal` - GM for 2 posts\n\
		3. `Normal` - GM for 3 posts\n\
		4. `Medium` - GM for 4 posts\n\
		5. `Hard` - GM for 5 or more posts\n\n\
		"delimiterlol" **FACT** • GM leveling system has been recently updated with a new algorithm, \
		which scans the GM message and then estimates the level, regardless of the number of posts.", "","", col_embed, datetimelog, 
		"","","");

	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, ""delimiterlol" **INFO** • For more info, ask a bot mod.");
	return 1;
}

@discord() command:bal(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);


	@discord() SendMsg(channel, "**<@%s>**\n\n**Pocket Money**\n"d_reply"`%i` "d_coin"\n\n**Deposited Money**\n"d_reply"`%i` "d_coin"", id, GetData(id, "Balance"), GetData(id, "DepBalance"));

	return 1;
}

@discord() command:work(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "work", "Stop right there worker!");

	if(GetEnergy(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	if(GetData(id, "Balance") >= 3000 && GetInvData(id, "Wallet") == 0)
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • Your pocket is full of coins - there is no space left for more!\n\
			"delimiterlol" **TIP** • Buy a "d_wallet" | `Wallet` to get space for more coins.");
		return 1;
	}

	if(GetData(id, "Balance") >= 25000)
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • Your wallet is full of coins - there is no space left for more!\n\
			"delimiterlol" **TIP** • Use `"BOT_PREFIX"dep` to deposit your coins and free up space.");
		return 1;
	}

	new wage = random(10000);

	SetData(id, "Balance", GetData(id, "Balance") + wage);

	SetEnergy(id, GetEnergy(id) - 1);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **WORK FINISHED** • You successfully finished your shift and your boss gave you "d_coin" `%i`!", id, wage);

	return 1;
}



stock GetClaimedDaily(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/cdl_%s.ini", user);
	new strFromFile2[128];
	//format(strFromFile2, sizeof strFromFile2, "Unknown");
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);

		return strval(strFromFile2);
	}
	return 0;
}

stock SetClaimedDaily(const user[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/cdl_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetClaimedDay(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/cday_%s.ini", user);
	new strFromFile2[128];
	//format(strFromFile2, sizeof strFromFile2, "Unknown");
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);

		return strval(strFromFile2);
	}
	return 0;
}

stock SetClaimedDay(const user[], const value)
{
	new file_name[150], string[10];
	format(string, sizeof string, "%i", value);
	format(file_name, sizeof file_name,"data/cday_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

/*
new h,m,s;
getdate(h,m,s);
if((m > GetCommandUsedMin(id, "cmd")) || (m < GetCommandUsedMin(id, "cmd")))
{
	SetCommandUsed(id, "cmd", "0");
}

SetCommandUsed(id, "cmd", "1");

SetCommandUsedMin(id, "cmd", m);
*/

@discord() command:daily(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new y,m,d;
	getdate(y,m,d);

	if((d > GetClaimedDay(id)) || (d < GetClaimedDay(id)))
	{
		SetClaimedDaily(id, "0");
	}

	if(GetClaimedDaily(id) == 1)
	{
		@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **ALREADY CLAIMED** • You already collected your daily income!", id);
		return 1;
	}

	SetData(id, "Balance", GetData(id, "Balance") + 10000);

	SetClaimedDaily(id, "1");

	SetClaimedDay(id, d);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **DAILY INCOME CLAIMED** • You successfully claimed your daily "d_coin" `10000`! You'll be able to claim your next daily the next day!", id);
	return 1;
}

@discord() command:premiumdaily(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	premiumcheck(id);

	CommandCooldownDay(channel, id, "premiumdaily", "You can claim this command once a day, seems like a common sense.");

	SetData(id, "Balance", GetData(id, "Balance") + 100000);
	SaveCommonChest(id, GetCommonChest(id) + 5);
	SaveRareChest(id, GetRareChest(id) + 3);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **DAILY PREMIUM INCOME CLAIMED** • You successfully claimed your daily "d_coin" `100000`! You'll be able to claim your next daily the next day!", id);
	@discord() SendInfo(channel, "**<@%s>**\n\nYou also got a bonus of:\n\n5x "d_commonchest" | `Common Chest`\n3x "d_rarechest" | `Rare Chest`", id);
	return 1;
}

@discord() command:beg(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetAchievement(id, "Beggar") == 0)
	{
		@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Beggar** achievement and got 1x "d_commonchest" | `Common Chest` as a reward.", id);
		SaveCommonChest(id, GetCommonChest(id) + 1);
		SetAchievement(id, "Beggar");
	}

	CommandCooldownMin(channel, id, "beg", "Don't be such a beggar - wait a bit.");

	new money = random(1000);
	new rubies = random(5);
	new meat = random(10);

	SetData(id, "Balance", GetData(id, "Balance") + money);
	SetData(id, "Rubies", GetData(id, "Rubies") + rubies);
	SetData(id, "CookedMeat", GetData(id, "CookedMeat") + meat);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **BEGGING FINISHED** • You were begging for a while and got:\n\n%ix "d_coin" | `Coins`\n%ix "d_ruby" | `Rubies`\n%ix "d_cookedmeat" | `Cooked Meat`", id, money, rubies, meat);
	return 1;
}

@discord() command:dep(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new money[30];

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[30]", money))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"dep [amount of coins to deposit]`\n\
			> "delimiterlol" **TIP** • To deposit all of your coins, use `"BOT_PREFIX"dep all`.");
		return 1;
	}

	if(!HasBankAccount(id) && GetInvData(id, "Safe") == 0)
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You don't have a bank account or a safe to deposite your coins to.");
		return 1;
	}

	if(!strcmp(money, "all"))
	{
		SetData(id, "DepBalance", GetData(id, "DepBalance") + GetData(id, "Balance"));

		SetData(id, "Balance", 0);

		@discord() SendMsg(channel, ""d_reply" **DEPOSITED** • <@%s>, you successfully deposited all of your coins!", id);
		return 1;
	}

	if(strval(money) == 0)
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You deposited absolutely nothing!");
		return 1;
	}

	if(strval(money) > GetData(id, "Balance"))
	{
		@discord() SendMsg(channel, ""d_reply" **WORK MORE** • You don't have that much coins!");
		return 1;
	}

	SetData(id, "Balance", GetData(id, "Balance") - strval(money));

	SetData(id, "DepBalance", GetData(id, "DepBalance") + strval(money));

	@discord() SendMsg(channel, ""d_reply" **DEPOSITED** • <@%s>, you successfully deposited `%i` "BOT_NAME" coins! "d_coin"", id, strval(money));

	return 1;
}

/*
@discord() command:depall(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(!HasBankAccount(id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You don't have a bank account.");
		return 1;
	}

	SetData(id, "DepBalance", GetData(id, "DepBalance") + GetData(id, "Balance"));

	SetData(id, "Balance", 0);

	@discord() SendMsg(channel, ""d_reply" **DEPOSITED** • <@%s>, you successfully deposited all of your coins to your bank!", id, money);

	return 1;
}
*/
@discord() command:with(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new money;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "i", money))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"with [amount of coins to withdraw]`");
		return 1;
	}

	if(!HasBankAccount(id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You don't have a bank account.");
		return 1;
	}

	if(money > GetData(id, "DepBalance"))
	{
		@discord() SendMsg(channel, ""d_reply" **NOT ENOUGH MONEY** • You don't have that much coins in your bank!");
		return 1;
	}

	SetData(id, "Balance", GetData(id, "Balance") + money);

	SetData(id, "DepBalance", GetData(id, "DepBalance") - money);

	@discord() SendMsg(channel, ""d_reply" **WITHDREW** • <@%s>, you successfully withdrew `%i`"d_coin" from bank!", id, money);

	return 1;
}

@discord() command:rob(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new user[DCC_ID_SIZE + 10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"rob [user ID or user mention]`");
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

	CommandCooldownMin(channel, id, "rob", "Robbing continuously is really not a good idea!");

	if(!strcmp(user, id))
	{
		@discord() SendMsg(channel, ""d_reply" **WHAT?** • You cannot rob yourself!");
		return 1;
	}

	if(GetInvData(id, "Mask") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **YOU GOT CAUGHT** • You got caught and could not rob any money!");
		@discord() SendInfo(channel, "Buy a "d_mask" | `"BOT_NAME"-looking Mask` at the shop so you can hide yourself behind it!");
		@discord() SendDM(DCC_FindUserById(user), "**ROB ATTEMPTED** • <@%s> attempted to rob you but did not succeed!", id);
		return 1;
	}

	if(GetData(user, "Balance") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **POCKETS ARE EMPTY** • This player has got no coins for you!");
		@discord() SendDM(DCC_FindUserById(user), "**ROB FAIL** • <@%s> tried to rob you, but found out that you've got no money for him!", id);
		return 1;
	}

	if(GetData(user, "Balance") < 0)
	{
		@discord() SendMsg(channel, ""d_reply" **FAILED** • This guy is in crippling debts - you \
			were fined with `1000`"d_coin" because you tried to rob him.");
		SetData(id, "Balance", GetData(id, "Balance") - 1000);
		@discord() SendDM(DCC_FindUserById(user), "**ROB FAIL** • <@%s> tried to rob you, but found out that you've got no money for him!", id);
		return 1;
	}

	SetData(id, "Balance", GetData(id, "Balance") + GetData(user, "Balance"));

	@discord() SendMsg(channel, "<@%s>\n\n"d_reply" **ROB WAS SUCCESSFUL** • You successfully robbed <@%s> and took away all of his money (`%i`"d_coin").", id, user, GetData(user, "Balance"));

	SetData(user, "Balance", 0);

	@discord() SendDM(DCC_FindUserById(user), "**YOU'RE ROBBED** • <@%s> robbed you and took all of your wallet money!", id);

	return 1;
}

@discord() command:heist(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new user[DCC_ID_SIZE + 10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"heist [user ID or user mention]`");
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

	if(!strcmp(user, id))
	{
		@discord() SendMsg(channel, ""d_reply" **WHAT?** • You cannot rob yourself!");
		return 1;
	}

	if(GetInvData(id, "Laptop") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_laptop" | `Laptop` to do hacking stuff and perform a heist!");
		return 1;
	}

	CommandCooldownHr(channel, id, "heist", "You forgot your laptop's password, you will probably find where did you write it down later.");

	if(GetInvData(user, "Safe") == 1)
	{
		@discord() SendInfo(channel, "This guy got a safe with a passcode on it! No money for you today, I guess!");
		return 1;
	}

	if(GetData(user, "DepBalance") == 0 || GetData(user, "DepBalance") < 0)
	{
		@discord() SendMsg(channel, ""d_reply" **BANK ACCOUNT IS EMPTY** • This player has got no coins for you!");
		@discord() SendDM(DCC_FindUserById(user), "**HEIST FAIL** • <@%s> tried to rob you, but found out that you've got no money on your bank account!", id);
		return 1;
	}

	new money = random(GetData(user, "DepBalance"));

	SetData(user, "DepBalance", GetData(user, "DepBalance") - money);
	SetData(id, "DepBalance", GetData(id, "DepBalance") + money);

	@discord() SendMsg(channel, "<@%s>\n\n"d_reply" **HEIST WAS SUCCESSFUL** • You successfully stole "d_coin" %i from <@%s>'s bank account!", id, money, user);

	@discord() SendDM(DCC_FindUserById(user), "**YOU'RE ROBBED** • <@%s>'s heist succeeded! He stole "d_coin" %i from your bank account!", id, money);

	return 1;
}

//PETS

@discord() command:petshop(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Pet Shop__**", 
		""d_reply" **PET SHOP** • This is the list of pets you can purchase.\n\n\
		"d_parrot" • **Parrot** (*ID: `1`*)\n\
		"d_reply" Price: "d_coin"`5000`\n\n\
		"d_dog" • **Dog** (*ID: `2`*)\n\
		"d_reply" Price: "d_coin"`15000`\n\n\
		"d_cat" • **Cat** (*ID: `3`*)\n\
		"d_reply" Price: "d_coin"`15000`\n\n\
		"d_pepefrog" • **Pepe Frog** (*ID: `4`*) "d_premium"\n\
		"d_reply" Price: "d_coin"`20000`\n\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

stock GetPet(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"pets/pet_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SetPet(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"pets/pet_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetPetName(const i[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"pets/name_%s.ini", i);
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

stock SetPetName(const i[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"pets/name_%s.ini",i);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetPetEnergy(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"pets/energy_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SetPetEnergy(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"pets/energy_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

@discord() command:buypet(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id, user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	if(GetPet(user) != 0)
	{
		@discord() SendMsg(channel, ""d_reply" **ONE IS ENOUGH** • You can't have more pets than one!");
		return 1;
	}

	if(sscanf(params, "i", id))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"buypet [pet ID]`");
		return 1;
	}


	if(id == 1)
	{
		if(GetData(user, "Balance") < 5000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		SetPet(user, 1);
		SetPetName(user, "Unnamed Pet");
		SetPetEnergy(user, d_max_bar_points);
		SetData(user, "Balance", GetData(user, "Balance") - 15000);
		@discord() SendMsg(channel, ""d_reply" **PET BOUGHT** • You successfully bought a "d_parrot" | `Parrot` pet for "d_coin" `15000`!");
		@discord() SendInfo(channel, "To view your pet's statistics, please use `"BOT_PREFIX"petstats`.");
		
		if(GetAchievement(user, "PetOwner") == 0)
		{
			@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Pet Owner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", user);
			SaveRareChest(user, GetRareChest(user) + 1);
			SetAchievement(user, "PetOwner");
		}
		return 1;
	}
	if(id == 2)
	{
		if(GetData(user, "Balance") < 15000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		SetPet(user, 2);
		SetPetName(user, "Unnamed Pet");
		SetPetEnergy(user, d_max_bar_points);
		SetData(user, "Balance", GetData(user, "Balance") - 15000);
		@discord() SendMsg(channel, ""d_reply" **PET BOUGHT** • You successfully bought a "d_dog" | `Dog` pet for "d_coin" `15000`!");
		@discord() SendInfo(channel, "To view your pet's statistics, please use `"BOT_PREFIX"petstats`.");
		
		if(GetAchievement(user, "PetOwner") == 0)
		{
			@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Pet Owner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", user);
			SaveRareChest(user, GetRareChest(user) + 1);
			SetAchievement(user, "PetOwner");
		}
		return 1;
	}
	if(id == 3)
	{
		if(GetData(user, "Balance") < 15000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		SetPet(user, 3);
		SetPetName(user, "Unnamed Pet");
		SetPetEnergy(user, d_max_bar_points);
		SetData(user, "Balance", GetData(user, "Balance") - 15000);
		@discord() SendMsg(channel, ""d_reply" **PET BOUGHT** • You successfully bought a "d_cat" | `Cat` pet for "d_coin" `15000`!");
		@discord() SendInfo(channel, "To view your pet's statistics, please use `"BOT_PREFIX"petstats`.");
		
		if(GetAchievement(user, "PetOwner") == 0)
		{
			@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Pet Owner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", user);
			SaveRareChest(user, GetRareChest(user) + 1);
			SetAchievement(user, "PetOwner");
		}
		return 1;
	}
	if(id == 4)
	{
		premiumcheck(user);
		if(GetData(user, "Balance") < 20000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		SetPet(user, 4);
		SetPetName(user, "Unnamed Pet");
		SetPetEnergy(user, d_max_bar_points);
		SetData(user, "Balance", GetData(user, "Balance") - 20000);
		@discord() SendMsg(channel, ""d_reply" **PET BOUGHT** • You successfully bought a "d_pepefrog" | `Pepe Frog` pet for "d_coin" `20000`!");
		@discord() SendInfo(channel, "To view your pet's statistics, please use `"BOT_PREFIX"petstats`.");
		
		if(GetAchievement(user, "PetOwner") == 0)
		{
			@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Pet Owner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", user);
			SaveRareChest(user, GetRareChest(user) + 1);
			SetAchievement(user, "PetOwner");
		}
		return 1;
	}


	@discord() SendMsg(channel, ""d_reply" **ERROR** • Wrong pet ID was given, please recheck the shop!");

	return 1;
}

@discord() command:sellpet(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	if(GetPet(user) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **NO PETS** • You are already lonely!");
		return 1;
	}


	SetPet(user, 0);

	new payout = random(1000);

	@discord() SendMsg(channel, ""d_reply" **BYE!** • Your pet could not be happier to run away! **You can buy another one or stay lonely.**\n\nBy the way, you got "d_coin" `%i` for your pet.", payout);

	SetData(user, "Balance", GetData(user, "Balance") + payout);

	return 1;
}

@discord() command:petstats(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetPet(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **ERROR** • You do not own a pet!");
		return 1;
	}

	new stats[2048];

	new pettype[100];

	if(GetPet(id) == 1)
	{
		format(pettype, sizeof pettype, ""d_parrot" | `Parrot`");
	}
	if(GetPet(id) == 2)
	{
		format(pettype, sizeof pettype, ""d_dog" | `Dog`");
	}
	if(GetPet(id) == 3)
	{
		format(pettype, sizeof pettype, ""d_cat" | `Cat`");
	}
	if(GetPet(id) == 4)
	{
		format(pettype, sizeof pettype, ""d_pepefrog" | `Pepe Frog`");
	}
	
	format(stats, sizeof stats, "**Pet's Name**\n\
		"d_reply" `%s`\n\n\
		**Pet Type**\n\
		"d_reply" %s\n\n\
		**Pet's Energy**\n\
		"d_reply" %s",
		GetPetName(id),
		pettype,
		GenerateBar(GetPetEnergy(id)));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Pet's Statistics__**", stats, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

@discord() command:namepet(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new name[100];

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	if(sscanf(params, "s[100]", name))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"namepet [pet name]`");
		return 1;
	}

	SetPetName(id, name);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Pet Name Updated__**", ""d_reply" **PET RENAMED** • Your pet was renamed!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));	

	return 1;
}

@discord() command:feedpet(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	if(GetPet(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **ERROR** • You can't feed your imaginary friends - but you can buy a pet! Use `"BOT_PREFIX"buypet`.");
		return 1;
	}

	if(GetAchievement(id, "PetOwner") == 0)
	{
		@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Pet Owner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", id);
		SaveRareChest(id, GetRareChest(id) + 1);
		SetAchievement(id, "PetOwner");
	}

	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Eat Command__**", ""delimiterlol" • You can feed your pet with food and increase its energy.\n\
		Usage: `"BOT_PREFIX"feedpet [item] [quantity]`\n\n\
		**__Items__**\n\
		**`meat`**\n"d_reply"Feed your pet with cooked meat!\n\
		**`fruits`**\n"d_reply"Feed your pet with fruits!\n\
		**`fish`**\n"d_reply"Feed your pet with cooked fish!\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **WHY AND HOW** • You can't use zero as quantity, sir.");
		return 1;
	}

	if(!strcmp(item, "meat"))
	{
		if(GetData(id, "CookedMeat") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_cookedmeat" | `Cooked Meat`.");
			return 1;
		}
		if(GetPetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not hungry at all! Its energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetPetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not that hungry! You need to give him %ix "d_cookedmeat" | `Cooked Meat` to fill up its energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "CookedMeat", GetData(id, "CookedMeat") - quantity);
		SetPetEnergy(id, GetPetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **DONE** • Your pet ate %ix "d_cookedmeat" | `Cooked Meat`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your pet's **energy** by the amount of food you gave him!");
		return 1;
	}
	if(!strcmp(item, "fruits"))
	{
		if(GetData(id, "CookedMeat") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_fruits" | `Fruits`.");
			return 1;
		}
		if(GetPetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not hungry at all! Its energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetPetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not that hungry! You need to give him %ix "d_fruits" | `Fruits` to fill up its energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "Fruits", GetData(id, "Fruits") - quantity);
		SetPetEnergy(id, GetPetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **DONE** • Your pet ate %ix "d_fruits" | `Fruits`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your pet's **energy** by the amount of food you gave him!");
		return 1;
	}
	if(!strcmp(item, "fish"))
	{
		if(GetData(id, "CookedFish") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_cookedfish" | `Cooked Fish`.");
			return 1;
		}
		if(GetPetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not hungry at all! Its energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetPetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • Your pet is not that hungry! You need to give him %ix "d_cookedfish" | `Cooked Fish` to fill up its energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "CookedFish", GetData(id, "CookedFish") - quantity);
		SetPetEnergy(id, GetPetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **DONE** • Your pet ate %ix "d_cookedfish" | `Cooked Fish`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your pet's **energy** by the amount of food you gave him!");
		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **HOW ABOUT NO?** • You can't give that to your pet!");
		@discord() SendInfo(channel, "Use `"BOT_PREFIX"feedpet` to view a list of available items.");
	}
	return 1;
}

//RP

@discord() command:shop(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new page;
	if(sscanf(params, "i", page))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"shop [shop page <1, 2>]`");
		return 1;
	}

	if(page == 1)
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Shop__**",
			""d_reply" **SHOP** • This is the list of items you can purchase.\n\n\
			"d_phone" • **Phone** (*ID: `1`*)\n\
			"d_reply" Price: "d_coin"`12000`\n\n\
			"d_gamepad" • **Gamepad** (*ID: `2`*)\n\
			"d_reply" Price: "d_coin"`20000`\n\n\
			"d_wallet" • **Wallet** (*ID: `3`*)\n\
			"d_reply" Price: "d_coin"`3000`\n\n\
			"d_pickaxe" • **Pickaxe** (*ID: `4`*)\n\
			"d_reply" Price: "d_coin"`20000`\n\n\
			"d_furnace" • **Furnace** (*ID: `5`*)\n\
			"d_reply" Price: "d_ruby"`20`\n\n\
			"d_slingshot" • **Slingshot** (*ID: `6`*)\n\
			"d_reply" Price: "d_ruby"`15`\n\n\
			"d_mask" • **"BOT_NAME"-looking Mask** (*ID: `7`*)\n\
			"d_reply" Price: "d_ruby"`4`\n\n\
			"d_fishingrod" • **Fishing Rod** (*ID: `8`*)\n\
			"d_reply" Price: "d_coin"`1000`\n\n\
			"d_desk" • **Desk** (*ID: `9`*)\n\
			"d_reply" Price: "d_ruby"`10`\n\n\
			"d_axe" • **Axe** (*ID: `10`*)\n\
			"d_reply" Price: "d_coin"`8000`\n\n\
			\n**Page: 1**", 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""), GetMention(useridmention));
		return 1;
	}
	if(page == 2)
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Shop__**",
			""d_reply" **SHOP** • This is the list of items you can purchase.\n\n\
			"d_laptop" • **Laptop** (*ID: `11`*)\n\
			"d_reply" Price: "d_banknote"`25`\n\n\
			"d_safe" • **Safe** (*ID: `12`*)\n\
			"d_reply" Price: "d_banknote"`50`\n\n\
			"d_protectiveshield" • **Protective Shield** (*ID: `13`*)\n\
			"d_reply" Price: "d_ruby"`40`\n\n\
			"d_shovel" • **Shovel** (*ID: `14`*)\n\
			"d_reply" Price: "d_coin"`20000`\n\n\
			\n**Page: 2**", 
			"",
			"", col_embed, datetimelog, 
			"",
			"",""), GetMention(useridmention));
		return 1;
	}

	@discord() SendInfo(channel, "I don't have that much items to sell! **Please try again with a valid shop page ID.**");

	return 1;
}

@discord() command:buy(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);

	new id, user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	if(sscanf(params, "i", id))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"buy [item ID]`");
		return 1;
	}

	/*if(GetData(user, "Balance") < 0)
	{
		@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You can't buy anything if your balance is a negative number! Please withdraw some money first.");
		return 1;
	}*/

	if(id == 1)
	{
		if(GetData(user, "Balance") < 12000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Phone") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_phone" | `Phone`!");
			return 1;
		}
		SetInvData(user, "Phone");
		SetData(user, "Balance", GetData(user, "Balance") - 12000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_phone" | `Phone` for "d_coin" `12000`!");
		return 1;
	}
	if(id == 2)
	{
		if(GetData(user, "Balance") < 20000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Gamepad") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_gamepad" | `Gamepad`!");
			return 1;
		}
		SetInvData(user, "Gamepad");
		SetData(user, "Balance", GetData(user, "Balance") - 20000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_gamepad" | `Gamepad` for "d_coin" `20000`!");
		return 1;
	}

	if(id == 3)
	{
		if(GetData(user, "Balance") < 3000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Wallet") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_wallet" | `Wallet`!");
			return 1;
		}
		SetInvData(user, "Wallet");
		SetData(user, "Balance", GetData(user, "Balance") - 3000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_wallet" | `Wallet` for "d_coin" `3000`!");
		return 1;
	}

	if(id == 4)
	{
		if(GetData(user, "Balance") < 20000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Pickaxe") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_pickaxe" | `Pickaxe`!");
			return 1;
		}
		SetInvData(user, "Pickaxe");
		SetData(user, "Balance", GetData(user, "Balance") - 20000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_pickaxe" | `Pickaxe` for "d_coin" `20000`!");
		return 1;
	}
	if(id == 5)
	{
		if(GetData(user, "Rubies") < 20)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Furnace") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_furnace" | `Furnace`!");
			return 1;
		}
		SetInvData(user, "Furnace");
		SetData(user, "Rubies", GetData(user, "Rubies") - 20);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_furnace" | `Furnace` for "d_ruby" `20`!");
		return 1;
	}
	if(id == 6)
	{
		if(GetData(user, "Rubies") < 15)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Slingshot") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_slingshot" | `Slingshot`!");
			return 1;
		}
		SetInvData(user, "Slingshot");
		SetData(user, "Rubies", GetData(user, "Rubies") - 15);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_slingshot" | `Slingshot` for "d_ruby" `15`!");
		return 1;
	}
	if(id == 7)
	{
		if(GetData(user, "Rubies") < 4)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Mask") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_mask" | `"BOT_NAME"-looking Mask`!");
			return 1;
		}
		SetInvData(user, "Mask");
		SetData(user, "Rubies", GetData(user, "Rubies") - 4);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_mask" | `"BOT_NAME"-looking Mask` for "d_ruby" `4`!");
		return 1;
	}
	if(id == 8)
	{
		if(GetData(user, "Balance") < 1000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "FishingRod") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_fishingrod" | `Fishing Rod`!");
			return 1;
		}
		SetInvData(user, "FishingRod");
		SetData(user, "Balance", GetData(user, "Balance") - 1000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_fishingrod" | `Fishing Rod` for "d_coin" `1000`!");
		return 1;
	}
	if(id == 9)
	{
		if(GetData(user, "Rubies") < 10)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Desk") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_desk" | `Desk`!");
			return 1;
		}
		SetInvData(user, "Desk");
		SetData(user, "Rubies", GetData(user, "Rubies") - 10);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_desk" | `Desk` for "d_ruby" `10`!");
		return 1;
	}
	if(id == 10)
	{
		if(GetData(user, "Balance") < 8000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Axe") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_axe" | `Axe`!");
			return 1;
		}
		SetInvData(user, "Axe");
		SetData(user, "Balance", GetData(user, "Balance") - 8000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_axe" | `Axe` for "d_coin" `8000`!");
		return 1;
	}
	if(id == 11)
	{
		if(GetData(user, "Banknotes") < 25)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Laptop") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_laptop" | `Laptop`!");
			return 1;
		}
		SetInvData(user, "Laptop");
		SetData(user, "Banknotes", GetData(user, "Banknotes") - 25);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_laptop" | `Laptop` for "d_banknote" `25`!");
		return 1;
	}
	if(id == 12)
	{
		if(GetData(user, "Banknotes") < 50)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Safe") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_safe" | `Safe`!");
			return 1;
		}
		SetInvData(user, "Safe");
		SetData(user, "Banknotes", GetData(user, "Banknotes") - 50);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_safe" | `Safe` for "d_banknote" `50`!");
		@discord() SendInfo(channel, "Your coins will be now deposited to your safe instead of a bank! Now noone knows your safe passcode and won't be able to steal your deposited money!");
		return 1;
	}
	if(id == 13)
	{
		if(GetData(user, "Rubies") < 40)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "ProtectiveShield") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_protectiveshield" | `Protective Shield`!");
			return 1;
		}
		SetInvData(user, "ProtectiveShield");
		SetData(user, "Rubies", GetData(user, "Rubies") - 40);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_protectiveshield" | `Protective Shield` for "d_ruby" `40`!");
		@discord() SendInfo(channel, "Your coins will be now deposited to your safe instead of a bank! Now noone knows your safe passcode and won't be able to steal your deposited money!");
		return 1;
	}

	if(id == 14)
	{
		if(GetData(user, "Balance") < 20000)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetInvData(user, "Shovel") == 1)
		{
			@discord() SendMsg(channel, ""d_reply" **ITEM OWNED** • You already own a "d_shovel" | `Shovel`!");
			return 1;
		}
		SetInvData(user, "Shovel");
		SetData(user, "Balance", GetData(user, "Balance") - 20000);
		@discord() SendMsg(channel, ""d_reply" **ITEM BOUGHT** • You successfully bought a "d_shovel" | `Shovel` for "d_coin" `20000`!");
		return 1;
	}

	@discord() SendMsg(channel, ""d_reply" **ERROR** • Wrong item ID was given, please recheck the shop!");

	return 1;
}

stock GenerateInvString(const id[], type)
{
	new string[256];
	if(type == IST_GOLD)
	{
		format(string, sizeof string, ""d_reply" "d_gold" • **Gold**: %ix\n", GetData(id, "Gold"));
	}
	if(type == IST_RUBIES)
	{
		format(string, sizeof string, ""d_reply" "d_ruby" • **Rubies**: %ix\n", GetData(id, "Rubies"));
	}
	if(type == IST_RAWMEAT)
	{
		format(string, sizeof string, ""d_reply" "d_rawmeat" • **Raw Meat**: %ix\n", GetData(id, "RawMeat"));
	}
	if(type == IST_COOKEDMEAT)
	{
		format(string, sizeof string, ""d_reply" "d_cookedmeat" • **Cooked Meat**: %ix\n", GetData(id, "CookedMeat"));
	}
	if(type == IST_FRUITS)
	{
		format(string, sizeof string, ""d_reply" "d_fruits" • **Fruits**: %ix\n", GetData(id, "Fruits"));
	}
	if(type == IST_MEDICINE)
	{
		format(string, sizeof string, ""d_reply" "d_medicine" • **Medicine**: %ix\n", GetData(id, "Medicine"));
	}
	if(type == IST_RAWFISH)
	{
		format(string, sizeof string, ""d_reply" "d_rawfish" • **Raw Fish**: %ix\n", GetData(id, "RawFish"));
	}
	if(type == IST_COOKEDFISH)
	{
		format(string, sizeof string, ""d_reply" "d_cookedfish" • **Cooked Fish**: %ix\n", GetData(id, "CookedFish"));
	}
	if(type == IST_PLANKS)
	{
		format(string, sizeof string, ""d_reply" "d_planks" • **Planks**: %ix\n", GetData(id, "Planks"));
	}
	if(type == IST_PAPER)
	{
		format(string, sizeof string, ""d_reply" "d_paper" • **Paper**: %ix\n", GetData(id, "Paper"));
	}
	if(type == IST_BANKNOTE)
	{
		format(string, sizeof string, ""d_reply" "d_banknote" • **Banknotes**: %ix\n", GetData(id, "Banknotes"));
	}
	if(type == IST_COPPER)
	{
		format(string, sizeof string, ""d_reply" "d_copper" • **Copper**: %ix\n", GetData(id, "Copper"));
	}

	return string;
}




stock GenerateChestString(const id[], type)
{
	new string[256];
	if(type == CHEST_COMMON)
	{
		format(string, sizeof string, ""d_reply" "d_commonchest" • **Common Chest**: %ix\nChest ID: `1`\n\n", GetCommonChest(id));
	}
	if(type == CHEST_RARE)
	{
		format(string, sizeof string, ""d_reply" "d_rarechest" • **Rare Chest**: %ix\nChest ID: `2`\n\n", GetRareChest(id));
	}
	return string;
}

@discord() command:inv(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new inv[4096], invtype[30];
	
	if(sscanf(params, "s[30]", invtype))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Inventory Command__**", ""delimiterlol" • View your inventory.\n\
		Usage: `"BOT_PREFIX"inv [inventory type]`\n\n\
		**__Inventory Types__**\n\
		**`shopitems`**\n"d_reply"View the items you've bought from the shop!\n\
		**`otheritems`**\n"d_reply"View the items you've found or produced so far!\n\
		**`chests`**\n"d_reply"View the chests you obtained!\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(!strcmp(invtype, "shopitems"))
	{
		format(inv, sizeof inv, ""d_reply" **INVENTORY** • These are the items you've bought from the shop!\n\n\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		",
		GetInvData(id, "Phone") ? ""d_reply" "d_phone" • **Phone** (*ID: `1`*)\n" : "",
		GetInvData(id, "Gamepad") ? ""d_reply" "d_gamepad" • **Gamepad** (*ID: `2`*)\n" : "",
		GetInvData(id, "Wallet") ? ""d_reply" "d_wallet" • **Wallet** (*ID: `3`*)\n" : "",
		GetInvData(id, "Pickaxe") ? ""d_reply" "d_pickaxe" • **Pickaxe** (*ID: `4`*)\n" : "",
		GetInvData(id, "Furnace") ? ""d_reply" "d_furnace" • **Furnace** (*ID: `5`*)\n" : "",
		GetInvData(id, "Slingshot") ? ""d_reply" "d_slingshot" • **Slingshot** (*ID: `6`*)\n" : "",
		GetInvData(id, "Mask") ? ""d_reply" "d_mask" • **"BOT_NAME"-looking Mask** (*ID: `7`*)\n" : "",
		GetInvData(id, "FishingRod") ? ""d_reply" "d_fishingrod" • **Fishing Rod** (*ID: `8`*)\n" : "",
		GetInvData(id, "Desk") ? ""d_reply" "d_desk" • **Desk** (*ID: `9`*)\n" : "",
		GetInvData(id, "Axe") ? ""d_reply" "d_axe" • **Axe** (*ID: `10`*)\n" : "",
		GetInvData(id, "Laptop") ? ""d_reply" "d_laptop" • **Laptop** (*ID: `11`*)\n" : "",
		GetInvData(id, "Safe") ? ""d_reply" "d_safe" • **Safe** (*ID: `12`*)\n" : "",
		GetInvData(id, "ProtectiveShield") ? ""d_reply" "d_protectiveshield" • **Protective Shield** (*ID: `13`*)\n" : "",
		GetInvData(id, "Shovel") ? ""d_reply" "d_shovel" • **Shovel** (*ID: `14`*)\n" : ""
		);

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Shop Items Inventory__**", inv, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(invtype, "otheritems"))
	{
		format(inv, sizeof inv, ""d_reply" **INVENTORY** • These are the items that you've found or produced!\n\n\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		%s\
		",
		(GetData(id, "Gold") == 0) ? "" : GenerateInvString(id, IST_GOLD),
		
		(GetData(id, "Rubies") == 0) ? "" : GenerateInvString(id, IST_RUBIES),
		
		(GetData(id, "RawMeat") == 0) ? "" : GenerateInvString(id, IST_RAWMEAT),
		
		(GetData(id, "CookedMeat") == 0) ? "" : GenerateInvString(id, IST_COOKEDMEAT), 
		
		(GetData(id, "Fruits") == 0) ? "" : GenerateInvString(id, IST_FRUITS), 
		
		(GetData(id, "Medicine") == 0) ? "" : GenerateInvString(id, IST_MEDICINE), 
		
		(GetData(id, "RawFish") == 0) ? "" : GenerateInvString(id, IST_RAWFISH), 
		
		(GetData(id, "CookedFish") == 0) ? "" : GenerateInvString(id, IST_COOKEDFISH), 

		(GetData(id, "Planks") == 0) ? "" : GenerateInvString(id, IST_PLANKS), 
		
		(GetData(id, "Paper") == 0) ? "" : GenerateInvString(id, IST_PAPER), 
		
		(GetData(id, "Banknotes") == 0) ? "" : GenerateInvString(id, IST_BANKNOTE),

		(GetData(id, "Copper") == 0) ? "" : GenerateInvString(id, IST_COPPER));

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Found & Produced Items Inventory__**", inv, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(invtype, "chests"))
	{
		format(inv, sizeof inv, ""d_reply" **INVENTORY** • These are the chests you've obtained so far!\n\n\
		%s\
		%s\
		",
		(GetCommonChest(id) == 0) ? "" : GenerateChestString(id, CHEST_COMMON),
		(GetRareChest(id) == 0) ? "" : GenerateChestString(id, CHEST_RARE)
		);

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Chest Inventory__**", inv, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
		return 1;
	}

	@discord() SendInfo(channel, "Inventory with such name wasn't found! Use `"BOT_PREFIX"inv` to see available inventories!");

	return 1;
}
@discord() command:openchest(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new chestid;
	
	if(sscanf(params, "i", chestid))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"openchest [chest ID]`");
		return 1;
	}

	if(chestid == CHEST_COMMON)
	{
		if(GetCommonChest(id) == 0)
		{
			@discord() SendMsg(channel, ""d_reply" **NO CHESTS?** • You do not have any "d_commonchest" | `Common Chests`.");
			return 1;
		}
		SaveCommonChest(id, GetCommonChest(id) - 1);

		new money = random(1000) + 1, rubies = random(100) + 1, gold = random(500) + 1;

		SetData(id, "Balance", GetData(id, "Balance") + money);
		SetData(id, "Gold", GetData(id, "Gold") + gold);
		SetData(id, "Rubies", GetData(id, "Rubies") + rubies);  

		@discord() SendMsg(channel, "<@%s>\n\n"d_reply" **CHEST OPENED** • You opened 1x "d_commonchest" | `Common Chest` and got the following:\n\n%ix "d_coin" | `Coins`\n%ix "d_gold" | `Gold`\n%ix "d_ruby" | `Rubies`", id, money, gold, rubies);
		return 1;
	}
	if(chestid == CHEST_RARE)
	{
		if(GetRareChest(id) == 0)
		{
			@discord() SendMsg(channel, ""d_reply" **NO CHESTS?** • You do not have any "d_rarechest" | `Rare Chests`.");
			return 1;
		}
		SaveRareChest(id, GetRareChest(id) - 1);

		new money = random(1000) + 1, banknotes = random(5) + 1, gold = random(500) + 1;

		SetData(id, "Balance", GetData(id, "Balance") + money);
		SetData(id, "Gold", GetData(id, "Gold") + gold);
		SetData(id, "Banknotes", GetData(id, "Banknotes") + banknotes);  

		@discord() SendMsg(channel, "<@%s>\n\n"d_reply" **CHEST OPENED** • You opened 1x "d_rarechest" | `Rare Chest` and got the following:\n\n%ix "d_coin" | `Coins`\n%ix "d_gold" | `Gold`\n%ix "d_banknote" | `Banknotes`", id, money, gold, banknotes);
		return 1;
	}
	@discord() SendInfo(channel, "I do not know what chest is that! You possibly gave me the wrong ID.");
	return 1;
}

@discord() command:mine(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "mine", "Slow down your demands miner!");

	if(GetInvData(id, "Pickaxe") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_pickaxe" | `Pickaxe` to go mining!");
		return 1;
	}

	if(GetEnergy(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	if(GetAchievement(id, "Miner") == 0)
	{
		@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Miner** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", id);
		SaveRareChest(id, GetRareChest(id) + 1);
		SetAchievement(id, "Miner");
	}

	new rubies = random(5);
	new gold = random(5);

	if(rubies == 0 && gold == 0)
	{
		SetEnergy(id, GetEnergy(id) - 1);
		@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **MINING FINISHED** • You've been mining for a while, but you could not find anything!", id);
		return 1;
	}

	SetData(id, "Rubies", GetData(id, "Rubies") + rubies);
	SetData(id, "Gold", GetData(id, "Gold") + gold);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **MINING FINISHED** • You've been mining for a while, you found:\n\n%ix "d_ruby" | `Rubies`\n%ix "d_gold" | `Gold`", id, rubies, gold);
	SetEnergy(id, GetEnergy(id) - 1);

	if(GetPet(id) != 0)
	{
		if(GetPetEnergy(id) == 0)
		{
			@discord() SendInfo(channel, "Your pet is too tired to work and could not help you this time! Use `"BOT_PREFIX"feedpet`!");
			return 1;
		}
		rubies = random(5);
	 	gold = random(10);
		@discord() SendInfo(channel, "**<@%s>**\n\n"d_reply" **PET BONUS** • Your pet somehow managed to help you, he mined this for you:\n\n%ix "d_ruby" | `Rubies`\n%ix "d_gold" | `Gold`", id, rubies, gold);
		SetData(id, "Rubies", GetData(id, "Rubies") + rubies);
		SetData(id, "Gold", GetData(id, "Gold") + gold);
		SetPetEnergy(id, GetPetEnergy(id) - 1);
	}

	return 1;
}

@discord() command:chop(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "chop", "Chopping trees repeatedly is not cool.");

	if(GetInvData(id, "Axe") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_axe" | `Axe` to go chopping trees!");
		return 1;
	}

	if(GetEnergy(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	new planks = random(5) + 1;

	SetData(id, "Planks", GetData(id, "Planks") + planks);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **CHOPPING FINISHED** • You've been chopping in a forest for a while, you got:\n\n%ix "d_planks" | `Planks`", id, planks);
	SetEnergy(id, GetEnergy(id) - 1);

	if(GetPet(id) != 0)
	{
		if(GetPetEnergy(id) == 0)
		{
			@discord() SendInfo(channel, "Your pet is too tired to work and could not help you this time! Use `"BOT_PREFIX"feedpet`!");
			return 1;
		}
		planks = random(5);
		@discord() SendInfo(channel, "**<@%s>**\n\n"d_reply" **PET BONUS** • Your pet somehow managed to help you, he got this for you:\n\n%ix "d_planks" | `Planks`", id, planks);
		SetData(id, "Planks", GetData(id, "Planks") + planks);
		SetPetEnergy(id, GetPetEnergy(id) - 1);
	}

	return 1;
}

@discord() command:fish(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "fish", "Fish in the lake are scared now, please wait some time until you fish again!");

	if(GetInvData(id, "FishingRod") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_fishingrod" | `Fishing Rod` to go fishing!");
		return 1;
	}

	new fish = random(5);

	if(fish == 0)
	{
		@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **FISHING FINISHED** • You've been fishing for a while, but you could not get a bite from anything!", id);
		return 1;
	}

	SetData(id, "RawFish", GetData(id, "RawFish") + fish);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **FISHING FINISHED** • You've been fishing for a while, you found:\n\n%ix "d_rawfish" | `Raw Fish`", id, fish);
	
	if(GetPet(id) != 0)
	{
		if(GetPetEnergy(id) == 0)
		{
			@discord() SendInfo(channel, "Your pet is too tired to work and could not help you this time! Use `"BOT_PREFIX"feedpet`!");
			return 1;
		}
		fish = random(5);
		@discord() SendInfo(channel, "**<@%s>**\n\n"d_reply" **PET BONUS** • Your pet somehow managed to help you, he fished this for you:\n\n%ix "d_rawfish" | `Raw Fish`", id, fish);
		SetData(id, "RawFish", GetData(id, "RawFish") + fish);
		SetPetEnergy(id, GetPetEnergy(id) - 1);
	}

	return 1;
}

@discord() command:hunt(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "hunt", "Chill hunter! All of the animals in the forest are scared to go out of their homes, wait some time to hunt again...");

	if(GetInvData(id, "Slingshot") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_slingshot" | `Slingshot` to go hunting!");
		return 1;
	}

	new rawmeat = random(5);
	new fruits = random(10);

	if(rawmeat == 0 && fruits == 0)
	{
		@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **HUNTING FINISHED** • You've been hunting for a while, but you could not find anything!", id);
		return 1;
	}

	SetData(id, "RawMeat", GetData(id, "RawMeat") + rawmeat);
	SetData(id, "Fruits", GetData(id, "Fruits") + fruits);

	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **HUNTING FINISHED** • You've been hunting and exploring for a while, you brought back:\n\n%ix "d_rawmeat" | `Raw Meat`\n%ix "d_fruits" | `Fruits`", id, rawmeat, fruits);

	if(GetPet(id) != 0)
	{
		if(GetPetEnergy(id) == 0)
		{
			@discord() SendInfo(channel, "Your pet is too tired to work and could not help you this time! Use `"BOT_PREFIX"feedpet`!");
			return 1;
		}
		rawmeat = random(5);
	 	fruits = random(10);
		@discord() SendInfo(channel, "**<@%s>**\n\n"d_reply" **PET BONUS** • Your pet somehow managed to help you, you got a bonus of:\n\n%ix "d_rawmeat" | `Raw Meat`\n%ix "d_fruits" | `Fruits`", id, rawmeat, fruits);
		SetData(id, "RawMeat", GetData(id, "RawMeat") + rawmeat);
		SetData(id, "Fruits", GetData(id, "Fruits") + fruits);
		SetPetEnergy(id, GetPetEnergy(id) - 1);
	}

	return 1;
}

@discord() command:melt(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	if(GetInvData(id, "Furnace") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_furnace" | `Furnace` to melt stuff!");
		return 1;
	}
	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Melt Command__**", ""delimiterlol" • You can melt stuff and get something else as a result.\n\
		Usage: `"BOT_PREFIX"melt [item] [quantity]`\n\n\
		**__Items__**\n\
		**`gold`**\n"d_reply"Melt gold and get coins!\n\
		**`meat`**\n"d_reply"Cook raw meat and make it edible!\n\
		**`fruits`**\n"d_reply"Melt fruits and get medicine!\n\
		**`fish`**\n"d_reply"Cook raw fish and make it edible!\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **WHY AND HOW** • You can't use zero as quantity, sir.");
		return 1;
	}

	if(!strcmp(item, "gold"))
	{
		if(GetData(id, "Gold") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have that much "d_gold" | `Gold`.");
			return 1;
		}
		SetData(id, "Balance", GetData(id, "Balance") + (quantity*5));
		SetData(id, "Gold", GetData(id, "Gold") - quantity);
		@discord() SendMsg(channel, ""d_reply" **ITEM MELTED** • You successfully melted %ix "d_gold" | `Gold` and got %ix "d_coin" | `Coins`!", quantity, quantity*5);
		return 1;
	}
	if(!strcmp(item, "meat"))
	{
		if(GetData(id, "RawMeat") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have that much "d_rawmeat" | `Raw Meat`.");
			return 1;
		}
		SetData(id, "CookedMeat", GetData(id, "CookedMeat") + quantity);
		SetData(id, "RawMeat", GetData(id, "RawMeat") - quantity);
		@discord() SendMsg(channel, ""d_reply" **ITEM COOKED** • You could not melt meat, but you could cook %ix "d_rawmeat" | `Raw Meat` and get %ix "d_cookedmeat" | `Cooked Meat`.", quantity, quantity);
		return 1;
	}
	if(!strcmp(item, "fruits"))
	{
		if(GetData(id, "Fruits") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have that much "d_fruits" | `Fruits`.");
			return 1;
		}
		SetData(id, "Medicine", GetData(id, "Medicine") + quantity);
		SetData(id, "Fruits", GetData(id, "Fruits") - quantity);
		@discord() SendMsg(channel, ""d_reply" **ITEM MELTED** • You melted %ix "d_fruits" | `Fruits` and got %ix "d_medicine" | `Medicine`.", quantity, quantity);
		return 1;
	}
	if(!strcmp(item, "fish"))
	{
		if(GetData(id, "RawFish") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **BALANCE ERROR** • You do not have that much "d_rawfish" | `Raw Fish`.");
			return 1;
		}
		SetData(id, "CookedFish", GetData(id, "CookedFish") + quantity);
		SetData(id, "RawFish", GetData(id, "RawFish") - quantity);
		@discord() SendMsg(channel, ""d_reply" **ITEM COOKED** • You could not melt fish, but you could cook %ix "d_rawfish" | `Raw Fish` and get %ix "d_cookedfish" | `Cooked Fish`.", quantity, quantity);
		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **WHAT** • You can't put that into furnace!");
		@discord() SendInfo(channel, "Use `"BOT_PREFIX"melt` to view a list of available items.");
	}
	return 1;
}

stock GetHealth(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"rp/hp_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SetHealth(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"rp/hp_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetEnergy(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"rp/energy_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SetEnergy(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"rp/energy_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GenerateBar(points = d_max_bar_points)
{
	new bar[512];
	if(points == 0)
	{
		format(bar, sizeof bar, ""d_emptybar1""d_emptybar2""d_emptybar2""d_emptybar2""d_emptybar3" • `0%%`");
	}
	if(points == 1)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_emptybar2""d_emptybar2""d_emptybar2""d_emptybar3" • `20%%`");
	}
	if(points == 2)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_emptybar2""d_emptybar2""d_emptybar3" • `40%%`");
	}
	if(points == 3)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_emptybar2""d_emptybar3" • `60%%`");
	}
	if(points == 4)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_fullbar2""d_emptybar3" • `80%%`");
	}
	if(points == 5)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_fullbar2""d_fullbar3" • `100%%`");
	}
	return bar;
}

@discord() command:mystats(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new stats[2048];
	
	format(stats, sizeof stats, "**Your Health**\n\
		"d_reply" %s\n\n\
		**Your Energy**\n\
		"d_reply" %s",
		GenerateBar(GetHealth(id)),
		GenerateBar(GetEnergy(id)));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Statistics__**", stats, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

@discord() command:eat(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Eat Command__**", ""delimiterlol" • You can eat food and gain energy.\n\
		Usage: `"BOT_PREFIX"eat [item] [quantity]`\n\n\
		**__Items__**\n\
		**`meat`**\n"d_reply"Eat cooked meat!\n\
		**`fruits`**\n"d_reply"Eat fruits!\n\
		**`medicine`**\n"d_reply"Eat medicine!\n\
		**`fish`**\n"d_reply"Eat cooked fish!\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **WHY AND HOW** • You can't use zero as quantity, sir.");
		return 1;
	}

	if(GetAchievement(id, "Consumer") == 0)
	{
		@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Consumer** achievement and got 1x "d_commonchest" | `Common Chest` as a reward.", id);
		SaveCommonChest(id, GetCommonChest(id) + 1);
		SetAchievement(id, "Consumer");
	}

	if(!strcmp(item, "meat"))
	{
		if(GetData(id, "CookedMeat") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_cookedmeat" | `Cooked Meat`.");
			return 1;
		}
		if(GetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't hungry at all! Your energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't that hungry! You need to eat %ix "d_cookedmeat" | `Cooked Meat` to fill up your energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "CookedMeat", GetData(id, "CookedMeat") - quantity);
		SetEnergy(id, GetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **LUNCH IS OVER** • You ate %ix "d_cookedmeat" | `Cooked Meat`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your **energy** by the amount of food you just ate!");
		return 1;
	}
	if(!strcmp(item, "fruits"))
	{
		if(GetData(id, "Fruits") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_fruits" | `Fruits`.");
			return 1;
		}
		if(GetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't hungry at all! Your energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't that hungry! You need to eat %ix "d_fruits" | `Fruits` to fill up your energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "Fruits", GetData(id, "Fruits") - quantity);
		SetEnergy(id, GetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **LUNCH IS OVER** • You ate %ix "d_fruits" | `Fruits`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your **energy** by the amount of food you just ate!");
		return 1;
	}
	if(!strcmp(item, "medicine"))
	{
		if(GetData(id, "Medicine") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_medicine" | `Medicine`.");
			return 1;
		}
		if(GetHealth(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't ill at all! Your health bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetHealth(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't that ill! You need to eat %ix "d_medicine" | `Medicine` to fill up your health bar.", 5 - GetHealth(id));
			return 1;
		}
		SetData(id, "Medicine", GetData(id, "Medicine") - quantity);
		SetHealth(id, GetHealth(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **YOU HEALED** • You ate %ix "d_medicine" | `Medicine`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your **health** by the amount of food you just ate!");
		return 1;
	}
	if(!strcmp(item, "fish"))
	{
		if(GetData(id, "CookedFish") < quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **QUANTITY ERROR** • You do not have that much "d_cookedfish" | `Cooked Fish`.");
			return 1;
		}
		if(GetEnergy(id) == d_max_bar_points)
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't hungry at all! Your energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_bar_points - GetEnergy(id)))
		{
			@discord() SendMsg(channel, ""d_reply" **STATISTICS ERROR** • You aren't that hungry! You need to eat %ix "d_cookedfish" | `Cooked Fish` to fill up your energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetData(id, "CookedFish", GetData(id, "CookedFish") - quantity);
		SetEnergy(id, GetEnergy(id) + quantity);
		@discord() SendMsg(channel, ""d_reply" **LUNCH IS OVER** • You ate %ix "d_cookedfish" | `Cooked Fish`!", quantity);
		
		@discord() SendInfo(channel, "You incresed your **energy** by the amount of food you just ate!");
		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **HOW ABOUT NO?** • You can't eat that!");
		@discord() SendInfo(channel, "Use `"BOT_PREFIX"eat` to view a list of available items.");
	}
	return 1;
}

@discord() command:make(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	if(GetInvData(id, "Desk") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_desk" | `Desk` to make stuff!");
		return 1;
	}

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Make Command__**", ""delimiterlol" • You can make items using other items.\n\
		Usage: `"BOT_PREFIX"make [item] [quantity]`\n\n\
		**__Items__**\n\
		**`paper`**\n"d_reply"Make paper! • *Requires:* 1x "d_planks" | `Planks`\n\
		**`banknotes`**\n"d_reply"Make paper money! • *Requires:* 1x "d_paper" | `Paper`, 100x "d_coin" | `Coins`\n\
		", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **WHY AND HOW** • What's the point of this command if you will use `0` as quantity?");
		return 1;
	}

	if(!strcmp(item, "paper"))
	{
		if(GetData(id, "Planks") < (1)*quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **NO ITEMS** • You do not have enough resources to make this item or this amount of items!");
			@discord() SendInfo(channel, "Use `"BOT_PREFIX"make` to view required resources for each item.");
			return 1;
		}
		SetData(id, "Planks", GetData(id, "Planks") - (1*quantity));
		SetData(id, "Paper", GetData(id, "Paper") + (1*quantity));
		@discord() SendMsg(channel, ""d_reply" **ITEM MADE** • You successfully used %ix "d_planks" | `Planks` and made %ix "d_paper" | `Paper`!", (1*quantity), (1*quantity));
		return 1;
	}
	if(!strcmp(item, "banknotes"))
	{
		if(GetData(id, "Paper") < (1)*quantity || GetData(id, "Balance") < (100)*quantity)
		{
			@discord() SendMsg(channel, ""d_reply" **NO ITEMS** • You do not have enough resources to make this item or this amount of items!");
			@discord() SendInfo(channel, "Use `"BOT_PREFIX"make` to view required resources for each item.");
			return 1;
		}
		SetData(id, "Paper", GetData(id, "Paper") - (1*quantity));
		SetData(id, "Balance", GetData(id, "Balance") - (100*quantity));
		SetData(id, "Banknotes", GetData(id, "Banknotes") + (1*quantity));
		@discord() SendMsg(channel, ""d_reply" **ITEM MADE** • You successfully used %ix "d_paper" | `Paper`, %ix "d_coin" | `Coins` and made %ix "d_banknote" | `Banknotes`!", (1*quantity), (100*quantity), (1*quantity));
		return 1;
	}

	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN ITEM** • That item does not even exist!");
		@discord() SendInfo(channel, "Use `"BOT_PREFIX"make` to view a list of available items.");
	}
	return 1;
}

@discord() command:achievements(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
	"**__"BOT_NAME" Achievements__**",
		""d_reply" **ACHIEVEMENTS** • This is the list of all achievements on the bot.\n\n\
		"d_arrow" • **Beggar** (Reward: 1x "d_commonchest" | `Common Chest`)\n\
		"d_reply"Use the `"BOT_PREFIX"beg` command!\n\n\
		"d_arrow" • **Consumer** (Reward: 1x "d_commonchest" | `Common Chest`)\n\
		"d_reply"Use the `"BOT_PREFIX"eat` command!\n\n\
		"d_arrow" • **Miner** (Reward: 1x "d_rarechest" | `Rare Chest`)\n\
		"d_reply"Use the `"BOT_PREFIX"mine` command!\n\n\
		"d_arrow" • **Pet Owner** (Reward: 1x "d_rarechest" | `Rare Chest`)\n\
		"d_reply"Use the `"BOT_PREFIX"buypet` command and get a pet!\n\n\
		"d_arrow" • **Digger** (Reward: 1x "d_rarechest" | `Rare Chest`)\n\
		"d_reply"Use the `"BOT_PREFIX"dig` command!\n\n\
		", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
	return 1;
}

@discord() command:myachievements(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new inv[4096];

	format(inv, sizeof inv, ""d_reply" **ACHIEVEMENTS** • These are the achievements you unlocked so far!\n\n\
		%s\
		%s\
		%s\
		%s\
		%s\
		",
		GetAchievement(id, "Beggar") ? ""d_arrow" • **Beggar**\n" : "",
		GetAchievement(id, "Consumer") ? ""d_arrow" • **Consumer**\n" : "",
		GetAchievement(id, "Miner") ? ""d_arrow" • **Miner**\n" : "",
		GetAchievement(id, "PetOwner") ? ""d_arrow" • **Pet Owner**\n" : "",
		GetAchievement(id, "Digger") ? ""d_arrow" • **Digger**\n" : ""
		);

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Unlocked Achievements__**", inv, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));

	return 1;
}




@discord() command:blacklist(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[40]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"blacklist [user ID or user mention]`");
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
		@discord() SendMsg(channel, ""d_reply" • This user can't be blacklisted as the user is a bot owner!");
		return 1;
	}


	if(IsBlacklisted(user))
	{
		Unblacklist(user);
		@discord() SendMsg(channel, ""d_reply" **UNBLACKLISTED** • <@%s> was unblacklisted successfully.", user);
		return 1;
	}

	if(!IsBlacklisted(user))
	{
		Blacklist(user);
		@discord() SendMsg(channel, ""d_reply" **BLACKLISTED** • <@%s> was blacklisted successfully.", user);
		return 1;
	}

	return 1;
}






/*

socialmedia

*/


@discord() command:smtos(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Terms of Use of "BRACE_TEAM" Account__**", "**Hello! It's mandatory for everyone to accept our Terms of Use in order to use the their BRACE:tm: account properly.**\n\n\
		**1.** Your nickname must not threaten any person, group of persons or community.\n\
		\n**2.** Your account name must be appropriate. It must not contain links, NSFW content, cruel words or obituary names.\n\
		\n**3.** The profile picture of your account must also be something suitable for all users of this bot. As a picture, you must not have NSFW content, inappropriate words or pictures of people you have taken without their permission!\n\
		\n**4.** Your account bio must not contain inappropriate, prohibited or IP-grab links, as well as content that threatens a person, group of persons or community.\n\n\n\
		> We deeply care about our community's security, therefore, we would like to ask you that if you notice an account that violates the mentioned terms of use, to immediately report that account via the `"BOT_PREFIX"report` command. Your report must include the user ID of the profile.\n\n\
		> After you have reported the account, we will review and investigate the account and remove the reported content from the account.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

stock SetAccount(const id[], const nickname[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"socialmedia/acc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, nickname);
	fclose(file2);
	return 1;
}

static GetNickname(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"socialmedia/acc_%s.ini", id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "unknown");
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

stock SetName(const id[], const name[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"socialmedia/accname_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, name);
	fclose(file2);
	return 1;
}

static GetName(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"socialmedia/accname_%s.ini", id);
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

stock SetBio(const id[], const name[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"socialmedia/accbio_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, name);
	fclose(file2);
	return 1;
}

static GetBio(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"socialmedia/accbio_%s.ini", id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "No bio");
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

stock SetPfp(const id[], const name[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"socialmedia/accpfp_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, name);
	fclose(file2);
	return 1;
}

static GetPfp(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"socialmedia/accpfp_%s.ini", id);
	new strFromFile2[512];
	format(strFromFile2, sizeof strFromFile2, "");
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

@discord() command:smregister(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[30];

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", nickname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"smregister [account nickname]`");
		return 1;
	}

	for(new i; i < strlen(nickname); i++)
	{
		if(nickname[i] == ' ')
		{
			@discord() SendMsg(channel, ""d_reply" **ERROR** • Nickname cannot contain spaces!");
			return 1;
		}
	}

	SetAccount(id, nickname);

	@discord() SendMsg(channel, "> "d_reply" **SUCCESS** • Great, <@%s> - your new social media account nickname is __*@*%s__!", id, nickname);
	return 1;
}

@discord() command:setaccdata(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	modcheck;

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	new user[30], option[30], value[100];

	if(sscanf(params, "s[30]s[30]s[100]", user, option, value))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Account Setup__**", ""delimiterlol" These are the options used to manipulate with other social media accounts.\n\
		Usage: `"BOT_PREFIX"setaccdata [user ID or user mention] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`verify`**\n"d_reply"Use `false` or `true` as a value.\n\
		**`nickname`**\n"d_reply"Set an account nickname.\n\
		**`name`**\n"d_reply"Set an account name.\n\
		**`bio`**\n"d_reply"Set an account bio.\n\
		**`pfp`**\n"d_reply"Set a profile picture.", 
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
	if(!strcmp(option, "verify"))
	{
		new file_name[150];
		if(!strcmp(value, "true"))
		{
			//verify a member
			format(file_name, sizeof file_name,"socialmedia/verify_%s.ini",user);
			new File: file2 = fopen(file_name, io_write);
			fwrite(file2, "verified.data(null->verified);");
			fclose(file2);

			@discord() SendMsg(channel, "<@%s>'s account was successfully verified.", user);
		}
		else if(!strcmp(value, "false"))
		{
			//remove a verified status
			format(file_name, sizeof file_name,"socialmedia/verify_%s.ini",user);
			fremove(file_name);

			@discord() SendMsg(channel, "<@%s>'s verified status was removed successfully.", user);
		}
		else
		{
			@discord() SendMsg(channel, ""d_reply" **UNKNOWN VALUE** • Invalid option value provided, use `"BOT_PREFIX"setaccdata` to view a list of available options and values.");
		}
		return 1;
	}
	if(!strcmp(option, "nickname"))
	{
		SetAccount(user, value);

		@discord() SendMsg(channel, "You successfully updated `Account Nickname` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	if(!strcmp(option, "name"))
	{
		SetName(user, value);

		@discord() SendMsg(channel, "You successfully updated `Account Name` for <@%s>'s account to `%s`.", user, value);
		
		return 1;
	}
	if(!strcmp(option, "bio"))
	{
		SetBio(user, value);

		@discord() SendMsg(channel, "You successfully updated `Account Bio` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	if(!strcmp(option, "pfp"))
	{
		SetPfp(user, value);

		@discord() SendMsg(channel, "You successfully updated `Account Profile Picture` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN OPTION** • Invalid option provided, use `"BOT_PREFIX"setaccdata` to view a list of available options.");
	}
	return 1;
}

@discord() command:smprofile(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	new user[30];

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"smprofile [user ID or user mention]`");
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
	new file_name[150];

	format(file_name, sizeof file_name,"socialmedia/verify_%s.ini",user);

	format(msg, sizeof msg, "**__%s__** • *@*%s %s\n\n\
		**User bio**\n\
		`%s`\n\n\
		**User's Economy**\n\
		"BOT_NAME" Coins: %i "d_coin"\n\
		Deposited coins: %i "d_coin"\n\n\
		**User's Activity**\n\
		Level: %i :crown:\n\
		Total message count: %i\n\n\
		**AFK Status**\n\
		%s\n\n\n\
		User ID: `%s`", 
		GetName(user),
		GetNickname(user),
		fexist(file_name) ? ""d_yes"" : " ",
		GetBio(user),
		GetData(user, "Balance"), 
		GetData(user, "DepBalance"),
		GetMessageCount(user) / 100 + 1, 
		GetMessageCount(user),
		GetAFK(user),
		user);


	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BRACE_TEAM" Account__**", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		GetPfp(user),""), GetMention(useridmention));
	
	return 1;
}

@discord() command:smaccname(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[30];

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", nickname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"smaccname [account name]`");
		return 1;
	}

	SetName(id, nickname);

	@discord() SendMsg(channel, "> "d_reply" **SUCCESS** • Okay, <@%s> - your new social media account name is __*%s*__!", id, nickname);
	return 1;
}

@discord() command:smbio(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[100];

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[100]", nickname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"smbio [bio]`");
		return 1;
	}

	SetBio(id, nickname);

	@discord() SendMsg(channel, "> "d_reply" **SUCCESS** • Your bio has been updated to `%s`, <@%s>!", nickname, id);
	return 1;
}

@discord() command:smpfp(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[512];

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[512]", nickname))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"smpfp [picture link - link can have up to 512 characters]`");
		return 1;
	}

	SetPfp(id, nickname);

	@discord() SendMsg(channel, "> "d_reply" **SUCCESS** • Your profile picture has been updated to `%s`, <@%s>!", nickname, id);
	return 1;
}

new newfeed[2048];
new feed[2048];

stock MakePost(const userid[], const name[], const nickname[], const text[])
{
	GetFeed();
	new file_name2[150];
	format(file_name2, sizeof file_name2,"socialmedia/verify_%s.ini",userid);
	new File: file2 = fopen("socialmedia/feed.ini", io_write);
	format(feed, sizeof feed, "**<@%s>** | __%s__ • @%s %s\\\\> `%s`\\\\%s", 
		userid, 
		name, 
		nickname, 
		fexist(file_name2) ? ""d_yes"" : "", 
		text,
		newfeed);
	fwrite(file2, feed);
	fclose(file2);
	return 1;
}

static GetFeed()
{
	format(newfeed, sizeof newfeed, "");
	//if(!fexist("socialmedia/feed.ini")) return newfeed;
	new File: file = fopen("socialmedia/feed.ini", io_read);
	if (file)
	{
		fread(file, newfeed);

		fclose(file);

		for(new i; i < strlen(newfeed); i++)
		{
			if(newfeed[i] == '\\') 
			{
				newfeed[i] = '\n';
			}
		}

		return 1;
	}
	return 0;
}

@discord() command:post(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	new text[150];

	if(sscanf(params, "s[150]", text))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"post [text]`");
		return 1;
	}

	MakePost(id, GetName(id), GetNickname(id), text);

	@discord() SendMsg(channel, ""d_reply" **POSTED** • Your text was posted on "BOT_NAME" network! View it using `"BOT_PREFIX"feed`.\n\n> "d_reply" **NOTE** • If your text wasn't posted, it may be because of the high volume of the interactions right now, please retry.");
	return 1;
}

@discord() command:feed(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	if(GetInvData(id, "Phone") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	GetFeed();

	format(feed, sizeof feed, ""d_phone" **NETWORK FEED** • View the most recent posts below.\n\n%s",newfeed);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Network Feed__**", feed, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
	return 1;
}

@discord() command:dig(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	SettingsCheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	CommandCooldownMin(channel, id, "dig", "Have control over your demands digger!");

	if(GetInvData(id, "Shovel") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_shovel" | `Shovel` to go digging!");
		return 1;
	}

	if(GetEnergy(id) == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	if(GetAchievement(id, "Digger") == 0)
	{
		@discord() SendInfo(channel, "<@%s>\n\nYou successfully unlocked a **Digger** achievement and got 1x "d_rarechest" | `Rare Chest` as a reward.", id);
		SaveRareChest(id, GetRareChest(id) + 1);
		SetAchievement(id, "Digger");
	}

	new copper = random(5);
	
	if(copper == 0)
	{
		SetEnergy(id, GetEnergy(id) - 1);
		@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **DIGGING FINISHED** • You've been digging for a while, but you could not find anything!", id);
		return 1;
	}


	@discord() SendMsg(channel, "**<@%s>**\n\n"d_reply" **DIGGING FINISHED** • You've been digging for a while, you found:\n\n%ix "d_copper" | `Copper`\n", id, copper);
	SetData(id, "Copper", GetData(id, "Copper") + copper);

	SetEnergy(id, GetEnergy(id) - 1);

	if(GetPet(id) != 0)
	{
		if(GetPetEnergy(id) == 0)
		{
			@discord() SendInfo(channel, "Your pet is too tired to work and could not help you this time! Use `"BOT_PREFIX"feedpet`!");
			return 1;
		}
		copper = random(5);
		@discord() SendInfo(channel, "**<@%s>**\n\n"d_reply" **PET BONUS** • Your pet somehow managed to help you, he mined this for you:\n\n%ix "d_copper" | `Copper`\n", id, copper);
		SetData(id, "Copper", GetData(id, "Copper") + copper);
		SetPetEnergy(id, GetPetEnergy(id) - 1);
	}

	return 1;
}

@discord() command:interactiontest(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author,id);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"BOT_NAME" Interaction Test__**", "React to the message!", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(id),
		"SetInteraction", "si", id, INTERACTION_TYPE_TEST);

	return 1;
}

@discord() command:qna(@discord() cmd_params)
{
	SetUpCommandChannel(channel,slashchannel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author,id);

	if(GetInvData(id, "Gamepad") == 0)
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	new question[100];

	if(sscanf(params, "s[100]", question))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"qna [question]`");
		return 1;
	}

	@discord() SendInfo(channel, "<@%s>\nYour question: **`%s`**\n\n> *%s*",id,question,QuestionAnswers[random(sizeof QuestionAnswers)]);

	return 1;
}
