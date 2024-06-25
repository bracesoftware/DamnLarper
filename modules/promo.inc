// Module written by DEntisT, © & ® BRACE™.

stock SetPromoData(const id[], const promocode[], value)
{
	new string[10], file_name[150];
	if(!strcmp(promocode, "braceweb"))
	{
		format(file_name, sizeof file_name,"promo/braceweb_%s.ini",id);
		format(string, sizeof(string), "%i", value);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	return 1;
}

stock GetPromoData(const id[], const promocode[])
{
	new value,file_name[150],strFromFile2[128];
	if(!strcmp(promocode, "braceweb"))
	{
		format(file_name, sizeof file_name,
			"promo/braceweb_%s.ini", id);
		if(!fexist(file_name)) return 0;
		new File: file = fopen(file_name, io_read);
		if (file)
		{
			fread(file, strFromFile2);
			
			value = strval(strFromFile2);

			fclose(file);

			return value;
		}
	}
	return 0;
}