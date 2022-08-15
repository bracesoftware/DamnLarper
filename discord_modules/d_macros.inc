// Module written by DEntisT, © & ® BRACE™.

#define SERVER_RISE_OF_NATIONS "RoN • Rise of Nations"

#define CMD_PREFIX '^'
#define MAX_LIST_ELEMENTS 50

#define BOT_USER_ID "954063234938306640"

#define MAX_STAFF_MEMBERS 100

new BOT_BETA_PHASE = 1;
#define BOT_VERSION "Beta @ 1.0"
#define BOT_NAME "Damn Larper"
#define BRACE_TEAM "® 𝐁 𝐑 𝐀 𝐂 𝐄™"

#define modcheck; if(IsUserMod(author)==0) { \
SendChannelMessage(channel,"> "d_reply" **AUTHORIZATION ERROR** • Only the "BRACE_TEAM" team can use this command!");return 1;}

#define premiumcheck(%1); if(GetPremium(%1)==0) { \
SendChannelMessage(channel,"> "d_reply" **NO PREMIUM?** • Only the "BOT_NAME" premium users can use or do this!");return 1;}

#define SettingsCheck(%1); if(settings[%1] == 0) { \
 SendChannelMessage(channel, "> "d_reply" **ERROR** • This command module has been disabled by a bot moderator."); return 1;}

#define servercheck(%1); new DCC_Guild:guild;DCC_GetChannelGuild(channel, guild);if(guild != %1) {\
 SendChannelMessage(channel, "> "d_reply" **ERROR** • I can't do that thing here because this is a custom feature made exclusively for another server!");return 1;}

#define usercheck(%0); if(DCC_FindUserById(%0) == DCC_INVALID_USER){ \
 SendChannelMessage(channel, "> "d_reply" **ERROR** • I can't find an user with such ID or name - please, recheck the user ID, and submit again.\n\nUser: <@%s>", %0); \
 return 1;}

#define channelcheck(%0); if(DCC_FindChannelById(%0) == DCC_INVALID_CHANNEL){ \
 SendChannelMessage(channel, "> "d_reply" **ERROR** • I can't find a channel with such ID or name - please, recheck the channel ID, and submit again.\n\nChannel: <@%s>", %0); \
 return 1;}

#define rolecheck(%0); if(DCC_FindRoleById(%0) == DCC_INVALID_ROLE){ \
 SendChannelMessage(channel, "> "d_reply" **ERROR** • I can't find a role with such ID or name - please, recheck the role ID, and submit again.\n\nRole: <@&%s>", %0); \
 return 1;}

#define @DISCORD_DECORATOR@command:%0(%1) DISCORD:%0(%1)

#define @DISCORD_DECORATOR@cmd_params DCC_Message:message,DCC_User:author,PARAMETERS[]
#define params PARAMETERS

#define RiseOfNations 	DCC_FindGuildById("965261756341559338")

#define bankicklog 			DCC_FindChannelById("1006119258851385404") //d
#define rpnotices 			DCC_FindChannelById("994393758940541100") //d
#define war_gm_output 		DCC_FindChannelById("994393810383675513") //d
#define submissionchannel 	DCC_FindChannelById("994393733879582883") //d
#define dateupdate 			DCC_FindChannelById("994393767836667965") //d
#define supportchannel 		DCC_FindChannelById("1006120126573191221") //d
#define lounge 				DCC_FindChannelById("994393740884062259") //d
#define commandchannel 		DCC_FindChannelById("994393746718326824") //d
#define gm_output 			DCC_FindChannelById("994393764900655224") //d
#define gm_count 			DCC_FindChannelById("1006120493507694622") //d
#define logs 				DCC_FindChannelById("1006560017845067876") //d
#define announcements 		DCC_FindChannelById("994393713461706832") //d
#define countchannel 		DCC_FindChannelById("994393752351285338") //d
#define reports 			DCC_FindChannelById("1006120959356452864") //d
#define appreview 			DCC_FindChannelById("1006140665819824208") //d
#define verifychannel   	DCC_FindChannelById("1006227267048968212") //d

#define rpchannel 			DCC_FindChannelById("994393772605571112") //d
#define rpchannel1 			DCC_FindChannelById("994393773826117762") //d
#define rpchannel2 			DCC_FindChannelById("994393776334311445") //d
#define rpchannel3 			DCC_FindChannelById("994393777911386234") //d
#define rpchannel4 			DCC_FindChannelById("994393780314722486") //d
#define rpchannel5 			DCC_FindChannelById("994393781833043999") //d
#define rpchannel6 			DCC_FindChannelById("994393787805741097") //d
#define rpchannel7 			DCC_FindChannelById("994393789445718066") //d

#define syschannelstring \
""d_reply" **SYSTEM CHANNEL** • This channel was successfully loaded as a system channel. *It is recommended to not delete it or modify it!*"

#define bot 				DCC_FindUserById(""BOT_USER_ID"")
#define muted				DCC_FindRoleByName(RiseOfNations, "Muted Member")
#define RiseOfNationsrole 			DCC_FindRoleByName(RiseOfNations, ""SERVER_RISE_OF_NATIONS"")
#define gm					DCC_FindRoleById("994393513766699051")
#define pgm					DCC_FindRoleById("994393514886561842")

#define nation 				DCC_FindRoleById("994393621182828544")
#define rebelorg 			DCC_FindRoleById("994393625179992125")
#define politicalorg 		DCC_FindRoleById("994393621761638411")
#define acoop 				DCC_FindRoleById("994393624022368397")
#define pcoop 				DCC_FindRoleById("994868405557530676")
#define civilian 			DCC_FindRoleById("994393622856347708")
#define unsec 				DCC_FindRoleById("1000682605458497588")
#define spectator 			DCC_FindRoleById("994393627646234694")
#define playerrole 			DCC_FindRoleById("994393626836750536")
#define corporation 		DCC_FindRoleById("1002196249308581948")

#define standardrole1 		DCC_FindRoleById("994393620406882324")
#define standardrole2 		DCC_FindRoleById("994567140181033061")
#define standardrole3 		DCC_FindRoleById("994393628397019216")
#define standardrole4 		DCC_FindRoleById("994393633866387527")
#define unverified 			DCC_FindRoleById("1006236985066795078")

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

#define antiraid(%0,%1,%2); SendChannelMessage(channel, ":shield: **ANTI-RAID** • Hi, <@%s>! The bot's anti-raid system has been activated for `%s`! The moderators will be notified.\n\n",%1,%2);

#define d_reply "<:d_reply:1007926037511946243>"
#define botpfp "<:damn_larper:1007667783699538061>"//"<:diplomy:1006605884706791494>"
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
#define d_mask botpfp
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
#define d_premium "<:d_premium:1008729855493406780>"

#define d_emptybar1 "<:d_emptybar1:1007987935049683036>"
#define d_emptybar2 "<:d_emptybar2:1007987961733840956>"
#define d_emptybar3 "<:d_emptybar3:1007987992058658936>"

#define d_fullbar1 "<:d_fullbar1:1007988024090574940>"
#define d_fullbar2 "<:d_fullbar2:1007988053542973560>"
#define d_fullbar3 "<:d_fullbar3:1007988082341056634>"

#define d_max_bar_points 5

#define BOT_PREFIX "damn "