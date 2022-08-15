// commands
native DCC_Command:DCC_CreateCommand(const command_name[DCC_COMMAND_SIZE], const description[DCC_COMMAND_DESCRIPTION_SIZE], const callback[], bool:allow_everyone = true, DCC_Guild:guild = DCC_INVALID_GUILD);
native DCC_DeleteCommand(DCC_Command:command);
