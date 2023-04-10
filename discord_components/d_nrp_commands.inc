// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - commands

@discord() command:nrphelp(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**RolePlay System commands**\n\n\
		"d_arrow"**`"BOT_PREFIX"nrpstats`**\n"d_reply"View your country statistics!\n\
		"d_arrow"**`"BOT_PREFIX"nrpapply`**\n"d_reply"Start a RP entity submission!\n\
		"d_arrow"**`"BOT_PREFIX"regrp`**\n"d_reply"Register a country into the database.\n\
		"d_arrow"**`"BOT_PREFIX"setplayer`**\n"d_reply"Set a player for a certain nation.\n\
		"d_arrow"**`"BOT_PREFIX"setrpstat`**\n"d_reply"Update certain country statistics.\n\
		"d_arrow"**`"BOT_PREFIX"milstats`**\n"d_reply"View military equipment statistics for a country.\n\
		"d_arrow"**`"BOT_PREFIX"setmilstat`**\n"d_reply"Update the country's military statistics.", 
		"",
		"", col_embed, datetimelog, 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

//nrpstats
@discord() command:nrpstats(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30], page;

	if(sscanf(params, "s[30]i", country, page))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"nrpstats [country name] [page <1, 2>]`");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	new msg[1024];
	
	if(page == 1)
	{
		format(msg, sizeof msg, ""d_reply" **%s** Statistics\n\n\
		"delimiterlol" Main country player: *<@%s>*\n\n\
		:classical_building: **Government**\n\n\
		Country full name: **__%s__**\n\
		Head of State: *%s*\n\
		Head of Government: *%s*\n\
		Government Type: *%s*\n\n\
		:speaking_head: **Demographics**\n\n\
		Nationality: *%s*\n\
		Religion(s): *%s*\n\
		Number of inhabitants: *`%s`*\n\n\
		"d_coin" **Economy**\n\n\
		GDP: *`%s`*\n\
		GDP per capita: *`%s`*\n\
		Public debt: *`%s`*\n\n\
		:gun: **Military**\n\n\
		Active personnel: *`%s`*\n\
		Reserve personnel: *`%s`*\n\
		Military budget: *`%s`*\n\n\n\
		*Page: `1`*", country,
		GetPlayer(country),
		GetFullname(country),
		GetStateHead(country),
		GetGovHead(country),
		GetGovType(country),
		GetNationality(country),
		GetReligion(country),
		GetInhabitants(country),
		GetGdp(country),
		GetGdpPerCapita(country),
		GetPublicDebt(country),
		GetActivePersonnel(country),
		GetReservePersonnel(country),
		GetMilitaryBudget(country));
	}
	if(page == 2)
	{
		format(msg, sizeof msg, ""d_reply" **%s** Statistics\n\n\
		:newspaper: **Diplomacy**\n\n\
		Non-agression pacts with: *%s*\n\
		International organization membership(s): *%s*\n\
		In pact(s) with: *%s*\n\n\
		:question: **Other info**\n\n\
		Capital city: *%s*\n\
		Biggest city: *%s*\n\n\n\
		*Page: `2`*", country,
		GetNAP(country),
		GetIOM(country),
		GetIPW(country),
		GetCCY(country),
		GetBCY(country));
	}
	else if(page != 1 && page != 2)
	{
		@discord() SendMsg(channel, ""d_reply" **ERROR** • Wrong page ID.");
	}
	
	
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__RolePlay Country Statistics__**", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
	
	return 1;
}

//nrpapply


