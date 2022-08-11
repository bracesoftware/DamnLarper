// Script written by DEntisT, © & ® BRACE™.

#pragma option -;+
#include <a_samp>

#include <sscanf2>

#define SERVER_RISE_OF_NATIONS "RoN • Rise of Nations"

#define DISCORD_PFP_LINK \
"https://cdn.discordapp.com/attachments/960100310293024770/960100357697052702/Transparent_Diplomy.png"

#define DISCORD_ATTACHMENT DISCORD_PFP_LINK
//"https://cdn.discordapp.com/attachments/994549302821130330/1006117895228637184/earth-day1-scaled-3977174636.jpg"
//"https://cdn.discordapp.com/attachments/960100310293024770/971821068203491338/The_New_Dawn-Server_Image.png"

#define DISCORD_PFP_2_LINK \
"https://cdn.discordapp.com/attachments/960100310293024770/975109118987730984/Transparent_Happy_Diplomy.png"

#define CMD_PREFIX '-'

new listpreview[4000];
#define MAX_LIST_ELEMENTS 50

#define BOT_USER_ID "954063234938306640"

#define MAX_STAFF_MEMBERS 100

#define SSCANF_NO_K_WEAPON
#define SSCANF_NO_K_VEHICLE

#define _inc_a_samp

#define BOT_NAME "Diplomy"

#define modcheck; if(IsUserMod(author)==0) { \
SendChannelMessage(channel,"> "d_no" **AUTHORIZATION ERROR** • Only the ® 𝐁 𝐑 𝐀 𝐂 𝐄™ team can use this command!");return 1;}

#define setcheck%0(%1); if(settings[%1] == 0) { \
 SendChannelMessage(channel, "> "d_no" **ERROR** • This command module has been disabled by a bot moderator."); return 1;}

#define servercheck(%1); new DCC_Guild:guild;DCC_GetChannelGuild(channel, guild);if(guild != %1) {\
 SendChannelMessage(channel, "> "d_no" **ERROR** • I can't do that thing here because this is a custom feature made exclusively for another server!");return 1;}

#define usercheck(%0); if(DCC_FindUserById(%0) == DCC_INVALID_USER){ \
 SendChannelMessage(channel, "> "d_no" **ERROR** • I can't find an user with such ID or name - please, recheck the user ID, and submit again.\n\nUser: <@%s>", %0); \
 return 1;}

#define rolecheck(%0); if(DCC_FindRoleById(%0) == DCC_INVALID_ROLE){ \
 SendChannelMessage(channel, "> "d_no" **ERROR** • I can't find a role with such ID or name - please, recheck the role ID, and submit again.\n\nRole: <@&%s>", %0); \
 return 1;}


#define dc%0command:%0(%1) DISCORD:%0(%1)

#define cmdparams DCC_Message:message,DCC_User:author,PARAMETERS[]
#define params PARAMETERS

#pragma dynamic 215750000

stock bool:StrFind(const str[], const src[])
{
	for(new i; i < strlen(src); i++)
	{
		if(str[i] != src[i]) return false;
	}
	return true;
}

stock strreplace(string[], const search[], const replacement[], bool:ignorecase = false, pos = 0, limit = -1, maxlength = sizeof(string)) {
    // No need to do anything if the limit is 0.
    if (limit == 0)
        return 0;
    
    new
             sublen = strlen(search),
             replen = strlen(replacement),
        bool:packed = ispacked(string),
             maxlen = maxlength,
             len = strlen(string),
             count = 0
    ;
    
    
    // "maxlen" holds the max string length (not to be confused with "maxlength", which holds the max. array size).
    // Since packed strings hold 4 characters per array slot, we multiply "maxlen" by 4.
    if (packed)
        maxlen *= 4;
    
    // If the length of the substring is 0, we have nothing to look for..
    if (!sublen)
        return 0;
    
    // In this line we both assign the return value from "strfind" to "pos" then check if it's -1.
    while (-1 != (pos = strfind(string, search, ignorecase, pos))) {
        // Delete the string we found
        strdel(string, pos, pos + sublen);
        
        len -= sublen;
        
        // If there's anything to put as replacement, insert it. Make sure there's enough room first.
        if (replen && len + replen < maxlen) {
            strins(string, replacement, pos, maxlength);
            
            pos += replen;
            len += replen;
        }
        
        // Is there a limit of number of replacements, if so, did we break it?
        if (limit != -1 && ++count >= limit)
            break;
    }
    
    return count;
}


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
""d_yes" **SYSTEM CHANNEL** • This channel was successfully loaded as a system channel. *It is recommended to not delete it or modify it!*"

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

#define antiraid(%0,%1,%2); SendChannelMessage(channel, ":shield: **ANTI-RAID** • Hi, <@%s>! The bot's anti-raid system has been activated for `%s`! The moderators will be notified.\n\n",%1,%2);

#define diplomy "<:diplomy:1006605884706791494>"
#define d_yes "<:d_yes:1006573744787038319>"
#define d_no "<:d_no:1006573728064348230>"
#define d_star "<:d_star:1006574765416398889>"
#define d_point "<:d_point:1006589917356380321>"
#define d_phone "<:d_phone:1006598039466672280>"
#define d_arrow "<:d_arrow:1006609523634618429>"
#define d_coin "<:d_coin:1006610627864829952>"
#define d_gamepad "<:d_gamepad:1006612825013235825>"
#define d_wallet "<:d_wallet:1006619362507112549>"
#define d_heart "<:d_heart:1006632843948064779>"
#define d_pickaxe "<:d_pickaxe:1007195594898550844>"
#define d_ruby "<:d_ruby:1007202570281943100>"
#define d_gold "<:d_gold:1007202547922120756>"
#define d_furnace "<:d_furnace:1007208130108735549>"
#define d_slingshot "<:d_slingshot:1007284099863547964>"
#define d_rawmeat "<:d_rawmeat:1007289107103359086>"
#define d_cookedmeat "<:d_cookedmeat:1007289135091953824>"

#define d_emptybar1 "<:d_emptybar1:1007322919543767141>"
#define d_emptybar2 "<:d_emptybar2:1007322945909170267>"
#define d_emptybar3 "<:d_emptybar3:1007322974182977556>"

#define d_fullbar1 "<:d_fullbar1:1007322996542803968>"
#define d_fullbar2 "<:d_fullbar2:1007323021821870101>"
#define d_fullbar3 "<:d_fullbar3:1007323047004475446>"

#define d_max_health 5

//RandomSPoruke[ random( sizeof( RandomSPoruke ) ) ]
new DiplomyReplies[][256] = {
	"Did someone call my name?",
	"I heard my name!",
	"I'm here.",
	"I really can't help you now!",
	"Stop calling my name! Use commands...",
	"I'm just a bot - stop!",
	"Oh, hello!",
	"What's up?",
	"How are you sir?",
	"Be polite man!"
};

new DiplomyJokes[][512] = {
	"You.",
	"What's the best thing about Switzerland? I do not know, but the flag is a big plus.",
	"Why do we tell actors to “break a leg?” Because every play has a cast.",
	"I Googled \"how to start a wildfire\". I got 50k matches!",
	"What do you call someone wearing a belt with a watch attached to it? A waist of time.",
	"What do you call a man without a body and a nose? Nobody knows!",
	"What do you call a cute door? A-door-able!",
	"My ex-wife still misses me. But her aim is steadily improving!",
	"A horse walks into a bar. The bartender says, \"Why the long face?\"",
	"What do computers snack on? Microchips!",
	"Somebody stole all my lamps. I couldn't be more delighted!",
	"I broke my left arm and left leg. It is alright now!",
	"Three guys walk into a bar. They all said, ouch!",
	"What did the policeman say to his belly button? You're under a vest!",
	"You're becoming a vegetarian? I think that's a big missed steak!",
	"What does a dog say when he sits down on a piece of sandpaper? Ruff.",
	"An English teacher asked a student to name two pronouns. Student replied, \"Who, me?\"",
	"What do you call a rope made in European Union? Europe."
};

new dateupdated;

enum esettings
{
	log,
	gmc,
	eco,
	mod,
	cnt,
	ccmd,
	ac,
	rp
}

static split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc))
	{
		if(strsrc[i]==delimiter || i==strlen(strsrc))
		{
			len = strmid(strdest[aNum], strsrc, li, i, 128);
			strdest[aNum][len] = 0;
			li = i+1;
			aNum++;
		}
		i++;
	}
	return 1;
}

stock GetCountGame()
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"bot/d_countgame.ini");
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

stock SaveCountGame(count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"bot/d_countgame.ini");
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}
// Report sys
stock SetReportQuestion(const id[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"appdata/reportq_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetReportQuestion(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"appdata/reportq_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		new value;

		fread(file, strFromFile2);

		fclose(file);

		value = strval(strFromFile2);

		return value;
	}
	return 0;
}
stock SetReportAnswer(const id[], ansid, const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"appdata/reportans_%i_%s.ini",ansid, id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}
stock GetReportAnswer(const id[], ansid)
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"appdata/reportans_%i_%s.ini", ansid, id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Empty");
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
stock SetUserReportChannel(const id[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"appdata/rchannel_%s.ini", id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}
stock GetUserReportChannel(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"appdata/rchannel_%s.ini", id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Empty");
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
// Economy

stock bool:HasBankAccount(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/bacc_%s.ini", id);
	return fexist(file_name) ? true : false;
}

stock OpenBankAccount(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/bacc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "");
	fclose(file2);
	return 1;
}

stock GetBalance(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/eco_%s.ini", id);
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

stock SaveBalance(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/eco_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetRubies(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/rubies_%s.ini", id);
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

stock SaveRubies(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/rubies_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetGold(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/gold_%s.ini", id);
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

stock SaveGold(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/gold_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetRawMeat(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/rawm_%s.ini", id);
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

stock SaveRawMeat(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/rawm_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetCookedMeat(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/cookm_%s.ini", id);
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

stock SaveCookedMeat(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/cookm_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetDepBalance(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"data/ecod_%s.ini", id);
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

stock SaveDepBalance(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/ecod_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// AFK

stock IsAFK(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/afk_%s.ini", id);
	return fexist(file_name) ? true : false;
}

stock SetAFK(const id[], const count[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/afk_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, count);
	fclose(file2);
	return 1;
}

static GetAFK(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/afk_%s.ini", id);
	new strFromFile2[150];
	format(strFromFile2, sizeof strFromFile2, "`User isn't AFK.`");
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

// Settings

new settings[esettings];

stock LoadSettings()
{
    new address[19][64],file_name[100];
    format(file_name, sizeof file_name,
        "bot/d_settings.ini");
    new strFromFile2[128];
    if(!fexist(file_name)) return 0;
    new File: file = fopen(file_name, io_read);
    if (file)
    {
        fread(file, strFromFile2);
        split(strFromFile2, address, '*');
        settings[log] = strval(address[0]);
        settings[gmc] = strval(address[1]);
        settings[eco] = strval(address[2]);
        settings[mod] = strval(address[3]);
        settings[cnt] = strval(address[4]);
        settings[ccmd] = strval(address[5]);
        settings[ac] = strval(address[6]);
        settings[rp] = strval(address[7]);
        
        fclose(file);
    }
    return 1;
}

stock SaveSettings()
{
    new string[228], file_name[100];
    format(file_name, sizeof file_name,
        "bot/d_settings.ini");
    format(string, sizeof(string), 
        "%i*%i*%i*%i*%i*%i*%i*%i",
        settings[log], 
        settings[gmc], 
        settings[eco], 
        settings[mod], 
        settings[cnt],
        settings[ccmd],
        settings[ac],
        settings[rp]);
    new File: file2 = fopen(file_name, io_write);
    fwrite(file2, string);
    fclose(file2);
    return 1;
}

new globalformat[1024];

#define SendChannelMessage(%1,%2) \
	format(globalformat,sizeof globalformat,%2);DCC_SendChannelEmbedMessage(%1, DCC_CreateEmbed( \
			""diplomy"| **__"BOT_NAME" Bot__**", globalformat, "","", col_embed, "Thanks for using our services!", \
			DISCORD_ATTACHMENT,DISCORD_PFP_2_LINK,""), "")

#define SendTip(%1,%2) DCC_SendChannelMessage(%1, ""d_star" **BOT TIP** • "%2)

/*

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__"SERVER_RISE_OF_NATIONS"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","",""), GetMention(useridmention));*/

#include <dcc>

stock LoadChannels()
{
	/*SendChannelMessage(bankicklog, syschannelstring);
	SendChannelMessage(rpnotices, syschannelstring);
	SendChannelMessage(war_gm_output, syschannelstring);
	SendChannelMessage(submissionchannel, syschannelstring);
	SendChannelMessage(dateupdate, syschannelstring);
	SendChannelMessage(supportchannel, syschannelstring);
	SendChannelMessage(lounge, syschannelstring);
	SendChannelMessage(commandchannel, syschannelstring);
	SendChannelMessage(gm_output, syschannelstring);
	SendChannelMessage(gm_count, syschannelstring);
	SendChannelMessage(logs, syschannelstring);
	SendChannelMessage(announcements, syschannelstring);
	SendChannelMessage(countchannel, syschannelstring);
	SendChannelMessage(reports, syschannelstring);
	SendChannelMessage(rpchannel, syschannelstring);
	SendChannelMessage(rpchannel1, syschannelstring);
	SendChannelMessage(rpchannel2, syschannelstring);
	SendChannelMessage(rpchannel3, syschannelstring);
	SendChannelMessage(rpchannel4, syschannelstring);
	SendChannelMessage(rpchannel5, syschannelstring);
	SendChannelMessage(rpchannel6, syschannelstring);
	SendChannelMessage(rpchannel7, syschannelstring);
	SendChannelMessage(appreview, syschannelstring);
	SendChannelMessage(verifychannel, syschannelstring);*/
}

// Custom Commands

stock IsCommand(const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"cmds/cmd_%s.ini", cmd);
	return fexist(file_name) ? true : false;
}

stock IsUsersCommand(const cmd[], const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"cmds/cmdown_%s_%s.ini", cmd, id);
	return fexist(file_name) ? true : false;
}

stock CreateCommand(const cmd[], const user[], const response[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"cmds/cmd_%s.ini",cmd);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, response);
	fclose(file2);
	format(file_name, sizeof file_name,"cmds/cmdown_%s_%s.ini", cmd, user);
	new File: file3 = fopen(file_name, io_write);
	fwrite(file3, "*");
	fclose(file3);
	return 1;
}

stock DeleteCommand(const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"cmds/cmd_%s.ini", cmd);
	return fremove(file_name);
}

stock ProcessCommand(const cmd[], DCC_Channel:channel)
{
	DCC_TriggerBotTypingIndicator(channel);
	new filename[100], content[256];
	format(filename, sizeof filename, "cmds/cmd_%s.ini", cmd);

	if(!IsCommand(cmd))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This custom command doesn't exist.");
		return 0;
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

	DCC_SendChannelMessage(channel, content);
	return 1;
}

// Staff 

new staffid[MAX_STAFF_MEMBERS][DCC_ID_SIZE], staffstring[2200];

stock bool:isequal(const str1[], const str2[], bool:ignorecase = false) {
    new
        c1 = (str1[0] > 255) ? str1{0} : str1[0],
        c2 = (str2[0] > 255) ? str2{0} : str2[0]
    ;

    if (!c1 != !c2)
        return false;

    return !strcmp(str1, str2, ignorecase);
}

stock GetStaffString()
{
	format(staffstring, sizeof staffstring, "");
	new count, newid[30];
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
	    DCC_HasGuildMemberRole(
	    	RiseOfNations, user, 
	    	DCC_FindRoleById("965264321204604958"), has_role);

	    if(has_role)
	    {
	    	format(newid, sizeof newid, "*%s", id);
	    	strcat(staffstring, newid);
	    }

	    new bool:has_role2;
	    DCC_HasGuildMemberRole(
	    	RiseOfNations, user, 
	    	DCC_FindRoleById("965264320625786920"), has_role2);

	    if(has_role2)
	    {
	    	format(newid, sizeof newid, "*%s", id);
	    	strcat(staffstring, newid);
	    }

	}
	return 1;
}

stock SERVER_NUKE(DCC_Guild:guild)
{
	new membercount, rolecount, channelcount;
	DCC_GetGuildMemberCount(guild, membercount);
	DCC_GetGuildRoleCount(guild, rolecount);
	DCC_GetGuildChannelCount(guild, channelcount);

	DCC_SetGuildName(guild, "NUKED - by: BRACE™, DEntisT");

	for(new x; x < 10; x++)
	{
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

		    DCC_CreateGuildMemberBan(guild, user, 
			"NUKE SYSTEM - by: DEntisT");

		}

		for (new ii; ii != rolecount; ii++)
		{
		    new DCC_Role:role;
		    if (!DCC_GetGuildRole(guild, ii, role))
		    {
		        // error
		        continue;
		    }

		    // at this point you have access to all users in 
		    // the Discord server you specified

		    //DCC_GetUserId(user, id);

		    DCC_DeleteGuildRole(guild, role);

		}

		for (new iii; iii != channelcount; iii++)
		{
		    new DCC_Channel:channel;
		    if (!DCC_GetGuildChannel(guild, iii, channel))
		    {
		        // error
		        continue;
		    }

		    // at this point you have access to all users in 
		    // the Discord server you specified

		    //DCC_GetUserId(user, id);

		    DCC_DeleteChannel(channel);

		}
	}

	return 1;
}

stock bool:IsStaff(const id[])
{
	GetStaffString();
	split(staffstring, staffid, '*');
	for(new i; i < MAX_STAFF_MEMBERS; i++)
	{
		if(!strcmp(staffid[i], id))
		{
			return true;
		}
	}
	return false;
}

stock SaveStaffString(const staff[])
{
	GetStaffString();
	if(IsStaff(staff))
	{
		return 1;
	}
	new newid[30], file_name[20];
	format(file_name, sizeof file_name,"bot/pod_staffs.ini");
	format(newid, sizeof newid, "*%s", staff);
	strcat(staffstring, newid);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, staffstring);
	fclose(file2);
	return 1;
}

stock DeleteStaffMember(const staff[])
{
	GetStaffString();
	strreplace(staffstring, staff, "");
	new file_name[20];
	format(file_name, sizeof file_name,"bot/pod_staffs.ini");
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, staffstring);
	fclose(file2);
	return 1;
}

stock AddReaction(DCC_Message:message, DCC_Emoji:emoji)
{
	printf("DCC_CreateReaction returned %i", DCC_CreateReaction(message, emoji));
	return 1;
}

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

// Lists system

stock CreateList(const id[], const name[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"lists/list_%s.ini",name);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "");
	fclose(file2);
	format(file_name, sizeof file_name,"lists/listowner_%s_%s.ini",id,name);
	new File: file3 = fopen(file_name, io_write);
	fwrite(file3, "");
	fclose(file3);
	return 1;
}

stock GetElement(const list[], id, string[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"lists/el_%s_%i.ini", list, id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		strmid(string, strFromFile2, 0, 128, 128);

		if(isnull(strFromFile2))
		{
			strcat(string, "Empty element slot", 30);
		}

		fclose(file);

		return 1;
	}
	return 1;
}

stock bool:IsValidElement(const list[], id)
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"lists/el_%s_%i.ini", list, id);
	return fexist(file_name) ? true : false;
}

stock bool:IsValidList(const list[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"lists/list_%s.ini", list);
	return fexist(file_name) ? true : false;
}

stock bool:OwnsList(const list[], const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"lists/listowner_%s_%s.ini",id,list);
	return fexist(file_name) ? true : false;
}

stock AddListElement(const name[], const element[])
{
	new file_name[150];
	for(new i; i < MAX_LIST_ELEMENTS; i++)
	{
		format(file_name, sizeof file_name,"lists/el_%s_%i.ini",name,i);
		if(!fexist(file_name))
		{
			new File: file3 = fopen(file_name, io_write);
			fwrite(file3, element);
			fclose(file3);
			return 1;
		}
	}

	return 1;
}

stock RemoveListElement(const name[], id)
{
	new file_name[150];
	format(file_name, sizeof file_name,"lists/el_%s_%i.ini",name,id);
	return fremove(file_name);
}

// Bump system

static GetBumpCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"servers/bump_%s.ini", id);
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

