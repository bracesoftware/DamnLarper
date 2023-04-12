// Module written by DEntisT, © & ® BRACE™.



new datetimelog[256];

#define CMD_PREFIX '^'
#define MAX_LIST_ELEMENTS 50

#define BOT_USER_ID "1094936702017093735"
#define BOT_AUTH_LINK "https://discord.com/api/oauth2/authorize?client_id="BOT_USER_ID"&permissions=8&scope=bot"
#define BOT_SUPPORT_MAIL "bracetm.official@gmail.com"

#define MAX_STAFF_MEMBERS 100

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

// Config

#define MAX_CMD_LEN         32
#define MAX_CMD_NAME        20

// Prefix

#if !defined CMD_PREFIX
	#define CMD_PREFIX      '!'
#endif

// Macros

#define DISCORD:%1(%2)      \
	forward discord_%1(%2); \
	public discord_%1(%2)

#define DC:%1(%2)           \
	DISCORD:%1(%2)

// Command result

#define DISCORD_SUCCESS     (1)
#define DISCORD_FAILURE     (0)


new BOT_BETA_PHASE = 1;

#define BOT_VERSION "v"DAMN_LARPER_MAJOR"."DAMN_LARPER_MINOR"-R"DAMN_LARPER_RELEASE""
#define BOT_NAME "Damn Larper"
#define BRACE_TEAM "® 𝐁 𝐑 𝐀 𝐂 𝐄™"

#define @DISCORD_DECORATOR@SendMsg(%1,%2) \
	format(formatted, sizeof formatted,%2); \
	DCC_SendChannelEmbedMessage(%1, DCC_CreateEmbed( \
			embed_titles[random(sizeof embed_titles)], formatted, "","", col_embed, datetimelog, \
			"","",""), "")

new info[2048];

#define @DISCORD_DECORATOR@SendInfo(%1,%2) format(info, sizeof info, ""d_reply" • "%2),DCC_SendChannelMessage(%1, info)

/*

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__"SERVER_RISE_OF_NATIONS"__**", response, "","", col_embed, datetimelog, 
			"","",""), GetMention(useridmention));*/

#pragma warning disable 217

#define CommandCooldownMin(%0,%1,%2,%3) \
new h,m,s;gettime(h,m,s); \
if((m>GetCommandUsedMin(%1,%2))||(m<GetCommandUsedMin(%1,%2)))SetCommandUsed(%1,%2,"0"); \
if(GetPremium(%1) == 0 && GetCommandUsed(%1,%2)==1){\
@discord() SendMsg(%0, "**<@%s>**\n\n"d_reply" **COOLDOWN** • "%3" **You can use this command once every 60 seconds.**", %1); \
return 1;}SetCommandUsed(%1,%2, "1");SetCommandUsedMin(%1,%2, m)

#define CommandCooldownHr(%0,%1,%2,%3) \
new h,m,s;gettime(h,m,s); \
if((h>GetCommandUsedHr(%1,%2))||(h<GetCommandUsedHr(%1,%2)))SetCommandUsed(%1,%2,"0"); \
if(GetPremium(%1) == 0 && GetCommandUsed(%1,%2)==1){\
@discord() SendMsg(%0, "**<@%s>**\n\n"d_reply" **COOLDOWN** • "%3" **You can use this command once every 1 hour.**", %1); \
return 1;}SetCommandUsed(%1,%2, "1");SetCommandUsedHr(%1,%2, h)

#define CommandCooldownDay(%0,%1,%2,%3) \
new y,m,d;getdate(y,m,d); \
if((d>GetCommandUsedDay(%1,%2))||(d<GetCommandUsedDay(%1,%2)))SetCommandUsed(%1,%2,"0"); \
if(GetCommandUsed(%1,%2)==1){\
@discord() SendMsg(%0, "**<@%s>**\n\n"d_reply" **COOLDOWN** • "%3" **You can use this command once every 1 day.**", %1); \
return 1;}SetCommandUsed(%1,%2, "1");SetCommandUsedDay(%1,%2, d)


new dmstring[2048];

