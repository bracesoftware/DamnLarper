// Module written by DEntisT, © & ® BRACE™.

forward OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success);

/*
public DCC_OnMessageReaction(DCC_Message:message, DCC_User:reaction_user, DCC_Emoji:emoji, DCC_MessageReactionType:reaction_type)
{
	if(reaction_type == REACTION_ADD)
	{
		
	}
	if(reaction_type == REACTION_REMOVE)
	{
		
	}
	return 1;
}

#if SLASH_COMMANDS == 1
forward SlashCommandTest(DCC_Interaction:interaction);
public SlashCommandTest(DCC_Interaction:interaction)
{
	new DCC_Channel:channel;
	DCC_GetInteractionChannel(interaction, channel);
	DCC_SendInteractionMessage(interaction, "This worked ig");
	return 1;
}
#endif
*/
public DCC_OnMessageCreate(DCC_Message: message) 
{
	if(DAMN_LARPER_LOADED==0) return 0;
	new
		DCC_User: author,
		bool: is_bot = false,
		content[256 + MAX_CMD_NAME + 2],
		command[MAX_CMD_NAME],
		params[256],
		discord[MAX_CMD_LEN] = "discord_"
	;

	new msg[1024];
	new count[523];
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

	format(mention, sizeof mention, "<@%s>", id);

	SetMention(id, mention);

	if(is_bot == false && author != bot && GetGuildVerification(guild) == 1 && GetUserVerification(guild, id) == 0)
	{
		if(channel != DCC_FindChannelById(GetGuildVerificationChannel(guild)))
		{
			DCC_DeleteMessage(message);
			@discord() SendInfo(DCC_FindChannelById(GetGuildVerificationChannel(guild)), "<@%s>\n\n"d_reply" **UNVERIFIED!** • You aren't verified in this guild so your message was deleted! You can use commands and chat **only** in this channel. You can use `"BOT_PREFIX"newverifycode` to generate a new verification code for this guild in case you lost yours or didn't even get it.", id);
			return 1;
		}
	}

	// Message control

	for(new i; i < strlen(msg); i++)
	{
		msg[i] = tolower(msg[i]);
		if(msg[i] == 'f' &&
			msg[i+1] == 'a' &&
			msg[i+2] == 'g' &&
			msg[i+3] == 'g' &&
			msg[i+4] == 'o' &&
			msg[i+5] == 't')
		{
			DCC_DeleteMessage(message);
			@discord() SendMsg(channel, ""d_reply" **MESSAGE MANAGEMENT** • Watch your language, <@%s>!", id);
		}
		if(channel == submissionchannel)
		{
			if(msg[i] == 'a' &&
				msg[i+1] == 'p' &&
				msg[i+2] == 'p' &&
				msg[i+3] == 'r' &&
				msg[i+4] == 'o' &&
				msg[i+5] == 'v')
			{
				SaveApprovalCount(id, GetApprovalCount(id) + 1);
				AddReaction(message, DCC_CreateEmoji("☑️"));
			}
			if(msg[i] == 'a' &&
				msg[i+1] == 'c' &&
				msg[i+2] == 'c' &&
				msg[i+3] == 'e' &&
				msg[i+4] == 'p' &&
				msg[i+5] == 't')
			{
				SaveApprovalCount(id, GetApprovalCount(id) + 1);
				AddReaction(message, DCC_CreateEmoji("☑️"));
			}
		}

		if(channel == supportchannel)
		{
			SaveSupportPoints(id, GetSupportPoints(id) + 1);
		}
	}

	SaveInactivityHours(id, 0);

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
	if(channel == submissionchannel && GetAppType(id) != 0)
	{
		//nation
		if(GetAppType(id) == 1)
		{
			if(GetUserQuestion(id) == 1)
			{
				SetUserAnswer(id, 1, msg);

				SetUserQuestion(id, "2");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 2** • Nation • <@%s>\n\n*`Who is the head of the nation (president) you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 3** • Nation • <@%s>\n\n*`Who is the head of government (prime minister) of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 4** • Nation • <@%s>\n\n*`What is the GDP of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 5** • Nation • <@%s>\n\n*`What is the GDP per capita of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 6** • Nation • <@%s>\n\n*`What is the military budget of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 7** • Nation • <@%s>\n\n*`In whose international organizations is the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 8** • Nation • <@%s>\n\n*`What's the alignment of the nation you're applying for? Is your nation supporting eastern or western bloc?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**FINAL QUESTION (No.9)** • Nation • <@%s>\n\n*`Number of citizens/population of the nation you're applying for? Is your nation supporting eastern or western bloc?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, ""d_reply" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				@discord() SendMsg(appreview, "__**Application for a `Nation`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nName of the State: `%s`\nHead of State: `%s`\nHead of Government: `%s`\nGDP: `%s`\nGDP per capita: `%s`\nMilitary budget: `%s`\nInternational organization membership: `%s`\nAlignment: `%s`\nPopulation: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
			}
		}
		//rebelorg
		if(GetAppType(id) == 2)
		{
			if(GetUserQuestion(id) == 1)
			{
				SetUserAnswer(id, 1, msg);

				SetUserQuestion(id, "2");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 2** • Rebellion Organization • <@%s>\n\n*`What's the official name of your rebellion?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 3** • Rebellion Organization • <@%s>\n\n*`What is your denonym?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 4** • Rebellion Organization • <@%s>\n\n*`How much influental is your rebellion?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 5** • Rebellion Organization • <@%s>\n\n*`What is your ideology?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 6** • Rebellion Organization • <@%s>\n\n*`How much money do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 7** • Rebellion Organization • <@%s>\n\n*`Who are your allies?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 8** • Rebellion Organization • <@%s>\n\n*`How many supporters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**FINAL QUESTION (No.9)** • Rebellion Organization • <@%s>\n\n*`How many fighters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, ""d_reply" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				@discord() SendMsg(appreview, "__**Application for a `Rebellion Organization`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nCountries based in: `%s`\nName of Rebellion: `%s`\nDenonym: `%s`\nInfluence: `%s`\nIdeology: `%s`\nMoney owned: `%s`\nAllies: `%s`\nSupporters: `%s`\nFighters: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
			}
		}
		//politicalorg
		if(GetAppType(id) == 3)
		{
			if(GetUserQuestion(id) == 1)
			{
				SetUserAnswer(id, 1, msg);

				SetUserQuestion(id, "2");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 2** • Political Organization • <@%s>\n\n*`What's the official name of your organization?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 3** • Political Organization • <@%s>\n\n*`How many seats do you have in pairlament upper house? How many seats do you have in pairlament lower house?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 4** • Political Organization • <@%s>\n\n*`How much influental is your political organization?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 5** • Political Organization • <@%s>\n\n*`What is your ideology?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 6** • Political Organization • <@%s>\n\n*`How much money do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 7** • Political Organization • <@%s>\n\n*`Who are your allies?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 8** • Political Organization • <@%s>\n\n*`How many supporters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**FINAL QUESTION (No.9)** • Political Organization • <@%s>\n\n*`How many members do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, ""d_reply" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				@discord() SendMsg(appreview, "__**Application for a `Political Organization`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nCountries based in: `%s`\nName of Organization: `%s`\nNumber of seats in pairlament (upper and lower house): `%s`\nInfluence: `%s`\nIdeology: `%s`\nMoney owned: `%s`\nAllies: `%s`\nSupporters: `%s`\nMembers: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
			}
		}
		//corporation
		if(GetAppType(id) == 4)
		{
			if(GetUserQuestion(id) == 1)
			{
				SetUserAnswer(id, 1, msg);

				SetUserQuestion(id, "2");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 2** • Corporation • <@%s>\n\n*`In which branch of industry is your corporation working in?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 3** • Corporation • <@%s>\n\n*`Who is the Chief Executive Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 4** • Corporation • <@%s>\n\n*`Who is the Chief Operations Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 5** • Corporation • <@%s>\n\n*`Who is the Chief Finance Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 6** • Corporation • <@%s>\n\n*`How much do you have money owned?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 7** • Corporation • <@%s>\n\n*`How much do you pay your employees each month?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**Question 8** • Corporation • <@%s>\n\n*`How much employees do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, "**FINAL QUESTION (No.9)** • Corporation • <@%s>\n\n*`How many customers do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				@discord() SendMsg(channel, ""d_reply" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				@discord() SendMsg(appreview, "__**Application for a `Corporation`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nName: `%s`\nIndustry type: `%s`\nChief Executive Offier: `%s`\nChief Operations Officer: `%s`\nChief Finance Officer: `%s`\nNet worth: `%s`\nMonthly employee salary: `%s`\nEmployees: `%s`\nCustomers: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
			}
		}
	}

	new msgid[DCC_ID_SIZE], channelid[DCC_ID_SIZE];
	DCC_GetMessageId(message, msgid);
	DCC_GetChannelId(channel, channelid);

	if(author != bot)
	{
		new msglen = strlen(msg);
		for(new i; i < msglen; i++)
		{
			if(msg[i] == '\10') strdel(msg, i, i+1);
		}
		for(new i; i < msglen; i++)
		{
			if(msg[i] == 'd' && 
				msg[i+1] == 'i' && 
				msg[i+2] == 'p' && 
				msg[i+3] == 'l' && 
				msg[i+4] == 'o' && 
				msg[i+5] == 'm' && 
				msg[i+6] == 'y')
			{
				DCC_SendChannelMessage(channel, DiplomyReplies[random(sizeof DiplomyReplies)]);
			}
		}
	}

	if(settings[ac] == 1)
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
					AddReaction(message, DCC_CreateEmoji("☑️"));
					return 1;
				}
			}
		}
		if(channel == rpchannel || channel == rpchannel1 || channel == rpchannel2 ||
			channel == rpchannel3 || channel == rpchannel4 || channel == rpchannel5 ||
			channel == rpchannel6 || channel == rpchannel7)
		{
			@discord() SendMsg(rpnotices, "<@%s> successfully submitted a RP sample! GameMasters will GM it soon. Click [here](https://discord.com/channels/987003062726058004/%s/%s) to view the message.", id, channelid, msgid);
		}
		if(channel == gm_output)
		{	
			new msglen = strlen(msg);
			if(settings[gmc] == 0) return 1;
			for(new i; i < msglen; i++)
			{
				if(msg[i] == '\10') strdel(msg, i, i+1);
			}
			new levelcount, linkcount, dept;
			for(new i; i < msglen; i++)
			{
				// Department check:

				if(msg[i] == '[' && 
					msg[i+1] == 'p' && 
					msg[i+2] == 'o' && 
					msg[i+3] == 'l' && 
					msg[i+4] == ']')
				{
					dept = dept + 1;
				}

				if(msg[i] == '[' && 
					msg[i+1] == 'e' && 
					msg[i+2] == 'c' && 
					msg[i+3] == 'o' && 
					msg[i+4] == ']')
				{
					dept = dept + 3;
				}

				if(msg[i] == '[' && 
					msg[i+1] == 'm' && 
					msg[i+2] == 'i' && 
					msg[i+3] == 'l' && 
					msg[i+4] == ']')
				{
					dept = dept + 8;
				}

				// Level estimator:

				if(msglen > 300)
					levelcount = 1;

				if(msglen > 500)
					levelcount = 2;

				if(msglen > 1000)
					levelcount = 3;

				if(msglen > 2000)
					levelcount = 4;

				if(msglen > 5000)
					levelcount = 5;

				if(msg[i] == 'h' &&
					msg[i+1] == 't' &&
					msg[i+2] == 't' &&
					msg[i+3] == 'p' &&
					msg[i+4] == 's' &&
					msg[i+5] == ':' &&
					msg[i+6] == '/' &&
					msg[i+7] == '/')
				{
					levelcount ++;
					linkcount ++;
				}

				if(msg[i] == '%') 
					levelcount++;


				/*if(msg[i] == '+' || 
					msg[i] == '*' || 
					msg[i] == '~' || 
					msg[i] == '=' || 
					msg[i] == '"' || 
					msg[i] == '#' || 
					msg[i] == '$' || 
					msg[i] == '/' || 
					msg[i] == '(' || 
					msg[i] == ')') 
					levelcount++;*/

				if(msg[i] == 'G' && msg[i+1] == 'D' && msg[i+2] == 'P')
				{
					levelcount ++;
				}

				if(msg[i] == 'd' && msg[i+1] == 'd' && msg[i+2] == 'p')
				{
					levelcount ++;
				}

				if(msg[i] == 'T' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					levelcount ++;
				}

				if(msg[i] == 't' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					levelcount ++;
				}

				if(msg[i] == 'i' && msg[i+1] == 'n' && msg[i+2] == 'f' 
					&& msg[i+3] == 'l' && msg[i+4] == 'a' && msg[i+5] == 't')
				{
					levelcount ++;
				}
			}

			if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9 && linkcount != 0)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • Sorry, <@%s> - invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • <@%s>, you can't chat or use commands in there!\n"delimiterlol" • If you think this is a mistake, report a bug using `"BOT_PREFIX"report` or check if you used a valid GM template (`"BOT_PREFIX"gmtemp`).", id);
				return 1;
			}
			else if(linkcount == 0)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
				return 1;
			}

			if(dept == 1) // Politics department solo
			{
				if(levelcount == 1)
				{
					//Click [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, channelid, msgid
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SavePolGMCount(id,GetPolGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 3) // Economics solo
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SaveEcoGMCount(id,GetEcoGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 8) // Military solo
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SaveMilGMCount(id,GetMilGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			// Mixed labels:
			
			if(dept == 4) // pol eco
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SavePolEcoGMCount(id,GetPolEcoGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 11) // eco mil
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SaveEcoMilGMCount(id,GetEcoMilGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 9) // mil pol
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SaveMilPolGMCount(id,GetMilPolGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}
			
			return 1;
		}
		else if(channel == war_gm_output)
		{
			if(settings[gmc] == 0) return 1;
			for(new i; i < strlen(msg); i++)
			{
				if(msg[i] == '\10') strdel(msg, i, i+1);
			}
			new levelcount, linkcount, dept;
			for(new i; i < strlen(msg); i++)
			{
				// Department check:

				if(msg[i] == '[' && 
					msg[i+1] == 'w' && 
					msg[i+2] == 'a' && 
					msg[i+3] == 'r' && 
					msg[i+4] == ']')
				{
					dept = dept + 1;
				}

				// Level estimator:

				new msglen = strlen(msg);

				if(msglen > 300)
					levelcount = 1;

				if(msglen > 500)
					levelcount = 2;

				if(msglen > 1000)
					levelcount = 3;

				if(msglen > 2000)
					levelcount = 4;

				if(msglen > 5000)
					levelcount = 5;

				if(msg[i] == 'h' &&
					msg[i+1] == 't' &&
					msg[i+2] == 't' &&
					msg[i+3] == 'p' &&
					msg[i+4] == 's' &&
					msg[i+5] == ':' &&
					msg[i+6] == '/' &&
					msg[i+7] == '/')
				{
					levelcount ++;
					linkcount ++;
				}
			}
			
			if(dept != 1)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • Sorry, <@%s> - invalid department label(s) provided. You can use: `[war]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • <@%s>, you can't chat or use commands in there!\n"delimiterlol" • If you think this is a mistake, report a bug using `"BOT_PREFIX"report` or check if you used a valid GM template (`"BOT_PREFIX"gmtemp`).", id);
			}
			else if(linkcount == 0)
			{
				@discord() SendMsg(channel, ""d_reply" **GM COUNT** • Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
				return 1;
			}

			for(new i; i < strlen(msg); i++)
			{

				if(msg[i] == '%') 
					levelcount++;

				if(msg[i] == 'G' && msg[i+1] == 'D' && msg[i+2] == 'P')
				{
					levelcount ++;
				}

				if(msg[i] == 'd' && msg[i+1] == 'd' && msg[i+2] == 'p')
				{
					levelcount ++;
				}

				if(msg[i] == 'T' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					levelcount ++;
				}

				if(msg[i] == 't' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					levelcount ++;
				}

				if(msg[i] == 'i' && msg[i+1] == 'n' && msg[i+2] == 'f' 
					&& msg[i+3] == 'l' && msg[i+4] == 'a' && msg[i+5] == 't')
				{
					levelcount ++;
				}
			}

			if(dept == 1) // war gm
			{
				if(levelcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(levelcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(levelcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(levelcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(levelcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```\n\nClick [here](https://discord.com/channels/987003062726058004/%s/%s) to view the GM message.", id, GetGMCount(id)+1, channelid, msgid);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, datetimelog, 
				"","",""));

				SaveWarGMCount(id,GetWarGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}
			return 1;
		}
	}

	if (!DCC_GetMessageAuthor(message, author) || author == DCC_INVALID_USER) { // The message author is invalid
		#if defined discdcmd_DCC_OnMessageCreate
			return discdcmd_DCC_OnMessageCreate(DCC_Message: message);
		#else
			return 0;
		#endif
	}

	DCC_GetMessageContent(message, content);

	//<@954 063 234 938 306 640>

	
	/*if(content[0] == '<' && content[1] == '@' && content[2] == '9' &&
		content[3] == '5' &&
		content[4] == '4' &&
		content[5] == '0' &&
		content[6] == '6' &&
		content[7] == '3' &&
		content[8] == '2' &&
		content[9] == '3' &&
		content[10] == '4' &&
		content[11] == '9' &&
		content[12] == '3' &&
		content[13] == '8' &&
		content[14] == '3' &&
		content[15] == '0' &&
		content[16] == '6' &&
		content[17] == '6' &&
		content[18] == '4' &&
		content[19] == '0' && content[20] == '>' && content[21] == ' ')
	{
		content[0] = CMD_PREFIX;
		strdel(content, 1, 22);
	}*/

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
		OnDiscordCommandPerformed(message, author, bool: CallLocalFunction(discord, "iis", _: message, _: author, params));
	#else
		CallLocalFunction(discord, "iis", _: message, _: author, params);
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
	}

	if(IsBlacklisted(id))
	{
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • You're blacklisted from using bot commands.");
		return 0;
	}

	return 1;
}