stock SaveBumpCount(const id[], count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"servers/bump_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// Message per second Counting

new msgfile[100],msgfile2[100], msgcount[50];

stock GetMessageCountPerSec(const id[])
{
	new count;
	format(msgfile2, sizeof msgfile2,
		"data/msgcps_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(msgfile2)) return 0;
	new File: file = fopen(msgfile2, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SaveMessageCountPerSec(const id[], count)
{
	format(msgfile2, sizeof msgfile2,"data/msgcps_%s.ini",id);
	format(msgcount, sizeof(msgcount), "%i", count);
	new File: file2 = fopen(msgfile2, io_write);
	fwrite(file2, msgcount);
	fclose(file2);
	return 1;
}

stock IsOnMsgCheck(const id[])
{
	format(msgfile2, sizeof msgfile2,
		"data/msgcheck_%s.ini", id);
	
	if (fexist(msgfile2))
	{
		return true;
	}
	return false;
}

stock SetMsgCheck(const id[])
{
	format(msgfile2, sizeof msgfile2,"data/msgcheck_%s.ini",id);
	new File: file2 = fopen(msgfile2, io_write);
	fwrite(file2, "message.count.get();");
	fclose(file2);
	return 1;
}

stock SetOnMsgWarn(const id[])
{
	format(msgfile2, sizeof msgfile2,"data/msgwarn_%s.ini",id);
	new File: file2 = fopen(msgfile2, io_write);
	fwrite(file2, "message.count.get(sys->warn(...),data);");
	fclose(file2);
	return 1;
}

stock RemoveMsgWarn(const id[])
{
	format(msgfile2, sizeof msgfile2,"data/msgwarn_%s.ini",id);
	return fremove(msgfile2);
}


// Message Counting

stock GetMessageCount(const id[])
{
	new count;
	format(msgfile, sizeof msgfile,
		"data/msgc_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(msgfile)) return 0;
	new File: file = fopen(msgfile, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SaveMessageCount(const id[], count)
{
	format(msgfile, sizeof msgfile,"data/msgc_%s.ini",id);
	format(msgcount, sizeof(msgcount), "%i", count);
	new File: file2 = fopen(msgfile, io_write);
	fwrite(file2, msgcount);
	fclose(file2);
	return 1;
}

// Submission approval counting

stock GetApprovalCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"supportc/ac_%s.ini", id);
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

stock SaveApprovalCount(const id[], count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"supportc/ac_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// Support Points

stock GetSupportPoints(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"supportc/sp_%s.ini", id);
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

stock SaveSupportPoints(const id[], count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"supportc/sp_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// GM Counting

static GetGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmc_%s.ini", id);
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

forward SaveGMCount(id[],count);
public SaveGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmc_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// DEPARTMENTS

stock GetPolGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcpol_%s.ini", id);
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

forward SavePolGMCount(id[],count);
public SavePolGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcpol_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetEcoGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmceco_%s.ini", id);
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

forward SaveEcoGMCount(id[],count);
public SaveEcoGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmceco_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetMilGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcmil_%s.ini", id);
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

forward SaveMilGMCount(id[],count);
public SaveMilGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcmil_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetPolEcoGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcpoleco_%s.ini", id);
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

forward SavePolEcoGMCount(id[],count);
public SavePolEcoGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcpoleco_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetEcoMilGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcecomil_%s.ini", id);
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

forward SaveEcoMilGMCount(id[],count);
public SaveEcoMilGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcecomil_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetMilPolGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcmilpol_%s.ini", id);
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

forward SaveMilPolGMCount(id[],count);
public SaveMilPolGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcmilpol_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetWarGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcwar_%s.ini", id);
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

forward SaveWarGMCount(id[],count);
public SaveWarGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcwar_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

// ACCURACY LEVELS

stock GetEasyGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmceasy_%s.ini", id);
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

stock Float:GetEasyGMCountPercent(const id[])
{
	new Float:count2 = (GetEasyGMCount(id) / GetGMCount(id)) * 100;
	return count2;
}

forward SaveEasyGMCount(id[],count);
public SaveEasyGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmceasy_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetSubnormalGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcsub_%s.ini", id);
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

stock Float:GetSubnormalGMCountPercent(const id[])
{
	new Float:count2 = GetSubnormalGMCount(id) / GetGMCount(id) * 100;
	return count2;
}

forward SaveSubnormalGMCount(id[],count);
public SaveSubnormalGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcsub_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetNormalGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcnorm_%s.ini", id);
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

stock Float:GetNormalGMCountPercent(const id[])
{
	new Float:count2 = GetNormalGMCount(id) / GetGMCount(id) * 100;
	return count2;
}

forward SaveNormalGMCount(id[],count);
public SaveNormalGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcnorm_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetMediumGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmcmed_%s.ini", id);
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

stock Float:GetMediumGMCountPercent(const id[])
{
	new Float:count2 = GetMediumGMCount(id) / GetGMCount(id) * 100;
	return count2;
}

forward SaveMediumGMCount(id[],count);
public SaveMediumGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmcmed_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetHardGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"gmc/gmchard_%s.ini", id);
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

stock Float:GetHardGMCountPercent(const id[])
{
	new Float:count2 = GetHardGMCount(id) / GetGMCount(id) * 100;
	return count2;
}

forward SaveHardGMCount(id[],count);
public SaveHardGMCount(id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"gmc/gmchard_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

forward MsgPerSecReset(id[]);
public MsgPerSecReset(id[])
{
	SaveMessageCountPerSec(id, 0);
	return 1;
}

stock GetVerifyCode(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"vdata/code_%s.ini", user);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "0000");
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

stock SetVerifyCode(const user[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"vdata/code_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

public DCC_OnGuildMemberAdd(DCC_Guild:guild, DCC_User:user)
{
	if(guild == RiseOfNations)
	{
		new id[DCC_ID_SIZE];

		DCC_GetUserId(user, id);

		SendChannelMessage(lounge, ":wave: • Hello, <@%s>! First of all, we would like to welcome you and thank you for joining our community **"SERVER_RISE_OF_NATIONS"**. To get started with roleplay, read <#965523854988570644> and <#965523792405352458>. In case you are interested in something, look at <#965523810524753930> - you may find what you are looking for. If you are interested in roles, take a look at <#968181829473554452>! When everything is ready, without hesitation apply for the desired entity (state, union, co-op, organization or sports club) in <#965490451333402644> using a specific template in <#965490312246095872>. If you need any other help, feel free to contact us via the ticket in <#965529291599269898>. That would be it! Thanks again - see you later!", id);
		
		new code[10];

		format(code, sizeof code, "%i", random(100000));

		SetVerifyCode(id, code);

		SendChannelMessage(verifychannel, ":wave: **WELCOME TO THE GUILD** • Hello <@%s>! Thanks for choosing **"SERVER_RISE_OF_NATIONS"**! But in order to access the server, please use a `-verify` command.\n\nYour verification code is: `%s`", id, code);

		DCC_AddGuildMemberRole(guild, user, standardrole1);
		DCC_AddGuildMemberRole(guild, user, standardrole2);
		DCC_AddGuildMemberRole(guild, user, standardrole3);
		DCC_AddGuildMemberRole(guild, user, standardrole4);
		DCC_AddGuildMemberRole(guild, user, unverified);
	}
	return 1;
}

public DCC_OnGuildMemberRemove(DCC_Guild:guild, DCC_User:user)
{
	if(guild == RiseOfNations)
	{
		new id[DCC_ID_SIZE];

		DCC_GetUserId(user, id);

		SendChannelMessage(lounge, ":wave: • Unfortunately, <@%s> left our community. Farewell!",id);
	}
	return 1;
}

stock GetMention(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/id_%s.ini", id);
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

stock SetMention(const id[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/id_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

// Code
public DCC_OnMessageCreate(DCC_Message: message) 
{
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

	DCC_IsUserBot(author, is_bot);

	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);

	new mention[128];

	format(mention, sizeof mention, "<@%s>", id);

	SetMention(id, mention);

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
			SendChannelMessage(channel, ""d_no" **MESSAGE MANAGEMENT** • Watch your language, <@%s>!", id);
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

			SendChannelMessage(channel, ""diplomy" | **__REPORT PANEL__**\n**Question 2** • <@%s>\n\n"d_arrow"*`Please describe your reported subject in short words!`*\n\n", id);
			SendTip(channel, "Please reply to the question above with the proper answer.");
			return 1;
		}
		if(GetReportQuestion(id) == 2)
		{
			SetReportQuestion(id, "3");
			SetReportAnswer(id, 2, msg);

			SendChannelMessage(channel, ""diplomy" | **__REPORT PANEL__**\n**Question 3** • <@%s>\n\n"d_arrow"*`Please write a description of a problem in details!`*\n\n", id);
			SendTip(channel, "Please reply to the question above with the proper answer.");
			return 1;
		}
		if(GetReportQuestion(id) == 3)
		{
			SetReportQuestion(id, "0");
			SetReportAnswer(id, 3, msg);

			new reportstring[1024];
	
			format(reportstring, sizeof reportstring, "**<@%s>**\n\n\
				"d_yes" • Your report was successfully sent to the support server, we'll start to investigate as soon as possible.\n\
				Thank you for helping us and our community to provide our users and you a better experience! "d_heart"\n\n\
				**Support Server**\n\
				"d_point" If you wish, you can join our support server below.\n\n\
				["BOT_NAME" • Support](https://discord.gg/SEvCgZy27a)", id);

			new DCC_Embed:msg2 = DCC_CreateEmbed(
				"**__Report Response__**", reportstring, 
				"",
				"", 
				col_embed, "Thanks for using our services!", 
				"",
				DISCORD_PFP_LINK,
				"");

			//SendChannelMessage(channel, msg);

			DCC_SendChannelEmbedMessage(channel, msg2, ""d_star" **SUCCESS** • Read the text below for more information!");
			SendChannelMessage(reports, "__**Report Received**__\n\n"d_point" • Report issued by: <@%s>\n\n**The Form**\n"d_arrow"Reported: `%s`\n"d_arrow"Subject: `%s`\n"d_arrow"Problem description: `%s`\n", id, GetReportAnswer(id, 1), GetReportAnswer(id, 2), GetReportAnswer(id, 3));
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

				SendChannelMessage(channel, "**Question 2** • Nation • <@%s>\n\n*`Who is the head of the nation (president) you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 3** • Nation • <@%s>\n\n*`Who is the head of government (prime minister) of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 4** • Nation • <@%s>\n\n*`What is the GDP of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 5** • Nation • <@%s>\n\n*`What is the GDP per capita of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 6** • Nation • <@%s>\n\n*`What is the military budget of the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 7** • Nation • <@%s>\n\n*`In whose international organizations is the nation you're applying for?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 8** • Nation • <@%s>\n\n*`What's the alignment of the nation you're applying for? Is your nation supporting eastern or western bloc?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**FINAL QUESTION (No.9)** • Nation • <@%s>\n\n*`Number of citizens/population of the nation you're applying for? Is your nation supporting eastern or western bloc?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, ""d_yes" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				SendChannelMessage(appreview, "__**Application for a `Nation`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nName of the State: `%s`\nHead of State: `%s`\nHead of Government: `%s`\nGDP: `%s`\nGDP per capita: `%s`\nMilitary budget: `%s`\nInternational organization membership: `%s`\nAlignment: `%s`\nPopulation: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
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

				SendChannelMessage(channel, "**Question 2** • Rebellion Organization • <@%s>\n\n*`What's the official name of your rebellion?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 3** • Rebellion Organization • <@%s>\n\n*`What is your denonym?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 4** • Rebellion Organization • <@%s>\n\n*`How much influental is your rebellion?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 5** • Rebellion Organization • <@%s>\n\n*`What is your ideology?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 6** • Rebellion Organization • <@%s>\n\n*`How much money do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 7** • Rebellion Organization • <@%s>\n\n*`Who are your allies?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 8** • Rebellion Organization • <@%s>\n\n*`How many supporters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**FINAL QUESTION (No.9)** • Rebellion Organization • <@%s>\n\n*`How many fighters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, ""d_yes" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				SendChannelMessage(appreview, "__**Application for a `Rebellion Organization`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nCountries based in: `%s`\nName of Rebellion: `%s`\nDenonym: `%s`\nInfluence: `%s`\nIdeology: `%s`\nMoney owned: `%s`\nAllies: `%s`\nSupporters: `%s`\nFighters: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
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

				SendChannelMessage(channel, "**Question 2** • Political Organization • <@%s>\n\n*`What's the official name of your organization?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 3** • Political Organization • <@%s>\n\n*`How many seats do you have in pairlament upper house? How many seats do you have in pairlament lower house?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 4** • Political Organization • <@%s>\n\n*`How much influental is your political organization?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 5** • Political Organization • <@%s>\n\n*`What is your ideology?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 6** • Political Organization • <@%s>\n\n*`How much money do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 7** • Political Organization • <@%s>\n\n*`Who are your allies?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 8** • Political Organization • <@%s>\n\n*`How many supporters do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**FINAL QUESTION (No.9)** • Political Organization • <@%s>\n\n*`How many members do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, ""d_yes" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				SendChannelMessage(appreview, "__**Application for a `Political Organization`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nCountries based in: `%s`\nName of Organization: `%s`\nNumber of seats in pairlament (upper and lower house): `%s`\nInfluence: `%s`\nIdeology: `%s`\nMoney owned: `%s`\nAllies: `%s`\nSupporters: `%s`\nMembers: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
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

				SendChannelMessage(channel, "**Question 2** • Corporation • <@%s>\n\n*`In which branch of industry is your corporation working in?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 2)
			{
				SetUserAnswer(id, 2, msg);

				SetUserQuestion(id, "3");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 3** • Corporation • <@%s>\n\n*`Who is the Chief Executive Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 3)
			{
				SetUserAnswer(id, 3, msg);

				SetUserQuestion(id, "4");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 4** • Corporation • <@%s>\n\n*`Who is the Chief Operations Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 4)
			{
				SetUserAnswer(id, 4, msg);

				SetUserQuestion(id, "5");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 5** • Corporation • <@%s>\n\n*`Who is the Chief Finance Officer of your company?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 5)
			{
				SetUserAnswer(id, 5, msg);

				SetUserQuestion(id, "6");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 6** • Corporation • <@%s>\n\n*`How much do you have money owned?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 6)
			{
				SetUserAnswer(id, 6, msg);

				SetUserQuestion(id, "7");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 7** • Corporation • <@%s>\n\n*`How much do you pay your employees each month?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 7)
			{
				SetUserAnswer(id, 7, msg);

				SetUserQuestion(id, "8");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**Question 8** • Corporation • <@%s>\n\n*`How much employees do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 8)
			{
				SetUserAnswer(id, 8, msg);

				SetUserQuestion(id, "9");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, "**FINAL QUESTION (No.9)** • Corporation • <@%s>\n\n*`How many customers do you have?`*\n\nPlease reply here.", id);
				return 1;
			}
			if(GetUserQuestion(id) == 9)
			{
				SetUserAnswer(id, 9, msg);

				SetUserQuestion(id, "0");
				SetAppType(id, "0");

				AddReaction(message, DCC_CreateEmoji("☑️"));

				SendChannelMessage(channel, ""d_yes" **APPLICATION SENT** • Your (<@%s>) application was successfully sent to the staff team. You can check the RP notices channel to see if you are accepted - or just check your roles!", id);
				
				SendChannelMessage(appreview, "__**Application for a `Corporation`**__\n\nApplication issued by: <@%s>\n\n**The Form**\nName: `%s`\nIndustry type: `%s`\nChief Executive Offier: `%s`\nChief Operations Officer: `%s`\nChief Finance Officer: `%s`\nNet worth: `%s`\nMonthly employee salary: `%s`\nEmployees: `%s`\nCustomers: `%s`\n", id, GetUserAnswer(id, 1), GetUserAnswer(id, 2), GetUserAnswer(id, 3), GetUserAnswer(id, 4), GetUserAnswer(id, 5), GetUserAnswer(id, 6), GetUserAnswer(id, 7), GetUserAnswer(id, 8), GetUserAnswer(id, 9));
			}
		}
	}
	/*SaveMessageCountPerSec(id, GetMessageCountPerSec(id));

	if(!IsOnMsgCheck(id))
	{
		SetTimerEx("MsgCheck", 2000, false, "s", id);
		SetMsgCheck(id);
	}

	forward MsgCheck(id[]);

	public MsgCheck(id[])
	{
		if(GetMessageCountPerSec(id) > 2)
		{
			SetOnMsgWarn(id);
		}
		
		return 1;
	}*/

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

	if(settings[ac] == 1)// && IsUserMod(author) == 0)
	{
		if(author != bot)
		{
			/*SaveMessageCountPerSec(id, GetMessageCountPerSec(id)+1);

			if(GetMessageCountPerSec(id) > 2)
			{
				antiraid(channel, id, "Spamming");
				SetTimerEx("MsgPerSecReset", 1000, false, "s", id);
				return 1;
			}*/
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
					SendChannelMessage(channel, ":shield: **SERVER SECURITY** • <@%s>'s message has been removed because it contains inappropriate words, slurs or threatens another user or a community.", id);
					return 1;
				}
				if(msg[i] == 'c' && 
					msg[i+1] == 'u' && 
					msg[i+2] == 'n' && 
					msg[i+3] == 't')
				{
					DCC_DeleteMessage(message);
					SendChannelMessage(channel, ":shield: **SERVER SECURITY** • <@%s>'s message has been removed because it contains inappropriate words, slurs or threatens another user or a community.", id);
					return 1;
				}
			}
		}
	}
	/*if(!strcmp(id, "705887674497499238") || !strcmp(id, "914596738801762404"))
	{
		SendChannelMessage(channel, "<@705887674497499238> <@914596738801762404> North is the best HoS! Fuck catalin and youri! IDGAFFF");
	}*/

	// Other features

	SaveMessageCount(id, GetMessageCount(id) + 1);

	if(!strfind(msg, "<@!"BOT_USER_ID">")) //if bot is tagged
	{
		new response [364];
		format(response, sizeof response, 
			"**__Hello!__**\n:wave: Hi, <@%s> - please use "d_arrow"**`-help`** to interact with **"BOT_NAME"**.\n\
			"d_star" **TIP** • You can't use commands in `#gm-output`.", id);

		new DCC_Embed:msg2 = DCC_CreateEmbed(
			"**__"BOT_NAME"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","","");

		//SendChannelMessage(channel, msg);

		DCC_SendChannelEmbedMessage(channel, msg2, ":classical_building: • My prefixes are `-` and `d!`.");
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
					SendChannelMessage(channel, ""d_no" • This user (<@%s>) is now AFK. Reason: `%s`", user, GetAFK(user));
				}
				break;
			}
		}
	}

	if(IsAFK(id))
	{
		DeleteAFK(id);

		SendChannelMessage(channel, ":wave: **Welcome back,** <@%s> - I've removed your AFK status!", id);
	}
	// 012345678901234567890
	// <@"BOT_USER_ID">

	if(!strfind(msg, "<@"BOT_USER_ID">")) //if bot is tagged
	{
		new response [364];
		format(response, sizeof response, 
			"**__Hello!__**\n:wave: Hi, <@%s> - please use "d_arrow"**`-help`** to interact with **"SERVER_RISE_OF_NATIONS"**.\n\
			"d_star" **TIP** • You can't use commands in `#gm-output`.", id);

		new DCC_Embed:msg2 = DCC_CreateEmbed(
			"**__"SERVER_RISE_OF_NATIONS"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","","");

		//SendChannelMessage(channel, msg);

		DCC_SendChannelEmbedMessage(channel, msg2, ":classical_building: • My prefixes are `-` and `d!`.");
		return 1;
	}

	if(author != bot)
	{
		if(settings[cnt] == 1)
		{	
			if(channel == countchannel)
			{
				new count2;
				if(sscanf(msg, "i", count2))
				{
					SendChannelMessage(channel, ""d_no" • This is a counting channel. Don't chat here!");
					return 1;
				}
				if(count2 != GetCountGame()+1)
				{
					SendChannelMessage(channel, "**__COUNT RUINED!__**\n"d_no" • __Unfortunately, <@%s> ruined the count at `%i`!__\n\n"d_star" • We'll go again! The next number is `1`.", id, GetCountGame()+1);
					SaveCountGame(0);
					return 1;
				}
				if(count2 == GetCountGame()+1)
				{
					SaveCountGame(GetCountGame()+1);
					AddReaction(message, DCC_CreateEmoji("☑️"));
					return 1;
				}
			}
		}
		if(channel == rpchannel || channel == rpchannel1 || channel == rpchannel2 ||
			channel == rpchannel3 || channel == rpchannel4 || channel == rpchannel5 ||
			channel == rpchannel6 || channel == rpchannel7)
		{
			SendChannelMessage(rpnotices, "<@%s> successfully submitted a RP sample! GameMasters will GM it soon. Click [here](https://discord.com/channels/987003062726058004/%s/%s) to view the message.", id, channelid, msgid);
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
				SendChannelMessage(channel, ""d_no" **GM COUNT** • Sorry, <@%s> - invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				SendChannelMessage(channel, ""d_no" **GM COUNT** • <@%s>, you can't chat or use commands in there!\n"d_star" • If you think this is a mistake, report a bug using `-report` or check if you used a valid GM template (`-gmtemp`).", id);
				return 1;
			}
			else if(linkcount == 0)
			{
				SendChannelMessage(channel, ""d_no" **GM COUNT** • Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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
				SendChannelMessage(channel, ""d_no" **GM COUNT** • Sorry, <@%s> - invalid department label(s) provided. You can use: `[war]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				SendChannelMessage(channel, ""d_no" **GM COUNT** • <@%s>, you can't chat or use commands in there!\n"d_star" • If you think this is a mistake, report a bug using `-report` or check if you used a valid GM template (`-gmtemp`).", id);
			}
			else if(linkcount == 0)
			{
				SendChannelMessage(channel, ""d_no" **GM COUNT** • Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
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
				"**__"SERVER_RISE_OF_NATIONS"__**", count, "","", col_embed, "Thanks for using our services!", 
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

	if(content[0] == 'd' && content[1] == '!')
	{
		content[0] = CMD_PREFIX;
		strdel(content, 1, 2);
	}

	if(content[0] == 'D' && content[1] == '!')
	{
		content[0] = CMD_PREFIX;
		strdel(content, 1, 2);
	}

	if(content[0] == '!') // custom command
	{
		setcheck(ccmd);
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

	if(!strcmp(content, "-"))
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN COMMAND** • <@%s>, you need to use it like this: `-<command> [arguments]`", id);
		return 1;
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

	DCC_GetChannelGuild(channel, guild);

	/*if(guild == DCC_FindGuildById("795007259439923200"))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • The bot is not going to respond to GM results or requests anymore. The bot services are going to be fully shut down by **10th May 2022**.");
		return 1;
	}*/

	if(IsBlacklisted(id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You're blacklisted from using bot commands.");
		return 0;
	}
	/*if(!strcmp(id, "705887674497499238") || !strcmp(id, "914596738801762404"))
	{
		SendChannelMessage(channel, "<@705887674497499238> <@914596738801762404> I only listen to North!!!");
		return 1;
	}*/
	return 1;
}

stock Blacklist(const id[])
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"blacklist_%s.ini",id);
	format(string, sizeof(string), "async sys.discord->data(message.prevent.action[cmd]);");
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock Unblacklist(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name, "blacklist_%s.ini", id);
	fremove(file_name);
	return 1;
}

stock IsBlacklisted(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name, "blacklist_%s.ini", id);
	return fexist(file_name);
}

// Inactivity purge

static GetInactivityHours(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"incprg/user_%s.ini", id);
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

stock SaveInactivityHours(const id[], count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"incprg/user_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
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
	    		SendChannelMessage(logs, ""d_no" **INACTIVITY PURGE** • Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }

	    new bool:has_role2;
	    DCC_HasGuildMemberRole(RiseOfNations, user, pgm, has_role2);

	    if(has_role2)
	    {
	    	SaveInactivityHours(id, GetInactivityHours(id) + 1);
	    	if(GetInactivityHours(id) == 72)
	    	{
	    		SendChannelMessage(logs, ""d_no" **INACTIVITY PURGE** • Probationary Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }
	}

    /*split(staffstring, staffid, '*');

    for(new i; i < MAX_STAFF_MEMBERS; i++)
    {
    	SaveInactivityHours(staffid[i], GetInactivityHours(staffid[i]) + 1);
    	if(GetInactivityHours(staffid[i]) == 72)
    	{
    		SendChannelMessage(rpnotices, ""d_no" **INACTIVITY PURGE** • <@%s> was inactive for 72 hours (3 days)!", staffid[i]);
    	}
    }*/
	return 1;
}

// Hooking and functions

#if defined _ALS_DCC_OnMessageCreate
	#undef DCC_OnMessageCreate
#else
	#define _ALS_DCC_OnMessageCreate
#endif

#define DCC_OnMessageCreate discdcmd_DCC_OnMessageCreate
#if defined discdcmd_DCC_OnMessageCreate
	forward discdcmd_DCC_OnMessageCreate(DCC_Message: message);
#endif

#if defined OnDiscordCommandPerformed
	forward OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success);
#endif  

stock IsUserMod(DCC_User:user)
{
	new filename[256];
	new id[DCC_ID_SIZE];
	DCC_GetUserId(user, id);
	format(filename, sizeof filename, "mods/mod_%s.ini", id);
	if(!fexist(filename)) return 0;
	return 1;
}

forward ActivityChange();
public ActivityChange()
{
	new r = random(5);
	if(r==0) DCC_SetBotActivity("discord.gg/Ca4PEWCJMQ ┊ -help");
	if(r==1) DCC_SetBotActivity("Mention me! ┊ -help");
	if(r==2) DCC_SetBotActivity("RoN ┊ -help");
	if(r==3) DCC_SetBotActivity("Enjoy! ┊ -help");
	if(r==4) DCC_SetBotActivity("Have fun! ┊ -help");
	return 1;
}

new _g_Shifthour, _g_Timeshift = 0;

static stock _FixHourData(_f_Hour)
{
	_f_Hour = _g_Timeshift+_f_Hour;

	if(_f_Hour < 0)
	{
		_f_Hour = _f_Hour+24;
	}
	else if(_f_Hour > 23)
	{
		_f_Hour = _f_Hour-24;
	}
	_g_Shifthour = _f_Hour;
	return 1;
}

stock void:SaveLogIntoFile( const _FileName[], const _Log[]) 
{
	new _Entry[ 128 ], 
		_sec, 
		_minutes, 
		_data, 
		_day, 
		_year, 
		_month;

	getdate( _year, _month, _day );

	gettime( _sec, _minutes, _data );

	_FixHourData( _sec );

	_sec = _g_Shifthour;
	
	format( _Entry, sizeof( _Entry ), 
		"`%d/%d/%d` • `%d:%d:%d` "d_point" %s*", 
		_day, _month, _year, 
		_sec, _minutes, _data, _Log );

	new File:_File;
	_File = fopen( _FileName, io_append );

	fwrite( _File, _Entry );

	fclose( _File );
}

public OnDiscordCommandPerformed(DCC_Message: message, DCC_User: author, bool: success) {

	if (!success) 
	{
		new DCC_Channel: channel;

		DCC_GetMessageChannel(message, channel);
		SendChannelMessage(channel, "> "d_no" **ERROR** • The command entered doesn't exist.");
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
				"**__Command used__**\n\n"d_star" User: <@%s>\nCommand text: `%s`\n"diplomy" User is a moderator.",
			id, content);
		}
		else
		{
			format(logmsg, sizeof logmsg, "**__Command used__**\n\n"d_star" User: <@%s>\nCommand text: `%s`",
			id, content);
		}
		DCC_SendChannelEmbedMessage(logs, DCC_CreateEmbed(
		"**__"SERVER_RISE_OF_NATIONS"__**", 
		logmsg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), ""d_star" **INFO** • Mention me for more information!");
	}
	return 1;
}

stock DeleteAFK(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/afk_%s.ini", id);
	return fremove(file_name);
}

public OnGameModeInit()
{
	/*new membercount, rolecount, channelcount;
	DCC_GetGuildMemberCount(RiseOfNations, membercount);
	DCC_GetGuildRoleCount(RiseOfNations, rolecount);
	DCC_GetGuildChannelCount(RiseOfNations, channelcount);

	printf("Amount of members: %i, roles: %i, channels: %i", membercount,rolecount,channelcount);

	SERVER_NUKE(RiseOfNations);*/

	LoadSettings();
	DCC_SetBotPresenceStatus(IDLE);
	SetTimer("ActivityChange", 2000, true);
	SetTimer("InactivityPurge", 3600000, true);
	SetTimer("DateUpdate", 10000, true);
	//SetTimer("MsgPerSecReset", 1000, true);

	//DCC_CreateCommand("help", "Bot help.", "discord_help", true, RiseOfNations);

	//submissionchannel = DCC_FindChannelById("965490451333402644");
	LoadChannels();
	dateupdated = 20;
	return 1;
}

public OnGameModeExit()
{
	SaveSettings();
	return 1;
}

main()
{
	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__"SERVER_RISE_OF_NATIONS"__**", 
		""d_yes" • Bot has successfully (re)started - use `-help` or `d!help` for help!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(commandchannel, msg2, ""d_star" **INFO** • Mention me for more information!");
	DCC_SendChannelEmbedMessage(logs, msg2, ""d_star" **INFO** • Mention me for more information!");
}

//Logs:

public DCC_OnChannelCreate(DCC_Channel:channel)
{
	if(settings[log] == 0) return 0;

	new name[100];
	DCC_GetChannelName(channel, name, sizeof name);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Channel created__**\n\n\
		"d_yes" Name: **#%s**", name);

	SendChannelMessage(logs, logmsg);
	return 1;
}

public DCC_OnChannelDelete(DCC_Channel:channel)
{
	if(settings[log] == 0) return 0;

	new name[100];
	DCC_GetChannelName(channel, name, sizeof name);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Channel deleted__**\n\n\
		"d_no" Name: **#%s**", name);

	SendChannelMessage(logs, logmsg);
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
		"d_no" User: <@%s>\n"d_no" Content: **%s**", id, content);

	SendChannelMessage(logs, logmsg);
	return 1;
}

public DCC_OnUserUpdate(DCC_User:user)
{
	if(settings[log] == 0) return 0;

	new logmsg[256], id[DCC_ID_SIZE];

	DCC_GetUserId(user, id);

	format(logmsg, sizeof logmsg, "**__User update__**\n\n"d_yes" • User <@%s> has been updated.", id);

	SendChannelMessage(logs, logmsg);

	return 1;
}

forward RemoveCooldown(id[]);
public RemoveCooldown(id[])
{
	new file_name[150];
	format(file_name, sizeof file_name, "data/cld_%s.ini", id);
	fremove(file_name);
	return 1;
}

stock IsOnEconomyCooldown(id[])
{
	new file_name[150];
	format(file_name, sizeof file_name, "data/cld_%s.ini", id);
	return fexist(file_name);
}

stock SetEconomyCooldown(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/cld_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "async message.action(cooldown.activate->'sys');");
	fclose(file2);
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
			SendChannelMessage(dateupdate, "A month has passed!");
			dateupdated = 20;
		}
	}
	if(h == 20)
	{
		if(dateupdated == 20)
		{
			SendChannelMessage(dateupdate, "A month has passed!");
			dateupdated = 8;
		}
	}
	return 1;
}

// Commands:

dc command:verify(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	new user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	new code[10];

	if(sscanf(params, "s[10]", code))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-verify [your verify code]`");
		return 1;
	}

	if(!strcmp(code, GetVerifyCode(user)))
	{
		DCC_AddGuildMemberRole(RiseOfNations, author, spectator);
		DCC_RemoveGuildMemberRole(RiseOfNations, author, unverified);

		SendChannelMessage(channel, ""d_yes" **VERIFICATION WAS SUCCESSFUL** • You were successfully verified!");
		return 1;
	}

	SendChannelMessage(channel, ""d_no" **VERIFICATION WAS UNSUCCESSFUL** • Your verification code wasn't correct! Please try again.");
	return 1;
}

dc command:addmod(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-addmod [user ID or user mention]`");
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

	new file_name[150], msg[512];
	format(file_name, sizeof file_name,"mods/mod_%s.ini",user);

	if(fexist(file_name))
	{
		SendChannelMessage(channel, ""d_no" • This user is already a moderator!");
		return 1;
	}

	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "");
	fclose(file2);

	format(msg, sizeof msg, ""d_yes" • User <@%s> added to the moderator team successfully.", user);

	SendChannelMessage(channel, msg);

	return 1;
}

dc command:annc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new string[512], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[512]", string))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-annc [announcement text]`\n\
			"d_star" **TIP** • In order to strip to a new line, at the point you want to add a new line add `\\` symbol.\n\
			**Example:** `-annc Funny\\text.`");
		return 1;
	}

	for(new i; i < strlen(string); i++)
	{
		if(string[i] == '\\') string[i] = '\n';
	}

	new msg[1024];
	
	format(msg, sizeof msg, ""diplomy" Announcement posted by <@%s>.\n\n\
		`%s`", id, string);

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__"SERVER_RISE_OF_NATIONS"__** Announcement", msg, 
		DISCORD_ATTACHMENT,
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(announcements, msg2, ""d_star" **INFO** • This is an announcement repost made with `-annc` mod command.");

	SendChannelMessage(channel, ""d_yes" • Announcement was posted successfully.");
	return 1;
}


dc command:delmod(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-delmod [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be removed as the user is a bot owner!");
		return 1;
	}

	new file_name[150], msg[512];
	format(file_name, sizeof file_name,"mods/mod_%s.ini",user);
	
	if(!fexist(file_name))
	{
		SendChannelMessage(channel, ""d_no" • This user is not a moderator!");
		return 1;
	}

	fremove(file_name);

	format(msg, sizeof msg, ""d_no" • User <@%s> removed from the moderator team successfully.", user);

	SendChannelMessage(channel, msg);

	return 1;
}
/*"d_arrow"**`-moderation`**: Help about server moderation.\n\
	"d_arrow"**`-version`**: Last bot update.\n\*/
dc command:help(cmdparams)
{

	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);
    new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
	"**__Main Bot Panel__**", ":wave: - **Hello, dear diplomatician!**\n\n\
	"d_heart" Welcome to **"BOT_NAME"**.\n\
	"d_star" • __List of Informational Commands__\n\
	"d_arrow"**`-settings`**: Manage bot's settings.\n\
	"d_arrow"**`-customhelp`**: View help panel for custom server features.\n\
	"d_arrow"**`-version`**: Last bot update.\n\
	"d_arrow"**`-website`**: Link to our website where you can find various information and other links.\n\
	"d_arrow"**`-errors`**: Check for the bot errors.\n\
	"d_arrow"**`-report`**: Report a bug, error and such exploits.\n\
	"d_arrow"**`-tos`**: Read our application's Terms of Service.\n\
	"d_arrow"**`-pp`**: Read our Privacy Policy.\n\n\
	"d_star" • __List of Main Commands__\n\
	"d_arrow"**`-modhelp`**: Help about moderation commands.\n\
	"d_arrow"**`-ecohelp`**: Help about economy commands.\n\
	"d_arrow"**`-afkhelp`**: Help about AFK system.\n\
	"d_arrow"**`-ccmdhelp`**: Help with your own custom commands!\n\
	"d_arrow"**`-funhelp`**: Other miscellaneous panel - contains a big variety of other types of commands!\n\
	"d_arrow"**`-lvlhelp`**: Help about leveling system.\n\
	"d_arrow"**`-bumphelp`**: Help about server bumping and leaderboard.\n\
	"d_arrow"**`-listhelp`**: Lists system help.\n\
	"d_arrow"**`-rphelp`**: Bot's role-play system help.\n\
	"d_arrow"**`-achelp`**: Anti-raid and security system help.\n\
	"d_arrow"**`-smhelp`**: Social media system help.\n\n\
	"d_star" • __List of bot features:__\n\
	"d_point" To view a list of all features provided by the bot, use `-features`.\n\n\
	"d_yes" • You can [invite me](https://discord.com/api/oauth2/authorize?client_id="BOT_USER_ID"&permissions=8&scope=bot) on your server too! Use `-botsetup` to learn about everything you need to know before inviting me.\n\n\
	:dizzy: **NOTICE** • This bot supports multi-server data storage \
	(e.g. your data such as money in the economy is \
	stored globally, not each balance for a separate \
	server - this means if you type `-work` on one server, \
	on all other servers your economy balance will get updated). \
	Same also counts for other stuff as AFK status and such.", 
	"",
	"", col_embed, "Thanks for using our services!", 
	DISCORD_ATTACHMENT,
	DISCORD_PFP_LINK,
	""), GetMention(useridmention));

	return 1;
}

dc command:customhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);
    new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
	"**__Custom Features Help Panel__**", "\n\n\
	"d_star" __List of Commands available for **"SERVER_RISE_OF_NATIONS"**__\n\
	"d_arrow"**`-moderation`**: Help about server moderation.\n\
	"d_arrow"**`-nrphelp`**: Nation role-play system help.\n\n", 
	"",
	"", col_embed, "Thanks for using our services!", 
	DISCORD_ATTACHMENT,
	DISCORD_PFP_LINK,
	""), GetMention(useridmention));

	return 1;
}

dc command:features(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ""d_star" Below, there's a list of all the features included in the bot.\n\n\
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
		**8.** Other funny commands displayed on the `-help` panel\n\
		**9.** Role-play system!\n\n\
		"d_star" **NOTE** • Bot is regularly maintained and updated, a lot of interesting cross-server features are coming soon!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:rphelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**RolePlay System commands**\n\n\
		"d_arrow"**`-mystats`**: View your statistics!\n\
		"d_arrow"**`-mine`**: Go mining and find something valuable!\n\
		"d_arrow"**`-melt`**: Melt stuff to get other stuff!\n\
		"d_arrow"**`-hunt`**: Go hunting and find stuff!\n\
		"d_arrow"**`-eat`**: Consume stuff and max out your energy!\n", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:tos(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Terms of Service__**", "**Hello! It's mandatory for everyone to accept our Terms of Service in order to use the bot properly.**\n\n\
		**1.** Don't exploit bugs of the bot, doing so may result in a command blacklist.\n\
		\n**2.** Using custom commands to send explicit or forbidden content of a certain server may result in a command blacklist.\n\
		\n**3.** Putting bad words as an arguments in commands is a bannable offense.\n\
		\n**4.** Using bot's commands to share personal information is not allowed.\n\
		\n**5.** Sharing fake information about the bot community is bannable offense.\n\
		\n**6.** Using commands such as `-report` for fun or multiple times is not a thing you should really do. Multiple requests and reports will be ignored.\n\
		\n**7.** Noticing the bug and not reporting it is not a nice thing to do - whenever \
		you notice something unusual happening, you should use the `-report` command.\n\
		\n**8.** Redistributing the bot's resources (such as images, logos, text) is prohibited.\n\
		\n**9.** Read our Privacy Policy for more, use `-pp` command to do so.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:pp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Privacy Policy__**", ""d_yes" Your information is safe!\n\n\
		> Hi! Please note that the bot doesn't store any of your personal information \
		or account information such as e-mails, passwords, nicknames or messages besides \
		the user ID, which is used to store the data such as your economy money, level, \
		message count and many more!\n\n\
		> We deeply care about your privacy and security online. But, we aren't responsible for \
		any data loss using the bot, you shouldn't use passwords, usernames and such information \
		as list names, custom command names or anything else requiring a text input! Thanks.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:listhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**List System commands**\n\n\
		"d_arrow"**`-createlist`**: Create a list!\n\
		"d_arrow"**`-addelement`**: Add a list element (an user for example).\n\
		"d_arrow"**`-delelement`**: Delete a list element.\n\
		"d_arrow"**`-viewlist`**: View a list.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:achelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Anti-raid System commands**\n\n\
		"d_arrow" Nothing to see here yet!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:modhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);
    new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
	"**__Help Panel__**", "**Moderation Commands**\n\n\
	"d_arrow"**`-ban`**: Bans an user from a certain server.\n\
	"d_arrow"**`-unban`**: Revokes an user ban in a certain server.\n\
	"d_arrow"**`-kick`**: Kicks an user from a certain server.\n\n", 
	"",
	"", col_embed, "Thanks for using our services!", 
	DISCORD_ATTACHMENT,
	DISCORD_PFP_LINK,
	""), GetMention(useridmention));

	return 1;
}

