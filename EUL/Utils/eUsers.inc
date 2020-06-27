#if defined EUTILS_INC
	#Endscript
#else
	#if defined EUTIL_INC_USERS
		#Endscript
	#endif
#endif

#define EUTIL_INC_USERS

#if !defined EUTIL_INC_UTILITIES
	#tryinclude <EUL\Utils\eUtilities>
#endif

#if !defined INI_Exists
	#define INI_Exists(%0) fexist(%0) // (%0) is a parameter. (A file directory in this case)
#endif
#if defined USER_FILE
	#error "USER_FILE constant definition cannot exist while eUsers is in use."
#else
	#define USER_FILE "Users/%s/%c/%s.ini" // The format of the files. (scriptfiles/Users/(First letter of player name}/(player name).ini)
#endif

#if defined MAX_LOGINS
	#error "MAX_LOGINS constant definition cannot exist while eUsers is in use."
#else
	#define MAX_LOGINS 3
#endif

enum data
{
	playerPassword
}

enum sData
{
	playerName
}

new playerData[MAX_PLAYERS][data];
new sPlayerData[MAX_PLAYERS][sData][25];

new bool:registering[MAX_PLAYERS];

new loginAttempts[MAX_PLAYERS];

new Dialog:dialog[MAX_PLAYERS];

new serverName[50] = "Default";

stock setServerName(str[50])
{
	serverName = str;
	return 1;
}

stock getLoginAttempts(playerid)
{
	return loginAttempts[playerid];
}

stock isPlayerRegistering(playerid)
{
	return registering[playerid];
}

stock ShowPlayerDialog2(playerid, dialogid, style, caption[], info[], button1[], button2[]) // Creates a dialog as-well as keeping track of stats.
{
	dialog[playerid] = Dialog:ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

stock HidePlayerDialog(playerid) // Ensures that the player does not have an active dialog.
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", "", "");
	dialog[playerid] = Dialog:-1;
}

stock IsPlayerViewingDialog(playerid) // Checks if a player has an active dialog.
{
	if(dialog[playerid] != Dialog:-1) return true;
	else return false;
}

stock udb_hash(buf[])
{
    new length=strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for (n=0; n<length; n++)
    {
       s1 = (s1 + buf[n]) % 65521;
       s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

stock SavePlayerData(playerid, file[]) // Opens, edits and closes the user file.
{
	new INI:UsrFile = INI_Open(file);

	INI_WriteString(UsrFile, "playerName", sPlayerData[playerid][playerName]);
	INI_WriteInt(UsrFile, "playerPassword", playerData[playerid][playerPassword]);

	INI_Close(UsrFile);
}

stock InitStatsForPlayer(playerid) // So we know what the values should be at all times.
{
	registering[playerid] = false;
	loginAttempts[playerid] = 0;
	dialog[playerid] = Dialog:-1;
	return 1;
}

stock PlayerExitServer(playerid) // So players can't possibly keep the stats of the previous player.
{
	sPlayerData[playerid][playerName] = "";
	playerData[playerid][playerPassword] = -1;

	InitStatsForPlayer(playerid); // Redundant, but possibly necessary.

	HidePlayerDialog(playerid);
	return 1;
}

forward LoadPlayerData(playerid, value[], name[]);

public LoadPlayerData(playerid, value[], name[])
{
	INI_String("playerName", sPlayerData[playerid][playerName], 25);
	INI_Int("playerPassword", playerData[playerid][playerPassword]);
	return 1;
}

