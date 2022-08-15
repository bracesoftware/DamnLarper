//  roles
native DCC_Role:DCC_FindRoleByName(DCC_Guild:guild, const role_name[]);
native DCC_Role:DCC_FindRoleById(const role_id[]);

native DCC_GetRoleId(DCC_Role:role, dest[DCC_ID_SIZE], max_size = sizeof dest);
native DCC_GetRoleName(DCC_Role:role, dest[], max_size = sizeof dest);
native DCC_GetRoleColor(DCC_Role:role, &color);
native DCC_GetRoleColour(DCC_Role:role, &colour) = DCC_GetRoleColor; // for our British mates
native DCC_GetRolePermissions(DCC_Role:role, &perm_high, &perm_low); // 64 bit integer
native DCC_IsRoleHoist(DCC_Role:role, &bool:is_hoist);
native DCC_GetRolePosition(DCC_Role:role, &position);
native DCC_IsRoleMentionable(DCC_Role:role, &bool:is_mentionable);