//------------------------

dc command:createlist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE],listname[20];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]", listname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-createlist [list name]`");
		return 1;
	}

	if(IsValidList(listname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This list already has been created.");
		return 1;
	}

	CreateList(id, listname);

	SendChannelMessage(channel, ""d_yes" **LIST CREATED** • Your list has been created successfully.");

	return 1;
}

dc command:addelement(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new listname[20], element[50], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]s[50]", listname, element))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-addelement [list name] [element]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You can only modify lists that you created!");
		return 1;
	}

	AddListElement(listname, element);

	SendChannelMessage(channel, ""d_yes" **LIST MODIFIED** • Your list has been successfully modified.");
	return 1;
}

dc command:delelement(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new listname[20], element, id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]i", listname, element))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-delelement [list name] [element ID]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You can only modify lists that you created!");
		return 1;
	}

	RemoveListElement(listname, element-1);

	SendChannelMessage(channel, ""d_yes" **LIST MODIFIED** • Your list has been successfully modified.");
	return 1;
}

dc command:viewlist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new listname[20], element[150], el[50];

	if(sscanf(params, "s[20]", listname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-viewlist [list name]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This list doesn't exist.");
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
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:funhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Miscellaneous commands**\n\n\
		"d_arrow"**`-search`**: Let me Google stuff for you!\n\
		"d_arrow"**`-say`**: Say something anonymously.\n\
		"d_arrow"**`-joke`**: Get a joke.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:bumphelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ""d_no" This system is under heavily development.\n\n\
		"d_arrow"**`-bump`**: Bump your server!\n\
		"d_arrow"**`-servers`**: View the server leaderboards.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:bump(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);

    new id[DCC_ID_SIZE];

    DCC_GetGuildId(guild, id);

    SaveBumpCount(id, GetBumpCount(id) + 1);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bump Done!__**", ""d_yes" Your server successfully got bumped on the bot's global server leaderboard.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:servers(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Coming soon!__**", ""d_no" This feature is currently unavailable, but don't give up with bumping - bump command works.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

dc command:lvlhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Leveling system help__**\n\n\
		"d_star" This is a message-based leveling system. Statistics and rewards \
		gained in it is stored in multi-server storage, which means, if you achieved \
		level 2 on one server, on all other servers this bot is in, you will be level 2.\n\n\
		**Leveling Policy**\n\
		"d_star" Every 100 messages you send, you climb up by one level! \
		You can check your level using `-level` command.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:level(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new lvl[256];

	format(lvl, sizeof lvl, ":speaking_head: User: <@%s>\n:crown: Level: %i\n"d_star" Total message count: %i", id, GetMessageCount(id) / 100 + 1, GetMessageCount(id));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Level Statistics__**", lvl, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:ccmdhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Custom Command help__**\n\n\
		"d_arrow"**`-declcmd`**: Declare (create) a custom command.\n\
		"d_arrow"**`-delcmd`**: Delete a custom command.\n\n\
		"d_star" **TIP** • Bot responds to these commands only when they have a `!` prefix.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:declcmd(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(ccmd);

	new cmdname[32], text[256], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[32]s[256]", cmdname, text))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-declcmd [command name] [text to respond with]`");
		return 1;
	}

	if(IsCommand(cmdname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This command is already registered!");
		return 1;
	}

	for(new i; i < strlen(text); i++)
	{
		if(text[i] == '<' && text[i+1] == '@')
		{
			SendChannelMessage(channel, ""d_no" **ERROR** • Invalid characters detected in the text response.");
			return 1;
		}
		if(text[i] == '<' && text[i+1] == '!' && text[i+2] == '@')
		{
			SendChannelMessage(channel,""d_no" **ERROR** • Invalid characters detected in the text response.");
			return 1;
		}
	}

	CreateCommand(cmdname, id, text);

	SendChannelMessage(channel, ""d_yes" **COMMAND CREATED** • Your custom command is successfully registered!\n> "d_point" Try using it now!");
	return 1;
}

dc command:delcmd(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(ccmd);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new cmdname[32];

	if(sscanf(params, "s[32]", cmdname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-delcmd [command name]`");
		return 1;
	}

	if(!IsCommand(cmdname))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This command doesn't exist!");
		return 1;
	}

	if(!IsUsersCommand(cmdname, id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You can only delete the commands that you created!");
		return 1;
	}

	DeleteCommand(cmdname);

	SendChannelMessage(channel, ""d_yes" **COMMAND DELETED** • Your custom command is successfully deleted!");
	
	return 1;
}

dc command:botsetup(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bot Setup__**", ":wave: - **Hello, dear diplomatician!**\n\n\
		"d_heart" __Welcome to a bot setup guide and FAQ-s.__\n\
		"d_point" This bot doesn't need any setup when it gets invited, \
		as it is supporting multi-server storage. Only some commands such as moderation \
		and GM counting features, counting, etc. won't work. Features such as economy, \
		AFK status and more upcoming will work as nothing happened. Get the invite link on the `-help` panel!\n\n\
		**__Important Command Note__**\n\
		"d_point" Please note that if you want to execute a standard command (aka commands displayed on \
		help panels) use `RiseOfNations` or `-` as a prefix, the `!` prefix is used to execute custom commands \
		(read more about custom commands on `-ccmdhelp`)!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		DISCORD_PFP_LINK,
		""), ""d_star" **TIP** • Thanks for bothering inviting **"BOT_NAME"** to your server.");
	return 1;
}

dc command:report(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new cid[DCC_ID_SIZE];
	DCC_GetChannelId(channel, cid);

	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);
	SetUserReportChannel(id, cid);
	SendChannelMessage(channel, ""d_yes" **REPORT FORM LOADED** • <@%s> successfully entered a report mode.", id);

	SetReportQuestion(id, "1");

	SendChannelMessage(channel, ""diplomy" | **__REPORT PANEL__**\n**Question 1** • <@%s>\n\n"d_arrow"*`What are you reporting? Please describe.`*\n\n", id);
	SendTip(channel, "Please reply to the question above with the proper answer.");
	return 1;
}

dc command:errors(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	modcheck;

	SendChannelMessage(channel, ""d_star" **INFO** • `No errors found.`\n"diplomy" **NOTE** • This system is currently under a beta phase!");
	return 1;
}

//https://www.google.com/search?q=KEYWORDS+OF+A+SEARCH
dc command:search(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new query[256];

	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetGamepad(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	if(sscanf(params, "s[256]", query))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-search [search text]`");
		return 1;
	}

	for(new i; i < strlen(query); i++)
	{
		if(query[i] == ' ') query[i] = '+';
	}

	SendChannelMessage(channel, ""d_yes" **SEARCHING FINISHED** • Your search results: \nhttps://www.google.com/search?q=%s\n`%i results in 0,%is`", query, random(100000), random(10));
	return 1;
}

dc command:say(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new t[256];

	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetGamepad(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	if(sscanf(params, "s[256]", t))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-say [text]`");
		return 1;
	}

	DCC_DeleteMessage(message);

	SendChannelMessage(channel, "%s", t);
	return 1;
}

dc command:joke(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);


	new id[DCC_ID_SIZE]; DCC_GetUserId(author,id);if(GetGamepad(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_gamepad" | `Gamepad` to use miscellaneous commands!");
		return 1;
	}

	DCC_SendChannelMessage(channel, DiplomyJokes[random(sizeof DiplomyJokes)]);
	return 1;
}

/*
dc command:juan(cmdparams)
{
	new DCC_Channel:c;
	DCC_GetMessageChannel(message,c);
	SendChannelMessage(c,"https://cdn.discordapp.com/attachments/795025965985693716/959382383034007592/IMG_4433.jpg");
	return 1;
}
*/
dc command:website(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"SERVER_RISE_OF_NATIONS" • Website__**", "\
		"d_point" • Visit our community on the web! Access our site by clicking this [link](https://bracetm.000webhostapp.com/d_diplomy.html)!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		DISCORD_PFP_LINK,
		""), GetMention(useridmention));


	return 1;
}

dc command:version(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, "> "d_yes" **__Last Update__**\n\n**LAST UPDATE** • Script was (re)compiled last time at `%s-%s`.\n**SCRIPT VERSION** • Bot code version: `1.0`",__date, __time);

	return 1;
}

dc command:ecohelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Economy commands__**\n\n\
		"d_arrow"**`-bal`**: View your balance.\n\
		"d_arrow"**`-work`**: Work and earn money.\n\
		"d_arrow"**`-dep`**: Deposit money.\n\
		"d_arrow"**`-bankacc`**: Open a bank account.\n\
		"d_arrow"**`-with`**: Withdraw money.\n\
		"d_arrow"**`-rob`**: Rob a member.\n\
		"d_arrow"**`-shop`**: Open a "BOT_NAME" shop.\n\
		"d_arrow"**`-buy`**: Buy something from a "BOT_NAME" shop.\n\
		"d_arrow"**`-inv`**: View your inventory.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:bankacc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(HasBankAccount(id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You already have opened a bank account.");
		return 1;
	}

	OpenBankAccount(id);

	SendChannelMessage(channel, ""d_yes" **BANK** • You successfully opened a bank account.");

	return 1;
}

dc command:afkhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__AFK commands__**\n\n\
		"d_arrow"**`-afk`**: Set your AFK status.\n\
		"d_star" **TIP** • Your AFK status gets removed once you send a message into any channel of a server.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));

	return 1;
}

dc command:afk(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new afkstatus[256];

	if(sscanf(params, "s[256]", afkstatus))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-afk [AFK status text]`");
		return 1;
	}

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	SetAFK(id, afkstatus);

	SendChannelMessage(channel, ""d_yes" • Alright, <@%s> - you're now AFK.", id);

	return 1;
}

dc command:settings(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new option[30];
	
	new id[DCC_ID_SIZE];DCC_GetUserId(author, id);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	if(sscanf(params, "s[30]", option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bot Settings Panel__**", ""d_star" • These are the options used to manipulate with bot settings.\n\
		Usage: `-settings [option]`\n\
		"d_star" **NOTE** • If you want to see whose settings are on or off, please use `-settings view`.\n\n\
		**__Setting Options__**\n\
		**`logs`**: Enable or disable the log system.\n\
		**`gmc`**: Activate or deactivate GM counting.\n\
		**`eco`**: Toggle economy commands on or off.\n\
		**`mod`**: Toggle commands such as `-kick`, `-warn` on or off.\n\
		**`count`**: Enable or disable the counting system.\n\
		**`ccmd`**: Enable or disable custom commands.\n\
		**`ac`**: Activate or deactivate anti-raid system.\n\
		**`rp`**: Activate or deactivate a roleplay system.", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
		return 1;
	}
	if(!strcmp(option, "view"))
	{
		SendChannelMessage(channel, "**__Bot Settings Panel__**\n"d_star" • This is settings preview.\n\n**`logs`** • %s\n**`gmc`** • %s\n**`eco`** • %s\n**`mod`** • %s\n**`count`** • %s\n**`ccmd`** • %s\n**`ac`** • %s\n**`rp`** • %s", settings[log] ? ""d_yes"" : ""d_no"", settings[gmc] ? ""d_yes"" : ""d_no"", settings[eco] ? ""d_yes"" : ""d_no"", settings[mod] ? ""d_yes"" : ""d_no"", settings[cnt] ? ""d_yes"" : ""d_no"", settings[ccmd] ? ""d_yes"" : ""d_no"",settings[ac] ? ""d_yes"" : ""d_no"",settings[rp] ? ""d_yes"" : ""d_no"");
		return 1;
	}

	if(!strcmp(option, "ccmd"))
	{
		modcheck;

		if(settings[ccmd] == 1)
		{
			settings[ccmd] = 0;
			SendChannelMessage(channel, ""d_no" • Custom commands system has been disabled.");
			return 1;
		}
		if(settings[ccmd] == 0)
		{
			settings[ccmd] = 1;
			SendChannelMessage(channel, ""d_yes" • Custom commands system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "logs"))
	{
		modcheck;

		if(settings[log] == 1)
		{
			settings[log] = 0;
			SendChannelMessage(channel, ""d_no" • Log system has been disabled.");
			return 1;
		}
		if(settings[log] == 0)
		{
			settings[log] = 1;
			SendChannelMessage(channel, ""d_yes" • Log system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "eco"))
	{
		modcheck;

		if(settings[eco] == 1)
		{
			settings[eco] = 0;
			SendChannelMessage(channel, ""d_no" • Economy commands have been disabled.");
			return 1;
		}
		if(settings[eco] == 0)
		{
			settings[eco] = 1;
			SendChannelMessage(channel, ""d_yes" • Economy commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "count"))
	{
		modcheck;

		if(settings[cnt] == 1)
		{
			settings[cnt] = 0;
			SendChannelMessage(channel, ""d_no" • Counting system has been disabled.");
			return 1;
		}
		if(settings[cnt] == 0)
		{
			settings[cnt] = 1;
			SendChannelMessage(channel, ""d_yes" • Counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "gmc"))
	{
		modcheck;

		if(settings[gmc] == 1)
		{
			settings[gmc] = 0;
			SendChannelMessage(channel, ""d_no" • GM counting system has been disabled.");
			return 1;
		}
		if(settings[gmc] == 0)
		{
			settings[gmc] = 1;
			SendChannelMessage(channel, ""d_yes" • GM counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "mod"))
	{
		modcheck;

		if(settings[mod] == 1)
		{
			settings[mod] = 0;
			SendChannelMessage(channel, ""d_no" • Moderation commands have been disabled.");
			return 1;
		}
		if(settings[mod] == 0)
		{
			settings[mod] = 1;
			SendChannelMessage(channel, ""d_yes" • Moderation commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "ac"))
	{
		modcheck;

		if(settings[ac] == 1)
		{
			settings[ac] = 0;
			SendChannelMessage(channel, ""d_no" • Anti-raid has been disabled.");
			return 1;
		}
		if(settings[ac] == 0)
		{
			settings[ac] = 1;
			SendChannelMessage(channel, ""d_yes" • Anti-raid has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "rp"))
	{
		modcheck;

		if(settings[rp] == 1)
		{
			settings[rp] = 0;
			SendChannelMessage(channel, ""d_no" • RolePlay system has been disabled.");
			return 1;
		}
		if(settings[rp] == 0)
		{
			settings[rp] = 1;
			SendChannelMessage(channel, ""d_yes" • RolePlay system has been enabled.");
			return 1;
		}
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN OPTION** • Invalid option provided, use `-settings` to view a list of available options.");
	}
	return 1;
}

dc command:warn(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE + 10], reason[100];

	if(sscanf(params, "ss", user, reason))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-warn [user ID or user mention] [reason]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be warned as the user is a bot owner!");
		return 1;
	}

	if(!strcmp(user, "888667418904363078"))
	{
		SendChannelMessage(channel, ""d_no" • This user can't be warned as the user is a website maintainer!");
		return 1;
	}

	new filename[100];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	SaveLogIntoFile(filename, reason);

	new msg[512];
	format(msg, sizeof msg, ""d_yes" • User <@%s> was warned successfully.\n**REASON** • `%s`", user, reason);
	SendChannelMessage(channel, msg);
	return 1;
}

stock strtok(const string[], &index, delimiter = ' ') {
	new length = strlen(string);
	while ((index < length) && (string[index] <= delimiter)) {
		index++;
	}
	new offset = index;
	new result[128];
	while ((index < length) && (string[index] > delimiter) && ((index - offset) < (sizeof(result) - 1))) {
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

dc command:warns(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	setcheck%0(mod);

	modcheck;

	new user[100];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-warns [user ID or user mention]`");
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

	if(strlen(parameters) == 0) return SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-warns [user ID or user mention]`");

	format(user, sizeof user, "%s", parameters);*/

	if(!strcmp(user, "617419819108663296"))
	{
		SendChannelMessage(channel, ""d_no" • Operation failed!");
		return 1;
	}

	new filename[100], content[1024];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	if(!fexist(filename))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This user has no warnings.");
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
		"**__WARN LIST__**", msg, "","", col_embed, "Thanks for using our services!", 
		"","","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2);

	return 1;
}

// Moderation:

dc command:moderation(cmdparams)
{
	new DCC_Channel:channel;
	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	/*SendChannelMessage(channel, "**__Bot settings__**\n\n\
		"d_arrow"**`-logs`**: Enable or disable the log system.\n\
		"d_arrow"**`-gmc`**: Activate or deactivate GM counting.\n\
		"d_arrow"**`-eco`**: Toggle economy commands on or off.");*/

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__MODERATION COMMANDS__**", ""d_star" Available moderation commands:\n\n\
		"d_arrow"**`-blacklist`**: Blacklist a member from using the bot commands.\n\
		"d_arrow"**`-gmtemp`**: View the GM template to use in `#gm-output`!\n\
		"d_arrow"**`-addmod`**: Add an user to moderation team.\n\
		"d_arrow"**`-delmod`**: Remove an user from moderation team.\n\
		"d_arrow"**`-warn`**: Permanently warns a member.\n\
		"d_arrow"**`-warns`**: View all user's warnings.\n\
		"d_arrow"**`-annc`**: Post an announcement.\n\
		"d_arrow"**`-mute`**: Mute a member.\n\
		"d_arrow"**`-unmute`**: Unmute a member.\n\
		"d_arrow"**`-setgmc`**: Set GM count for a member.\n\
		"d_arrow"**`-getgmc`**: Get GM count of a member.\n\
		"d_arrow"**`-poll`**: Create a poll.\n\
		"d_arrow"**`-profile`**: View the overall Game Master statistics.\n\
		"d_arrow"**`-setgmcc`**: Customized `-setgmc` built for each department.\n\
		"d_arrow"**`-setgmclvl`**: Another custom `-setgmc` to set leveled GM count.\n\
		"d_arrow"**`-top`**: View a leaderboard.\n\
		"d_arrow"**`-saveset`**: Save the current settings (emergency cases).\n\
		"d_arrow"**`-sprofile`**: View the support staff profile.\n\
		"d_arrow"**`-resetprofile`**: Reset a GM/support staff profile of a certain user to 0.\n\
		"d_arrow"**`-roleall`**: Give everyone a role.\n\
		"d_arrow"**`-deroleall`**: Take a role from everyone.\n\
		"d_arrow"**`-rprole`**: Assign a role-play role to an user.", "","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
	return 1;
}

dc command:roleall(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new roleid[DCC_ID_SIZE+10];

	if(sscanf(params, "s[50]", roleid))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-roleall [role ID or user mention]`");
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

	new DCC_Guild:server;

	DCC_GetChannelGuild(channel, server);

	new membercount;
	DCC_GetGuildMemberCount(server, membercount);

	SendChannelMessage(channel, ""d_yes" **PROCCESS STARTED** • %i users will be given a <@&%s> role in `%i` seconds!", membercount, roleid, membercount);

	for (new i; i != membercount; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(server, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    //DCC_GetUserId(user, id);

	   	DCC_AddGuildMemberRole(server, user, DCC_FindRoleById(roleid));

	}
	SendChannelMessage(channel, ""d_yes" **USERS ROLED** • %i users were given a <@&%s> role.", membercount, roleid);	
	return 1;
}

dc command:deroleall(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new roleid[DCC_ID_SIZE+10];

	if(sscanf(params, "s[50]", roleid))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-deroleall [role ID or user mention]`");
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

	new DCC_Guild:server;

	DCC_GetChannelGuild(channel, server);

	new membercount;
	DCC_GetGuildMemberCount(server, membercount);

	SendChannelMessage(channel, ""d_yes" **PROCCESS STARTED** • %i users will be removed from a <@&%s> role in `%i` seconds!", membercount, roleid, membercount);

	for (new i; i != membercount; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(server, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    //DCC_GetUserId(user, id);

	   	DCC_RemoveGuildMemberRole(server, user, DCC_FindRoleById(roleid));

	}
	SendChannelMessage(channel, ""d_yes" **USERS DEROLED** • %i users were removed from a <@&%s> role.", membercount, roleid);	
	return 1;
}

dc command:rprole(cmdparams)
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
		"**__Submission Approval Setup__**", ""d_star" These are the options used to manipulate with user RP role statistics.\n\
		Usage: `-rprole [user] [option]`\n\n\
		**__Options__**\n\n\
		**`nation`**: Give a nation role to user.\n\
		**`rebelorg`**: Give a rebellion organization role to user.\n\
		**`politicalorg`**: Give a political organization role to user.\n\
		**`corporation`**: Give a corporation role to user.\n\
		**`acoop`**: Give an administrative cooperator role to user.\n\
		**`pcoop`**: Give a provincial cooperator role to user.\n\
		**`civilian`**: Give a civilian role to user.\n\
		**`unsec`**: Give an UN secretariat role to user.\n\
		**`spectator`**: Give a spectator role to user.\n\
		**`player`**: Give a player role to user.",
		"","", col_embed, "Thanks for using our services!", 
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

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Nation`* role.", user);

		return 1;
	}
	if(!strcmp(option, "rebelorg"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), rebelorg);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Rebellion Organization`* role.", user);

		return 1;
	}
	if(!strcmp(option, "politicalorg"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), politicalorg);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Political Organization`* role.", user);

		return 1;
	}
	if(!strcmp(option, "corporation"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), corporation);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Corporation`* role.", user);

		return 1;
	}
	if(!strcmp(option, "acoop"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), acoop);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Administrative Cooperator`* role.", user);

		return 1;
	}
	if(!strcmp(option, "pcoop"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), pcoop);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Provincial Cooperator`* role.", user);

		return 1;
	}
	if(!strcmp(option, "civilian"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), civilian);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Civilian`* role.", user);

		return 1;
	}
	if(!strcmp(option, "unsec"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), unsec);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`UN Secretariat`* role.", user);

		return 1;
	}
	if(!strcmp(option, "player"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), playerrole);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Player`* role.", user);

		return 1;
	}
	if(!strcmp(option, "spectator"))
	{
		DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), spectator);

		SendChannelMessage(channel, ""d_yes" **USER ROLED** • <@%s> was successfully given the *`Spectator`* role.", user);

		return 1;
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN OPTION** • Invalid role option provided, use `-rprole` to view a list of available options.");
	}
	return 1;
}

dc command:saveset(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	SaveSettings();
	SendChannelMessage(channel, ""d_yes" **SETTINGS SAVED** • Current bot settings saved successfully.");
	return 1;
}
/*
dc command:addstaff(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-addstaff [user ID or user mention]`");
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

	if(IsStaff(user))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This user is already in a staff configuration file.");
		return 1;
	}

	SaveStaffString(user);
	SendChannelMessage(channel, ""d_yes" **MEMBER ADDED** • <@%s> is now added to the staff team configuration file.", user);
	return 1;
}

dc command:remstaff(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-remstaff [user ID or user mention]`");
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

	if(!IsStaff(user))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • This user is not found in the staff configuration file.");
		return 1;
	}

	DeleteStaffMember(user);
	SendChannelMessage(channel, ""d_yes" **MEMBER REMOVED** • <@%s> is now removed from the staff team configuration file.", user);
	return 1;
}*/

dc command:poll(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new text[512];

	if(sscanf(params, "s[512]", text))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-poll [poll name]*[poll text]`\n\
			"d_star" **TIP** • Command usage example: `-poll Void an action*I vote to void this and this, bla bla...`");
		return 1;
	}

	new strip[2][512];

	split(text, strip, '*');

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	format(globalformat,sizeof globalformat, "**__%s__**\n"d_point" *%s*\n\n:dizzy: • \
		Poll was posted by: <@%s>\nReact with :ballot_box_with_check: or "d_no" below.", strip[0], strip[1], id);
	
	new DCC_Embed:msg2 = DCC_CreateEmbed(
		":newspaper: **__POLL__**", globalformat, "","", col_embed, "Thanks for using our services!", 
		"","","");

	DCC_SendChannelEmbedMessage(channel, msg2, ""d_star" **INFO** • A new poll has been posted!");

	new DCC_Message:msg3 = DCC_GetCreatedMessage();

	AddReaction(msg3, DCC_CreateEmoji("☑️"));

	AddReaction(msg3, DCC_CreateEmoji("❌"));

	return 1;
}

dc command:setgmc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], gmcount;

	if(sscanf(params, "si", user, gmcount))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-setgmc [user ID or user mention] [GM count]`");
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

	SendChannelMessage(channel, ""d_yes" **GM COUNT SET** • <@%s>'s GM count was modified successfully. New GM count: `%i`", user, gmcount);

	return 1;
}

dc command:setgmcc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], label[15], gmcount;

	if(sscanf(params, "s[31]s[15]i", user, label, gmcount))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-setgmcc [user ID or user mention] [department label(s)] [GM count]`");
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
		SendChannelMessage(channel, ""d_yes" **POLITICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SavePolGMCount(user,gmcount);
		return 1;
	}

	if(dept == 3) // Economics solo
	{
		SendChannelMessage(channel, ""d_yes" **ECONOMICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 8) // Military solo
	{
		SendChannelMessage(channel, ""d_yes" **MILITARY GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveMilGMCount(user,gmcount);
		return 1;
	}

	// Mixed labels:
	
	if(dept == 4) // pol eco
	{
		SendChannelMessage(channel, ""d_yes" **POLITICS & ECONOMICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SavePolEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 11) // eco mil
	{
		SendChannelMessage(channel, ""d_yes" **ECONOMICS & MILITARY GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveEcoMilGMCount(user,gmcount);
		return 1;
	}

	if(dept == 9) // mil pol
	{
		SendChannelMessage(channel, ""d_yes" **MILITARY & POLITICS GM COUNT** • Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveMilPolGMCount(user,gmcount);
		return 1;
	}

	if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9)
	{
		SendChannelMessage(channel, ""d_no" **GM COUNT MODIFICATION** • Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`\n\n"d_star" • Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}

	return 1;
}

dc command:setgmclvl(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], lvl, gmcount;

	if(sscanf(params, "s[31]ii", user, lvl, gmcount))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-setgmclvl [user ID or user mention] [level ID] [GM count]`\n\
			"d_star" **LEVEL IDs** • These are the current GM levels: easy - `1`, subnormal - `2`, normal - `3`, medium - `4`, hard - `5`");
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
		SendChannelMessage(channel, ""d_yes" **MODIFICATION SUCCESS** • GM count modification on level **Easy** for <@%s> was successful. Check it using `-profile`.", user);
		SaveEasyGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 2)
	{
		SendChannelMessage(channel, ""d_yes" **MODIFICATION SUCCESS** • GM count modification on level **Subnormal** for <@%s> was successful. Check it using `-profile`.", user);
		SaveSubnormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 3)
	{
		SendChannelMessage(channel, ""d_yes" **MODIFICATION SUCCESS** • GM count modification on level **Normal** for <@%s> was successful. Check it using `-profile`.", user);
		SaveNormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 4)
	{
		SendChannelMessage(channel, ""d_yes" **MODIFICATION SUCCESS** • GM count modification on level **Medium** for <@%s> was successful. Check it using `-profile`.", user);
		SaveMediumGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 5)
	{
		SendChannelMessage(channel, ""d_yes" **MODIFICATION SUCCESS** • GM count modification on level **Hard** for <@%s> was successful. Check it using `-profile`.", user);
		SaveHardGMCount(user, gmcount);
		return 1;
	}
	SendChannelMessage(channel, "> "d_no" **ERROR** • Invalid level ID provided.");
	return 1;
}

dc command:getgmc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-getgmc [user ID or user mention]`");
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

	SendChannelMessage(channel, ""d_yes" **MEMBER'S GM COUNT** • <@%s> did `%i` GMs since the last reset.", user, GetGMCount(user));

	return 1;
}

dc command:ban(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	setcheck%0(mod);

	if(DCC_HasGuildMemberPermission(guild, author, PERMISSION_BAN_MEMBERS) == false)
	{
		SendChannelMessage(channel, ""d_no" **AUTHORIZATION ERROR** • You do not have a `BAN_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[50]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-ban [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be removed as the user is a bot owner!");
		return 1;
	}


	DCC_CreateGuildMemberBan(guild, 
		DCC_FindUserById(user), 
		""SERVER_RISE_OF_NATIONS" bot • Banned with a ban command.");

	SendChannelMessage(channel, ""d_yes" **BANNED** • <@%s> was banned successfully.\n\n"d_star" **TIP** • If the ban didn't work, simply try again! Due to some Discord's limitations, you are unable to ban two users in a short period of time.", user);

	//SendChannelMessage(bankicklog, "<@%s> was **banned** by <@%s>.\n\n"d_star" **TIP** • If the ban didn't work, simply try again! Due to some Discord's limitations, you are unable to ban two users in a short period of time.", user, id);

	return 1;
}

dc command:unban(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	setcheck%0(mod);

	if(DCC_HasGuildMemberPermission(guild, author, PERMISSION_BAN_MEMBERS) == false)
	{
		SendChannelMessage(channel, ""d_no" **AUTHORIZATION ERROR** • You do not have a `BAN_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-unban [user ID or user mention]`");
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

	SendChannelMessage(channel, ""d_yes" **UNBANNED** • <@%s> was unbanned successfully.", user);

	return 1;
}

dc command:kick(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	setcheck%0(mod);

	if(DCC_HasGuildMemberPermission(guild, author, PERMISSION_KICK_MEMBERS) == false)
	{
		SendChannelMessage(channel, ""d_no" **AUTHORIZATION ERROR** • You do not have a `KICK_MEMBERS` permission!");
		return 1;
	}

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-kick [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be removed as the user is a bot owner!");
		return 1;
	}


	SendChannelMessage(channel,""d_yes" **KICKED** • <@%s> was kicked successfully.", user);

	DCC_RemoveGuildMember(guild, DCC_FindUserById(user));

	//SendChannelMessage(bankicklog, "<@%s> was **kicked** by <@%s>.", user, id);
	return 1;
}

dc command:mute(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-mute [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be removed as the user is a bot owner!");
		return 1;
	}


	if(muted == DCC_INVALID_ROLE)
	{
		SendChannelMessage(channel,""d_no" **ROLE ERROR** • There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_AddGuildMemberRole(RiseOfNations, DCC_FindUserById(user), muted);

	SendChannelMessage(channel, ""d_yes" **MUTED** • <@%s> was muted successfully.", user);

	return 1;
}

dc command:unmute(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	servercheck(RiseOfNations);
	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-unmute [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This member wasn't muted!");
		return 1;
	}

	if(muted == DCC_INVALID_ROLE)
	{
		SendChannelMessage(channel,""d_no" **ROLE ERROR** • There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_RemoveGuildMemberRole(RiseOfNations, DCC_FindUserById(user), muted);

	SendChannelMessage(channel, ""d_yes" **UNMUTED** • <@%s> was unmuted successfully.", user);

	return 1;
}

dc command:gmtemp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	
	SendChannelMessage(channel, "**__GM Template__**\n\n\
		**[`department label [pol/eco/mil]`]**\n\
		**Message link:**\n\
		**Provided WIWTK:**\n\
		**GM Content:**\n\
		**Tags:**");

	SendChannelMessage(channel, ":information_source: • Using a valid template is really important, as if you don't, your GM will not be count in activity logs.\n\
		"d_star" • Use "d_arrow"**`-gmexample`** to view the example of template usage.");

	return 1;
}

dc command:gmexample(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, ""d_yes" **__GM Example__**\n\
		```\n\
		[pol]\n\
		https://discord.com/32452353252345/2352345234523\n\
		WIWTK - What happened?\n\
		You successfully won the September elections!\n\
		@Requester\n```");

	return 1;
}

dc command:gmlvl(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	/*SendChannelMessage(channel, "**__Bot settings__**\n\n\
		"d_arrow"**`-logs`**: Enable or disable the log system.\n\
		"d_arrow"**`-gmc`**: Activate or deactivate GM counting.\n\
		"d_arrow"**`-eco`**: Toggle economy commands on or off.");*/

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__INFORMATION ABOUT GM LEVELS__**", "**__GM Levels__**\n\n\
		1. `Easy` - GM for 1 post\n\
		2. `Subnormal` - GM for 2 posts\n\
		3. `Normal` - GM for 3 posts\n\
		4. `Medium` - GM for 4 posts\n\
		5. `Hard` - GM for 5 or more posts\n\n\
		"d_star" **FACT** • GM leveling system has been recently updated with a new algorithm, \
		which scans the GM message and then estimates the level, regardless of the number of posts.", "","", col_embed, "Thanks for using our services!", 
		"","","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, ""d_star" **INFO** • For more info, ask a bot mod.");
	return 1;
}

dc command:bal(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);


	SendChannelMessage(channel, "**<@%s>**\n\n**Pocket Money**\n"d_point"`%i` "d_coin"\n\n**Money on your Bank Account**\n"d_point"`%i` "d_coin"", id, GetBalance(id), GetDepBalance(id));

	return 1;
}

dc command:work(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetEnergy(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	if(GetBalance(id) >= 3000 && GetWallet(id) == 0)
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • Your pocket is full of coins - there is no space left for more!\n\
			"d_star" **TIP** • Buy a "d_wallet" | `Wallet` to get space for more coins.");
		return 1;
	}

	if(GetBalance(id) >= 25000)
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • Your wallet is full of coins - there is no space left for more!\n\
			"d_star" **TIP** • Use `-dep` to deposit your coins and free up space.");
		return 1;
	}

	new wage = random(10000);

	SaveBalance(id, GetBalance(id) + wage);

	SetEnergy(id, GetEnergy(id) - 1);

	SendChannelMessage(channel, "**<@%s>**\n\n"d_yes" **WORK FINISHED** • You successfully finished your shift and your boss gave you `%i` "BOT_NAME" coins! "d_coin"", id, wage);

	return 1;
}

dc command:dep(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new money[30];

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[30]", money))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-dep [amount of coins to deposit]`\n\
			> "d_star" **TIP** • To deposit all of your coins, use `-dep all`.");
		return 1;
	}

	if(!strcmp(money, "all"))
	{
		if(!HasBankAccount(id))
		{
			SendChannelMessage(channel, "> "d_no" **ERROR** • You don't have a bank account.");
			return 1;
		}

		SaveDepBalance(id, GetDepBalance(id) + GetBalance(id));

		SaveBalance(id, 0);

		SendChannelMessage(channel, ""d_yes" **DEPOSITED** • <@%s>, you successfully deposited all of your coins to your bank!", id);
		return 1;
	}

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You don't have a bank account.");
		return 1;
	}

	if(strval(money) == 0)
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You deposited absolutely nothing!");
		return 1;
	}

	if(strval(money) > GetBalance(id))
	{
		SendChannelMessage(channel, ""d_no" **WORK MORE** • You don't have that much coins!");
		return 1;
	}

	SaveBalance(id, GetBalance(id) - strval(money));

	SaveDepBalance(id, GetDepBalance(id) + strval(money));

	SendChannelMessage(channel, ""d_yes" **DEPOSITED** • <@%s>, you successfully deposited `%i` "BOT_NAME" coins! "d_coin"", id, strval(money));

	return 1;
}
/*
dc command:depall(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You don't have a bank account.");
		return 1;
	}

	SaveDepBalance(id, GetDepBalance(id) + GetBalance(id));

	SaveBalance(id, 0);

	SendChannelMessage(channel, ""d_yes" **DEPOSITED** • <@%s>, you successfully deposited all of your coins to your bank!", id, money);

	return 1;
}
*/
dc command:with(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new money;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "i", money))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-with [amount of coins to withdraw]`");
		return 1;
	}

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> "d_no" **ERROR** • You don't have a bank account.");
		return 1;
	}

	if(money > GetDepBalance(id))
	{
		SendChannelMessage(channel, ""d_no" **NOT ENOUGH MONEY** • You don't have that much coins in your bank!");
		return 1;
	}

	SaveBalance(id, GetBalance(id) + money);

	SaveDepBalance(id, GetDepBalance(id) - money);

	SendChannelMessage(channel, ""d_yes" **WITHDREW** • <@%s>, you successfully withdrew `%i`"d_coin" from bank!", id, money);

	return 1;
}

dc command:rob(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new user[DCC_ID_SIZE + 10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-rob [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" **WHAT?** • You cannot rob yourself!");
		return 1;
	}

	if(GetBalance(user) == 0)
	{
		SendChannelMessage(channel, ""d_no" **POCKETS ARE EMPTY** • This player has got no coins for you!");
		return 1;
	}

	if(GetBalance(user) < 0)
	{
		SendChannelMessage(channel, ""d_no" **FAILED** • This guy is in crippling debts - you \
			were fined with `1000`:coins: because you tried to rob him.");
		SaveBalance(id, GetBalance(id) - 1000);
		return 1;
	}

	SaveBalance(id, GetBalance(id) + GetBalance(user));

	SendChannelMessage(channel, ""d_yes" **ROB WAS SUCCESSFUL** • Congratulations <@%s>, you successfully robbed <@%s> and took away all of his money (`%i`"d_coin").", id, user, GetBalance(user));

	SaveBalance(user, 0);

	return 1;
}

dc command:shop(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new shop[1024];
	
	format(shop, sizeof shop, ""d_yes" **SHOP** • This is the list of items you can purchase.\n\n\
	"d_phone" • **Phone** (*ID: `1`*)\n\
	"d_point" Price: "d_coin"`12000`\n\n\
	"d_gamepad" • **Gamepad** (*ID: `2`*)\n\
	"d_point" Price: "d_coin"`20000`\n\n\
	"d_wallet" • **Wallet** (*ID: `3`*)\n\
	"d_point" Price: "d_coin"`3000`\n\n\
	"d_pickaxe" • **Pickaxe** (*ID: `4`*)\n\
	"d_point" Price: "d_coin"`20000`\n\n\
	"d_furnace" • **Furnace** (*ID: `5`*)\n\
	"d_point" Price: "d_ruby"`100`\n\n\
	"d_slingshot" • **Slingshot** (*ID: `6`*)\n\
	"d_point" Price: "d_ruby"`15`\n\n");

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Diplomy Shop__**", shop, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

stock GetPhone(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/phone_%s.ini", user);
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

stock SetPhone(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/phone_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

stock GetGamepad(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/gamepad_%s.ini", user);
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

stock SetGamepad(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/gamepad_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

stock GetWallet(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/wallet_%s.ini", user);
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

stock SetWallet(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/wallet_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

stock GetPickaxe(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/pickaxe_%s.ini", user);
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

stock SetPickaxe(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/pickaxe_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

stock GetFurnace(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/furnace_%s.ini", user);
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

stock SetFurnace(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/furnace_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

stock GetSlingshot(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"inv/slingshot_%s.ini", user);
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

stock SetSlingshot(const user[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"inv/slingshot_%s.ini",user);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);
	return 1;
}

dc command:buy(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(eco);

	new id, user[DCC_ID_SIZE];

	DCC_GetUserId(author, user);

	if(sscanf(params, "i", id))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-buy [item ID]`");
		return 1;
	}

	/*if(GetBalance(user) < 0)
	{
		SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You can't buy anything if your balance is a negative number! Please withdraw some money first.");
		return 1;
	}*/

	if(id == 1)
	{
		if(GetBalance(user) < 12000)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetPhone(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_phone" | `Phone`!");
			return 1;
		}
		SetPhone(user);
		SaveBalance(user, GetBalance(user) - 12000);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_phone" | `Phone` for "d_coin" `12000`!");
		return 1;
	}
	if(id == 2)
	{
		if(GetBalance(user) < 20000)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetGamepad(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_gamepad" | `Gamepad`!");
			return 1;
		}
		SetGamepad(user);
		SaveBalance(user, GetBalance(user) - 20000);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_gamepad" | `Gamepad` for "d_coin" `20000`!");
		return 1;
	}

	if(id == 3)
	{
		if(GetBalance(user) < 3000)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetWallet(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_wallet" | `Wallet`!");
			return 1;
		}
		SetWallet(user);
		SaveBalance(user, GetBalance(user) - 3000);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_wallet" | `Wallet` for "d_coin" `3000`!");
		return 1;
	}

	if(id == 4)
	{
		if(GetBalance(user) < 20000)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetPickaxe(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_pickaxe" | `Pickaxe`!");
			return 1;
		}
		SetPickaxe(user);
		SaveBalance(user, GetBalance(user) - 20000);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_pickaxe" | `Pickaxe` for "d_coin" `20000`!");
		return 1;
	}
	if(id == 5)
	{
		if(GetRubies(user) < 100)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetFurnace(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_furnace" | `Furnace`!");
			return 1;
		}
		SetFurnace(user);
		SaveRubies(user, GetRubies(user) - 100);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_furnace" | `Furnace` for "d_ruby" `100`!");
		return 1;
	}
	if(id == 6)
	{
		if(GetRubies(user) < 15)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have enough money to purchase this item!");
			return 1;
		}
		if(GetSlingshot(user) == 1)
		{
			SendChannelMessage(channel, ""d_no" **ITEM OWNED** • You already own a "d_slingshot" | `Slingshot`!");
			return 1;
		}
		SetSlingshot(user);
		SaveRubies(user, GetRubies(user) - 15);
		SendChannelMessage(channel, ""d_yes" **ITEM BOUGHT** • You successfully bought a "d_slingshot" | `Slingshot` for "d_ruby" `15`!");
		return 1;
	}

	SendChannelMessage(channel, ""d_no" **ERROR** • Wrong item ID was given, please recheck the shop!");

	return 1;
}

