
// messages
native DCC_GetMessageId(DCC_Message:message, dest[DCC_ID_SIZE], max_size = DCC_ID_SIZE);
native DCC_GetMessageChannel(DCC_Message:message, &DCC_Channel:channel);
native DCC_GetMessageAuthor(DCC_Message:message, &DCC_User:author);
native DCC_GetMessageContent(DCC_Message:message, dest[], max_size = sizeof dest);
native DCC_IsMessageTts(DCC_Message:message, &bool:is_tts);
native DCC_IsMessageMentioningEveryone(DCC_Message:message, &bool:mentions_everyone);
native DCC_GetMessageUserMentionCount(DCC_Message:message, &mentioned_user_count);
native DCC_GetMessageUserMention(DCC_Message:message, offset, &DCC_User:mentioned_user);
native DCC_GetMessageRoleMentionCount(DCC_Message:message, &mentioned_role_count);
native DCC_GetMessageRoleMention(DCC_Message:message, offset, &DCC_Role:mentioned_role);

native DCC_DeleteMessage(DCC_Message:message);

native DCC_Message:DCC_GetCreatedMessage(); // for use in DCC_SendChannelMessage result callback

native DCC_DeleteInternalMessage(DCC_Message:message); // This deletes a stored message, this DOES NOT delete it on discord, this is for persistent messages.

native DCC_EditMessage(DCC_Message:message, const content[], DCC_Embed:embed = DCC_Embed:0);

native DCC_SetMessagePersistent(DCC_Message:message, bool:persistent);
native DCC_CacheChannelMessage(const channel_id[DCC_ID_SIZE], const message_id[DCC_ID_SIZE], const callback[] = "", const format[] = "", {Float, _}:...);

native DCC_Embed:DCC_CreateEmbed(const title[] = "", const description[] = "", const url[] = "", const timestamp[] = "", color = 0, const footer_text[] = "", const footer_icon_url[] = "", const thumbnail_url[] = "", const image_url[] = "");
native DCC_DeleteEmbed(DCC_Embed:embed);
native DCC_SendChannelEmbedMessage(DCC_Channel:channel, DCC_Embed:embed, const message[] = "", const callback[] = "", const format[] = "", {Float, _}:...);
native DCC_AddEmbedField(DCC_Embed:embed, const name[], const value[], bool:inline = false);
native DCC_SetEmbedTitle(DCC_Embed:embed, const title[]);
native DCC_SetEmbedDescription(DCC_Embed:embed, const description[]);
native DCC_SetEmbedUrl(DCC_Embed:embed, const url[]);
native DCC_SetEmbedTimestamp(DCC_Embed:embed, const timestamp[]);
native DCC_SetEmbedColor(DCC_Embed:embed, color);
native DCC_SetEmbedColour(DCC_Embed:embed, colour) = DCC_SetEmbedColor; // oi m8
native DCC_SetEmbedFooter(DCC_Embed:embed, const footer_text[], const footer_icon_url[] = "");
native DCC_SetEmbedThumbnail(DCC_Embed:embed, const thumbnail_url[]);
native DCC_SetEmbedImage(DCC_Embed:embed, const image_url[]);

forward DCC_OnMessageCreate(DCC_Message:message);
forward DCC_OnMessageDelete(DCC_Message:message);
forward DCC_OnMessageReaction(DCC_Message:message, DCC_User:reaction_user, DCC_Emoji:emoji, DCC_MessageReactionType:reaction_type);