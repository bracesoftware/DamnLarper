// Module written by DEntisT, © & ® BRACE™.

@discord() command:balance(@discord() cmd_params)
{
	return discord_bal(message, author, PARAMETERS, slashchannel);
}

@discord() command:deposit(@discord() cmd_params)
{
	return discord_dep(message, author, PARAMETERS, slashchannel);
}

@discord() command:withdraw(@discord() cmd_params)
{
	return discord_with(message, author, PARAMETERS, slashchannel);
}

@discord() command:inventory(@discord() cmd_params)
{
	return discord_inv(message, author, PARAMETERS, slashchannel);
}
