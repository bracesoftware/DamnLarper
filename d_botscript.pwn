#pragma option -;+
#include <a_samp>

#include <sscanf2>

#define SERVER_NAME "TND | The New Dawn"

#define DISCORD_PFP_LINK \
"https://cdn.discordapp.com/attachments/960100310293024770/960100357697052702/Transparent_Diplomy.png"

#define DISCORD_ATTACHMENT \
"https://cdn.discordapp.com/attachments/960100310293024770/971821068203491338/The_New_Dawn-Server_Image.png"

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
SendChannelMessage(channel,"> :x: **AUTHORIZATION ERROR** | You're not authorized to use this command!");return 1;}

#define setcheck%0(%1); if(settings[%1] == 0) { \
 SendChannelMessage(channel, "> :x: **ERROR** | This command module has been disabled."); return 1;}

#define servercheck; new DCC_Guild:guild;DCC_GetChannelGuild(channel, guild);if(guild != neod) {\
 SendChannelMessage(channel, "> :x: **ERROR** | I can't do that thing here!");return 1;}

#define usercheck(%0); if(DCC_FindUserById(%0) == DCC_INVALID_USER){ \
 SendChannelMessage(channel, "> :x: **ERROR** | I can't find an user with such ID or name - please, recheck the user ID, and submit again.\n\nUser: <@%s>", %0); \
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

new DCC_User:bot;

new DCC_Channel:commandchannel;
new DCC_Channel:gm_output;
new DCC_Channel:gm_count;
new DCC_Channel:logs;
new DCC_Channel:announcements;

new DCC_Channel:countchannel;

new DCC_Channel:reports;

new DCC_Role:muted;
new DCC_Role:gm;
new DCC_Role:pgm;
new DCC_Role:neodrole;

#define neod DCC_FindGuildById("965261756341559338")
#define bankicklog logs//DCC_FindChannelById("970971248525971466")
#define rpnotices DCC_FindChannelById("970015377289535538")
#define conflictnews DCC_FindChannelById("971015027295412234")

#define dateupdate DCC_FindChannelById("972564789668741130")

#define lounge DCC_FindChannelById("965261757050400800")

#define col_embed 0x7fff00

#define antiraid(%0,%1,%2); SendChannelMessage(channel, ":shield: **ANTI-RAID** | Hi, <@%s>! The bot's anti-raid system has been activated for `%s`! The moderators will be notified.\n\n",%1,%2);

new dateupdated;

enum esettings
{
	log,
	gmc,
	eco,
	mod,
	cnt,
	ccmd,
	ac
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
		"bot/pod_countgame.ini");
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
	format(file_name, sizeof file_name,"bot/pod_countgame.ini");
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
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
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/afk_%s.ini",id);
	format(string, sizeof(string), "%s", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetAFK(const id[])//, reason[])
{
	new file_name[150], reason[200];
	format(file_name, sizeof file_name,
		"data/afk_%s.ini", id);
	format(reason, sizeof reason, "Unknown");
	if(!fexist(file_name)) return reason;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, reason, 200);

		fclose(file);

		return reason;
	}
	return reason;
}

// Settings

new settings[esettings];

stock LoadSettings()
{
    new address[19][64],file_name[100];
    format(file_name, sizeof file_name,
        "bot/pod_settings.ini");
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
        
        fclose(file);
    }
    return 1;
}

stock SaveSettings()
{
    new string[228], file_name[100];
    format(file_name, sizeof file_name,
        "bot/pod_settings.ini");
    format(string, sizeof(string), 
        "%i*%i*%i*%i*%i*%i*%i",
        settings[log], 
        settings[gmc], 
        settings[eco], 
        settings[mod], 
        settings[cnt],
        settings[ccmd],
        settings[ac]);
    new File: file2 = fopen(file_name, io_write);
    fwrite(file2, string);
    fclose(file2);
    return 1;
}

new globalformat[1024];

#define SendChannelMessage(%1,%2) \
	format(globalformat,sizeof globalformat,%2);DCC_SendChannelEmbedMessage(%1, DCC_CreateEmbed( \
			"**__"SERVER_NAME"__**", globalformat, "","", col_embed, "Thanks for using our services!", \
			"",DISCORD_PFP_2_LINK,""), "")

/*

		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
			"**__"SERVER_NAME"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","",""), "");*/

