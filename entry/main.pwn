// Script written by DEntisT, © & ® BRACE™.

#pragma option -;+

#define @DISCORD_DECORATOR@%0\32; @DISCORD_DECORATOR@

#define @discord%0(%1) @DISCORD_DECORATOR@

#define SLASH_COMMANDS 1
stock DAMN_LARPER_REWRITE = 1;

#define DAMN_LARPER_MAJOR	"2"
#define DAMN_LARPER_MINOR	"1"
#define DAMN_LARPER_RELEASE	"1"

#define USE_DEPRECATED_COMPONENTS 0

#pragma dynamic 215750000


// API, implementations

#include "../api_elements/server.inc"

#include "../api_elements/sscanf.inc"
#include "../api_elements/crashdetect.inc"

#include "../api_elements/discord_setup.inc"
#include "../api_elements/discord_channels.inc"
#include "../api_elements/discord_messages.inc"
#include "../api_elements/discord_users.inc"
#include "../api_elements/discord_roles.inc"
#include "../api_elements/discord_guilds.inc"
#include "../api_elements/discord_bot.inc"
#include "../api_elements/discord_misc.inc"
#include "../api_elements/discord_emoji.inc"
#include "../api_elements/discord_reactions.inc"
#include "../api_elements/discord_commands.inc"
#include "../api_elements/discord_interactions.inc"

#include "../api_elements/mysql.inc"
#include "../api_elements/sql_api.inc"

// NRP_Components

#if USE_DEPRECATED_COMPONENTS == 1

#include "../deprecated/nrp/setup.inc"

#endif

// Modules

#include "../modules/emoji.inc"
#include "../modules/setup.inc"
#include "../modules/vars.inc"
#include "../modules/sql.inc"

#include "../modules/utils.inc"
#include "../modules/inv.inc"
#include "../modules/pets.inc"
#include "../modules/achievements.inc"
#include "../modules/guild_cfg.inc"

#include "../modules/func.inc"
#include "../modules/cmd_slash.inc"
#include "../modules/interactions.inc"

#include "../modules/cmd_alias.inc"

#include "../modules/user_cfg.inc"

// Commands:

#include "../modules/cmd_impl.inc"

// Other components:

#if USE_DEPRECATED_COMPONENTS == 1

// Included on the top:#include "../discord_components/d_nrp_macros.inc"
#include "../deprecated/nrp/cmd_impl.inc"
#include "../deprecated/nrp/cmd_mod.inc"
#include "../deprecated/nrp/utils.inc"
#include "../deprecated/nrp/func.inc"

#endif

// Other things

main()
{
	print("The script started sir.");
}