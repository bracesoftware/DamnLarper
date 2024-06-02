// Module written by DEntisT, © & ® BRACE™.



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


//Bank account - currency

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
	if(!strcmp(data, "Level"))
	{
		format(file_name, sizeof file_name,
			"data/lvl_%s.ini", id);
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
	if(!strcmp(data, "Copper"))
	{
		format(file_name, sizeof file_name,
			"data/copper_%s.ini", id);
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
	if(!strcmp(data, "Worm"))
	{
		format(file_name, sizeof file_name,
			"data/worm_%s.ini", id);
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
	if(!strcmp(data, "Level"))
	{
		format(file_name, sizeof file_name,"data/lvl_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
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
	if(!strcmp(data, "Copper"))
	{
		format(file_name, sizeof file_name,"data/copper_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}
	if(!strcmp(data, "Worm"))
	{
		format(file_name, sizeof file_name,"data/worm_%s.ini",id);
		format(string, sizeof(string), "%i", count);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, string);
		fclose(file2);
	}

	return 1;
}


stock GetInvData(const user[], const data[])
{
	new file_name[150];
	new strFromFile2[128];
	if(!strcmp(data, "Phone"))
	{
		format(file_name, sizeof file_name,
			"inv/phone_%s.ini", user);
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
	if(!strcmp(data, "Gamepad"))
	{
		format(file_name, sizeof file_name,
			"inv/gamepad_%s.ini", user);
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
	if(!strcmp(data, "Wallet"))
	{
		format(file_name, sizeof file_name,
			"inv/wallet_%s.ini", user);
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
	if(!strcmp(data, "Pickaxe"))
	{
		format(file_name, sizeof file_name,
			"inv/pickaxe_%s.ini", user);
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
	if(!strcmp(data, "Furnace"))
	{
		format(file_name, sizeof file_name,
			"inv/furnace_%s.ini", user);
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
	if(!strcmp(data, "Slingshot"))
	{
		format(file_name, sizeof file_name,
			"inv/slingshot_%s.ini", user);
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
	if(!strcmp(data, "Mask"))
	{
		format(file_name, sizeof file_name,
			"inv/mask_%s.ini", user);
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
	if(!strcmp(data, "FishingRod"))
	{
		format(file_name, sizeof file_name,
			"inv/frod_%s.ini", user);
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
	if(!strcmp(data, "Desk"))
	{
		format(file_name, sizeof file_name,
			"inv/desk_%s.ini", user);
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
	if(!strcmp(data, "Axe"))
	{
		format(file_name, sizeof file_name,
			"inv/axe_%s.ini", user);
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
	if(!strcmp(data, "Laptop"))
	{
		format(file_name, sizeof file_name,
			"inv/laptop_%s.ini", user);
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
	if(!strcmp(data, "Safe"))
	{
		format(file_name, sizeof file_name,
			"inv/safe_%s.ini", user);
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
	if(!strcmp(data, "ProtectiveShield"))
	{
		format(file_name, sizeof file_name,
			"inv/protshield_%s.ini", user);
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
	if(!strcmp(data, "Shovel"))
	{
		format(file_name, sizeof file_name,
			"inv/shovel_%s.ini", user);
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
	if(!strcmp(data, "Backpack"))
	{
		format(file_name, sizeof file_name,
			"inv/backpack_%s.ini", user);
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

stock SetInvData(const user[], const data[])
{
	new file_name[150];
	if(!strcmp(data, "Phone"))
	{
		format(file_name, sizeof file_name,"inv/phone_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Gamepad"))
	{
		format(file_name, sizeof file_name,"inv/gamepad_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Wallet"))
	{
		format(file_name, sizeof file_name,"inv/wallet_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Pickaxe"))
	{
		format(file_name, sizeof file_name,"inv/pickaxe_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Furnace"))
	{
		format(file_name, sizeof file_name,"inv/furnace_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Slingshot"))
	{
		format(file_name, sizeof file_name,"inv/slingshot_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Mask"))
	{
		format(file_name, sizeof file_name,"inv/mask_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "FishingRod"))
	{
		format(file_name, sizeof file_name,"inv/frod_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Desk"))
	{
		format(file_name, sizeof file_name,"inv/desk_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Axe"))
	{
		format(file_name, sizeof file_name,"inv/axe_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Laptop"))
	{
		format(file_name, sizeof file_name,"inv/laptop_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Safe"))
	{
		format(file_name, sizeof file_name,"inv/safe_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "ProtectiveShield"))
	{
		format(file_name, sizeof file_name,"inv/protshield_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Shovel"))
	{
		format(file_name, sizeof file_name,"inv/shovel_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	if(!strcmp(data, "Backpack"))
	{
		format(file_name, sizeof file_name,"inv/backpack_%s.ini",user);
		new File: file2 = fopen(file_name, io_write);
		fwrite(file2, "1");
		fclose(file2);
	}
	return 1;
}



// IMPL


stock GenerateInvString(const id[], type)
{
	new string[256];
	if(type == IST_GOLD)
	{
		format(string, sizeof string, ""d_reply" "d_gold" • **Gold**: %ix\n", GetData(id, "Gold"));
	}
	if(type == IST_RUBIES)
	{
		format(string, sizeof string, ""d_reply" "d_ruby" • **Rubies**: %ix\n", GetData(id, "Rubies"));
	}
	if(type == IST_RAWMEAT)
	{
		format(string, sizeof string, ""d_reply" "d_rawmeat" • **Raw Meat**: %ix\n", GetData(id, "RawMeat"));
	}
	if(type == IST_COOKEDMEAT)
	{
		format(string, sizeof string, ""d_reply" "d_cookedmeat" • **Cooked Meat**: %ix\n", GetData(id, "CookedMeat"));
	}
	if(type == IST_FRUITS)
	{
		format(string, sizeof string, ""d_reply" "d_fruits" • **Fruits**: %ix\n", GetData(id, "Fruits"));
	}
	if(type == IST_MEDICINE)
	{
		format(string, sizeof string, ""d_reply" "d_medicine" • **Medicine**: %ix\n", GetData(id, "Medicine"));
	}
	if(type == IST_RAWFISH)
	{
		format(string, sizeof string, ""d_reply" "d_rawfish" • **Raw Fish**: %ix\n", GetData(id, "RawFish"));
	}
	if(type == IST_COOKEDFISH)
	{
		format(string, sizeof string, ""d_reply" "d_cookedfish" • **Cooked Fish**: %ix\n", GetData(id, "CookedFish"));
	}
	if(type == IST_PLANKS)
	{
		format(string, sizeof string, ""d_reply" "d_planks" • **Planks**: %ix\n", GetData(id, "Planks"));
	}
	if(type == IST_PAPER)
	{
		format(string, sizeof string, ""d_reply" "d_paper" • **Paper**: %ix\n", GetData(id, "Paper"));
	}
	if(type == IST_BANKNOTE)
	{
		format(string, sizeof string, ""d_reply" "d_banknote" • **Banknotes**: %ix\n", GetData(id, "Banknotes"));
	}
	if(type == IST_COPPER)
	{
		format(string, sizeof string, ""d_reply" "d_copper" • **Copper**: %ix\n", GetData(id, "Copper"));
	}
	if(type == IST_WORM)
	{
		format(string, sizeof string, ""d_reply" "d_worm" • **Worm**: %ix\n", GetData(id, "Worm"));
	}

	return string;
}




stock GenerateChestString(const id[], type)
{
	new string[256];
	if(type == CHEST_COMMON)
	{
		format(string, sizeof string, ""d_reply" "d_commonchest" • **Common Chest**: %ix\nChest ID: `1`\n\n", GetCommonChest(id));
	}
	if(type == CHEST_RARE)
	{
		format(string, sizeof string, ""d_reply" "d_rarechest" • **Rare Chest**: %ix\nChest ID: `2`\n\n", GetRareChest(id));
	}
	return string;
}