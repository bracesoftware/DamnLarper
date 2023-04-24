//  users
native DCC_User:DCC_FindUserByName(const user_name[], const user_discriminator[]);
native DCC_User:DCC_FindUserById(const user_id[]);

native DCC_GetUserName(DCC_User:user, dest[DCC_USERNAME_SIZE], max_size = sizeof dest);
native DCC_GetUserId(DCC_User:user, dest[DCC_ID_SIZE], max_size = DCC_ID_SIZE);
native DCC_GetUserDiscriminator(DCC_User:user, dest[], max_size = sizeof dest);
native DCC_IsUserBot(DCC_User:user, &bool:is_bot);
native DCC_IsUserVerified(DCC_User:user, &bool:is_verified);


forward DCC_OnUserUpdate(DCC_User:user);