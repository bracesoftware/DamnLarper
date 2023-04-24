//  guilds
native DCC_Guild:DCC_FindGuildByName(const guild_name[]);
native DCC_Guild:DCC_FindGuildById(const guild_id[]);

native DCC_GetGuildId(DCC_Guild:guild, dest[DCC_ID_SIZE], max_size = sizeof dest);
native DCC_GetGuildName(DCC_Guild:guild, dest[], max_size = sizeof dest);
native DCC_GetGuildOwnerId(DCC_Guild:guild, dest[DCC_ID_SIZE], max_size = sizeof dest);
native DCC_GetGuildRole(DCC_Guild:guild, offset, &DCC_Role:role);
native DCC_GetGuildRoleCount(DCC_Guild:guild, &count);
native DCC_GetGuildMember(DCC_Guild:guild, offset, &DCC_User:user);
native DCC_GetGuildMemberCount(DCC_Guild:guild, &count);
native DCC_GetGuildMemberVoiceChannel(DCC_Guild:guild, DCC_User:user, &DCC_Channel:channel);
native DCC_GetGuildMemberNickname(DCC_Guild:guild, DCC_User:user, dest[DCC_NICKNAME_SIZE], max_size = sizeof dest);
native DCC_GetGuildMemberRole(DCC_Guild:guild, DCC_User:user, offset, &DCC_Role:role);
native DCC_GetGuildMemberRoleCount(DCC_Guild:guild, DCC_User:user, &count);
native DCC_HasGuildMemberRole(DCC_Guild:guild, DCC_User:user, DCC_Role:role, &bool:has_role);
native DCC_GetGuildMemberStatus(DCC_Guild:guild, DCC_User:user, &DCC_UserPresenceStatus:status);
native DCC_GetGuildChannel(DCC_Guild:guild, offset, &DCC_Channel:channel);
native DCC_GetGuildChannelCount(DCC_Guild:guild, &count);
native DCC_GetAllGuilds(DCC_Guild:dest[], max_size = sizeof dest);

native DCC_SetGuildName(DCC_Guild:guild, const name[]);
native DCC_CreateGuildChannel(DCC_Guild:guild, const name[], DCC_ChannelType:type, const callback[] = "", const format[] = "", {Float, _}:...);
native DCC_Channel:DCC_GetCreatedGuildChannel();
native DCC_SetGuildMemberNickname(DCC_Guild:guild, DCC_User:user, const nickname[]);
native DCC_SetGuildMemberVoiceChannel(DCC_Guild:guild, DCC_User:user, DCC_Channel:channel);
native DCC_AddGuildMemberRole(DCC_Guild:guild, DCC_User:user, DCC_Role:role);
native DCC_RemoveGuildMemberRole(DCC_Guild:guild, DCC_User:user, DCC_Role:role);
native DCC_RemoveGuildMember(DCC_Guild:guild, DCC_User:user); // kicks the user from the server
native DCC_CreateGuildMemberBan(DCC_Guild:guild, DCC_User:user, const reason[] = "");
native DCC_RemoveGuildMemberBan(DCC_Guild:guild, DCC_User:user);
native DCC_SetGuildRolePosition(DCC_Guild:guild, DCC_Role:role, position);
native DCC_SetGuildRoleName(DCC_Guild:guild, DCC_Role:role, const name[]);
native DCC_SetGuildRolePermissions(DCC_Guild:guild, DCC_Role:role, perm_high, perm_low);
native DCC_SetGuildRoleColor(DCC_Guild:guild, DCC_Role:role, color);
native DCC_SetGuildRoleHoist(DCC_Guild:guild, DCC_Role:role, bool:hoist);
native DCC_SetGuildRoleMentionable(DCC_Guild:guild, DCC_Role:role, bool:mentionable);
native DCC_CreateGuildRole(DCC_Guild:guild, const name[], const callback[] = "", const format[] = "", {Float, _}:...);
native DCC_Role:DCC_GetCreatedGuildRole();
native DCC_DeleteGuildRole(DCC_Guild:guild, DCC_Role:role);
stock bool:DCC_HasGuildMemberPermission(DCC_Guild:guild, DCC_User:user, permission)
{
	new rolecount;
	DCC_GetGuildRoleCount(guild, rolecount);

	for (new ii; ii != rolecount; ii++)
	{
	    new DCC_Role:role;
	    if(!DCC_GetGuildRole(guild, ii, role))
	    {
	        continue;
	    }

	    new bool:hasrole;

	    DCC_HasGuildMemberRole(guild, user, role, hasrole);

	    if(!hasrole)
	    {
	    	continue;
	    }

	    new perm_high, perm_low;

	    DCC_GetRolePermissions(role, perm_high, perm_low);

	    new permissions = perm_high | perm_low;

	    if((permissions & permission) == permission)
	    {
	    	return true;
	    }
	}
	return false;
}


forward DCC_OnGuildCreate(DCC_Guild:guild);
forward DCC_OnGuildUpdate(DCC_Guild:guild);
forward DCC_OnGuildDelete(DCC_Guild:guild);

forward DCC_OnGuildMemberAdd(DCC_Guild:guild, DCC_User:user);
forward DCC_OnGuildMemberUpdate(DCC_Guild:guild, DCC_User:user);
forward DCC_OnGuildMemberVoiceUpdate(DCC_Guild:guild, DCC_User:user, DCC_Channel:channel);
forward DCC_OnGuildMemberRemove(DCC_Guild:guild, DCC_User:user);

forward DCC_OnGuildRoleCreate(DCC_Guild:guild, DCC_Role:role);
forward DCC_OnGuildRoleUpdate(DCC_Guild:guild, DCC_Role:role);
forward DCC_OnGuildRoleDelete(DCC_Guild:guild, DCC_Role:role);