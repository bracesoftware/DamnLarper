// Module written by DEntisT, © & ® BRACE™.
/*
#if SLASH_COMMANDS == 1
stock CreateCommands(DCC_Guild:guild)
{
	new DCC_Command:cmd = DCC_CreateCommand("help", "Help command", "SlashCommandTest", true, guild);
}
#endif
*/
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

stock bool:IsUserGuildOwner(DCC_Guild:guild, const user[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildOwnerId(guild, id);
	if(!strcmp(id, user)) return true;
	return false;
}

stock GetServers()
{
	new count;
	new strFromFile2[128];
	if(!fexist("bot/servers.ini")) return 0;
	new File: file = fopen("bot/servers.ini", io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		count = strval(strFromFile2);

		fclose(file);

		return count;
	}
	return 0;
}

stock SetServers(count)
{
	new string[10];
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen("bot/servers.ini", io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock bool:dpp_strcmp(const str1[], const str2[], bool:ignorecase = false) //creds slice
{
    new
        c1 = (str1[0] > 255) ? str1{0} : str1[0],
        c2 = (str2[0] > 255) ? str2{0} : str2[0]
    ;

    if (!c1 != !c2)
        return false;

    return !strcmp(str1, str2, ignorecase);
}

stock split(const strsrc[], strdest[][], delimiter)
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

// Command timers
stock GetCommandUsedMin(const user[], const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/cmin_%s_%s.ini", user, cmd);
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

stock SetCommandUsedMin(const user[], const cmd[], const value)
{
	new file_name[150], string[10];
	format(string, sizeof string, "%i", value);
	format(file_name, sizeof file_name,"data/cmin_%s_%s.ini",user,cmd);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetCommandUsedHr(const user[], const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/chr_%s_%s.ini", user, cmd);
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

stock SetCommandUsedHr(const user[], const cmd[], const value)
{
	new file_name[150], string[10];
	format(string, sizeof string, "%i", value);
	format(file_name, sizeof file_name,"data/chr_%s_%s.ini",user,cmd);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetCommandUsedDay(const user[], const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/cdy_%s_%s.ini", user, cmd);
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

stock SetCommandUsedDay(const user[], const cmd[], const value)
{
	new file_name[150], string[10];
	format(string, sizeof string, "%i", value);
	format(file_name, sizeof file_name,"data/cdy_%s_%s.ini",user,cmd);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetCommandUsed(const user[], const cmd[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/cmdu_%s_%s.ini", user, cmd);
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

stock SetCommandUsed(const user[], const cmd[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"data/cmdu_%s_%s.ini",user,cmd);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
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
// Premium
stock GetPremium(const id[])
{
	new value,file_name[150];
	format(file_name, sizeof file_name,
		"data/premium_%s.ini", id);
	new strFromFile2[128];
	if(!fexist(file_name)) return 0;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);
		
		value = strval(strFromFile2);

		fclose(file);

		return value;
	}
	return 0;
}

stock SetPremium(const id[],value)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"data/premium_%s.ini",id);
	format(string, sizeof(string), "%i", value);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}


stock GetMention(const id[])
{
	new file_name[300];
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
	new file_name[300];
	format(file_name, sizeof file_name,"data/id_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
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

stock GetAFK(const id[])
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
		@discord() SendMsg(channel, "> "d_reply" **ERROR** • This custom command doesn't exist.");
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

stock LoadChannels()
{
	/*@discord() SendMsg(bankicklog, syschannelstring);
	@discord() SendMsg(rpnotices, syschannelstring);
	@discord() SendMsg(war_gm_output, syschannelstring);
	@discord() SendMsg(submissionchannel, syschannelstring);
	@discord() SendMsg(dateupdate, syschannelstring);
	@discord() SendMsg(supportchannel, syschannelstring);
	@discord() SendMsg(lounge, syschannelstring);
	@discord() SendMsg(commandchannel, syschannelstring);
	@discord() SendMsg(gm_output, syschannelstring);
	@discord() SendMsg(gm_count, syschannelstring);
	@discord() SendMsg(logs, syschannelstring);
	@discord() SendMsg(announcements, syschannelstring);
	@discord() SendMsg(countchannel, syschannelstring);
	@discord() SendMsg(reports, syschannelstring);
	@discord() SendMsg(rpchannel, syschannelstring);
	@discord() SendMsg(rpchannel1, syschannelstring);
	@discord() SendMsg(rpchannel2, syschannelstring);
	@discord() SendMsg(rpchannel3, syschannelstring);
	@discord() SendMsg(rpchannel4, syschannelstring);
	@discord() SendMsg(rpchannel5, syschannelstring);
	@discord() SendMsg(rpchannel6, syschannelstring);
	@discord() SendMsg(rpchannel7, syschannelstring);
	@discord() SendMsg(appreview, syschannelstring);
	@discord() SendMsg(verifychannel, syschannelstring);*/
}

// Staff 

stock bool:isequal(const str1[], const str2[], bool:ignorecase = false) {
    new
        c1 = (str1[0] > 255) ? str1{0} : str1[0],
        c2 = (str2[0] > 255) ? str2{0} : str2[0]
    ;

    if (!c1 != !c2)
        return false;

    return !strcmp(str1, str2, ignorecase);
}


stock AddReaction(DCC_Message:message, DCC_Emoji:emoji)
{
	printf("DCC_CreateReaction returned %i", DCC_CreateReaction(message, emoji));
	return 1;
}
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

stock GetBumpCount(const id[])
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

forward MsgPerSecReset(id[]);
public MsgPerSecReset(id[])
{
	SaveMessageCountPerSec(id, 0);
	return 1;
}

stock GetVerifyCode(DCC_Guild:guild, const user[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"vdata/code_%s_%s.ini", user, id);
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

stock SetVerifyCode(DCC_Guild:guild, const user[], const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"vdata/code_%s_%s.ini",user, id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock IsUserMod(DCC_User:user)
{
	new filename[256];
	new id[DCC_ID_SIZE];
	DCC_GetUserId(user, id);
	format(filename, sizeof filename, "mods/mod_%s.ini", id);
	if(!fexist(filename)) return 0;
	return 1;
}


new _g_Shifthour, _g_Timeshift = 0;
stock _FixHourData(_f_Hour)
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
		"`%d/%d/%d` • `%d:%d:%d` "d_reply" %s*", 
		_day, _month, _year, 
		_sec, _minutes, _data, _Log );

	new File:_File;
	_File = fopen( _FileName, io_append );

	fwrite( _File, _Entry );

	fclose( _File );
}




stock GetUserVerification(DCC_Guild:guild, const user[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/ver_%s_%s.ini", id,user);
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

stock SetUserVerification(DCC_Guild:guild, const user[], value)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150], string[10];

	format(file_name, sizeof file_name,"serverdata/ver_%s_%s.ini",id,user);
	format(string, sizeof(string), "%i", value);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetGuildCountGame(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/cnt_%s.ini", id);
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

stock SaveGuildCountGame(DCC_Guild:guild, count)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"serverdata/cnt_%s.ini", id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}


stock DeleteAFK(const id[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"data/afk_%s.ini", id);
	return fremove(file_name);
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


stock SetAccount(const id[], const nickname[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"socialmedia/acc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, nickname);
	fclose(file2);
	return 1;
}

stock GetNickname(const id[])
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

stock GetName(const id[])
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

stock GetBio(const id[])
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

stock GetPfp(const id[])
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