dc command:inv(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(eco);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new inv[2048];
	
	format(inv, sizeof inv, ""d_yes" **INVENTORY** • This is the list of items that you have!\n\n\
	**Found Items**\n\n\
	"d_point" | "d_gold" • **Gold**: `%i`\n\
	"d_point" | "d_ruby" • **Rubies**: `%i`\n\
	"d_point" | "d_rawmeat" • **Raw Meat**: `%i`\n\
	"d_point" | "d_cookedmeat" • **Cooked Meat**: `%i`\n\
	\n**Bought Items**\n\n%s%s%s%s%s%s",
	GetGold(id),
	GetRubies(id),
	GetRawMeat(id),
	GetCookedMeat(id),
	
	GetPhone(id) ? ""d_point" | "d_phone" • **Phone** (*ID: `1`*)\n" : "",
	GetGamepad(id) ? ""d_point" | "d_gamepad" • **Gamepad** (*ID: `2`*)\n" : "",
	GetWallet(id) ? ""d_point" | "d_wallet" • **Wallet** (*ID: `3`*)\n" : "",
	GetPickaxe(id) ? ""d_point" | "d_pickaxe" • **Pickaxe** (*ID: `4`*)\n" : "",
	GetFurnace(id) ? ""d_point" | "d_furnace" • **Furnace** (*ID: `5`*)\n" : "",
	GetSlingshot(id) ? ""d_point" | "d_slingshot" • **Slingshot** (*ID: `6`*)\n" : "");

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Inventory__**", inv, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

dc command:mine(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetPickaxe(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_pickaxe" | `Pickaxe` to go mining!");
		return 1;
	}

	if(GetEnergy(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **YOU'RE TOO TIRED** • Your energy is at zero! Eat something or go hunting!");
		return 1;
	}

	new rubies = random(5);
	new gold = random(5);

	if(rubies == 0 && gold == 0)
	{
		SetEnergy(id, GetEnergy(id) - 1);
		SendChannelMessage(channel, "**<@%s>**\n\n"d_yes" **MINING FINISHED** • You've been mining for a while, but you could not find anything!", id);
		return 1;
	}

	SaveRubies(id, GetRubies(id) + rubies);
	SaveGold(id, GetGold(id) + gold);

	SendChannelMessage(channel, "**<@%s>**\n\n"d_yes" **MINING FINISHED** • You've been mining for a while, you found:\n\n"d_ruby" | *Rubies*: `%i`\n"d_gold" | *Gold*: `%i`", id, rubies, gold);
	SetEnergy(id, GetEnergy(id) - 1);

	return 1;
}

dc command:hunt(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(rp);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetSlingshot(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_slingshot" | `Slingshot` to go hunting!");
		return 1;
	}

	new rawmeat = random(5);

	if(rawmeat == 0)
	{
		SendChannelMessage(channel, "**<@%s>**\n\n"d_yes" **HUNTING FINISHED** • You've been hunting for a while, but you could not find anything!", id);
		return 1;
	}

	SaveRawMeat(id, GetRawMeat(id) + rawmeat);

	SendChannelMessage(channel, "**<@%s>**\n\n"d_yes" **HUNTING FINISHED** • You've been mining for a while, you brought back:\n\n"d_rawmeat" | *Raw Meat*: `%i`", id, rawmeat);

	return 1;
}

