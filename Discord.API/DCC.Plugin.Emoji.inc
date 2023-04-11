// emoji
native DCC_Emoji:DCC_CreateEmoji(const name[DCC_EMOJI_NAME_SIZE], const snowflake[DCC_ID_SIZE] = "");
native DCC_DeleteEmoji(DCC_Emoji:emoji);
native DCC_GetEmojiName(DCC_Emoji:emoji, dest[DCC_EMOJI_NAME_SIZE], maxlen = DCC_EMOJI_NAME_SIZE);