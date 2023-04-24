// Module written by DEntisT, © & ® BRACE™.


stock GetPet(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"pets/pet_%s.ini", id);
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

stock SetPet(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"pets/pet_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}

stock GetPetName(const i[])
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"pets/name_%s.ini", i);
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

stock SetPetName(const i[], const value[])
{
	new file_name[150];
	format(file_name, sizeof file_name,"pets/name_%s.ini",i);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, value);
	fclose(file2);
	return 1;
}

stock GetPetEnergy(const id[])
{
	new count,file_name[150];
	format(file_name, sizeof file_name,
		"pets/energy_%s.ini", id);
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

stock SetPetEnergy(const id[],count)
{
	new string[10], file_name[150];
	format(file_name, sizeof file_name,"pets/energy_%s.ini",id);
	format(string, sizeof(string), "%i", count);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, string);
	fclose(file2);
	return 1;
}