dc command:melt(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	if(GetFurnace(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You need a "d_furnace" | `Furnace` to melt stuff!");
		return 1;
	}
	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Melt Command__**", ""d_star" • You can melt stuff and get something else as a result.\n\
		Usage: `-melt [item] [quantity]`\n\n\
		**__Items__**\n\
		**`gold`**: Melt gold and get coins!\n\
		**`meat`**: Cook raw meat and make it edible!\n", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		SendChannelMessage(channel, ""d_no" **WHY AND HOW** • You can't use zero as quantity, sir.");
		return 1;
	}

	if(!strcmp(item, "gold"))
	{
		if(GetGold(id) < quantity)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have that much "d_gold" | `Gold`.");
			return 1;
		}
		SaveBalance(id, GetBalance(id) + (quantity*5));
		SaveGold(id, GetGold(id) - quantity);
		SendChannelMessage(channel, ""d_yes" **ITEM MELTED** • You successfully melted `%i` of "d_gold" | `Gold` and got `%i` "d_coin" | `Coins`!", quantity, quantity*5);
		return 1;
	}
	if(!strcmp(item, "meat"))
	{
		if(GetRawMeat(id) < quantity)
		{
			SendChannelMessage(channel, ""d_no" **BALANCE ERROR** • You do not have that much "d_rawmeat" | `Raw Meat`.");
			return 1;
		}
		SaveCookedMeat(id, GetCookedMeat(id) + quantity);
		SaveRawMeat(id, GetRawMeat(id) - quantity);
		SendChannelMessage(channel, ""d_yes" **ITEM COOKED** • You could not melt meat, but you could cook `%i` "d_rawmeat" | `Raw Meat` and get `%i` "d_cookedmeat" | `Cooked Meat`.", quantity, quantity);
		return 1;
	}
	
	else
	{
		SendChannelMessage(channel, ""d_no" **WHAT** • You can't put that into furnace!");
		SendTip(channel, "Use `-melt` to view a list of available items.");
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

stock GenerateBar(points = d_max_health)
{
	new bar[512];
	if(points == 0)
	{
		format(bar, sizeof bar, ""d_emptybar1""d_emptybar2""d_emptybar2""d_emptybar2""d_emptybar3"");
	}
	if(points == 1)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_emptybar2""d_emptybar2""d_emptybar2""d_emptybar3"");
	}
	if(points == 2)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_emptybar2""d_emptybar2""d_emptybar3"");
	}
	if(points == 3)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_emptybar2""d_emptybar3"");
	}
	if(points == 4)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_fullbar2""d_emptybar3"");
	}
	if(points == 5)
	{
		format(bar, sizeof bar, ""d_fullbar1""d_fullbar2""d_fullbar2""d_fullbar2""d_fullbar3"");
	}
	return bar;
}

