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
#define BOT_VERSION "Beta @ 1.0"
#define BOT_NAME "Damn Larper"
#define BRACE_TEAM "® 𝐁 𝐑 𝐀 𝐂 𝐄™"

#define @DISCORD_DECORATOR@SendMsg(%1,%2) \
	format(formatted, sizeof formatted,%2); \
	DCC_SendChannelEmbedMessage(%1, DCC_CreateEmbed( \
			""botpfp"| **__"BOT_NAME"__**", formatted, "","", col_embed, datetimelog, \
			"","",""), "")

new info[2048];

#define @DISCORD_DECORATOR@SendInfo(%1,%2) format(info, sizeof info, ""d_reply" • "%2);DCC_SendChannelMessage(%1, info)

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
 return 1;}

#define channelcheck(%0); if(DCC_FindChannelById(%0) == DCC_INVALID_CHANNEL){ \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't find a channel with such ID or name - please, recheck the channel ID, and submit again.\n\nChannel: <@%s>", %0); \
 return 1;}

#define rolecheck(%0); if(DCC_FindRoleById(%0) == DCC_INVALID_ROLE){ \
 @discord() SendMsg(channel, "> "d_reply" **ERROR** • I can't find a role with such ID or name - please, recheck the role ID, and submit again.\n\nRole: <@&%s>", %0); \
 return 1;}

#define @DISCORD_DECORATOR@command:%0(%1) DISCORD:%0(%1)

#define @DISCORD_DECORATOR@cmd_params DCC_Message:message,DCC_User:author,PARAMETERS[]
#define params PARAMETERS



#define d_beta "<:d_beta:1009087077725519974>"


#define syschannelstring \
""d_reply" **SYSTEM CHANNEL** • This channel was successfully loaded as a system channel. *It is recommended to not delete it or modify it!*"

#define bot 				DCC_FindUserById(BOT_USER_ID)


#define col_embed 0x414040//0x7fff00

#define IST_GOLD 1
#define IST_RUBIES 2
#define IST_RAWMEAT 3
#define IST_COOKEDMEAT 4
#define IST_FRUITS 5
#define IST_MEDICINE 6
#define IST_RAWFISH 7
#define IST_COOKEDFISH 8
#define IST_PLANKS 9
#define IST_PAPER 10
#define IST_BANKNOTE 11

#define antiraid(%0,%1,%2); @discord() SendChannelMessage(channel, ":shield: **ANTI-RAID** • Hi, <@%s>! The bot's anti-raid system has been activated for `%s`! The moderators will be notified.\n\n",%1,%2);

#define botpfp "<:damn_larper:1094703864512512162>"
//"<:damn_larper:1007667783699538061>"//"<:diplomy:1006605884706791494>"
#define d_mask botpfp
#define damn_larper botpfp
#define damn_larper_text "<:damn_larper_text:1094703969651150898>"
#define d_premium "<:d_premium:1094931187027423252>"

#define d_reply "<:d_reply:1007926037511946243>"
#define d_yes "<:d_yes:1006573744787038319>"
#define d_no "<:d_no:1006573728064348230>"
#define d_star "<:d_star:1006574765416398889>"
#define d_point "<:d_point:1006589917356380321>"
#define d_phone "<:d_phone:1006598039466672280>"
#define d_arrow "<:d_arrow:1007929867330924574>"
#define d_coin "<:d_coin:1006610627864829952>"
#define d_gamepad "<:d_gamepad:1006612825013235825>"
#define d_wallet "<:d_wallet:1007669164351164536>"
#define d_heart "<:d_heart:1006632843948064779>"
#define d_pickaxe "<:d_pickaxe:1007195594898550844>"
#define d_ruby "<:d_ruby:1007939594878210120>"
#define d_gold "<:d_gold:1007202547922120756>"
#define d_furnace "<:d_furnace:1007668206346965032>"
#define d_slingshot "<:d_slingshot:1007284099863547964>"
#define d_rawmeat "<:d_rawmeat:1007289107103359086>"
#define d_cookedmeat "<:d_cookedmeat:1007289135091953824>"
#define d_fruits "<:d_fruits:1007394012816212028>"
#define d_medicine "<:d_medicine:1007394053203169442>"
#define d_parrot "<:d_parrot:1007595843215425580>"
#define delimiterlol ""
#define d_fishingrod "<:d_fishingrod:1007940238255083530>"
#define d_rawfish "<:d_rawfish:1007946738344140861>"
#define d_cookedfish "<:d_cookedfish:1007946768769617970>"
#define d_desk "<:d_desk:1008014818013347850>"
#define d_axe "<:d_axe:1008012306640294019>"
#define d_planks "<:d_planks:1008015338618761258>"
#define d_paper "<:d_paper:1008015390766530580>"
#define d_banknote "<:d_banknote:1007992117550911598>"
#define d_laptop "<:d_laptop:1008048319370645544>"
#define d_commonchest "<:d_commonchest:1008080211939708948>"
#define d_rarechest "<:d_rarechest:1008460112853213314>"
//"<:d_premium:1008729855493406780>"
#define d_safe "<:d_safe:1008815134229151805>"
#define d_dog "<:d_dog:1008841252650889286>"
#define d_cat "<:d_cat:1008844391043039262>"
#define d_protectiveshield "<:d_protectiveshield:1094973029953568798>"

#define d_emptybar1 "<:d_emptybar1:1007987935049683036>"
#define d_emptybar2 "<:d_emptybar2:1007987961733840956>"
#define d_emptybar3 "<:d_emptybar3:1007987992058658936>"

#define d_fullbar1 "<:d_fullbar1:1007988024090574940>"
#define d_fullbar2 "<:d_fullbar2:1007988053542973560>"
#define d_fullbar3 "<:d_fullbar3:1007988082341056634>"

#define d_max_bar_points 5

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