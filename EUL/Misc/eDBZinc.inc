#include <a_samp>

#define PowerFile "PwrData/%c/%s.inc"
#define SCM SendClientMessage
#define SCMToAll SendClientMessageToAll

#define DIALOG_SELECT_RACE 17600
#define DIALOG_LEVEL 17601
#define DIALOG_LEVEL_ITEM 17602
#define DIALOG_STATS 17603

#define RACE_DIALOG_INFO "Human\nNameikian\nFrost Demon\nYardratian\nSaiyan"
#define LEVEL_DIALOG_INFO "Power\nEnergy Manipulation\nMax Stamina"

#define INI_Exists(%0) fexist(%0)

#define KEY_PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define KEY_RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

//Color defines.

#define COLOR_GRAY 0xAFAFAFAA
#define COLOR_GREEN 0x00FF00FF
#define COLOR_RED 0xFF0000FF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_BLUE 0x0000FFFF
#define COLOR_LIGHTBLUE 0x33CCFFAA
#define COLOR_ORANGE 0xFF9900FF
#define COLOR_LIME 0x10F441AA
#define COLOR_MAGENTA 0xFF00FFFF
#define COLOR_NAVY 0x000080AA
#define COLOR_AQUA 0xF0F8FFAA
#define COLOR_CRIMSON 0xDC143CAA
#define COLOR_FLBLUE 0x6495EDAA
#define COLOR_BISQUE 0xFFE4C4AA
#define COLOR_BLACK 0x000000AA
#define COLOR_CHARTREUSE 0x7FFF00AA
#define COLOR_BROWN 0XA52A2AAA
#define COLOR_CORAL 0xFF7F50AA
#define COLOR_GOLD 0xB8860BAA
#define COLOR_GREENYELLOW 0xADFF2FAA
#define COLOR_INDIGO 0x4B00B0AA
#define COLOR_IVORY 0xFFFF82AA
#define COLOR_LAWNGREEN 0x7CFC00AA
#define COLOR_SEAGREEN 0x20B2AAAA
#define COLOR_LIMEGREEN 0x32CD32AA
#define COLOR_MIDNIGHTBLUE 0X191970AA
#define COLOR_MAROON 0x800000AA
#define COLOR_OLIVE 0x808000AA
#define COLOR_ORANGERED 0xFF4500AA
#define COLOR_PINK 0xFFC0CBAA
#define COLOR_SPRINGGREEN 0x00FF7FAA
#define COLOR_TOMATO 0xFF6347AA
#define COLOR_YELLOWGREEN 0x9ACD32AA
#define COLOR_MEDIUMAQUA 0x83BFBFAA
#define COLOR_MEDIUMMAGENTA 0x8B008BAA
#define COLOR_THCGREEN 0x00FF88AA
#define COLOR_ADMIN adcolor(playerid)

//Integratable Colors
#define COL_BLUE "{0000FF}"
#define COL_ASAY "{008B8B}"
#define COL_RED "{FF0000}"
#define COL_WHITE "{FFFFFF}"
#define COL_ORA "{FF9900}"
#define COL_YELLOW "{FFFF00}"
#define COL_GREEN "{00FF00}"
#define COL_GRAY "{AFAFAF}"
#define COL_WBLUE "{0055CC}"
#define COL_CRIMSON "{DC143C}"
#define COL_LBLUE "{99FFFF}"
#define COL_PURPLE "{CC00DD}"

//BeckzBoi's Colors(Some used to replace my colors.)
//http://forum.sa-mp.com/member.php?u=5303 (BeckzyBoi)

#define COLOR_ASAY 0xFF0000FF
#define COLOR_OSAY 0x007700FF
#define COLOR_HSAY 0x1684CAFF
#define COLOR_LRED 0xFF4747FF
#define COLOR_LGREEN 0x00FF9900
#define COLOR_LBLUE 0x99FFFFFF
#define COLOR_PURPLE 0xCC00DDFF
#define COLOR_PEACH 0xFFCC66FF
#define COLOR_SILVER 0xDDDDDDFF
#define COLOR_WANTEDBLUE 0x0055CCFF
#define COLOR_DARK_VIOLET 0x9400D3FF
#define COLOR_SUPPORT 0x00E5EEFF
//#define COLOR_ADMIN 0x00CCFF66
#define COLOR_PLAYER 0xFFFF33FF
#define COLOR_VIP1 0xC0C0C0FF
#define COLOR_VIP2 0xDAA520FF

new Dialog:powerDialog[MAX_PLAYERS];
new dialogType[MAX_PLAYERS];

new levels[MAX_PLAYERS];

new currentItem[MAX_PLAYERS];

new Float:health[MAX_PLAYERS];

new bool:charging[MAX_PLAYERS];

enum powerStats
{
	powerCap,
	energyManip,
	race
}

new power[MAX_PLAYERS][powerStats];

enum Float:floatPowerStats
{
    Float:energy,
	Float:stamina,
	Float:exp
}

new Float:floatPower[MAX_PLAYERS][floatPowerStats];

ShowPlayerDialog2(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	powerDialog[playerid] = Dialog:ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
	dialogType[playerid] = dialogid;
}

HidePlayerDialog(playerid)
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", "", "");
	powerDialog[playerid] = Dialog:-1;
	dialogType[playerid] = -1;
}

bool:IsPlayerViewingAnyDialog(playerid)
{
	if(powerDialog[playerid] != Dialog:-1) return true;
	return false;
}