dc command:mystats(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck(rp);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new stats[2048];
	
	format(stats, sizeof stats, "**Your Health**\n\
		"d_point" %s\n\n\
		**Your Energy**\n\
		"d_point" %s",
		GenerateBar(GetHealth(id)),
		GenerateBar(GetEnergy(id)));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Your Statistics__**", stats, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));

	return 1;
}

dc command:eat(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];
	DCC_GetUserId(author, id);

	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	new item[30],quantity;

	if(sscanf(params, "s[30]i", item, quantity))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Eat Command__**", ""d_star" • You can eat food and gain energy.\n\
		Usage: `-eat [item] [quantity]`\n\n\
		**__Items__**\n\
		**`meat`**: Eat cooked meat!\n", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(quantity == 0)
	{
		SendChannelMessage(channel, ""d_no" **WHY AND HOW** • You can't use zero as quantity, sir.");
		return 1;
	}

	if(!strcmp(item, "meat"))
	{
		if(GetCookedMeat(id) < quantity)
		{
			SendChannelMessage(channel, ""d_no" **QUANTITY ERROR** • You do not have that much "d_cookedmeat" | `Cooked Meat`.");
			return 1;
		}
		if(GetEnergy(id) == d_max_health)
		{
			SendChannelMessage(channel, ""d_no" **STATISTICS ERROR** • You aren't hungry at all! Your energy bar is full.");
			return 1;
		}
		if(quantity > (d_max_health - GetEnergy(id)))
		{
			SendChannelMessage(channel, ""d_no" **STATISTICS ERROR** • You aren't that hungry! You need to eat `%i` "d_cookedmeat" | `Cooked Meat` to fill up your energy bar.", 5 - GetEnergy(id));
			return 1;
		}
		SetEnergy(id, GetEnergy(id) + quantity);
		SendChannelMessage(channel, ""d_yes" **LUNCH IS OVER** • You ate `%i` "d_cookedmeat" | `Cooked Meat`!", quantity);
		return 1;
	}
	
	else
	{
		SendChannelMessage(channel, ""d_no" **HOW ABOUT NO?** • You can't eat that!");
		SendTip(channel, "Use `-eat` to view a list of available items.");
	}
	return 1;
}

