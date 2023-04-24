// natives
//  channels
native DCC_Channel:DCC_FindChannelByName(const channel_name[]);
native DCC_Channel:DCC_FindChannelById(const channel_id[]);

native DCC_GetChannelId(DCC_Channel:channel, dest[DCC_ID_SIZE], max_size = sizeof dest);
native DCC_GetChannelType(DCC_Channel:channel, &DCC_ChannelType:type);
native DCC_GetChannelGuild(DCC_Channel:channel, &DCC_Guild:guild);
native DCC_GetChannelName(DCC_Channel:channel, dest[], max_size = sizeof dest);
native DCC_GetChannelTopic(DCC_Channel:channel, dest[], max_size = sizeof dest);
native DCC_GetChannelPosition(DCC_Channel:channel, &position);
native DCC_IsChannelNsfw(DCC_Channel:channel, &bool:is_nsfw);
native DCC_GetChannelParentCategory(DCC_Channel:channel, &DCC_Channel:category);

native DCC_SendChannelMessage(DCC_Channel:channel, const message[], const callback[] = "", const format[] = "", {Float, _}:...);
native DCC_SetChannelName(DCC_Channel:channel, const name[]);
native DCC_SetChannelTopic(DCC_Channel:channel, const topic[]);
native DCC_SetChannelPosition(DCC_Channel:channel, position);
native DCC_SetChannelNsfw(DCC_Channel:channel, bool:is_nsfw);
native DCC_SetChannelParentCategory(DCC_Channel:channel, DCC_Channel:parent_category);
native DCC_DeleteChannel(DCC_Channel:channel);


forward DCC_OnChannelCreate(DCC_Channel:channel);
forward DCC_OnChannelUpdate(DCC_Channel:channel);
forward DCC_OnChannelDelete(DCC_Channel:channel);