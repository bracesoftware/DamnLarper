// reaction
native DCC_CreateReaction(DCC_Message:message, DCC_Emoji:reaction_emoji);
native DCC_DeleteMessageReaction(DCC_Message:message, DCC_Emoji:reaction_emoji = DCC_Emoji:0); // if reaction_emoji is 0 (default value) this will delete ALL of the reactions on the message.
