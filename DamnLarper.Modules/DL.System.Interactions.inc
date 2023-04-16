// Script written by DEntisT, © & ® BRACE™.


// Data management

#define INTERACTION_EMOJI_YES	 	DCC_CreateEmoji("✅")
#define INTERACTION_EMOJI_NO 		DCC_CreateEmoji("❌")

// Interaction type
#define INTERACTION_TYPE_TEST 			0
#define INTERACTION_TYPE_TEST_STR 		"0"

// Funcs

forward SetInteraction(user[], type);
public SetInteraction(user[], type)
{
	__Internal_SetInteraction(
		DCC_GetCreatedMessage(),
		DCC_FindUserById(user),
		type)
	;
	return 1;
}

stock __Internal_SetInteraction(DCC_Message:message, DCC_User:user, interaction_type)
{
	new messageid[DCC_ID_SIZE], userid[DCC_ID_SIZE];
	DCC_GetMessageId(message, messageid);
	DCC_GetUserId(user,userid);
	new file_name[150];

	format(file_name, sizeof file_name,"interactions/msg_%s.ini",messageid);
	new File: file2 = fopen(file_name, io_write);
	fwrite(file2, "1");
	fclose(file2);

	format(file_name, sizeof file_name,"interactions/user_%s.ini",userid);
	file2 = fopen(file_name, io_write);
	fwrite(file2, messageid);
	fclose(file2);

	if(interaction_type == INTERACTION_TYPE_TEST)
	{
		DCC_CreateReaction(message, INTERACTION_EMOJI_YES);
		format(file_name, sizeof file_name,"interactions/inttype_%s.ini",messageid);
		file2 = fopen(file_name, io_write);
		fwrite(file2, INTERACTION_TYPE_TEST_STR);
		fclose(file2);
	}
	return 1;
}

stock GetInteractionType(DCC_Message:message)
{
	new messageid[DCC_ID_SIZE];
	DCC_GetMessageId(message, messageid);
	new file_name[150];
	format(file_name, sizeof file_name,
		"interactions/inttype_%s.ini",messageid);
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


//////////////////////////////////////////////////////////

stock bool:IsMessageAnInteraction(DCC_Message:message)
{
	new messageid[DCC_ID_SIZE];
	DCC_GetMessageId(message, messageid);
	new file_name[150];
	format(file_name, sizeof file_name,
		"interactions/msg_%s.ini", messageid);
	return bool:(fexist(file_name));	
}

stock bool:IsUserInteractionOwner(DCC_User:user, DCC_Message:message)
{
	new userid[DCC_ID_SIZE],messageid[DCC_ID_SIZE];
	DCC_GetUserId(user, userid);
	DCC_GetMessageId(message,messageid);

	new file_name[150];
	format(file_name, sizeof file_name,
		"interactions/user_%s.ini", userid);
	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Unknown");
	if(!fexist(file_name)) return false;
	new File: file = fopen(file_name, io_read);
	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);

		return (!strcmp(strFromFile2, messageid));
	}
	return false;
}


// Impl

public DCC_OnMessageReaction(
DCC_Message:message, DCC_User:reaction_user, DCC_Emoji:emoji, DCC_MessageReactionType:reaction_type)
{
	if(IsMessageAnInteraction(message)) //check if message is an interaction
	{
		if(IsUserInteractionOwner(reaction_user, message) && !IsUserABot_2(reaction_user)) //check if reaction_user is using the interaction
		{
			if(GetInteractionType(message) == INTERACTION_TYPE_TEST)
			{
				if(reaction_type == REACTION_ADD)
				{
					if(emoji == INTERACTION_EMOJI_YES)
					{
						new DCC_Channel:channel;
						DCC_GetMessageChannel(message,channel);
						@discord() SendInfo(channel, "This works!");
					}
				}
			}
		}
	}
	return 1;
}

//////////////////////////////////////

forward TurnInteractionOff(DCC_User:user);
public TurnInteractionOff(DCC_User:user)
{
	new userid[DCC_ID_SIZE];
	DCC_GetUserId(user, userid);
	
	new file_name[150];
	format(file_name, sizeof file_name,
		"interactions/user_%s.ini", userid);

	new strFromFile2[128];
	format(strFromFile2, sizeof strFromFile2, "Unknown");
	if(!fexist(file_name)) return 1;

	new File: file = fopen(file_name, io_read);

	if (file)
	{
		fread(file, strFromFile2);

		fclose(file);
	}

	format(file_name, sizeof file_name,
		"interactions/msg_%s.ini", strFromFile2);

	if(!fexist(file_name)) return 1;

	fremove(file_name);
	return 1;
}