#define @DISCORD_DECORATOR@SendDM(%1,%2) \
	format(dmstring, sizeof dmstring,%2);DCC_CreatePrivateChannel(%1, "senddm", "s", dmstring)


new formatted[2048];

#define modcheck; if(IsUserMod(author)==0) { \
@discord() SendMsg(channel,"> "d_reply" **AUTHORIZATION ERROR** • Only the "BRACE_TEAM" team can use this command!");return 1;}

#define premiumcheck(%1); if(GetPremium(%1)==0) { \
@discord() SendMsg(channel,"> "d_reply" **NO PREMIUM?** • Only the "BOT_NAME" premium users can use or do this!");return 1;}

#define SettingsCheck(%1); if(settings[%1] == 0) { \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • This command module has been disabled by a bot moderator."); return 1;}

#define servercheck(%1); new DCC_Guild:guild;DCC_GetChannelGuild(channel, guild);if(guild != %1) {\
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't do that thing here because this is a custom feature made exclusively for another server!");return 1;}

#define usercheck(%0); if(DCC_FindUserById(%0) == DCC_INVALID_USER){ \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't find an user with such ID or name - please, recheck the user ID, and submit again.\n\nUser: <@%s>", %0); \
 return 1;}if(IsUserABot(%0)==true){@discord() SendMsg(channel, "> "d_reply" **THIS IS A BOT** • <@%s> is a damn bot dude! What are you going to do with a bot?", %0); \
 return 1;}

#define channelcheck(%0); if(DCC_FindChannelById(%0) == DCC_INVALID_CHANNEL){ \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't find a channel with such ID or name - please, recheck the channel ID, and submit again.\n\nChannel: <#%s>", %0); \
 return 1;}

#define rolecheck(%0); if(DCC_FindRoleById(%0) == DCC_INVALID_ROLE){ \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't find a role with such ID or name - please, recheck the role ID, and submit again.\n\nRole: <@&%s>", %0); \
 return 1;}

#define @DISCORD_DECORATOR@command:%0(%1) DISCORD:%0(%1)

#define @DISCORD_DECORATOR@cmd_params DCC_Message:message,DCC_User:author,PARAMETERS[]
#define params PARAMETERS

stock bool:IsUserABot(const user[])
{
	new bool:is_bot, DCC_User:user2 = DCC_FindUserById(user);
	DCC_IsUserBot(user2,is_bot);
	return is_bot;
}

stock bool:IsUserABot_2(DCC_User:user)
{
	new bool:is_bot;
	DCC_IsUserBot(user,is_bot);
	return is_bot;
}


#define syschannelstring \
""d_reply" **SYSTEM CHANNEL** • This channel was successfully loaded as a system channel. *It is recommended to not delete it or modify it!*"

#define bot 				DCC_FindUserById(BOT_USER_ID)


#define col_embed 0x414040//0x7fff00




#define IST_GOLD 			1
#define IST_RUBIES 			2
#define IST_RAWMEAT 		3
#define IST_COOKEDMEAT 		4
#define IST_FRUITS 			5
#define IST_MEDICINE 		6
#define IST_RAWFISH 		7
#define IST_COOKEDFISH 		8
#define IST_PLANKS 			9
#define IST_PAPER 			10
#define IST_BANKNOTE 		11
#define IST_COPPER 			12


#define CHEST_COMMON 		1
#define CHEST_RARE 			2

#define delimiterlol ""

#define d_max_bar_points 5

#define antiraid(%0,%1,%2); @discord() SendChannelMessage(channel, ":shield: **ANTI-RAID** • Hi, <@%s>! The bot's anti-raid system has been activated for `%s`! The moderators will be notified.\n\n",%1,%2);



#define BOT_PREFIX "damn "
//"<@"BOT_USER_ID"> "

forward senddm(message[]);
public senddm(message[])
{
	new DCC_Channel:channel = DCC_GetCreatedPrivateChannel();
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed( 
			""botpfp"| **__"BOT_NAME"__**", message, "","", col_embed, datetimelog, 
			"","",""), "");
	return 1;
}