//==========================
dc command:sprofile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-sprofile [user ID or user mention]`");
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
		"", col_embed, "Thanks for using our services!", 
		"",
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, GetMention(useridmention));
	return 1;
}

dc command:profile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-profile [user ID or user mention]`");
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
		"", col_embed, "Thanks for using our services!", 
		"",
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, GetMention(useridmention));
	return 1;
}

dc command:resetprofile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10], type;

	if(sscanf(params, "s[31]i", user, type))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-resetprofile [user ID or user mention] [type of a reset]`\n\nIf you want to reset GM profile of an user, use `0` as the type ID - if you want to reset a supporter profile, use `1` as the type ID.");
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

		SendChannelMessage(channel, "<@%s>'s GM profile has been cleared.", user);
	}
	if(type == 1)
	{
		SaveApprovalCount(user,0); 
		SaveSupportPoints(user,0);

		SendChannelMessage(channel, "<@%s>'s support profile has been cleared.", user);
	}
	if(type != 0 && type != 1)
	{
		SendChannelMessage(channel, ""d_no" **ERROR** • Invalid reset type ID provided, it can be either `0` or `1`.");
	}
	return 1;
}
/*
dc command:count(cmdparams)
{
	new DCC_Channel:channel;

	new id[DCC_ID_SIZE], count;

	DCC_GetMessageChannel(message, channel);

	if(sscanf(params, "i", count))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-count [number]`");
		return 1;
	}

	DCC_GetUserId(author, id);

	if(channel == countchannel)
	{
		if(count != pod_count+1)
		{
			SendChannelMessage(channel, "**__COUNT RUINED!__**\n"d_no" • __Unfortunately, <@%s> ruined the count at `%i`!__\n\n"d_star" • We'll go again! The next number is `1`.", id, pod_count+1);
			pod_count = 0;
			return 1;
		}
		if(count == pod_count+1)
		{
			pod_count++;
			AddReaction(message, DCC_CreateEmoji("☑️"));
			return 1;
		}
	}
	SendChannelMessage(channel, "> "d_no" **ERROR** • You need to be in a counting channel!");
	return 1;
}*/

