// Module written by DEntisT, © & ® BRACE™.

#if defined DAMNLARPER_NO_SQL
#endinput
#endif

new MySQL:d_sql_database;

stock d_sql_gethost()
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"sql/host.sql");
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


stock d_sql_getpassword()
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"sql/password.sql");
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



stock d_sql_getuser()
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"sql/user.sql");
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



stock d_sql_getdb()
{
	new file_name[150];
	format(file_name, sizeof file_name,
		"sql/db.sql");
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

/////////////////////////////////////////////////////////////////////////////////////

stock SetupSQLDatabase()
{
	print("Database being set up...");
	return 1;
}

d_sqlconnect(); public d_sqlconnect()
{
	new MySQLOpt: option_id = mysql_init_options();

	mysql_set_option(option_id, AUTO_RECONNECT, true); // it automatically reconnects when loosing connection to mysql server

	d_sql_database = mysql_connect(
		d_sql_gethost(), 
		d_sql_getuser(),
		d_sql_getpassword(),
		d_sql_getdb(),
		option_id);

	if (d_sql_database == MYSQL_INVALID_HANDLE || mysql_errno(d_sql_database) != 0)
	{
		print("MySQL connection failed. Server is shutting down.");
		SendRconCommand("exit"); // close the server if there is no connection
		return 1;
	}

	print("MySQL connection is successful.");

	SetupSQLDatabase();
	return 1;
}