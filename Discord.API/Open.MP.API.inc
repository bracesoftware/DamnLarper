#include <open.mp>

#endinput

//console
native print(const string[]);
native printf(const format[], ...);
native random(max);

//files
enum filemode
{
	io_read,            /* file must exist */
	io_write,           /* creates a new file */
	io_readwrite,       /* opens an existing file, or creates a new file */
	io_append,          /* appends to file (write-only) */
}
native fexist(const pattern[]);
native File:fopen(const name[], filemode: mode = io_readwrite);
native fread(File: handle, string[], size = sizeof string, bool: pack = false);
native fclose(File: handle);
native fwrite(File: handle, const string[]);
native fremove(const name[]);

//strings
native strmid(dest[], const source[], start, end, maxlength=sizeof dest);
native strlen(const string[]);
native strval(const string[]);
native strcmp(const string1[], const string2[], bool:ignorecase=false, length=cellmax);
native format(output[], len, const format[], ...);
native strdel(string[], start, end);
native tolower(c);
native strfind(const string[], const sub[], bool:ignorecase=false, pos=0);
native strcat(dest[], const source[], maxlength=sizeof dest);

//time
native gettime(hour=0, minute=0, second=0);
native getdate(year=0, month=0, day=0);

//a_samp

#pragma rational Float

#define INVALID_PLAYER_ID -1
#define MAX_PLAYER_NAME 30
#define MAX_PLAYERS 30

native GetMaxPlayers();
native GetPlayerName(playerid, const name[], len);
native IsPlayerNPC(playerid);
native IsPlayerConnected(playerid);
native CallLocalFunction(const function[], const format[], ...);
native SetTimer(const funcname[], interval, repeating);

forward OnFilterScriptInit();
forward OnGameModeInit();
forward OnPlayerConnect(playerid);
forward OnPlayerDisconnect(playerid, reason);
forward OnGameModeExit();

//sscanf
#define SSCANF_NO_PLAYERS
#define SSCANF_NO_K_WEAPON
#define SSCANF_NO_K_VEHICLE
#define SSCANF_NO_NICE_FEATURES