forward InactivityPurge();
public InactivityPurge()
{
	new count;
	DCC_GetGuildMemberCount(RiseOfNations, count);

	new id[DCC_ID_SIZE];

	for (new i; i != count; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(RiseOfNations, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    DCC_GetUserId(user, id);

	    new bool:has_role;
	    DCC_HasGuildMemberRole(RiseOfNations, user, gm, has_role);

	    if(has_role)
	    {
	    	SaveInactivityHours(id, GetInactivityHours(id) + 1);
	    	if(GetInactivityHours(id) == 72)
	    	{
	    		@discord() SendMsg(logs, ""d_reply" **INACTIVITY PURGE** • Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }

	    new bool:has_role2;
	    DCC_HasGuildMemberRole(RiseOfNations, user, pgm, has_role2);

	    if(has_role2)
	    {
	    	SaveInactivityHours(id, GetInactivityHours(id) + 1);
	    	if(GetInactivityHours(id) == 72)
	    	{
	    		@discord() SendMsg(logs, ""d_reply" **INACTIVITY PURGE** • Probationary Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }
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

	if(GetGuildVerification(guild) == 1)
	{
		new code[10];

		format(code, sizeof code, "%i", random(100000));

		SetVerifyCode(guild, id, code);

		@discord() SendMsg(DCC_FindChannelById(GetGuildVerificationChannel(guild)), ""botpfp" **WELCOME TO THE GUILD** • Hello <@%s>! Thanks for choosing this guild to join! But in order to send messages here, please use a `"BOT_PREFIX"verify` command.\n\nYour verification code **for this guild** is: `%s`", id, code);
		@discord() SendInfo(DCC_FindChannelById(GetGuildVerificationChannel(guild)), "<@%s>\n\nPlease make sure to verify as fast as possible to be able to chat, use commands and more!", id);
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

new DCC_Guild:all_guilds[50];

forward ActivityChange();
public ActivityChange()
{
	DCC_GetAllGuilds(all_guilds);
	format(activity, sizeof activity, "on %s servers! • damn help", _:all_guilds);
	DCC_SetBotActivity(activity);
	return 1;
}


public DCC_OnChannelCreate(DCC_Channel:channel)
{
	if(settings[log] == 0) return 0;

	new name[100];
	DCC_GetChannelName(channel, name, sizeof name);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Channel created__**\n\n\
		"d_reply" Name: **#%s**", name);

	@discord() SendMsg(logs, logmsg);
	return 1;
}

public DCC_OnChannelDelete(DCC_Channel:channel)
{
	if(settings[log] == 0) return 0;

	new name[100];
	DCC_GetChannelName(channel, name, sizeof name);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Channel deleted__**\n\n\
		"d_reply" Name: **#%s**", name);

	@discord() SendMsg(logs, logmsg);
	return 1;
}

public DCC_OnMessageDelete(DCC_Message:message)
{
	if(settings[log] == 0) return 0;

	new content[1024], DCC_User:author, id[DCC_ID_SIZE];
	DCC_GetMessageAuthor(message, author);
	DCC_GetMessageContent(message, content);

	DCC_GetUserId(author, id);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Message deleted__**\n\n\
		"d_reply" User: <@%s>\n"d_reply" Content: **%s**", id, content);

	@discord() SendMsg(logs, logmsg);
	return 1;
}

public DCC_OnUserUpdate(DCC_User:user)
{
	if(settings[log] == 0) return 0;

	new logmsg[256], id[DCC_ID_SIZE];

	DCC_GetUserId(user, id);

	format(logmsg, sizeof logmsg, "**__User update__**\n\n"d_reply" • User <@%s> has been updated.", id);

	@discord() SendMsg(logs, logmsg);

	return 1;
}


forward DateUpdate();
public DateUpdate()
{
	new h,m,s;
	gettime(h,m,s);
	if(h == 8)
	{
		if(dateupdated == 8)
		{
			@discord() SendMsg(dateupdate, "A month has passed!");
			dateupdated = 20;
		}
	}
	if(h == 20)
	{
		if(dateupdated == 20)
		{
			@discord() SendMsg(dateupdate, "A month has passed!");
			dateupdated = 8;
		}
	}
	return 1;
}


public OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success) 
{
	new DCC_Channel: channel;

	DCC_GetMessageChannel(message, channel);
	
	new DCC_Guild:guild;

	DCC_GetChannelGuild(channel, guild);
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
	}
	if(BOT_BETA_PHASE == 1)
	{
		@discord() SendInfo(channel, ""d_beta" "BOT_NAME" achieved the **Beta Test** phase of development, help us in the development process by reporting all the bugs and issues using the `"BOT_PREFIX"report` command!");
	}
	return 1;
}

public OnGameModeInit()
{
	printf("OnGameModeInit called");
	new y,m,d,h,n,s;
	getdate(y,m,d);
	gettime(h,n,s);
	format(datetimelog, sizeof datetimelog, ""BOT_NAME" • %i/%i/%i • %i:%i:%i",d,m,y,h,n,s);

	LoadSettings();
	DCC_SetBotPresenceStatus(IDLE);
	SetTimer("ActivityChange", 2000, true);
	SetTimer("InactivityPurge", 3600000, true);
	SetTimer("DateUpdate", 10000, true);
	SetTimer("DateTimeLog", 1000, true);

	LoadChannels();
	#if SLASH_COMMANDS == 1
	LoadCommands();
	#endif
	dateupdated = 20;

	DAMN_LARPER_LOADED = 1;
	printf("OnGameModeInit performed");
	return 1;
}

forward DateTimeLog();
public DateTimeLog()
{
	new y,m,d,h,n,s;
	getdate(y,m,d);
	gettime(h,n,s);
	format(datetimelog, sizeof datetimelog, ""BOT_NAME" • %i/%i/%i • %i:%i:%i",d,m,y,h,n,s);
	return 1;
}

public OnGameModeExit()
{
	SaveSettings();
	return 1;
}