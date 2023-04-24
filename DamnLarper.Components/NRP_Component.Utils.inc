// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - utils




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


// GM Counting

stock GetGMCount(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"ron/gmc_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmc_%s.ini",id);
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
		"ron/gmcpol_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcpol_%s.ini",id);
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
		"ron/gmceco_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmceco_%s.ini",id);
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
		"ron/gmcmil_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcmil_%s.ini",id);
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
		"ron/gmcpoleco_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcpoleco_%s.ini",id);
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
		"ron/gmcecomil_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcecomil_%s.ini",id);
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
		"ron/gmcmilpol_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcmilpol_%s.ini",id);
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
		"ron/gmcwar_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcwar_%s.ini",id);
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
		"ron/gmceasy_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmceasy_%s.ini",id);
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
		"ron/gmcsub_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcsub_%s.ini",id);
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
		"ron/gmcnorm_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcnorm_%s.ini",id);
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
		"ron/gmcmed_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmcmed_%s.ini",id);
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
		"ron/gmchard_%s.ini", id);
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
	format(file_name, sizeof file_name,"ron/gmchard_%s.ini",id);
	format(string, sizeof(string), "%i", count++);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
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

stock RegisterCountry(const country[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"ron/country_%s.ini",country);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "value.1;");
	fclose(file2);
	return 1;
}

stock GetPlayer(const country[])
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

stock GetFullname(const country[])
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

stock GetStateHead(const country[])
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

stock GetGovHead(const country[])
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

stock GetGovType(const country[])
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

stock GetGdp(const country[])
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

stock GetGdpPerCapita(const country[])
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

stock GetPublicDebt(const country[])
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

stock GetNationality(const country[])
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

stock GetReligion(const country[])
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

stock GetInhabitants(const country[])
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

stock GetActivePersonnel(const country[])
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

stock GetReservePersonnel(const country[])
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


forward NRP_SETDATE();
public NRP_SETDATE()
{
	dateupdated = 20;
	return 1;
}