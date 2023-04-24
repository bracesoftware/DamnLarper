// Script written by DEntisT, © & ® BRACE™.
// Nation RP bot component - macros

#define SERVER_RISE_OF_NATIONS "RoN • Rise of Nations"


#define RiseOfNations 		DCC_FindGuildById("987003062726058004")

new RISE_OF_NATIONS_GLOBALSTRING[1024];
new dateupdated;
new staffid[MAX_STAFF_MEMBERS][DCC_ID_SIZE], staffstring[2200];


#define bankicklog 			DCC_FindChannelById("1006119258851385404") //d
#define rpnotices 			DCC_FindChannelById("994393758940541100") //d
#define war_gm_output 		DCC_FindChannelById("994393810383675513") //d
#define submissionchannel 	DCC_FindChannelById("994393733879582883") //d
#define dateupdate 			DCC_FindChannelById("994393767836667965") //d
#define supportchannel 		DCC_FindChannelById("1006120126573191221") //d
#define lounge 				DCC_FindChannelById("994393740884062259") //d
#define commandchannel 		DCC_FindChannelById("994393746718326824") //d
#define gm_output 			DCC_FindChannelById("994393764900655224") //d
#define gm_count 			DCC_FindChannelById("1006120493507694622") //d
#define logs 				DCC_FindChannelById("1006560017845067876") //d
#define announcements 		DCC_FindChannelById("994393713461706832") //d
#define countchannel 		DCC_FindChannelById("994393752351285338") //d
#define appreview 			DCC_FindChannelById("1006140665819824208") //d
#define verifychannel   	DCC_FindChannelById("1006227267048968212") //d

#define rpchannel 			DCC_FindChannelById("994393772605571112") //d
#define rpchannel1 			DCC_FindChannelById("994393773826117762") //d
#define rpchannel2 			DCC_FindChannelById("994393776334311445") //d
#define rpchannel3 			DCC_FindChannelById("994393777911386234") //d
#define rpchannel4 			DCC_FindChannelById("994393780314722486") //d
#define rpchannel5 			DCC_FindChannelById("994393781833043999") //d
#define rpchannel6 			DCC_FindChannelById("994393787805741097") //d
#define rpchannel7 			DCC_FindChannelById("994393789445718066") //d

#define muted				DCC_FindRoleByName(RiseOfNations, "Muted Member")
#define RiseOfNationsrole 			DCC_FindRoleByName(RiseOfNations, ""SERVER_RISE_OF_NATIONS"")
#define gm					DCC_FindRoleById("994393513766699051")
#define pgm					DCC_FindRoleById("994393514886561842")

#define nation 				DCC_FindRoleById("994393621182828544")
#define rebelorg 			DCC_FindRoleById("994393625179992125")
#define politicalorg 		DCC_FindRoleById("994393621761638411")
#define acoop 				DCC_FindRoleById("994393624022368397")
#define pcoop 				DCC_FindRoleById("994868405557530676")
#define civilian 			DCC_FindRoleById("994393622856347708")
#define unsec 				DCC_FindRoleById("1000682605458497588")
#define spectator 			DCC_FindRoleById("994393627646234694")
#define playerrole 			DCC_FindRoleById("994393626836750536")
#define corporation 		DCC_FindRoleById("1002196249308581948")

#define standardrole1 		DCC_FindRoleById("994393620406882324")
#define standardrole2 		DCC_FindRoleById("994567140181033061")
#define standardrole3 		DCC_FindRoleById("994393628397019216")
#define standardrole4 		DCC_FindRoleById("994393633866387527")
#define unverified 			DCC_FindRoleById("1006236985066795078")