#include <dcc>

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
		SendChannelMessage(channel, "> :x: **ERROR** | This custom command doesn't exist.");
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
	DCC_GetGuildMemberCount(neod, count);

	new id[DCC_ID_SIZE];

	for (new i; i != count; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(neod, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    DCC_GetUserId(user, id);

	    new bool:has_role;
	    DCC_HasGuildMemberRole(
	    	neod, user, 
	    	DCC_FindRoleById("965264321204604958"), has_role);

	    if(has_role)
	    {
	    	format(newid, sizeof newid, "*%s", id);
	    	strcat(staffstring, newid);
	    }

	    new bool:has_role2;
	    DCC_HasGuildMemberRole(
	    	neod, user, 
	    	DCC_FindRoleById("965264320625786920"), has_role2);

	    if(has_role2)
	    {
	    	format(newid, sizeof newid, "*%s", id);
	    	strcat(staffstring, newid);
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

public DCC_OnGuildMemberAdd(DCC_Guild:guild, DCC_User:user)
{
	if(guild == neod)
	{
		new id[DCC_ID_SIZE];

		DCC_GetUserId(user, id);

		SendChannelMessage(lounge, "Hello, <@%s>! First of all, we would like to welcome you and thank you for joining our community **The New Dawn**. To get started with roleplay, read <#965523854988570644> and <#965523792405352458>. In case you are interested in something, look at <#965523810524753930> - you may find what you are looking for. If you are interested in roles, take a look at <#968181829473554452>! When everything is ready, without hesitation apply for the desired entity (state, union, co-op, organization or sports club) in <#965490451333402644> using a specific template in <#965490312246095872>. If you need any other help, feel free to contact us via the ticket in <#965529291599269898>. That would be it! Thanks again - see you later!", id);
	}
	return 1;
}

public DCC_OnGuildMemberRemove(DCC_Guild:guild, DCC_User:user)
{
	if(guild == neod)
	{
		new id[DCC_ID_SIZE];

		DCC_GetUserId(user, id);

		SendChannelMessage(lounge, "Unfortunately, <@%s> left our community. Farewell!",id);
	}
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

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

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
			SendChannelMessage(channel, ":x: **MESSAGE MANAGEMENT** | Watch your language, <@%s>!", id);
		}
		if(channel == DCC_FindChannelById("965490451333402644"))
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

		if(channel == DCC_FindChannelById("970971122680078346"))
		{
			SaveSupportPoints(id, GetSupportPoints(id) + 1);
		}
	}

	SaveInactivityHours(id, 0);

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

	if(settings[ac] == 1)
	{
		if(author != bot)
		{
			SaveMessageCountPerSec(id, GetMessageCountPerSec(id)+1);

			if(GetMessageCountPerSec(id) > 2)
			{
				antiraid(channel, id, "Spamming");
				SetTimerEx("MsgPerSecReset", 1000, false, "s", id);
				return 1;
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
			"**__Hello!__**\n:wave: Hi, <@%s> - please use **`-help`** to interact with **"SERVER_NAME"**.\n\
			:star: **TIP** | You can't use commands in `#gm-output`.", id);

		new DCC_Embed:msg2 = DCC_CreateEmbed(
			"**__"SERVER_NAME"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","","");

		//SendChannelMessage(channel, msg);

		DCC_SendChannelEmbedMessage(channel, msg2, ":classical_building: | My prefixes are `-` and `d!`.");
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
					SendChannelMessage(channel, ":x: | This user (<@%s>) is now AFK. Reason: `%s`", user, GetAFK(user));
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
			"**__Hello!__**\n:wave: Hi, <@%s> - please use **`-help`** to interact with **"SERVER_NAME"**.\n\
			:star: **TIP** | You can't use commands in `#gm-output`.", id);

		new DCC_Embed:msg2 = DCC_CreateEmbed(
			"**__"SERVER_NAME"__**", response, "","", col_embed, "Thanks for using our services!", 
			"","","");

		//SendChannelMessage(channel, msg);

		DCC_SendChannelEmbedMessage(channel, msg2, ":classical_building: | My prefixes are `-` and `d!`.");
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
					SendChannelMessage(channel, ":x: | This is a counting channel. Don't chat here!");
					return 1;
				}
				if(count2 != GetCountGame()+1)
				{
					SendChannelMessage(channel, "**__COUNT RUINED!__**\n:x: | __Unfortunately, <@%s> ruined the count at `%i`!__\n\n:star: | We'll go again! The next number is `1`.", id, GetCountGame()+1);
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
		if(channel == gm_output)
		{
			if(settings[gmc] == 0) return 1;
			for(new i; i < strlen(msg); i++)
			{
				if(msg[i] == '\10') strdel(msg, i, i+1);
			}
			new linkcount, dept;
			for(new i; i < strlen(msg); i++)
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

				if(msg[i] == 'h' &&
					msg[i+1] == 't' &&
					msg[i+2] == 't' &&
					msg[i+3] == 'p' &&
					msg[i+4] == 's' &&
					msg[i+5] == ':' &&
					msg[i+6] == '/' &&
					msg[i+7] == '/')
				{
					linkcount ++;
				}

				if(msg[i] == '%') 
					linkcount++;

				if(msg[i] == 'G' && msg[i+1] == 'D' && msg[i+2] == 'P')
				{
					linkcount ++;
				}

				if(msg[i] == 'd' && msg[i+1] == 'd' && msg[i+2] == 'p')
				{
					linkcount ++;
				}

				if(msg[i] == 'T' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					linkcount ++;
				}

				if(msg[i] == 't' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					linkcount ++;
				}

				if(msg[i] == 'i' && msg[i+1] == 'n' && msg[i+2] == 'f' 
					&& msg[i+3] == 'l' && msg[i+4] == 'a' && msg[i+5] == 't')
				{
					linkcount ++;
				}
			}

			if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9 && linkcount != 0)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | Sorry, <@%s> - invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | <@%s>, you can't chat or use commands in there!\n:star: | If you think this is a mistake, report a bug using `-report` or check if you used a valid GM template (`-gmtemp`).", id);
				return 1;
			}
			else if(linkcount == 0)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
				return 1;
			}

			if(dept == 1) // Politics department solo
			{
				if(linkcount == 1)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SavePolGMCount(id,GetPolGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 3) // Economics solo
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SaveEcoGMCount(id,GetEcoGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 8) // Military solo
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SaveMilGMCount(id,GetMilGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			// Mixed labels:
			
			if(dept == 4) // pol eco
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Politics & Economics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SavePolEcoGMCount(id,GetPolEcoGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 11) // eco mil
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```",
						 id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Economics & Military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SaveEcoMilGMCount(id,GetEcoMilGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}

			if(dept == 9) // mil pol
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```",
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **Military & Politics**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
				"","",""));

				SaveMilPolGMCount(id,GetMilPolGMCount(id)+1);

				SaveGMCount(id,GetGMCount(id)+1);
				return 1;
			}
			
			return 1;
		}
		else if(channel == conflictnews)
		{
			if(settings[gmc] == 0) return 1;
			for(new i; i < strlen(msg); i++)
			{
				if(msg[i] == '\10') strdel(msg, i, i+1);
			}
			new linkcount, dept;
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

				if(msg[i] == 'h' &&
					msg[i+1] == 't' &&
					msg[i+2] == 't' &&
					msg[i+3] == 'p' &&
					msg[i+4] == 's' &&
					msg[i+5] == ':' &&
					msg[i+6] == '/' &&
					msg[i+7] == '/')
				{
					linkcount ++;
				}
			}
			
			if(dept != 1)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | Sorry, <@%s> - invalid department label(s) provided. You can use: `[war]`", id);
				return 1;
			}
			else if(dept == 0 && linkcount == 0)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | <@%s>, you can't chat or use commands in there!\n:star: | If you think this is a mistake, report a bug using `-report` or check if you used a valid GM template (`-gmtemp`).", id);
			}
			else if(linkcount == 0)
			{
				SendChannelMessage(channel, ":x: **GM COUNT** | Sorry, your GM wasn't counted <@%s> - you need to provide a post link in your GM!", id);
				return 1;
			}

			for(new i; i < strlen(msg); i++)
			{

				if(msg[i] == '%') 
					linkcount++;

				if(msg[i] == 'G' && msg[i+1] == 'D' && msg[i+2] == 'P')
				{
					linkcount ++;
				}

				if(msg[i] == 'd' && msg[i+1] == 'd' && msg[i+2] == 'p')
				{
					linkcount ++;
				}

				if(msg[i] == 'T' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					linkcount ++;
				}

				if(msg[i] == 't' && msg[i+1] == 'a' && msg[i+2] == 'x')
				{
					linkcount ++;
				}

				if(msg[i] == 'i' && msg[i+1] == 'n' && msg[i+2] == 'f' 
					&& msg[i+3] == 'l' && msg[i+4] == 'a' && msg[i+5] == 't')
				{
					linkcount ++;
				}
			}

			if(dept == 1) // war gm
			{
				if(linkcount == 1){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Easy**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveEasyGMCount(id, GetEasyGMCount(id)+1);
				}
				if(linkcount == 2){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Subnormal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", 
						id, GetGMCount(id)+1);
					SaveSubnormalGMCount(id, GetSubnormalGMCount(id)+1);
				}
				if(linkcount == 3){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Normal**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveNormalGMCount(id, GetNormalGMCount(id)+1);
				}
				if(linkcount == 4){
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Medium**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveMediumGMCount(id, GetMediumGMCount(id)+1);
				}
				if(linkcount > 4)
				{
					format(count, sizeof count, "**GM Count**\n\nGameMaster: <@%s>\nDepartment: **War - military**\n\
						Level: **Hard**\n\
						Total GM count: `%i`\n```\nUse -gmlvl to see more about GM levels.\n```", id, GetGMCount(id)+1);
					SaveHardGMCount(id, GetHardGMCount(id)+1);
				}
				AddReaction(message, DCC_CreateEmoji("☑️"));//AddReaction(message, yes);
				DCC_SendChannelEmbedMessage(gm_count, DCC_CreateEmbed(
				"**__"SERVER_NAME"__**", count, "","", col_embed, "Thanks for using our services!", 
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
		SendChannelMessage(channel, ":x: **UNKNOWN COMMAND** | <@%s>, you need to use it like this: `-<command> [arguments]`", id);
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

	if(guild == DCC_FindGuildById("795007259439923200"))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | The bot is not going to respond to GM results or requests anymore. The bot services are going to be fully shut down by **10th May 2022**.");
		return 1;
	}

	if(IsBlacklisted(id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You're blacklisted from using bot commands.");
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
	DCC_GetGuildMemberCount(neod, count);

	new id[DCC_ID_SIZE];

	for (new i; i != count; i++)
	{
	    new DCC_User:user;
	    if (!DCC_GetGuildMember(neod, i, user))
	    {
	        // error
	        continue;
	    }

	    // at this point you have access to all users in 
	    // the Discord server you specified

	    DCC_GetUserId(user, id);

	    new bool:has_role;
	    DCC_HasGuildMemberRole(neod, user, gm, has_role);

	    if(has_role)
	    {
	    	SaveInactivityHours(id, GetInactivityHours(id) + 1);
	    	if(GetInactivityHours(id) == 72)
	    	{
	    		SendChannelMessage(logs, ":x: **INACTIVITY PURGE** | Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }

	    new bool:has_role2;
	    DCC_HasGuildMemberRole(neod, user, pgm, has_role2);

	    if(has_role2)
	    {
	    	SaveInactivityHours(id, GetInactivityHours(id) + 1);
	    	if(GetInactivityHours(id) == 72)
	    	{
	    		SendChannelMessage(logs, ":x: **INACTIVITY PURGE** | Probationary Game Master <@%s> was inactive for 72 hours (3 days)!", id);
	    	}
	    }
	}

    /*split(staffstring, staffid, '*');

    for(new i; i < MAX_STAFF_MEMBERS; i++)
    {
    	SaveInactivityHours(staffid[i], GetInactivityHours(staffid[i]) + 1);
    	if(GetInactivityHours(staffid[i]) == 72)
    	{
    		SendChannelMessage(rpnotices, ":x: **INACTIVITY PURGE** | <@%s> was inactive for 72 hours (3 days)!", staffid[i]);
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
	if(r==0) DCC_SetBotActivity("discord.gg/XyjwzU4u5f ┊ -help");
	if(r==1) DCC_SetBotActivity("Mention me! ┊ -help");
	if(r==2) DCC_SetBotActivity("TND ┊ -help");
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
		"`%d/%d/%d` | `%d:%d:%d` :arrow_forward: %s*", 
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
		SendChannelMessage(channel, "> :x: **ERROR** | The command entered doesn't exist.");
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
				"**__Command used__**\n\n:star: User: <@%s>\nCommand text: `%s`\n:exclamation: User is a moderator.",
			id, content);
		}
		else
		{
			format(logmsg, sizeof logmsg, "**__Command used__**\n\n:star: User: <@%s>\nCommand text: `%s`",
			id, content);
		}
		DCC_SendChannelEmbedMessage(logs, DCC_CreateEmbed(
		"**__"SERVER_NAME"__**", 
		logmsg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), ":star: **INFO** | Mention me for more information!");
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
	LoadSettings();
	DCC_SetBotPresenceStatus(IDLE);
	SetTimer("ActivityChange", 2000, true);
	SetTimer("InactivityPurge", 3600000, true);
	SetTimer("DateUpdate", 10000, true);
	//SetTimer("MsgPerSecReset", 1000, true);

	bot = DCC_FindUserById(""BOT_USER_ID"");

	muted = DCC_FindRoleByName(neod, "Muted Member");
	neodrole = DCC_FindRoleByName(neod, ""SERVER_NAME"");
	pgm = DCC_FindRoleById("965264321204604958");
	gm = DCC_FindRoleById("965264320625786920");

	commandchannel = DCC_FindChannelById("965262345280577536");
	gm_output = DCC_FindChannelById("965522890852286464");
	gm_count = DCC_FindChannelById("965620934524407848");
	logs = DCC_FindChannelById("965593169104371842");
	announcements = DCC_FindChannelById("965522423539724288");

	countchannel = DCC_FindChannelById("971122895575195688");

	reports = DCC_FindChannelById("971124443659243520");

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
		"**__"SERVER_NAME"__**", 
		":white_check_mark: | Bot has successfully (re)started - use `-help` or `d!help` for help!", 
		DISCORD_ATTACHMENT,
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(commandchannel, msg2, ":star: **INFO** | Mention me for more information!");
	DCC_SendChannelEmbedMessage(logs, msg2, ":star: **INFO** | Mention me for more information!");
}

//Logs:

public DCC_OnChannelCreate(DCC_Channel:channel)
{
	if(settings[log] == 0) return 0;

	new name[100];
	DCC_GetChannelName(channel, name, sizeof name);

	new logmsg[256];

	format(logmsg, sizeof logmsg, "**__Channel created__**\n\n\
		:white_check_mark: Name: **#%s**", name);

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
		:x: Name: **#%s**", name);

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
		:x: User: <@%s>\n:x: Content: **%s**", id, content);

	SendChannelMessage(logs, logmsg);
	return 1;
}

public DCC_OnUserUpdate(DCC_User:user)
{
	if(settings[log] == 0) return 0;

	new logmsg[256], id[DCC_ID_SIZE];

	DCC_GetUserId(user, id);

	format(logmsg, sizeof logmsg, "**__User update__**\n\n:white_check_mark: | User <@%s> has been updated.", id);

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

dc command:addmod(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-addmod [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This user is already a moderator!");
		return 1;
	}

	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "");
	fclose(file2);

	format(msg, sizeof msg, ":white_check_mark: | User <@%s> added to the moderator team successfully.", user);

	SendChannelMessage(channel, msg);

	return 1;
}

dc command:annc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new string[512], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[512]", string))
	{
		SendChannelMessage(channel, ":x: | Usage: `-annc [announcement text]`\n\
			:star: **TIP** | In order to strip to a new line, at the point you want to add a new line add `\\` symbol.\n\
			**Example:** `-annc Funny\\text.`");
		return 1;
	}

	for(new i; i < strlen(string); i++)
	{
		if(string[i] == '\\') string[i] = '\n';
	}

	new msg[1024];
	
	format(msg, sizeof msg, ":exclamation: Announcement posted by <@%s>.\n\n\
		`%s`", id, string);

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__"SERVER_NAME"__** Announcement", msg, 
		DISCORD_ATTACHMENT,
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		"","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(announcements, msg2, ":star: **INFO** | This is an announcement repost made with `-annc` mod command.");

	SendChannelMessage(channel, ":white_check_mark: | Announcement was posted successfully.");
	return 1;
}


dc command:delmod(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE + 10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-delmod [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This user can't be removed as the user is a bot owner!");
		return 1;
	}

	new file_name[150], msg[512];
	format(file_name, sizeof file_name,"mods/mod_%s.ini",user);
	
	if(!fexist(file_name))
	{
		SendChannelMessage(channel, ":x: | This user is not a moderator!");
		return 1;
	}

	fremove(file_name);

	format(msg, sizeof msg, ":x: | User <@%s> removed from the moderator team successfully.", user);

	SendChannelMessage(channel, msg);

	return 1;
}

dc command:help(cmdparams)
{

	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new DCC_Guild:guild;

    DCC_GetChannelGuild(channel, guild);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
	"**__MAIN PANEL FOR "SERVER_NAME" BOT!__**", ":wave: - **Hello, dear diplomatician!**\n\n\
	:heart: Welcome to **"SERVER_NAME"**.\n\
	:star: __List of main commands:__\n\
	**`-settings`**: Manage bot's settings.\n\
	**`-moderation`**: Help about server moderation.\n\
	**`-version`**: Last bot update.\n\
	**`-website`**: Link to our website where you can find various information and other links.\n\
	**`-errors`**: Check for the bot errors.\n\
	**`-report`**: Report a bug, error and such exploits.\n\
	**`-tos`**: Read our application's Terms of Service.\n\
	**`-pp`**: Read our Privacy Policy.\n\n\
	:star: __List of other commands for fun:__\n\
	**`-ecohelp`**: Help about economy commands.\n\
	**`-afkhelp`**: Help about AFK system.\n\
	**`-ccmdhelp`**: Help with your own custom commands!\n\
	**`-funhelp`**: Other miscellaneous panel - contains a big variety of other types of commands!\n\
	**`-lvlhelp`**: Help about leveling system.\n\
	**`-bumphelp`**: Help about server bumping and leaderboard.\n\
	**`-listhelp`**: Lists system help.\n\
	**`-rphelp`**: Nation role-play system help.\n\
	**`-achelp`**: Anti-raid system help.\n\
	**`-smhelp`**: Social media system help.\n\n\
	:star: __List of bot features:__\n\
	:arrow_forward: To view a list of all features provided by the bot, use `-features`.\n\n\
	:thumbsup: You can [invite me](https://discord.com/api/oauth2/authorize?client_id="BOT_USER_ID"&permissions=8&scope=bot) on your server too! Use `-botsetup` to learn about everything you need to know before inviting me.\n\n\
	:dizzy: **NOTICE** | This bot supports multi-server data storage \
	(e.g. your data such as money in the economy is \
	stored globally, not each balance for a separate \
	server - this means if you type `-work` on one server, \
	on all other servers your economy balance will get updated). \
	Same also counts for other stuff as AFK status and such.", 
	"",
	"", col_embed, "Thanks for using our services!", 
	DISCORD_ATTACHMENT,
	DISCORD_PFP_LINK,
	""), ":star: **TIP** | This is a help panel, also called a main panel, \
    	navigate to other panels using the commands mentioned there.");

	return 1;
}

dc command:features(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ":star: Below, there's a list of all the features included in the bot.\n\n\
		**Exclusive "SERVER_NAME" Features**\n\
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
		:star: **NOTE** | Bot is regularly maintained and updated, a lot of interesting cross-server features are coming soon!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

	return 1;
}

dc command:tos(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

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
		\n**8.** Read our Privacy Policy for more, use `-pp` command to do so.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:pp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Privacy Policy__**", ":white_check_mark: Your information is safe!\n\n\
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
		""), "");
	return 1;
}

dc command:listhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**List System commands**\n\n\
		**`-createlist`**: Create a list!\n\
		**`-addelement`**: Add a list element (an user for example).\n\
		**`-delelement`**: Delete a list element.\n\
		**`-viewlist`**: View a list.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:achelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Anti-raid System commands**\n\n\
		**`-settings ac`**: Disable/enable the system.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:createlist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE],listname[20];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[20]", listname))
	{
		SendChannelMessage(channel, ":x: | Usage: `-createlist [list name]`");
		return 1;
	}

	if(IsValidList(listname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This list already has been created.");
		return 1;
	}

	CreateList(id, listname);

	SendChannelMessage(channel, ":white_check_mark: **LIST CREATED** | Your list has been created successfully.");

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
		SendChannelMessage(channel, ":x: | Usage: `-addelement [list name] [element]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You can only modify lists that you created!");
		return 1;
	}

	AddListElement(listname, element);

	SendChannelMessage(channel, ":white_check_mark: **LIST MODIFIED** | Your list has been successfully modified.");
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
		SendChannelMessage(channel, ":x: | Usage: `-delelement [list name] [element ID]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This list doesn't exist.");
		return 1;
	}

	if(!OwnsList(listname, id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You can only modify lists that you created!");
		return 1;
	}

	RemoveListElement(listname, element-1);

	SendChannelMessage(channel, ":white_check_mark: **LIST MODIFIED** | Your list has been successfully modified.");
	return 1;
}

dc command:viewlist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new listname[20], element[150], el[50];

	if(sscanf(params, "s[20]", listname))
	{
		SendChannelMessage(channel, ":x: | Usage: `-viewlist [list name]`");
		return 1;
	}

	if(!IsValidList(listname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This list doesn't exist.");
		return 1;
	}

	//GetElement(list, element, dest);

	format(listpreview, sizeof listpreview, ":newspaper: This is a preview of **%s** list.\n\
		`[element ID] | [element content]`\n\n", listname);

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
		""), "");

	return 1;
}

dc command:funhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Miscellaneous commands**\n\n\
		**`-search`**: Let me Google stuff for you!\n\
		**`-say`**: Say something anonymously.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

	return 1;
}

dc command:bumphelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", ":x: This system is under heavily development.\n\n\
		**`-bump`**: Bump your server!\n\
		**`-servers`**: View the server leaderboards.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

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

    SaveBumpCount(id, GetBumpCount(id) + 1);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bump Done!__**", ":white_check_mark: Your server successfully got bumped on the bot's global server leaderboard.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:servers(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

    DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Coming soon!__**", ":x: This feature is currently unavailable, but don't give up with bumping - bump command works.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:lvlhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Leveling system help__**\n\n\
		:star: This is a message-based leveling system. Statistics and rewards \
		gained in it is stored in multi-server storage, which means, if you achieved \
		level 2 on one server, on all other servers this bot is in, you will be level 2.\n\n\
		**Leveling Policy**\n\
		:star: Every 100 messages you send, you climb up by one level! \
		You can check your level using `-level` command.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

	return 1;
}

dc command:level(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new lvl[256];

	format(lvl, sizeof lvl, ":speaking_head: User: <@%s>\n:crown: Level: %i\n:star: Total message count: %i", id, GetMessageCount(id) / 100 + 1, GetMessageCount(id));

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Level Statistics__**", lvl, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

	return 1;
}

dc command:ccmdhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Custom Command help__**\n\n\
		**`-declcmd`**: Declare (create) a custom command.\n\
		**`-delcmd`**: Delete a custom command.\n\n\
		:star: **TIP** | Bot responds to these commands only when they have a `!` prefix.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

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
		SendChannelMessage(channel, ":x: | Usage: `-declcmd [command name] [text to respond with]`");
		return 1;
	}

	if(IsCommand(cmdname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This command is already registered!");
		return 1;
	}

	for(new i; i < strlen(text); i++)
	{
		if(text[i] == '<' && text[i+1] == '@')
		{
			SendChannelMessage(channel, ":x: **ERROR** | Invalid characters detected in the text response.");
			return 1;
		}
		if(text[i] == '<' && text[i+1] == '!' && text[i+2] == '@')
		{
			SendChannelMessage(channel,":x: **ERROR** | Invalid characters detected in the text response.");
			return 1;
		}
	}

	CreateCommand(cmdname, id, text);

	SendChannelMessage(channel, ":white_check_mark: **COMMAND CREATED** | Your custom command is successfully registered!\n> :arrow_forward: Try using it now!");
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
		SendChannelMessage(channel, ":x: | Usage: `-delcmd [command name]`");
		return 1;
	}

	if(!IsCommand(cmdname))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This command doesn't exist!");
		return 1;
	}

	if(!IsUsersCommand(cmdname, id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You can only delete the commands that you created!");
		return 1;
	}

	DeleteCommand(cmdname);

	SendChannelMessage(channel, ":white_check_mark: **COMMAND DELETED** | Your custom command is successfully deleted!");
	
	return 1;
}

dc command:botsetup(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Bot Setup__**", ":wave: - **Hello, dear diplomatician!**\n\n\
		:heart: __Welcome to a bot setup guide and FAQ-s.__\n\
		:arrow_forward: This bot doesn't need any setup when it gets invited, \
		as it is supporting multi-server storage. Only some commands such as moderation \
		and GM counting features, counting, etc. won't work. Features such as economy, \
		AFK status and more upcoming will work as nothing happened. Get the invite link on the `-help` panel!\n\n\
		**__Important Command Note__**\n\
		:arrow_forward: Please note that if you want to execute a standard command (aka commands displayed on \
		help panels) use `neod` or `-` as a prefix, the `!` prefix is used to execute custom commands \
		(read more about custom commands on `-ccmdhelp`)!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		DISCORD_PFP_LINK,
		""), ":star: **TIP** | Thanks for bothering inviting **Diplomy** to your server.");
	return 1;
}

dc command:report(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new text[256], id[DCC_ID_SIZE];

	if(sscanf(params, "s[256]", text))
	{
		SendChannelMessage(channel, ":x: | Usage: `-report [report text]`");
		return 1;
	}

	DCC_GetUserId(author, id);

	new msg[1024];
	
	format(msg, sizeof msg, ":thumbsup: - **Hi**, <@%s>**!**\n\n\
		:white_check_mark: | Your report was successfully sent to the support server, we'll start to investigate as soon as possible.\n\
		Thank you for helping us and our community to provide our users and you a better experience! :heart:\n\n\
		**Support Server**\n\
		:arrow_forward: If you wish, you can join our support server below.\n\n\
		["SERVER_NAME" | Support](https://discord.gg/XyjwzU4u5f)", id);

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		":briefcase: **__REPORT RESPONSE__**", msg, 
		"",
		"", 
		col_embed, "Thanks for using our services!", 
		"",
		DISCORD_PFP_LINK,
		"");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, ":star: **SUCCESS** | Read the text below for more information!");

	SendChannelMessage(reports, "**__New Report__**\n\n:speaking_head: **User:** <@%s>\n:newspaper: **Text:** __%s__", id, text);
	return 1;
}

dc command:errors(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	modcheck;

	SendChannelMessage(channel, ":star: **INFO** | `No errors found.`\n:exclamation: **NOTE** | This system is currently under a beta phase!");
	return 1;
}

//https://www.google.com/search?q=KEYWORDS+OF+A+SEARCH
dc command:search(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new query[256];

	if(sscanf(params, "s[256]", query))
	{
		SendChannelMessage(channel, ":x: | Usage: `-search [search text]`");
		return 1;
	}

	for(new i; i < strlen(query); i++)
	{
		if(query[i] == ' ') query[i] = '+';
	}

	SendChannelMessage(channel, ":white_check_mark: **SEARCHING FINISHED** | Your search results: \nhttps://www.google.com/search?q=%s\n`%i results in 0,%is`", query, random(100000), random(10));
	return 1;
}

dc command:say(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new t[256];

	if(sscanf(params, "s[256]", t))
	{
		SendChannelMessage(channel, ":x: | Usage: `-say [text]`");
		return 1;
	}

	DCC_DeleteMessage(message);

	SendChannelMessage(channel, "%s", t);
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

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__"SERVER_NAME" | Website__**", "\
		:arrow_forward: | Visit our community on the web! Access our site by clicking this [link](https://diplomybot.000webhostapp.com/index.html)!", 
		"",
		"", col_embed, "Thanks for using our services!", 
		DISCORD_ATTACHMENT,
		DISCORD_PFP_LINK,
		""), "");


	return 1;
}

dc command:version(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, "> :white_check_mark: **__Last Update__**\n\n**LAST UPDATE** | Script was (re)compiled last time at `%s-%s`.\n**SCRIPT VERSION** | Bot code version: `1.0`",__date, __time);

	return 1;
}

dc command:ecohelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__Economy commands__**\n\n\
		**`-bal`**: View your balance.\n\
		**`-work`**: Work and earn money.\n\
		**`-dep`**: Deposit money.\n\
		**`-bankacc`**: Open a bank account.\n\
		**`-with`**: Withdraw money.\n\
		**`-rob`**: Rob a member.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

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
		SendChannelMessage(channel, "> :x: **ERROR** | You already have opened a bank account.");
		return 1;
	}

	OpenBankAccount(id);

	SendChannelMessage(channel, ":white_check_mark: **BANK** | You successfully opened a bank account.");

	return 1;
}

dc command:afkhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**__AFK commands__**\n\n\
		**`-afk`**: Set your AFK status.\n\
		:star: **TIP** | Your AFK status gets removed once you send a message into any channel of a server.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");

	return 1;
}

dc command:afk(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new afkstatus[256];

	if(sscanf(params, "s[256]", afkstatus))
	{
		SendChannelMessage(channel, ":x: | Usage: `-afk [AFK status text]`");
		return 1;
	}

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	SetAFK(id, afkstatus);

	SendChannelMessage(channel, ":white_check_mark: | Alright, <@%s> - you're now AFK.", id);

	return 1;
}

dc command:settings(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	new option[30];

	if(sscanf(params, "s[30]", option))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__BOT SETTINGS PANEL__**", ":star: These are the options used to manipulate with bot settings.\n\
		Usage: `-settings [option]`\n\n\
		**__Settings ON by default__**\n\
		**`logs`**: Enable or disable the log system.\n\
		**`gmc`**: Activate or deactivate GM counting.\n\
		**`eco`**: Toggle economy commands on or off.\n\
		**`mod`**: Toggle commands such as `-kick`, `-warn` on or off.\n\n\
		**__Settings OFF by default__**\n\
		**`count`**: Enable or disable the counting system.\n\
		**`ccmd`**: Enable or disable custom commands.\n\
		**`ac`**: Activate or deactivate anti-raid system.", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), ":star: **INFO** | Only bot mods can use these commands.");
		return 1;
	}

	if(!strcmp(option, "ccmd"))
	{
		modcheck;

		if(settings[ccmd] == 1)
		{
			settings[ccmd] = 0;
			SendChannelMessage(channel, ":x: | Custom commands system has been disabled.");
			return 1;
		}
		if(settings[ccmd] == 0)
		{
			settings[ccmd] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Custom commands system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "logs"))
	{
		modcheck;

		if(settings[log] == 1)
		{
			settings[log] = 0;
			SendChannelMessage(channel, ":x: | Log system has been disabled.");
			return 1;
		}
		if(settings[log] == 0)
		{
			settings[log] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Log system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "eco"))
	{
		modcheck;

		if(settings[eco] == 1)
		{
			settings[eco] = 0;
			SendChannelMessage(channel, ":x: | Economy commands have been disabled.");
			return 1;
		}
		if(settings[eco] == 0)
		{
			settings[eco] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Economy commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "count"))
	{
		modcheck;

		if(settings[cnt] == 1)
		{
			settings[cnt] = 0;
			SendChannelMessage(channel, ":x: | Counting system has been disabled.");
			return 1;
		}
		if(settings[cnt] == 0)
		{
			settings[cnt] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "gmc"))
	{
		modcheck;

		if(settings[gmc] == 1)
		{
			settings[gmc] = 0;
			SendChannelMessage(channel, ":x: | GM counting system has been disabled.");
			return 1;
		}
		if(settings[gmc] == 0)
		{
			settings[gmc] = 1;
			SendChannelMessage(channel, ":white_check_mark: | GM counting system has been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "mod"))
	{
		modcheck;

		if(settings[mod] == 1)
		{
			settings[mod] = 0;
			SendChannelMessage(channel, ":x: | Moderation commands have been disabled.");
			return 1;
		}
		if(settings[mod] == 0)
		{
			settings[mod] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Moderation commands have been enabled.");
			return 1;
		}
	}
	if(!strcmp(option, "ac"))
	{
		modcheck;

		if(settings[ac] == 1)
		{
			settings[ac] = 0;
			SendChannelMessage(channel, ":x: | Anti-raid has been disabled.");
			return 1;
		}
		if(settings[ac] == 0)
		{
			settings[ac] = 1;
			SendChannelMessage(channel, ":white_check_mark: | Anti-raid has been enabled.");
			return 1;
		}
	}
	else
	{
		SendChannelMessage(channel, ":x: **UNKNOWN OPTION** | Invalid option provided, use `-settings` to view a list of available options.");
	}
	return 1;
}

dc command:warn(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE + 10], reason[100];

	if(sscanf(params, "ss", user, reason))
	{
		SendChannelMessage(channel, ":x: | Usage: `-warn [user ID or user mention] [reason]`");
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
		SendChannelMessage(channel, ":x: | This user can't be warned as the user is a bot owner!");
		return 1;
	}

	if(!strcmp(user, "888667418904363078"))
	{
		SendChannelMessage(channel, ":x: | This user can't be warned as the user is a website maintainer!");
		return 1;
	}

	new filename[100];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	SaveLogIntoFile(filename, reason);

	new msg[512];
	format(msg, sizeof msg, ":white_check_mark: | User <@%s> was warned successfully.\n**REASON** | `%s`", user, reason);
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

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[100];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-warns [user ID or user mention]`");
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

	if(strlen(parameters) == 0) return SendChannelMessage(channel, ":x: | Usage: `-warns [user ID or user mention]`");

	format(user, sizeof user, "%s", parameters);*/

	if(!strcmp(user, "617419819108663296"))
	{
		SendChannelMessage(channel, ":x: | Operation failed!");
		return 1;
	}

	new filename[100], content[1024];
	format(filename, sizeof filename, "warns/wrn_%s.ini", user);

	if(!fexist(filename))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | This user has no warnings.");
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

	/*SendChannelMessage(channel, "**__Bot settings__**\n\n\
		**`-logs`**: Enable or disable the log system.\n\
		**`-gmc`**: Activate or deactivate GM counting.\n\
		**`-eco`**: Toggle economy commands on or off.");*/

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__MODERATION COMMANDS__**", ":star: Available moderation commands:\n\n\
		**`-blacklist`**: Blacklist a member from using the bot commands.\n\
		**`-gmtemp`**: View the GM template to use in `#gm-output`!\n\
		**`-addmod`**: Add an user to moderation team.\n\
		**`-delmod`**: Remove an user from moderation team.\n\
		**`-warn`**: Permanently warns a member.\n\
		**`-warns`**: View all user's warnings.\n\
		**`-annc`**: Post an announcement.\n\
		**`-mute`**: Mute a member.\n\
		**`-unmute`**: Unmute a member.\n\
		**`-kick`**: Kick a member.\n\
		**`-ban`**: Ban a member.\n\
		**`-unban`**: Unban a member.\n\
		**`-setgmc`**: Set GM count for a member.\n\
		**`-getgmc`**: Get GM count of a member.\n\
		**`-poll`**: Create a poll.\n\
		**`-profile`**: View the overall Game Master statistics.\n\
		**`-setgmcc`**: Customized `-setgmc` built for each department.\n\
		**`-setgmclvl`**: Another custom `-setgmc` to set leveled GM count.\n\
		**`-top`**: View a leaderboard.\n\
		**`-saveset`**: Save the current settings (emergency cases).\n\
		**`-sprofile`**: View the support staff profile.", "","", col_embed, "Thanks for using our services!", 
		"","",""), ":star: **INFO** | Only bot mods can use these commands.");
	return 1;
}

dc command:saveset(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	SaveSettings();
	SendChannelMessage(channel, ":white_check_mark: **SETTINGS SAVED** | Current bot settings saved successfully.");
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
		SendChannelMessage(channel, ":x: | Usage: `-addstaff [user ID or user mention]`");
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
		SendChannelMessage(channel, "> :x: **ERROR** | This user is already in a staff configuration file.");
		return 1;
	}

	SaveStaffString(user);
	SendChannelMessage(channel, ":white_check_mark: **MEMBER ADDED** | <@%s> is now added to the staff team configuration file.", user);
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
		SendChannelMessage(channel, ":x: | Usage: `-remstaff [user ID or user mention]`");
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
		SendChannelMessage(channel, "> :x: **ERROR** | This user is not found in the staff configuration file.");
		return 1;
	}

	DeleteStaffMember(user);
	SendChannelMessage(channel, ":white_check_mark: **MEMBER REMOVED** | <@%s> is now removed from the staff team configuration file.", user);
	return 1;
}*/

dc command:poll(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new text[512];

	if(sscanf(params, "s[512]", text))
	{
		SendChannelMessage(channel, ":x: | Usage: `-poll [poll name]*[poll text]`\n\
			:star: **TIP** | Command usage example: `-poll Void an action*I vote to void this and this, bla bla...`");
		return 1;
	}

	new strip[2][512];

	split(text, strip, '*');

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	format(globalformat,sizeof globalformat, "**__%s__**\n:arrow_forward: *%s*\n\n:dizzy: | \
		Poll was posted by: <@%s>\nReact with :ballot_box_with_check: or :x: below.", strip[0], strip[1], id);
	
	new DCC_Embed:msg2 = DCC_CreateEmbed(
		":newspaper: **__POLL__**", globalformat, "","", col_embed, "Thanks for using our services!", 
		"","","");

	DCC_SendChannelEmbedMessage(channel, msg2, ":star: **INFO** | A new poll has been posted!");

	new DCC_Message:msg3 = DCC_GetCreatedMessage();

	AddReaction(msg3, DCC_CreateEmoji("☑️"));

	AddReaction(msg3, DCC_CreateEmoji("❌"));

	return 1;
}

dc command:setgmc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE+10], gmcount;

	if(sscanf(params, "si", user, gmcount))
	{
		SendChannelMessage(channel, ":x: | Usage: `-setgmc [user ID or user mention] [GM count]`");
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

	SendChannelMessage(channel, ":white_check_mark: **GM COUNT SET** | <@%s>'s GM count was modified successfully. New GM count: `%i`", user, gmcount);

	return 1;
}