bool:IsPlayerViewingDialog(playerid, dialogid)
{
	if(dialogType[playerid] == dialogid) return true;
	else return false;
}

GetName(playerid)
{
    new
        pName[MAX_PLAYER_NAME];

    GetPlayerName(playerid, pName, MAX_PLAYER_NAME);
    return pName;
}

stock DisplayStatsForPlayer(playerid, pplayerid)
{
	new string[40], string2[256];
	format(string, sizeof(string), "%s's stats", GetName(pplayerid));
	format(string2, sizeof(string2), "Power:\t%d\nEnergy Manipulation:\t%d\nStamina:\t%f", power[pplayerid][powerCap], power[pplayerid][energyManip], floatPower[pplayerid][stamina]);

	ShowPlayerDialog2(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, "%s's stats", string2, "Done");
}

stock SavePlayerPower(playerid)
{
	new file[45], name[25] = GetName(playerid);
	format(file, sizeof(file), PowerFile, name[0], name);

	if(!INI_Exists(file)) return 0;

	new INI:PwrFile = INI_Open(file);

	INI_WriteInt(PwrFile, "powerCap", power[playerid][powerCap]);
	INI_WriteInt(PwrFile, "energyManip", power[playerid][energyManip]);
	INI_WriteInt(PwrFile, "race", power[playerid][race]);

	INI_WriteFloat(PwrFile, "energy", floatPower[playerid][energy]);
	INI_WriteFloat(PwrFile, "health", health[playerid]);
	INI_WriteFloat(PwrFile, "stamina", floatPower[playerid][stamina]);
	INI_WriteFloat(PwrFile, "exp", floatPower[playerid][exp]);

	INI_Close(PwrFile);
}

stock OverwriteStringStat(playerid, stat[], value[])
{
	new file[45], name[25] = GetName(playerid);
	format(file, sizeof(file), PowerFile, name[0], name);

	if(!INI_Exists(file)) return 0;

	new INI:PwrFile = INI_Open(file);

	INI_WriteString(PwrFile, stat, value);

	INI_Close(PwrFile);
}

stock OverwriteFloatStat(playerid, stat[], Float:value)
{
	new file[45], name[25];
	name = GetName(playerid);
	format(file, sizeof(file), PowerFile, name[0], name);

	if(!INI_Exists(file)) return 0;

	new INI:PwrFile = INI_Open(file);

	INI_WriteFloat(PwrFile, stat, value);

	INI_Close(PwrFile);
	
	return 1;
}

stock OverwriteIntStat(playerid, stat[], value)
{
	new file[45], name[25];
	name = GetName(playerid);
	format(file, sizeof(file), PowerFile, name[0], name);

	if(!INI_Exists(file)) return 0;

	new INI:PwrFile = INI_Open(file);

	INI_WriteInt(PwrFile, stat, value);

	INI_Close(PwrFile);
	
	return 1;
}

stock GetRaceInt(pRace[50])
{
	if(strcmp(pRace, "Human", false, sizeof(race))) return 1;
	if(strcmp(pRace, "Namekian", false, sizeof(race))) return 2;
	if(strcmp(pRace, "FrostDemon", false, sizeof(race))) return 3;
	if(strcmp(pRace, "Yardratian", false, sizeof(race))) return 4;
	if(strcmp(pRace, "Saiyan", false, sizeof(race))) return 5;
	if(strcmp(pRace, "N/A", false, sizeof(race))) return 0;
	return 0;
}

stock AssignPlayerRace(playerid, pRace)
{
	OverwriteIntStat(playerid, "race", pRace);
}

stock AssignPlayerRaceByString(playerid, pRace[50])
{
	OverwriteIntStat(playerid, "race", GetRaceInt(pRace));
}

stock ChangeClientHealth(playerid, Float:amount)
{
	new Float:pHealth;
	GetPlayerHealth(playerid, pHealth);
	SetPlayerHealth(playerid, pHealth + (amount));
}

stock determineLevels(playerid)
{
	new pLevels, Float:exper;
	exper = floatPower[playerid][exp];

	while(exper >= (power[playerid][powerCap] - power[playerid][energyManip]) * (2 * GetPlayerScore(playerid)))
	{
	    exper -= (power[playerid][powerCap] - power[playerid][energyManip]) * (2 * GetPlayerScore(playerid));
	    pLevels++;
	}

	return pLevels;
}

forward LoadPlayerPower(playerid, name[], value[]);
forward ChargeEnergy(playerid);

public LoadPlayerPower(playerid, name[], value[])
{
	INI_Int("powerCap", power[playerid][powerCap]);
	INI_Int("energyManip", power[playerid][energyManip]);
	INI_Int("race", power[playerid][race]);

	INI_Float("energy", floatPower[playerid][energy]);
	INI_Float("health", health[playerid]);
	INI_Float("stamina", floatPower[playerid][stamina]);
	INI_Float("exp", floatPower[playerid][exp]);
	return 1;
}

public ChargeEnergy(playerid)
{
	if(charging[playerid])
	{
		if(floatPower[playerid][energy] > (power[playerid][energyManip] / 100))
		{
			floatPower[playerid][stamina] += (power[playerid][energyManip] / 100);
			floatPower[playerid][energy] -= (power[playerid][energyManip] / 100);
		}
		else charging[playerid] = false;
	}
	else return 0;

	return 1;
}
