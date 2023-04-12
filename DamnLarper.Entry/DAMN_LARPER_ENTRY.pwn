// Script written by DEntisT, © & ® BRACE™.

#pragma option -;+

new DAMN_LARPER_LOADED = 1;

#define @DISCORD_DECORATOR@%0\32; @DISCORD_DECORATOR@

#define @discord%0(%1) @DISCORD_DECORATOR@

#define SLASH_COMMANDS 1

// API, implementations

#include "../Discord.API/Open.MP.API.inc"

#include "../Discord.API/sscanf.Plugin.inc"
#include "../Discord.API/crashdetect.Plugin.inc"

#include "../Discord.API/DCC.Plugin.Setup.inc"
#include "../Discord.API/DCC.Plugin.Channels.inc"
#include "../Discord.API/DCC.Plugin.Messages.inc"
#include "../Discord.API/DCC.Plugin.Users.inc"
#include "../Discord.API/DCC.Plugin.Roles.inc"
#include "../Discord.API/DCC.Plugin.Guilds.inc"
#include "../Discord.API/DCC.Plugin.Bot.inc"
#include "../Discord.API/DCC.Plugin.Misc.inc"
#include "../Discord.API/DCC.Plugin.Emoji.inc"
#include "../Discord.API/DCC.Plugin.Reactions.inc"
#include "../Discord.API/DCC.Plugin.Commands.inc"
#include "../Discord.API/DCC.Plugin.Interactions.inc"

// NRP_Components

#include "../DamnLarper.Components/NRP_Component.Macros.inc"

// Modules

#include "../DamnLarper.Modules/DL.System.Emoji.inc"
#include "../DamnLarper.Modules/DL.System.Macros.inc"
#include "../DamnLarper.Modules/DL.System.Vars.inc"
#include "../DamnLarper.Modules/DL.System.Utils.inc"
#include "../DamnLarper.Modules/DL.System.GuildCfg.inc"
#include "../DamnLarper.Modules/DL.System.Publics.inc"
#include "../DamnLarper.Modules/DL.System.SlashCmds.inc"
#include "../DamnLarper.Modules/DL.System.Interactions.inc"

#pragma dynamic 215750000

// Commands:

#include "../DamnLarper.Modules/DL.System.Commands.inc"


// Other components:

// Included on the top:#include "../discord_components/d_nrp_macros.inc"
#include "../DamnLarper.Components/NRP_Component.Cmds.inc"
#include "../DamnLarper.Components/NRP_Component.ModCmds.inc"
#include "../DamnLarper.Components/NRP_Component.Utils.inc"
#include "../DamnLarper.Components/NRP_Component.Impl.inc"



// Other things

main()
{
	print("The script started sir");
}