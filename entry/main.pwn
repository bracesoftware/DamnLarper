/*
*
*	Damn Larper
*	Discord Bot
*
*	by: DEntisT
*
*	v7.1-R1-alpha
*
*/

// Script written by DEntisT, © & ® BRACE™.

#pragma option -;+

#define @DISCORD_DECORATOR@%0\32; @DISCORD_DECORATOR@

#define @discord%0(%1) @DISCORD_DECORATOR@

#define DAMN_LARPER_MAJOR	"7"
#define DAMN_LARPER_MINOR	"2"
#define DAMN_LARPER_RELEASE	"2"

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

#include "../api_elements/fsutil.inc"

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

// Promo sys:
#include "../modules/promo.inc"

// Other components:

#if USE_DEPRECATED_COMPONENTS == 1

// Included on the top:#include "../discord_components/d_nrp_macros.inc"
#include "../deprecated/nrp/cmd_impl.inc"
#include "../deprecated/nrp/cmd_mod.inc"
#include "../deprecated/nrp/utils.inc"
#include "../deprecated/nrp/func.inc"

#endif

// Other things

Damn_SendBotAnnouncement()
{

	new dir:dHandle = dir_open("./scriptfiles/serverdata/");
	new item[100], type;
		
	while(dir_list(dHandle, item, type))
	{
	    if(type == FM_FILE)
	    {
	    	if(item[0] == 'a' && item[1] == 'n' && item[2] == 'c' && item[3] == '_')
	    	{
	    		third__strreplace(item, "anc_", "");
	    		third__strreplace(item, ".ini", "");
	    		printf("Guild found: '%s'",item);

	    		@discord() SendMsg(DCC_FindChannelById(GetGuildAnnouncementChannel(DCC_FindGuildById(item))), "**__Announcement from the Devs__**\n\n"botpfp" **%s** • %s",d_annc_title,d_announcement);
	    	}
	    }
	}
			
	dir_close(dHandle);

	return 1;
}

main()
{
	print("_______________________");
	print("==========================");
	print("DAMN LARPER IS BACK!");
	print("The script started sir.");
	print("==========================");
	strmid(d_annc_title, "We're back!", 0, sizeof d_annc_title);
	strmid(d_announcement, "The bot is online again; get help at `"BOT_PREFIX"help`.\n• **Script Version**\n"d_reply"Bot code version is: `"BOT_VERSION"`", 0, sizeof d_announcement);
	Damn_SendBotAnnouncement();//RemoveDir("test__dentist", true);
}

