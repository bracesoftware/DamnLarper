// bot
native DCC_BotPresenceStatus:DCC_GetBotPresenceStatus();

native DCC_TriggerBotTypingIndicator(DCC_Channel:channel);
native DCC_SetBotNickname(DCC_Guild:guild, const nickname[]);
stock DCC_ClearBotNickname(DCC_Guild:guild)
{
	return DCC_SetBotNickname(guild, "");
}
native DCC_CreatePrivateChannel(DCC_User:user, const callback[], const format[] = "", {Float, _}:...);
native DCC_Channel:DCC_GetCreatedPrivateChannel();
native DCC_SetBotPresenceStatus(DCC_BotPresenceStatus:status);
native DCC_SetBotActivity(const name[]);
stock DCC_ClearBotActivity()
{
	return DCC_SetBotActivity("");
}