dc command:setgmcc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE+10], label[15], gmcount;

	if(sscanf(params, "s[31]s[15]i", user, label, gmcount))
	{
		SendChannelMessage(channel, ":x: | Usage: `-setgmcc [user ID or user mention] [department label(s)] [GM count]`");
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
		SendChannelMessage(channel, ":white_check_mark: **POLITICS GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SavePolGMCount(user,gmcount);
		return 1;
	}

	if(dept == 3) // Economics solo
	{
		SendChannelMessage(channel, ":white_check_mark: **ECONOMICS GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 8) // Military solo
	{
		SendChannelMessage(channel, ":white_check_mark: **MILITARY GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveMilGMCount(user,gmcount);
		return 1;
	}

	// Mixed labels:
	
	if(dept == 4) // pol eco
	{
		SendChannelMessage(channel, ":white_check_mark: **POLITICS & ECONOMICS GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SavePolEcoGMCount(user,gmcount);
		return 1;
	}

	if(dept == 11) // eco mil
	{
		SendChannelMessage(channel, ":white_check_mark: **ECONOMICS & MILITARY GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveEcoMilGMCount(user,gmcount);
		return 1;
	}

	if(dept == 9) // mil pol
	{
		SendChannelMessage(channel, ":white_check_mark: **MILITARY & POLITICS GM COUNT** | Successfully modified the <@%s>'s GM count - check it using `-profile`.", user);
		SaveMilPolGMCount(user,gmcount);
		return 1;
	}

	if(dept != 1 && dept != 3 && dept != 8 && dept != 4 && dept != 11 && dept != 9)
	{
		SendChannelMessage(channel, ":x: **GM COUNT MODIFICATION** | Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`\n\n:star: | Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}

	return 1;
}

dc command:setgmclvl(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE+10], lvl, gmcount;

	if(sscanf(params, "s[31]ii", user, lvl, gmcount))
	{
		SendChannelMessage(channel, ":x: | Usage: `-setgmclvl [user ID or user mention] [level ID] [GM count]`\n\
			:star: **LEVEL IDs** | These are the current GM levels: easy - `1`, subnormal - `2`, normal - `3`, medium - `4`, hard - `5`");
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
		SendChannelMessage(channel, ":white_check_mark: **MODIFICATION SUCCESS** | GM count modification on level **Easy** for <@%s> was successful. Check it using `-profile`.", user);
		SaveEasyGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 2)
	{
		SendChannelMessage(channel, ":white_check_mark: **MODIFICATION SUCCESS** | GM count modification on level **Subnormal** for <@%s> was successful. Check it using `-profile`.", user);
		SaveSubnormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 3)
	{
		SendChannelMessage(channel, ":white_check_mark: **MODIFICATION SUCCESS** | GM count modification on level **Normal** for <@%s> was successful. Check it using `-profile`.", user);
		SaveNormalGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 4)
	{
		SendChannelMessage(channel, ":white_check_mark: **MODIFICATION SUCCESS** | GM count modification on level **Medium** for <@%s> was successful. Check it using `-profile`.", user);
		SaveMediumGMCount(user, gmcount);
		return 1;
	}
	if(lvl == 5)
	{
		SendChannelMessage(channel, ":white_check_mark: **MODIFICATION SUCCESS** | GM count modification on level **Hard** for <@%s> was successful. Check it using `-profile`.", user);
		SaveHardGMCount(user, gmcount);
		return 1;
	}
	SendChannelMessage(channel, "> :x: **ERROR** | Invalid level ID provided.");
	return 1;
}

dc command:getgmc(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-getgmc [user ID or user mention]`");
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

	SendChannelMessage(channel, ":white_check_mark: **MEMBER'S GM COUNT** | <@%s> did `%i` GMs since the last reset.", user, GetGMCount(user));

	return 1;
}

dc command:ban(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-ban [user ID or user mention]`");
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

	usercheck(user);

	if(!strcmp(user, "617419819108663296"))
	{
		SendChannelMessage(channel, ":x: | This user can't be removed as the user is a bot owner!");
		return 1;
	}


	DCC_CreateGuildMemberBan(neod, DCC_FindUserById(user), 
		""SERVER_NAME" bot | Banned with a ban command.");

	SendChannelMessage(channel, ":white_check_mark: **BANNED** | <@%s> was banned successfully.", user);

	SendChannelMessage(bankicklog, "<@%s> was **banned** by <@%s>.\n\n:star: **TIP** | If the ban didn't work, simply try again! Due to some Discord's limitations, you are unable to ban two users in a short period of time.", user, id);

	return 1;
}

dc command:unban(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-unban [user ID or user mention]`");
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

	DCC_RemoveGuildMemberBan(neod, DCC_FindUserById(user));

	SendChannelMessage(channel, ":white_check_mark: **UNBANNED** | <@%s> was unbanned successfully.", user);

	return 1;
}

dc command:kick(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-kick [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This user can't be removed as the user is a bot owner!");
		return 1;
	}


	SendChannelMessage(channel,":white_check_mark: **KICKED** | <@%s> was kicked successfully.", user);

	DCC_RemoveGuildMember(neod, DCC_FindUserById(user));

	SendChannelMessage(bankicklog, "<@%s> was **kicked** by <@%s>.", user, id);
	return 1;
}

dc command:mute(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-mute [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This user can't be removed as the user is a bot owner!");
		return 1;
	}


	if(muted == DCC_INVALID_ROLE)
	{
		SendChannelMessage(channel,":x: **ROLE ERROR** | There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_AddGuildMemberRole(neod, DCC_FindUserById(user), muted);

	SendChannelMessage(channel, ":white_check_mark: **MUTED** | <@%s> was muted successfully.", user);

	return 1;
}

dc command:unmute(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);
	servercheck;
	setcheck%0(mod);

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-unmute [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This member wasn't muted!");
		return 1;
	}

	if(muted == DCC_INVALID_ROLE)
	{
		SendChannelMessage(channel,":x: **ROLE ERROR** | There is no such role named `Muted`, make one first.");
		return 1;
	}

	DCC_RemoveGuildMemberRole(neod, DCC_FindUserById(user), muted);

	SendChannelMessage(channel, ":white_check_mark: **UNMUTED** | <@%s> was unmuted successfully.", user);

	return 1;
}

dc command:gmtemp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;
	
	SendChannelMessage(channel, "**__GM Template__**\n\n\
		**[`department label [pol/eco/mil]`]**\n\
		**Message link:**\n\
		**Provided WIWTK:**\n\
		**GM Content:**\n\
		**Tags:**");

	SendChannelMessage(channel, ":information_source: | Using a valid template is really important, as if you don't, your GM will not be count in activity logs.\n\
		:star: | Use **`-gmexample`** to view the example of template usage.");

	return 1;
}

dc command:gmexample(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, ":white_check_mark: **__GM Example__**\n\
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
		**`-logs`**: Enable or disable the log system.\n\
		**`-gmc`**: Activate or deactivate GM counting.\n\
		**`-eco`**: Toggle economy commands on or off.");*/

	new DCC_Embed:msg2 = DCC_CreateEmbed(
		"**__INFORMATION ABOUT GM LEVELS__**", "**__GM Levels__**\n\n\
		1. `Easy` - GM for 1 post\n\
		2. `Subnormal` - GM for 2 posts\n\
		3. `Normal` - GM for 3 posts\n\
		4. `Medium` - GM for 4 posts\n\
		5. `Hard` - GM for 5 or more posts\n\n\
		:star: **FACT** | GM leveling system has been recently updated with a new algorithm, \
		which scans the GM message and then estimates the level, regardless of the number of posts.", "","", col_embed, "Thanks for using our services!", 
		"","","");

	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, msg2, ":star: **INFO** | For more info, ask a bot mod.");
	return 1;
}

dc command:bal(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);


	SendChannelMessage(channel, "**__<@%s>'s Current balance__**\n\n:arrow_forward: | Your current balance is `%i`:coin:.\n> :credit_card: | You have `%i`:coin: on your bank.", id, GetBalance(id), GetDepBalance(id));

	return 1;
}

dc command:work(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(GetBalance(id) >= 25000)
	{
		SendChannelMessage(channel, "> :x: **ERROR** | Your pocket is full of coins - there is no space left for more!\n\
			:star: **TIP** | Use `-dep` to deposit your coins and free up space.");
		return 1;
	}

	new wage = random(10000);

	SaveBalance(id, GetBalance(id) + wage);

	SendChannelMessage(channel, "**__<@%s>'s Work shift results__**\n\n:white_check_mark: You successfully finished your shift and your boss gave you `%i` "BOT_NAME" coins! :coin:", id, wage);

	return 1;
}

dc command:shop(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	SendChannelMessage(channel, "The "BOT_NAME" coin shop feature is soon to be released!");

	return 1;
}

dc command:dep(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new money;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(sscanf(params, "i", money))
	{
		SendChannelMessage(channel, ":x: | Usage: `-dep [amount of coins to deposit]`\n\
			> :star: **TIP** | To deposit all of your coins, use `-depall`.");
		return 1;
	}

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You don't have a bank account.");
		return 1;
	}

	if(money > GetBalance(id))
	{
		SendChannelMessage(channel, ":x: **WORK MORE** | You don't have that much coins!");
		return 1;
	}

	SaveBalance(id, GetBalance(id) - money);

	SaveDepBalance(id, GetDepBalance(id) + money);

	SendChannelMessage(channel, ":white_check_mark: **DEPOSITED** | <@%s>, you successfully deposited `%i` "BOT_NAME" coins! :coin:", id, money);

	return 1;
}

dc command:depall(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	setcheck%0(eco);

	new money;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You don't have a bank account.");
		return 1;
	}

	SaveDepBalance(id, GetDepBalance(id) + GetBalance(id));

	SaveBalance(id, 0);

	SendChannelMessage(channel, ":white_check_mark: **DEPOSITED** | <@%s>, you successfully deposited all of your coins to your bank!", id, money);

	return 1;
}

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
		SendChannelMessage(channel, ":x: | Usage: `-with [amount of coins to withdraw]`");
		return 1;
	}

	if(!HasBankAccount(id))
	{
		SendChannelMessage(channel, "> :x: **ERROR** | You don't have a bank account.");
		return 1;
	}

	if(money > GetDepBalance(id))
	{
		SendChannelMessage(channel, ":x: **NOT ENOUGH MONEY** | You don't have that much coins in your bank!");
		return 1;
	}

	SaveBalance(id, GetBalance(id) + money);

	SaveDepBalance(id, GetDepBalance(id) - money);

	SendChannelMessage(channel, ":white_check_mark: **WITHDREW** | <@%s>, you successfully withdrew `%i`:coin: from bank!", id, money);

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
		SendChannelMessage(channel, ":x: | Usage: `-rob [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: **WHAT?** | You cannot rob yourself!");
		return 1;
	}

	if(GetBalance(user) == 0)
	{
		SendChannelMessage(channel, ":x: **POCKETS ARE EMPTY** | This player has got no coins for you!");
		return 1;
	}

	if(GetBalance(user) < 0)
	{
		SendChannelMessage(channel, ":x: **FAILED** | This guy is in crippling debts - you \
			were fined with `1000`:coins: because you tried to rob him.");
		SaveBalance(id, GetBalance(id) - 1000);
		return 1;
	}

	SaveBalance(id, GetBalance(id) + GetBalance(user));

	SendChannelMessage(channel, ":white_check_mark: **ROB WAS SUCCESSFUL** | Congratulations <@%s>, you successfully robbed <@%s> and took away all of his money (`%i`:money_with_wings:).", id, user, GetBalance(user));

	SaveBalance(user, 0);

	return 1;
}

dc command:sprofile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-sprofile [user ID or user mention]`");
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

	DCC_SendChannelEmbedMessage(channel, msg2, ":star: **INFO** | Contact a bot mod or use `-report` for mistakes or errors.");
	return 1;
}

dc command:profile(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	//modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s[31]", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-profile [user ID or user mention]`");
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

	DCC_SendChannelEmbedMessage(channel, msg2, ":star: **INFO** | Contact a bot mod or use `-report` for mistakes or errors.");
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
		SendChannelMessage(channel, ":x: | Usage: `-count [number]`");
		return 1;
	}

	DCC_GetUserId(author, id);

	if(channel == countchannel)
	{
		if(count != pod_count+1)
		{
			SendChannelMessage(channel, "**__COUNT RUINED!__**\n:x: | __Unfortunately, <@%s> ruined the count at `%i`!__\n\n:star: | We'll go again! The next number is `1`.", id, pod_count+1);
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
	SendChannelMessage(channel, "> :x: **ERROR** | You need to be in a counting channel!");
	return 1;
}*/

dc command:top(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

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
	    	:arrow_forward: If you want to view a leaderboard for each department, provide a department label after the command trigger:\n`-top [department]`", 
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
		SendChannelMessage(channel, ":x: **GM COUNT LEADERBOARD** | Sorry, invalid department label(s) provided. You can use: `[pol]`, `[eco]`, `[mil]`, `[pol][eco]`, `[eco][mil]`, `[mil][pol]`, `[war]`\n\n:star: | Make sure you don't have spaces between `]`s and `[`s!");
		return 1;
	}
    return 1;
}

dc command:blacklist(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new user[DCC_ID_SIZE+10];

	if(sscanf(params, "s", user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-blacklist [user ID or user mention]`");
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
		SendChannelMessage(channel, ":x: | This user can't be blacklisted as the user is a bot owner!");
		return 1;
	}


	if(IsBlacklisted(user))
	{
		Unblacklist(user);
		SendChannelMessage(channel, ":white_check_mark: **UNBLACKLISTED** | <@%s> was unblacklisted successfully.", user);
		return 1;
	}

	if(!IsBlacklisted(user))
	{
		Blacklist(user);
		SendChannelMessage(channel, ":white_check_mark: **BLACKLISTED** | <@%s> was blacklisted successfully.", user);
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
		"rp/country_%s.ini", country);
	return fexist(file_name) ? true : false;
}

static RegisterCountry(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"rp/country_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "value.1;");
	fclose(file2);
	return 1;
}

static GetPlayer(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"rp/player_%s.ini", country);
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
	format(file_name, sizeof file_name,"rp/player_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, id);
	fclose(file2);
	return 1;
}

static GetStateHead(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"rp/statehead_%s.ini", country);
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
		"rp/govhead_%s.ini", country);
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

stock SetStateHead(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"rp/statehead_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock SetGovHead(const country[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"rp/govhead_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

dc command:rphelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**RolePlay System commands**\n\n\
		**`-rpstats`**: View your country statistics!\n\
		**`-regrp`**: Register a country into the database.\n\
		**`-setplayer`**: Set a player for a certain nation.\n\
		**`-setrpstat`**: Update certain country statistics.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
	return 1;
}

dc command:rpstats(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30];

	if(sscanf(params, "s[30]", country))
	{
		SendChannelMessage(channel, ":x: | Usage: `-rpstats [country name]`");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ":x: **UNKNOWN COUNTRY** | This country hasn't been registered in the database.");
		return 1;
	}

	new msg[1024];
	
	format(msg, sizeof msg, ":speaking_head: **%s** Statistics\n\n\
		:star: Main country player: *<@%s>*\n\n\
		:classical_building: **Government**\n\n\
		Head of State: *%s*\n\
		Head of Government: *%s*", country,
		GetPlayer(country),
		GetStateHead(country),
		GetGovHead(country));


	//SendChannelMessage(channel, msg);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Game Master Profile__**", msg, 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",""), ":star: **INFO** | Contact a bot mod or use `-report` for mistakes or errors.");
	
	return 1;
}

dc command:setplayer(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	//modcheck;

	new user[DCC_ID_SIZE+10], id[DCC_ID_SIZE], country[30];

	DCC_GetUserId(author, id);

	if(sscanf(params, "s[30]s[31]", country, user))
	{
		SendChannelMessage(channel, ":x: | Usage: `-setplayer [country] [user ID or user mention]`");
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

	servercheck;

	modcheck;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30];

	if(sscanf(params, "s[30]", country))
	{
		SendChannelMessage(channel, ":x: | Usage: `-regrp [country name]`");
		return 1;
	}

	if(IsValidCountry(country))
	{
		SendChannelMessage(channel, ":x: **ALREADY REGISTERED** | This country has been registered in the database before.");
		return 1;
	}

	RegisterCountry(country);

	SendChannelMessage(channel, "> :white_check_mark: **SUCCESS** | Country `%s` successfully registered.", country);
	return 1;
}

dc command:setrpstat(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	modcheck;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new country[30], option[30], value[100];

	if(sscanf(params, "s[30]s[30]s[100]", country, option, value))
	{
		DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__RP Stats Setup__**", ":star: These are the options used to manipulate with RP country statistics.\n\
		Usage: `-setrpstat [country] [option] [value]`\n\n\
		**__Options__**\n\n\
		**`statehead`**: Set the name of the head of state of a country.\n\
		**`govhead`**: Set the name of the head of the government of a country.", 
		"","", col_embed, "Thanks for using our services!", 
		"","",""), ":star: **INFO** | Only bot mods can use these commands.");
		return 1;
	}

	if(!IsValidCountry(country))
	{
		SendChannelMessage(channel, ":x: **UNKNOWN COUNTRY** | This country hasn't been registered in the database.");
		return 1;
	}

	//options

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
	else
	{
		SendChannelMessage(channel, ":x: **UNKNOWN OPTION** | Invalid option provided, use `-setrpstats` to view a list of available options.");
	}
	return 1;
}

/*

socialmedia

*/

dc command:smhelp(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	DCC_SendChannelEmbedMessage(channel, DCC_CreateEmbed(
		"**__Help Panel__**", "**Social Media System**\n\n\
		**`-smregister`**: Register an account on social media.\n\
		**`-post`**: Post a message on social media.\n\
		**`-feed`**: The latest social media posts.", 
		"",
		"", col_embed, "Thanks for using our services!", 
		"",
		"",
		""), "");
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

dc command:smregister(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	servercheck;

	new id[DCC_ID_SIZE];

	DCC_GetUserId(author, id);

	new nickname[30];

	if(sscanf(params, "s[30]", nickname))
	{
		SendChannelMessage(channel, ":x: | Usage: `-smregister [account nickname]`");
		return 1;
	}

	SetAccount(id, nickname);

	SendChannelMessage(channel, "> :white_check_mark: **SUCCESS** | Great, <@%s> - your new social media account is __*@*%s__!", id, nickname);
	return 1;
}

dc command:post(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, ":x: **ERROR** | This system is under a beta development and isn't yet released.");

	return 1;
}

dc command:feed(cmdparams)
{
	new DCC_Channel:channel;

	DCC_GetMessageChannel(message, channel);

	SendChannelMessage(channel, ":x: **ERROR** | This system is under a beta development and isn't yet released.");

	return 1;
}