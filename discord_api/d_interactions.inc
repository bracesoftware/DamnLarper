// interactions
native DCC_GetInteractionMentionCount(DCC_Interaction:interaction, &mentioned_user_count);
native DCC_GetInteractionMention(DCC_Interaction:interaction, offset, &DCC_User:mentioned_user);
native DCC_GetInteractionContent(DCC_Interaction:interaction, dest[], max_size = sizeof dest);
native DCC_GetInteractionChannel(DCC_Interaction:interaction, &DCC_Channel:channel);
native DCC_GetInteractionGuild(DCC_Interaction:interaction, &DCC_Guild:guild);
native DCC_SendInteractionEmbed(DCC_Interaction:interaction, DCC_Embed:embed, const message[] = "");
native DCC_SendInteractionMessage(DCC_Interaction:interaction, const message[] = "");
