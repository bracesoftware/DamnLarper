// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - functions

forward NRP_MSG_COMPONENT(DCC_Message:message);
public NRP_MSG_COMPONENT(DCC_Message:message)
{
	if(DAMN_LARPER_REWRITE == 1)
	{
		// All of the code below is deprecated, so just avoid executing it.
		return 1;
	}
	// main component
	new
		DCC_User: author,
		bool: is_bot = false
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

	new msgid[DCC_ID_SIZE], channelid[DCC_ID_SIZE];
	DCC_GetMessageId(message, msgid);
	DCC_GetChannelId(channel, channelid);

	//component 1
	if(author != bot)
	{
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
	//component 2

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

	//component 3
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
	//component 4
	SaveInactivityHours(id, 0);
	//component 5
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

