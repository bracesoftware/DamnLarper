/*
*
*	Damn Larper
*	Discord Bot
*
*	by: DEntisT
*
*	v2.1-R3-alpha
*
*/

// Script written by DEntisT, © & ® BRACE™.

#pragma option -;+

#define @DISCORD_DECORATOR@%0\32; @DISCORD_DECORATOR@

#define @discord%0(%1) @DISCORD_DECORATOR@

#define DAMN_LARPER_MAJOR	"4"
#define DAMN_LARPER_MINOR	"0"
#define DAMN_LARPER_RELEASE	"1"

////////////////////////////////

#define USE_DEPRECATED_COMPONENTS 0
#define DAMNLARPER_NO_SQL

#pragma dynamic 215750000

//#tryinclude <samp/a_samp>

// API, implementations

#include "../api_elements/server.inc"

#include "../api_elements/sscanf.inc"
#include "../api_elements/crashdetect.inc"

#include "../api_elements/discord.inc"

#if !defined DAMNLARPER_NO_SQL

#include "../api_elements/mysql.inc"
#include "../api_elements/sql_api.inc"

#endif

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
	print("DAMN LARPER IS BACK!");
	print("The script started sir.");
}