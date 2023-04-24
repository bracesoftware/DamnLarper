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
	if(!strcmp(achievement, "PetOwner"))
	{
		format(file_name, sizeof file_name,
			"achieve/petowner_%s.ini", user);
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
	if(!strcmp(achievement, "Digger"))
	{
		format(file_name, sizeof file_name,
			"achieve/digger_%s.ini", user);
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
	if(!strcmp(achievement, "PetOwner"))
	{
		format(file_name, sizeof file_name,"achieve/petowner_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(achievement, "Digger"))
	{
		format(file_name, sizeof file_name,"achieve/digger_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	return 1;
}
