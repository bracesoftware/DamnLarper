// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - utils

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