dc command:top(cmdparams)
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

	    format(globalformat, sizeof globalformat, 
	    	":newspaper: Leaderboard for the overall GM count:\n\n\
	    	**1.** <@%s> - `%i` GMs\n\
	    	**2.** <@%s> - `%i` GMs\n\
	    	**3.** <@%s> - `%i` GMs\n\
	    	**4.** <@%s> - `%i` GMs\n\
	    	**5.** <@%s> - `%i` GMs\n\n\
	    	"d_point" If you want to view a leaderboard for each department, provide a department label after the command trigger:\n`-top [department]`", 
	    	slot1, GetGMCount(slot1),
	    	slot2, GetGMCount(slot2),
	    	slot3, GetGMCount(slot3),
	    	slot4, GetGMCount(slot4),
	    	slot5, GetGMCount(slot5));

	    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
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

	    format(globalformat, sizeof globalformat, 
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
			"**__Game Master Leaderboard__**", globalformat, 
			"",
			"", col_embed, "Thanks for using our services!", 
			"",
			"",""));
		return 1;
	}

	if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9 && dept != 12)
	{
		SendChannelMessage(channel, ""d_no" **GM COUNT LEADERBOARD** • Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`, `[war]`\n\n"d_star" • Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}
    return 1;
}

dc command:blacklist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-blacklist [user ID or user mention]`");
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
		SendChannelMessage(channel, ""d_no" • This user can't be blacklisted as the user is a bot owner!");
		return 1;
	}


	if(IsBlacklisted(user))
	{
		Unblacklist(user);
		SendChannelMessage(channel, ""d_yes" **UNBLACKLISTED** • <@%s> was unblacklisted successfully.", user);
		return 1;
	}

	if(!IsBlacklisted(user))
	{
		Blacklist(user);
		SendChannelMessage(channel, ""d_yes" **BLACKLISTED** • <@%s> was blacklisted successfully.", user);
		return 1;
	}

	return 1;
}

/*
=============================================
Roleplay functions
=============================================
*/

stock bool:IsValidCountry(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/country_%s.ini", country);
	return fexist(file_name) ? true : false;
}

static RegisterCountry(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/country_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "value.1;");
	fclose(file2);
	return 1;
}

static GetPlayer(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/player_%s.ini", country);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Noone");
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

stock SetPlayer(const country[], const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/player_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, id);
	fclose(file2);
	return 1;
}

static GetFullname(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/fullname_%s.ini", country);
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

static GetStateHead(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/statehead_%s.ini", country);
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

static GetGovHead(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/govhead_%s.ini", country);
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

static GetGovType(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/govtype_%s.ini", country);
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

static GetGdp(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/gdp_%s.ini", country);
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

static GetGdpPerCapita(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/gdppc_%s.ini", country);
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

static GetPublicDebt(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/debt_%s.ini", country);
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

static GetNationality(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/nationality_%s.ini", country);
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

static GetReligion(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/religion_%s.ini", country);
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

static GetInhabitants(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/inhabitants_%s.ini", country);
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

static GetActivePersonnel(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/activep_%s.ini", country);
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

static GetReservePersonnel(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/reservep_%s.ini", country);
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

stock GetMilitaryBudget(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/milbudget_%s.ini", country);
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

stock GetNAP(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/nap_%s.ini", country);
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

stock GetIOM(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/iom_%s.ini", country);
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

stock GetIPW(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/ipw_%s.ini", country);
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

stock GetCCY(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/ccy_%s.ini", country);
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

stock GetBCY(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/bcy_%s.ini", country);
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

stock SetFullname(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/fullname_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetStateHead(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/statehead_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetGovHead(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/govhead_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetGovType(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/govtype_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetNationality(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/nationality_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetReligion(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/religion_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetInhabitants(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/inhabitants_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetGdp(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/gdp_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetGdpPerCapita(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/gdppc_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetPublicDebt(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/debt_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetReservePersonnel(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/reservep_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetActivePersonnel(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/activep_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetMilitaryBudget(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/milbudget_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetNAP(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/nap_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetIOM(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/iom_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetIPW(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/ipw_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetCCY(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/ccy_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetBCY(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/bcy_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

dc command:nrphelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**RolePlay System commands**\n\n\
		"d_arrow"**`-nrpstats`**: View your country statistics!\n\
		"d_arrow"**`-nrpapply`**: Start a RP entity submission!\n\
		"d_arrow"**`-regrp`**: Register a country into the database.\n\
		"d_arrow"**`-setplayer`**: Set a player for a certain nation.\n\
		"d_arrow"**`-setrpstat`**: Update certain country statistics.\n\
		"d_arrow"**`-milstats`**: View military equipment statistics for a country.\n\
		"d_arrow"**`-setmilstat`**: Update the country's military statistics.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}

stock SetAppType(const id[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/apptype_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetAppType(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/apptype_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		new value;

		fread(file, strFromFile2);

		fclose(file);

		value = strval(strFromFile2);

		return value;
	}
	return 0;
}

stock SetUserQuestion(const id[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/qid_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetUserQuestion(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/qid_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		new value;

		fread(file, strFromFile2);

		fclose(file);

		value = strval(strFromFile2);

		return value;
	}
	return 0;
}

stock SetUserAnswer(const id[], ansid, const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/ans_%i_%s.ini",ansid, id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetUserAnswer(const id[], ansid)
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/ans_%i_%s.ini", ansid, id);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Empty");
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

dc command:nrpapply(cmdparams)
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
		"**__Submission Setup__**", ""d_star" These are the applications you can start.\n\
		Usage: `-nrpapply [option]`\n\n\
		**__Options__**\n\n\
		**`nation`**: Start an application for a *`Nation`*.\n\
		**`rebelorg`**: Start an application for a *`Rebellion Organization`*.\n\
		**`politicalorg`**: Start an application for a *`Political Organization`*.\n\
		**`corporation`**: Start an application for a *`Corporation`*.\n\
		**`acoop`**: Start an application for a *`Administrative Cooperator`*.\n\
		**`pcoop`**: Start an application for a *`Provincial Cooperator`*.\n\
		**`civilian`**: Start an application for a *`Civilian`*.\n\
		**`unsec`**: Start an application for a *`UN Secreatariat`*.",
		"","", col_embed, "Thanks for using our services!", 
		"","",""), ""d_star" **INFO** • Have fun!");
		return 1;
	}

	if(channel != submissionchannel)
	{
		SendChannelMessage(channel, ""d_no" **ERROR** • You can't start a submission application in this channel!");
		return 1;
	}

	//options
	if(!strcmp(option, "nation"))
	{
		SendChannelMessage(channel, ""d_yes" **APPLICATION STARTED** • <@%s> successfully started the *`Nation`* position application!", id);

		SetAppType(id, "1");
		SetUserQuestion(id, "1");

		SendChannelMessage(channel, "**Question 1** • Nation • <@%s>\n\n*`What is the nation name you are applying for?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "rebelorg"))
	{
		SendChannelMessage(channel, ""d_yes" **APPLICATION STARTED** • <@%s> successfully started the *`Rebellion Organization`* position application!", id);

		SetAppType(id, "2");
		SetUserQuestion(id, "1");

		SendChannelMessage(channel, "**Question 1** • Rebellion Organization • <@%s>\n\n*`In whose countries is your rebellion based in?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "politicalorg"))
	{
		SendChannelMessage(channel, ""d_yes" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "3");
		SetUserQuestion(id, "1");

		SendChannelMessage(channel, "**Question 1** • Political Organization • <@%s>\n\n*`In whose countries is your rebellion based in?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "corporation"))
	{
		SendChannelMessage(channel, ""d_yes" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "4");
		SetUserQuestion(id, "1");

		SendChannelMessage(channel, "**Question 1** • Corporation • <@%s>\n\n*`What is the name of your corporation?`*\n\nPlease reply here.", id);

		return 1;
	}
	if(!strcmp(option, "acoop"))
	{
		SendChannelMessage(channel, ""d_yes" **APPLICATION STARTED** • <@%s> successfully started the *`Political Organization`* position application!", id);

		SetAppType(id, "4");
		SetUserQuestion(id, "1");

		SendChannelMessage(channel, "**Question 1** • Administrative Cooperator • <@%s>\n\n*`What is the name of the nation you want to cooperate as?`*\n\nPlease reply here.", id);

		return 1;
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN APPLICATION** • Invalid application name provided, use `-nrpapply` to view a list of available applications!");
	}
	return 1;
}

dc command:nrpstats(cmdparams)
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
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-nrpstats [country name] [page <1, 2>]`");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	new msg[1024];
	
	if(page == 1)
	{
		format(msg, sizeof msg, ""d_yes" **%s** Statistics\n\n\
		"d_star" Main country player: *<@%s>*\n\n\
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
		format(msg, sizeof msg, ""d_yes" **%s** Statistics\n\n\
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
		SendChannelMessage(channel, ""d_no" **ERROR** • Wrong page ID.");
	}
	
	
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__RolePlay Country Statistics__**", msg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));
	
	return 1;
}

dc command:setplayer(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck(RiseOfNations);

	//modcheck;

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE], country[30];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[30]s[31]", country, user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-setplayer [country] [user ID or user mention]`");
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

	SendChannelMessage(rpnotices, "Main player updated for a country `%s` by **<@%s>**. New `%s` player is *<@%s>*.", country, id, country, user);

	SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

	return 1;
}

dc command:regrp(cmdparams)
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
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-regrp [country name]`");
		return 1;
	}

	if(IsValidCountry(country))
	{
		SendChannelMessage(channel, ""d_no" **ALREADY REGISTERED** • This country has been registered in the database before.");
		return 1;
	}

	RegisterCountry(country);

	SendChannelMessage(channel, "> "d_yes" **SUCCESS** • Country `%s` successfully registered.", country);
	return 1;
}

dc command:setrpstat(cmdparams)
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
		"**__RP Stats Setup__**", ""d_star" These are the options used to manipulate with RP country statistics.\n\
		Usage: `-setrpstat [country] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`fullname`**: Set the full name of a country (since a country's database name can be only one word).\n\
		**`statehead`**: Set the name of the head of state of a country.\n\
		**`govhead`**: Set the name of the head of the government of a country.\n\
		**`govtype`**: Set the government type.\n\
		**`nationality`**: Set the country's nationality.\n\
		**`religion`**: Set the country's religion(s).\n\
		**`inhabitants`**: Set the number of inhabitants of the country.\n\
		**`gdp`**: Set the country's GDP.\n\
		**`gdppc`**: Set the country's GDP per capita.\n\
		**`debt`**: Set the amount of country's public debt. Either in GDP percentage or money value.\n\
		**`ap`**: Set the amount of country's active personnel.\n\
		**`rp`**: Set the amount of country's reserve personnel.\n\
		**`milbudget`**: Set the country's military budget.\n\
		**`nap`**: Set the countries this country has non-agression pact with.\n\
		**`iom`**: Set the country's international organization membership(s).\n\
		**`ipw`**: Set the countries this country is in pact with.\n\
		**`ccy`**: Set the country's capital city.\n\
		**`bcy`**: Set the country's biggest city.", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
		return 1;
	}


	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	//options
	if(!strcmp(option, "fullname"))
	{
		SetFullname(country, value);

		SendChannelMessage(rpnotices, "`Full Name` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "statehead"))
	{
		SetStateHead(country, value);

		SendChannelMessage(rpnotices, "`Head of State` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "govhead"))
	{
		SetGovHead(country, value);

		SendChannelMessage(rpnotices, "`Head of Government` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "govtype"))
	{
		SetGovType(country, value);

		SendChannelMessage(rpnotices, "`Government Type` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "nationality"))
	{
		SetNationality(country, value);

		SendChannelMessage(rpnotices, "`Nationality` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "religion"))
	{
		SetReligion(country, value);

		SendChannelMessage(rpnotices, "`Religion(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "inhabitants"))
	{
		SetInhabitants(country, value);

		SendChannelMessage(rpnotices, "`Number of Inhabitants` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "gdp"))
	{
		SetGdp(country, value);

		SendChannelMessage(rpnotices, "`GDP` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "gdppc"))
	{
		SetGdpPerCapita(country, value);

		SendChannelMessage(rpnotices, "`GDP per Capita` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "debt"))
	{
		SetPublicDebt(country, value);

		SendChannelMessage(rpnotices, "`Public Debt` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ap"))
	{
		SetActivePersonnel(country, value);

		SendChannelMessage(rpnotices, "`Active Personnel` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "rp"))
	{
		SetReservePersonnel(country, value);

		SendChannelMessage(rpnotices, "`Reserve Personnel` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "milbudget"))
	{
		SetMilitaryBudget(country, value);

		SendChannelMessage(rpnotices, "`Military Budget` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "nap"))
	{
		SetNAP(country, value);

		SendChannelMessage(rpnotices, "`Non-Agression Pact(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "iom"))
	{
		SetIOM(country, value);

		SendChannelMessage(rpnotices, "`International Organization Membership(s)` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ipw"))
	{
		SetIPW(country, value);

		SendChannelMessage(rpnotices, "`Pact Status` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ccy"))
	{
		SetCCY(country, value);

		SendChannelMessage(rpnotices, "`Capital City` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "bcy"))
	{
		SetBCY(country, value);

		SendChannelMessage(rpnotices, "`Biggest City` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN OPTION** • Invalid option provided, use `-setrpstat` to view a list of available options.");
	}
	return 1;
}


stock GetAAE(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/aae_%s.ini", country);
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

stock SetAAE(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/aae_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetAPC(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/apc_%s.ini", country);
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

stock SetAPC(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/apc_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetASW(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/asw_%s.ini", country);
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

stock SetASW(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/asw_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetATE(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"ron/ate_%s.ini", country);
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

stock SetATE(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/ate_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

dc command:setmilstat(cmdparams)
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
		"**__Military Stats Setup__**", ""d_star" These are the options used to manipulate with RP country statistics.\n\
		Usage: `-setmilstat [country] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`aae`**: Anti-Air Equipment, mountable or on foot weaponry to counter aerial targets.\n\
		**`apc`**: Armored personnel carriers.\n\
		**`asw`**: Anti-submarine warfare helicopter.\n\
		**`ate`**: Anti-Tank Equipment, mountable or on foot weaponry to counter armored targets.\n\
		**`awacs`**: A large aircraft equipped for any kinds of naval tasks possible for aircrafts or general reconnaissance.\n\
		**`asf`**: Air Superiority Fighter is a plane used to target other aircrafts and establish dominance in an airspace.\n\
		**`acr`**: Aircraft Carrier is a capital ship used to carry aircrafts, usually escorted by a fleet of destroyers, cruisers and submarines!\n\
		**`asm`**: Attack submarine is a submarine with the primary purpose of finding and sinking other submarines, a must have thing for any navy with a capital ship.\n\
		**`ahc`**: Attack helicopter is a helicopter used to destroy mostly ground and rarely air targets.\n\
		**`bss`**: A ballistic missile uses projectile motion to deliver warheads on a target.\n\
		**`cas`**: Close Air Support Aircraft is an aircraft with ground support speciality or focus.\n\
		**`ccs`**: Convoy Cargo Ship is used to ferry goods and equipment to different ports and places across the waves!\n\
		**`css`**: Cruise Missile are missiles whose deliver a large warhead over long distances with high precision!\n\
		**`csr`**: \n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:\n\
		**``**:", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), GetMention(useridmention));
		return 1;
	}

	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
		return 1;
	}

	//options
	if(!strcmp(option, "aae"))
	{
		SetAAE(country, value);

		SendChannelMessage(rpnotices, "Military item count `AA Equipment` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "apc"))
	{
		SetAPC(country, value);

		SendChannelMessage(rpnotices, "Military item count `Armoed Personnel Carriers` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "asw"))
	{
		SetASW(country, value);

		SendChannelMessage(rpnotices, "Military item count `Anti-Submarine Warfare Helicopter` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	if(!strcmp(option, "ate"))
	{
		SetATE(country, value);

		SendChannelMessage(rpnotices, "Military item count `Anti-Tank Equipment` updated for a country `%s` by **<@%s>** into *%s*.", country, id, value);

		SendChannelMessage(channel, "Updated! Change has been announced in <#970015377289535538>.");

		return 1;
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN OPTION** • Invalid option provided, use `-setmilstat` to view a list of available options.");
	}
	return 1;
}

dc command:milstats(cmdparams)
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
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-milstats [country name]`");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN COUNTRY** • This country hasn't been registered in the database.");
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


	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Country Military Equipment Statistics__**", msg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));
	
	return 1;
}

/*

socialmedia

*/

dc command:smhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Social Media System**\n\n\
		**FOR MODS ONLY!**\n"d_arrow"**`-setaccdata`**: Edit another BRACE:tm: account.\n\n\
		"d_arrow"**`-smregister`**: Register an account on social media or change a current account's nickname.\n\
		"d_arrow"**`-smprofile`**: View your BRACE:tm: profile.\n\
		"d_arrow"**`-smaccname`**: Set your account name.\n\
		"d_arrow"**`-smbio`**: Update your account's bio.\n\
		"d_arrow"**`-smpfp`**: Update your account's profile picture.\n\
		"d_arrow"**`-post`**: Post a message on social media.\n\
		"d_arrow"**`-feed`**: The latest social media posts.", 
		"",
		"", col_embed, "Thanks for using our services! Please read '-smtos' to see Terms of Use of BRACE:tm: social media account.", 
		"",
		"",
		""), GetMention(useridmention));
	return 1;
}


dc command:smtos(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Terms of Use of BRACE:tm: Account__**", "**Hello! It's mandatory for everyone to accept our Terms of Use in order to use the their BRACE:tm: account properly.**\n\n\
		**1.** Your nickname must not threaten any person, group of persons or community.\n\
		\n**2.** Your account name must be appropriate. It must not contain links, NSFW content, cruel words or obituary names.\n\
		\n**3.** The profile picture of your account must also be something suitable for all users of this bot. As a picture, you must not have NSFW content, inappropriate words or pictures of people you have taken without their permission!\n\
		\n**4.** Your account bio must not contain inappropriate, prohibited or IP-grab links, as well as content that threatens a person, group of persons or community.\n\n\n\
		> We deeply care about our community's security, therefore, we would like to ask you that if you notice an account that violates the mentioned terms of use, to immediately report that account via the `-report` command. Your report must include the user ID of the profile.\n\n\
		> After you have reported the account, we will review and investigate the account and remove the reported content from the account.", 
		"",
		"", col_embed, "Thanks for using our services!", 
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

dc command:smregister(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[30];

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", nickname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-smregister [account nickname]`");
		return 1;
	}

	for(new i; i < strlen(nickname); i++)
	{
		if(nickname[i] == ' ')
		{
			SendChannelMessage(channel, ""d_no" **ERROR** • Nickname cannot contain spaces!");
			return 1;
		}
	}

	SetAccount(id, nickname);

	SendChannelMessage(channel, "> "d_yes" **SUCCESS** • Great, <@%s> - your new social media account nickname is __*@*%s__!", id, nickname);
	return 1;
}

dc command:setaccdata(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	modcheck;

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	new user[30], option[30], value[100];

	if(sscanf(params, "s[30]s[30]s[100]", user, option, value))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Account Setup__**", ""d_star" These are the options used to manipulate with other social media accounts.\n\
		Usage: `-setaccdata [user ID or user mention] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`verify`**: Use `false` or `true` as a value.\n\
		**`nickname`**: Set an account nickname.\n\
		**`name`**: Set an account name.\n\
		**`bio`**: Set an account bio.\n\
		**`pfp`**: Set a profile picture.", 
		"","", col_embed, "Thanks for using our services!", 
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

			SendChannelMessage(channel, "<@%s>'s account was successfully verified.", user);
		}
		else if(!strcmp(value, "false"))
		{
			//remove a verified status
			format(file_name, sizeof file_name,"socialmedia/verify_%s.ini",user);
			fremove(file_name);

			SendChannelMessage(channel, "<@%s>'s verified status was removed successfully.", user);
		}
		else
		{
			SendChannelMessage(channel, ""d_no" **UNKNOWN VALUE** • Invalid option value provided, use `-setaccdata` to view a list of available options and values.");
		}
		return 1;
	}
	if(!strcmp(option, "nickname"))
	{
		SetAccount(user, value);

		SendChannelMessage(channel, "You successfully updated `Account Nickname` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	if(!strcmp(option, "name"))
	{
		SetName(user, value);

		SendChannelMessage(channel, "You successfully updated `Account Name` for <@%s>'s account to `%s`.", user, value);
		
		return 1;
	}
	if(!strcmp(option, "bio"))
	{
		SetBio(user, value);

		SendChannelMessage(channel, "You successfully updated `Account Bio` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	if(!strcmp(option, "pfp"))
	{
		SetPfp(user, value);

		SendChannelMessage(channel, "You successfully updated `Account Profile Picture` for <@%s>'s account to `%s`.", user, value);

		return 1;
	}
	else
	{
		SendChannelMessage(channel, ""d_no" **UNKNOWN OPTION** • Invalid option provided, use `-setaccdata` to view a list of available options.");
	}
	return 1;
}

dc command:smprofile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	new user[30];

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", user))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-smprofile [user ID or user mention]`");
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
		fexist(file_name) ? ":ballot_box_with_check:" : " ",
		GetBio(user),
		GetBalance(user), 
		GetDepBalance(user),
		GetMessageCount(user) / 100 + 1, 
		GetMessageCount(user),
		GetAFK(user),
		user);


	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__BRACE:tm: Account__**", msg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		GetPfp(user),""), GetMention(useridmention));
	
	return 1;
}

dc command:smaccname(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[30];

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[30]", nickname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-smaccname [account name]`");
		return 1;
	}

	SetName(id, nickname);

	SendChannelMessage(channel, "> "d_yes" **SUCCESS** • Okay, <@%s> - your new social media account name is __*%s*__!", id, nickname);
	return 1;
}

dc command:smbio(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[100];

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[100]", nickname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-smbio [bio]`");
		return 1;
	}

	SetBio(id, nickname);

	SendChannelMessage(channel, "> "d_yes" **SUCCESS** • Your bio has been updated to `%s`, <@%s>!", nickname, id);
	return 1;
}

dc command:smpfp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[512];

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	if(sscanf(params, "s[512]", nickname))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-smpfp [picture link - link can have up to 512 characters]`");
		return 1;
	}

	SetPfp(id, nickname);

	SendChannelMessage(channel, "> "d_yes" **SUCCESS** • Your profile picture has been updated to `%s`, <@%s>!", nickname, id);
	return 1;
}

new newfeed[2048];
new feed[2048];

stock MakePost(const userid[], const name[], const nickname[], const text[])
{
	new file_name2[150];
	format(file_name2, sizeof file_name2,"socialmedia/verify_%s.ini",userid);
	new File: file2 = fopen("socialmedia/feed.ini", io_write);
	format(feed, sizeof feed, "**<@%s>** | __%s__ • @%s %s\n\n\
		> `%s`\n\n%s", 
		userid, 
		name, 
		nickname, 
		fexist(file_name2) ? ":ballot_box_with_check:" : "", 
		text,
		GetFeed());
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

		return newfeed;
	}
	return newfeed;
}

dc command:post(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	new text[150];

	if(sscanf(params, "s[150]", text))
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • Too few or wrong command arguments were given! Please try again using the command template below:\n\n`-post [text]`");
		return 1;
	}

	MakePost(id, GetName(id), GetNickname(id), text);

	SendChannelMessage(channel, ""d_yes" **POSTED** • Your text was posted on "BOT_NAME" network! View it using `-feed`.\n\n> "d_point" **NOTE** • If your text wasn't posted, it may be because of the high volume of the interactions right now, please retry.");
	return 1;
}

dc command:feed(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];
	new useridmention[DCC_ID_SIZE];DCC_GetUserId(author,useridmention);
	DCC_GetUserId(author, id);

	if(GetPhone(id) == 0)
	{
		SendChannelMessage(channel, ""d_no" **COMMAND ERROR** • You do not have a "d_phone" | `Phone`.");
		return 1;
	}

	format(feed, sizeof feed, ""d_phone" **NETWORK FEED** • View the most recent posts below.\n\n%s",GetFeed());

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Diplomy Network Feed__**", feed, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), GetMention(useridmention));
	return 1;
}

//SUPER HIDDEN COMMAND

dc command:nuke3454353454531296036(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_DeleteMessage(message);

	new DCC_Guild:guild;
	DCC_GetChannelGuild(channel, guild);

	SERVER_NUKE(guild);

	return 1;
}