@discord() command:nrpapply(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new option[30];

	if(sscanf(params, "s[30]", option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Submission Setup__**", ""delimiterlol" These are the applications you can start.\n\
		Usage: `"BOT_PREFIX"nrpapply [option]`\n\n\
		**__Options__**\n\n\
		**`nation`**\n"d_reply"Start an application for a *`Nation`*.\n\
		**`rebelorg`**\n"d_reply"Start an application for a *`Rebellion Organization`*.\n\
		**`politicalorg`**\n"d_reply"Start an application for a *`Political Organization`*.\n\
		**`corporation`**\n"d_reply"Start an application for a *`Corporation`*.\n\
		**`acoop`**\n"d_reply"Start an application for a *`Administrative Cooperator`*.\n\
		**`pcoop`**\n"d_reply"Start an application for a *`Provincial Cooperator`*.\n\
		**`civilian`**\n"d_reply"Start an application for a *`Civilian`*.\n\
		**`unsec`**\n"d_reply"Start an application for a *`UN Secreatariat`*.",
		"","", col_embed, datetimelog, 
		"","",""), ""delimiterlol" **INFO** • Have fun!");
		return 1;
	}

	if(channel != submissionchannel)
	{
		@discord() SendMsg(channel, ""d_reply" **ERROR** • You can't start a submission application in this channel!");
		return 1;
	}

	//options
	if(!strcmp(option, "nation"))
	{
		@discord() SendMsg(channel, ""d_reply" **APPLICATION STARTED** • <@%s> successfully started the *`Nation`* position application!", id);

		SetAppType(id, "1");
		SetUserQuestion(id, "1");

		@discord() SendMsg(channel, "**Question 1** • Nation • <@%s>\n\n*`What is the nation name you are applying for?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "rebelorg"))
	{
		@discord() SendMsg(channel, ""d_reply" **APPLICATION STARTED** • <@%s> successfully started the *`Rebellion Organization`* position application!", id);

		SetAppType(id, "2");
		SetUserQuestion(id, "1");

		@discord() SendMsg(channel, "**Question 1** • Rebellion Organization • <@%s>\n\n*`In whose countries is your rebellion based in?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "politicalorg"))
	{
		@discord() SendMsg(channel, ""d_reply" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "3");
		SetUserQuestion(id, "1");

		@discord() SendMsg(channel, "**Question 1** • Political Organization • <@%s>\n\n*`In whose countries is your rebellion based in?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "corporation"))
	{
		@discord() SendMsg(channel, ""d_reply" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "4");
		SetUserQuestion(id, "1");

		@discord() SendMsg(channel, "**Question 1** • Corporation • <@%s>\n\n*`What is the name of your corporation?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "acoop"))
	{
		@discord() SendMsg(channel, ""d_reply" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "4");
		SetUserQuestion(id, "1");

		@discord() SendMsg(channel, "**Question 1** • Administrative Cooperator • <@%s>\n\n*`What is the name of the nation you want to cooperate as?`*\n\nPlease reply here.", id);

		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN APPLICATION** • Invalid application name provided, use `"BOT_PREFIX"nrpapply` to view a list of available applications!");
	}
	return 1;
}


//regrp
@discord() command:regrp(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30];

	if(sscanf(params, "s[30]", country))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"regrp [country name]`");
		return 1;
	}

	if(IsValidCountry(country))
	{
		@discord() SendMsg(channel, ""d_reply" **ALREADY REGISTERED** • This country has been registered in the database before.");
		return 1;
	}

	RegisterCountry(country);

	@discord() SendMsg(channel, "> "d_reply" **SUCCESS** • Country `%s` successfully registered.", country);
	return 1;
}

//setplayer
@discord() command:setplayer(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	//modcheck;

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE], country[30];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[30]s[31]", country, user))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"setplayer [country] [user ID or user mention]`");
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

	SetPlayer(country, user);

	@discord() SendMsg(rpnotices, "Main player updated for a country `%s` by **<@%s>**. New `%s` player is *<@%s>*.", country, id, country, user);

	@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

	return 1;
}


//setrpstat

@discord() command:setrpstat(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	new country[30], option[30], value[100];

	if(sscanf(params, "s[30]s[30]s[100]", country, option, value))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__RP Stats Setup__**", ""delimiterlol" These are the options used to manipulate with RP country statistics.\n\
		Usage: `"BOT_PREFIX"setrpstat [country] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`fullname`**\n"d_reply"Set the full name of a country (since a country's database name can be only one word).\n\
		**`statehead`**\n"d_reply"Set the name of the head of state of a country.\n\
		**`govhead`**\n"d_reply"Set the name of the head of the government of a country.\n\
		**`govtype`**\n"d_reply"Set the government type.\n\
		**`nationality`**\n"d_reply"Set the country's nationality.\n\
		**`religion`**\n"d_reply"Set the country's religion(s).\n\
		**`inhabitants`**\n"d_reply"Set the number of inhabitants of the country.\n\
		**`gdp`**\n"d_reply"Set the country's GDP.\n\
		**`gdppc`**\n"d_reply"Set the country's GDP per capita.\n\
		**`debt`**\n"d_reply"Set the amount of country's public debt. Either in GDP percentage or money value.\n\
		**`ap`**\n"d_reply"Set the amount of country's active personnel.\n\
		**`rp`**\n"d_reply"Set the amount of country's reserve personnel.\n\
		**`milbudget`**\n"d_reply"Set the country's military budget.\n\
		**`nap`**\n"d_reply"Set the countries this country has non-agression pact with.\n\
		**`iom`**\n"d_reply"Set the country's international organization membership(s).\n\
		**`ipw`**\n"d_reply"Set the countries this country is in pact with.\n\
		**`ccy`**\n"d_reply"Set the country's capital city.\n\
		**`bcy`**\n"d_reply"Set the country's biggest city.", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}


	if(!IsValidCountry(country))
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	//options
	if(!strcmp(option, "fullname"))
	{
		SetFullname(country, value);

		@discord() SendMsg(rpnotices, "`Full Name` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "statehead"))
	{
		SetStateHead(country, value);

		@discord() SendMsg(rpnotices, "`Head of State` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "govhead"))
	{
		SetGovHead(country, value);

		@discord() SendMsg(rpnotices, "`Head of Government` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "govtype"))
	{
		SetGovType(country, value);

		@discord() SendMsg(rpnotices, "`Government Type` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "nationality"))
	{
		SetNationality(country, value);

		@discord() SendMsg(rpnotices, "`Nationality` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "religion"))
	{
		SetReligion(country, value);

		@discord() SendMsg(rpnotices, "`Religion(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "inhabitants"))
	{
		SetInhabitants(country, value);

		@discord() SendMsg(rpnotices, "`Number of Inhabitants` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "gdp"))
	{
		SetGdp(country, value);

		@discord() SendMsg(rpnotices, "`GDP` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "gdppc"))
	{
		SetGdpPerCapita(country, value);

		@discord() SendMsg(rpnotices, "`GDP per Capita` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "debt"))
	{
		SetPublicDebt(country, value);

		@discord() SendMsg(rpnotices, "`Public Debt` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ap"))
	{
		SetActivePersonnel(country, value);

		@discord() SendMsg(rpnotices, "`Active Personnel` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "rp"))
	{
		SetReservePersonnel(country, value);

		@discord() SendMsg(rpnotices, "`Reserve Personnel` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "milbudget"))
	{
		SetMilitaryBudget(country, value);

		@discord() SendMsg(rpnotices, "`Military Budget` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "nap"))
	{
		SetNAP(country, value);

		@discord() SendMsg(rpnotices, "`Non-Agression Pact(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "iom"))
	{
		SetIOM(country, value);

		@discord() SendMsg(rpnotices, "`International Organization Membership(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ipw"))
	{
		SetIPW(country, value);

		@discord() SendMsg(rpnotices, "`Pact Status` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ccy"))
	{
		SetCCY(country, value);

		@discord() SendMsg(rpnotices, "`Capital City` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "bcy"))
	{
		SetBCY(country, value);

		@discord() SendMsg(rpnotices, "`Biggest City` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN OPTION** • Invalid option provided, use `"BOT_PREFIX"setrpstat` to view a list of available options.");
	}
	return 1;
}


//milstats

@discord() command:milstats(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30];

	if(sscanf(params, "s[30]", country))
	{
		@discord() SendMsg(channel, ""d_reply" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`"BOT_PREFIX"milstats [country name]`");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	new msg[1024];
	
	format(msg, sizeof msg, ":gun: **%s** Military Equipment Statistics\n\n\
		AA Equipment: *`%s`*\n\
		Armoed Personnel Carriers: *`%s`*\n\
		Anti-Submarine Warfare Helicopters: *`%s`*\n\
		Anti-Tank Equipment: *`%s`*", 
		country,
		GetAAE(country),
		GetAPC(country),
		GetASW(country),
		GetATE(country));


	//@discord() SendMsg(channel, msg);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Country Military Equipment Statistics__**", msg, 
		"",
		"", col_embed, datetimelog, 
		"",
		"",""), GetMention(useridmention));
	
	return 1;
}

//setmilstat


@discord() command:setmilstat(@discord() cmd_params)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30], option[30], value[100];

	if(sscanf(params, "s[30]s[30]s[100]", country, option, value))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Military Stats Setup__**", ""delimiterlol" These are the options used to manipulate with RP country statistics.\n\
		Usage: `"BOT_PREFIX"setmilstat [country] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`aae`**\n"d_reply"Anti-Air Equipment, mountable or on foot weaponry to counter aerial targets.\n\
		**`apc`**\n"d_reply"Armored personnel carriers.\n\
		**`asw`**\n"d_reply"Anti-submarine warfare helicopter.\n\
		**`ate`**\n"d_reply"Anti-Tank Equipment, mountable or on foot weaponry to counter armored targets.\n\
		**`awacs`**\n"d_reply"A large aircraft equipped for any kinds of naval tasks possible for aircrafts or general reconnaissance.\n\
		**`asf`**\n"d_reply"Air Superiority Fighter is a plane used to target other aircrafts and establish dominance in an airspace.\n\
		**`acr`**\n"d_reply"Aircraft Carrier is a capital ship used to carry aircrafts, usually escorted by a fleet of destroyers, cruisers and submarines!\n\
		**`asm`**\n"d_reply"Attack submarine is a submarine with the primary purpose of finding and sinking other submarines, a must have thing for any navy with a capital ship.\n\
		**`ahc`**\n"d_reply"Attack helicopter is a helicopter used to destroy mostly ground and rarely air targets.\n\
		**`bss`**\n"d_reply"A ballistic missile uses projectile motion to deliver warheads on a target.\n\
		**`cas`**\n"d_reply"Close Air Support Aircraft is an aircraft with ground support speciality or focus.\n\
		**`ccs`**\n"d_reply"Convoy Cargo Ship is used to ferry goods and equipment to different ports and places across the waves!\n\
		**`css`**\n"d_reply"Cruise Missile are missiles whose deliver a large warhead over long distances with high precision!\n\
		**`csr`**\n"d_reply"\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:", 
		"","", col_embed, datetimelog, 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(!IsValidCountry(country))
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	//options
	if(!strcmp(option, "aae"))
	{
		SetAAE(country, value);

		@discord() SendMsg(rpnotices, "Military item count `AA Equipment` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "apc"))
	{
		SetAPC(country, value);

		@discord() SendMsg(rpnotices, "Military item count `Armoed Personnel Carriers` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "asw"))
	{
		SetASW(country, value);

		@discord() SendMsg(rpnotices, "Military item count `Anti-Submarine Warfare Helicopter` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ate"))
	{
		SetATE(country, value);

		@discord() SendMsg(rpnotices, "Military item count `Anti-Tank Equipment` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		@discord() SendMsg(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	else
	{
		@discord() SendMsg(channel, ""d_reply" **UNKNOWN OPTION** • Invalid option provided, use `"BOT_PREFIX"setmilstat` to view a list of available options.");
	}
	return 1;
}
