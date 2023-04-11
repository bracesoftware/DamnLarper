// Module written by DEntisT, © & ® BRACE™.

//GetGuildCountChannel(guild),GetGuildCountChannel(guild),GetGuildAirportChannel(guild),GetGuildVerification(guild) ? "true" : "false",GetGuildVerificationChannel(guild),GetGuildLevelChannel(guild),GetGuildAnnouncementChannel(guild),GetGuildSecurity(guild) ? "true" : "false"

// log channel

stock GetGuildLogChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/lgc_%s.ini", id);
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

stock SetGuildLogChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/lgc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}


//count channel

stock GetGuildCountChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/cnc_%s.ini", id);
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

stock SetGuildCountChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/cnc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

//airport channel


stock GetGuildAirportChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/arc_%s.ini", id);
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

stock SetGuildAirportChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/arc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

//verification status


stock GetGuildVerification(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/verf_%s.ini", id);
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

stock SetGuildVerification(DCC_Guild:guild, value)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150], string[10];

	format(file_name, sizeof file_name,"serverdata/verf_%s.ini",id);
	format(string, sizeof(string), "%i", value);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}


// verification channel


stock GetGuildVerificationChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/vfc_%s.ini", id);
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

stock SetGuildVerificationChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/vfc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}



//level channel


stock GetGuildLevelChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/lvc_%s.ini", id);
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

stock SetGuildLevelChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/lvc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}


// announcement channel



stock GetGuildAnnouncementChannel(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/anc_%s.ini", id);
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

stock SetGuildAnnouncementChannel(DCC_Guild:guild, const value[])
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,"serverdata/anc_%s.ini",id);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}


// security status 


stock GetGuildSecurity(DCC_Guild:guild)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150];
	format(file_name, sizeof file_name,
		"serverdata/secsys_%s.ini", id);
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

stock SetGuildSecurity(DCC_Guild:guild, value)
{
	new id[DCC_ID_SIZE];
	DCC_GetGuildId(guild, id);
	new file_name[150], string[10];

	format(file_name, sizeof file_name,"serverdata/secsys_%s.ini",id);
	format(string, sizeof(string), "%i", value);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}