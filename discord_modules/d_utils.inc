// Module written by DEntisT, © & ® BRACE™.
//Achievements

stock GetAchievement(const user[], const achievement[])
{
	new file_name[150];
	new strFromFile2[128];
	if(!strcmp(achievement, "Beggar"))
	{
		format(file_name, sizeof file_name,
			"achieve/beggar_%s.ini", user);
		//format(strFromFile2, sizeof strFromFile2, "Unknown");
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);

			fclose(file);

			return strval(strFromFile2);
		}
	}
	if(!strcmp(achievement, "Consumer"))
	{
		format(file_name, sizeof file_name,
			"achieve/consumer_%s.ini", user);
		//format(strFromFile2, sizeof strFromFile2, "Unknown");
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);

			fclose(file);

			return strval(strFromFile2);
		}
	}
	if(!strcmp(achievement, "Miner"))
	{
		format(file_name, sizeof file_name,
			"achieve/miner_%s.ini", user);
		//format(strFromFile2, sizeof strFromFile2, "Unknown");
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);

			fclose(file);

			return strval(strFromFile2);
		}
	}
	return 0;
}

stock SetAchievement(const user[], const achievement[])
{
	new file_name[150];
	if(!strcmp(achievement, "Beggar"))
	{
		format(file_name, sizeof file_name,"achieve/beggar_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(achievement, "Consumer"))
	{
		format(file_name, sizeof file_name,"achieve/consumer_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(achievement, "Miner"))
	{
		format(file_name, sizeof file_name,"achieve/miner_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	return 1;
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

// Chests

stock GetCommonChest(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"inv/commonc_%s.ini", id);
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

stock SaveCommonChest(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"inv/commonc_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetRareChest(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"inv/rarec_%s.ini", id);
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

stock SaveRareChest(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"inv/rarec_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
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
//bankacc
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

//Economy 


stock GetData(const id[], const data[])
{
	new count,file_name[150],strFromFile2[128];
	if(!strcmp(data, "Balance"))
	{
		format(file_name, sizeof file_name,
			"data/eco_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "DepBalance"))
	{
		format(file_name, sizeof file_name,
			"data/ecod_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Rubies"))
	{
		format(file_name, sizeof file_name,
			"data/rubies_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Planks"))
	{
		format(file_name, sizeof file_name,
			"data/planks_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Paper"))
	{
		format(file_name, sizeof file_name,
			"data/paper_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Banknotes"))
	{
		format(file_name, sizeof file_name,
			"data/banknote_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Gold"))
	{
		format(file_name, sizeof file_name,
			"data/gold_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "RawMeat"))
	{
		format(file_name, sizeof file_name,
			"data/rawm_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "RawFish"))
	{
		format(file_name, sizeof file_name,
			"data/rawf_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "CookedMeat"))
	{
		format(file_name, sizeof file_name,
			"data/cookm_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "CookedFish"))
	{
		format(file_name, sizeof file_name,
			"data/cookf_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Fruits"))
	{
		format(file_name, sizeof file_name,
			"data/fruits_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	if(!strcmp(data, "Medicine"))
	{
		format(file_name, sizeof file_name,
			"data/meds_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			count = strval(strFromFile2);

			fclose(file);

			return count;
		}
	}
	return 0;
}

stock SetData(const id[], const data[], count)
{
	new string[10], file_name[150];
	if(!strcmp(data, "Balance"))
	{
		format(file_name, sizeof file_name,"data/eco_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "DepBalance"))
	{
		format(file_name, sizeof file_name,"data/ecod_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Rubies"))
	{
		format(file_name, sizeof file_name,"data/rubies_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Planks"))
	{
		format(file_name, sizeof file_name,"data/planks_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Paper"))
	{
		format(file_name, sizeof file_name,"data/paper_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Banknotes"))
	{
		format(file_name, sizeof file_name,"data/banknote_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Gold"))
	{
		format(file_name, sizeof file_name,"data/gold_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "RawMeat"))
	{
		format(file_name, sizeof file_name,"data/rawm_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "RawFish"))
	{
		format(file_name, sizeof file_name,"data/rawf_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "CookedMeat"))
	{
		format(file_name, sizeof file_name,"data/cookm_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "CookedFish"))
	{
		format(file_name, sizeof file_name,"data/cookf_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Fruits"))
	{
		format(file_name, sizeof file_name,"data/fruits_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Medicine"))
	{
		format(file_name, sizeof file_name,"data/meds_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	return 1;
}