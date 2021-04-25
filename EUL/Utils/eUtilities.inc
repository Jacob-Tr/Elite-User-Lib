#if defined EUTILS_INC
	#endscript
#else
	#if defined EUTILS_INC_UTILITIES
		#endscript
	#endif
#endif

#define EUTILS_INC_UTILITIES

#if !defined MAX_STRING
	#define MAX_STRING 255
#endif
#if !defined MENU_TITLE_LEN
	#define MENU_TITLE_LEN 32
#endif
#if !defined MENU_ITEM_LEN
	#define MENU_ITEM_LEN 31
#endif
#if !defined SCM
	#define SCM SendClientMessage
#endif
#if !defined SCMToAll
	#define SCMToAll SendClientMessageToAll
#endif
#if !defined SCL
	#define SCL(%0) printf("<Server>: %s", (%0))
#endif

#if defined TEXTDRAW_TEXT_LIMIT
	#undef TEXTDRAW_TEXT_LIMIT
#endif

#define NULL_PTEXT PlayerText:0
#define NULL_TEXT Text:0

#define TEXTDRAW_TEXT_LIMIT 255

#define MAX_TEXTS 25
#define MAX_PLAYERTEXTS 15

#define SPEED_MULTIPLIER 140

#define RND_ABS 0
#define RND_UP 1
#define RND_DOWN 2

new el_dialog[MAX_PLAYERS] = {-1, -1, ...};

new PlayerText:p_textdraws[MAX_PLAYERS][MAX_TEXTS];

new bool:text_shown[MAX_PLAYERS][MAX_TEXTS];
new bool:player_text_shown[MAX_PLAYERS][MAX_TEXTS];

#define MAX_WEAPON_NAME 32
new weapon_name[][32] =
{
	"Fists",
	"Brass Knuckles",
	"Golf Club",
	"Nite Stick",
	"Knife",
	"Baseball Bat",
	"Shovel",
	"Pool Cue",
	"Katana",
	"Chainsaw",
	"Dildo",
	"Small Vibrator",
	"Large Vibrator",
	"Vibrator",
	"Flowers",
	"Cane",
	"Grenade",
	"Tear Gas",
	"Molotov Cocktail",
	"",
	"",
	"",
	"9mm Pistol",
	"Silenced 9mm",
	"Desert Eagle",
	"Shotgun",
	"Sawn-off Shotgun",
	"Combat Shotgun",
	"Micro SMG",
	"SMG",
	"AK47",
	"M4",
	"Tec9",
	"Rifle",
	"Sniper Rifle",
	"Rocket Launcher",
	"HS Rocket Launcher",
	"Flamethrower",
	"Minigun",
	"Satchel Charge",
	"Detonator",
	"Spraycan",
	"Fire Extinguisher",
	"Camera",
	"Nightvision Goggles",
	"Thermal Goggles",
	"Parachute",
	"",
	"",
	"Collision",
	"Collision/Helicopter",
	"Explosion",
	"",
	"Drowned",
	"Suicide"
};

#define MAX_VEHICLE_NAME 32
new veh_name[][32] =
{
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Perennial",
	"Sentinel",
	"Dumper",
	"Firetruck",
	"Trashmaster",
	"Stretch",
	"Manana",
	"Infernus",
	"Voodoo",
	"Pony",
	"Mule",
	"Cheetah",
	"Ambulance",
	"Leviathan",
	"Moonbeam",
	"Esperanto",
	"Taxi",
	"Washington",
	"Bobcat",
	"Whoopee",
	"BF Injection",
	"Hunter",
	"Premier",
	"Enforcer",
	"Securicar",
	"Banshee",
	"Predator",
	"Bus",
	"Rhino",
	"Barracks",
	"Hotknife",
	"Trailer",
	"Previon",
	"Coach",
	"Cabbie",
	"Stallion",
	"Rumpo",
	"RC Bandit",
	"Romero",
	"Packer",
	"Monster",
	"Admiral",
	"Squalo",
	"Seasparrow",
	"Pizzaboy",
	"Tram",
	"Trailer",
	"Turismo",
	"Speeder",
	"Reefer",
	"Tropic",
	"Flatbed",
	"Yankee",
	"Caddy",
	"Solair",
	"Berkley's RC Van",
	"Skimmer",
	"PCJ-600",
	"Faggio",
	"Freeway",
	"RC Baron",
	"RC Raider",
	"Glendale",
	"Oceanic",
	"Sanchez",
	"Sparrow",
	"Patriot",
	"Quad",
	"Coastguard",
	"Dinghy",
	"Hermes",
	"Sabre",
	"Rustler",
	"ZR-350",
	"Walton",
	"Regina",
	"Comet",
	"BMX",
	"Burrito",
	"Camper",
	"Marquis",
	"Baggage",
	"Dozer",
	"Maverick",
	"News Chopper",
	"Rancher",
	"FBI Rancher",
	"Virgo",
	"Greenwood",
	"Jetmax",
	"Hotring",
	"Sandking",
	"Blista Compact",
	"Police Maverick",
	"Boxville",
	"Benson",
	"Mesa",
	"RC Goblin",
	"Hotring Racer A",
	"Hotring Racer B",
	"Bloodring Banger",
	"Rancher",
	"Super GT",
	"Elegant",
	"Journey",
	"Bike",
	"Mountain Bike",
	"Beagle",
	"Cropduster",
	"Stunt",
	"Tanker",
	"Roadtrain",
	"Nebula",
	"Majestic",
	"Buccaneer",
	"Shamal",
	"Hydra",
	"FCR-900",
	"NRG-500",
	"HPV1000",
	"Cement Truck",
	"Tow Truck",
	"Fortune",
	"Cadrona",
	"FBI Truck",
	"Willard",
	"Forklift",
	"Tractor",
	"Combine",
	"Feltzer",
	"Remington",
	"Slamvan",
	"Blade",
	"Freight",
	"Streak",
	"Vortex",
	"Vincent",
	"Bullet",
	"Clover",
	"Sadler",
	"Firetruck",
	"Hustler",
	"Intruder",
	"Primo",
	"Cargobob",
	"Tampa",
	"Sunrise",
	"Merit",
	"Utility",
	"Nevada",
	"Yosemite",
	"Windsor",
	"Monster",
	"Monster",
	"Uranus",
	"Jester",
	"Sultan",
	"Stratum",
	"Elegy",
	"Raindance",
	"RC Tiger",
	"Flash",
	"Tahoma",
	"Savanna",
	"Bandito",
	"Freight Flat",
	"Streak Carriage",
	"Kart",
	"Mower",
	"Dune",
	"Sweeper",
	"Broadway",
	"Tornado",
	"AT-400",
	"DFT-30",
	"Huntley",
	"Stafford",
	"BF-400",
	"News Van",
	"Tug",
	"Trailer",
	"Emperor",
	"Wayfarer",
	"Euros",
	"Hotdog",
	"Club",
	"Freight Box",
	"Trailer",
	"Andromada",
	"Dodo",
	"RC Cam",
	"Launch",
	"Police",
	"Police",
	"Police",
	"Ranger",
	"Picador",
	"S.W.A.T",
	"Alpha",
	"Phoenix",
	"Glendale Shit",
	"Sadler Shit",
	"Luggage",
	"Luggage",
	"Stairs",
	"Boxville",
	"Tiller",
	"Utility Trailer"
};

#define GetVehicleName el_getvehiclename
stock el_getvehiclename(vehicleid)
{
	new string[32];
	string = veh_name[vehicleid - 400];
	string[strlen(string) + 1] = EOS;
	return string;
}

#define GetWeaponName el_getweaponname
stock el_getweaponname(weaponid)
{
	new string[32];
	string = weapon_name[weaponid];
	string[strlen(string) + 1] = EOS;
	return string;
}

#define ShowPlayerDialog2 el_ShowPlayerDialog2
stock el_ShowPlayerDialog2(playerid, dialogid, style, caption[], info[], button1[], button2[]) // Creates a dialog as-well as keeping track of stats.
{
	el_dialog[playerid] = dialogid;
	ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
	return 1;
}

#define HidePlayerDialog el_HidePlayerDialog
stock el_HidePlayerDialog(playerid) // Ensures that the player does not have an active dialog.
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", "", "");
	el_dialog[playerid] = -1;
}

#define IsPlayerViewingDialog el_IsPlayerViewingDialog
stock el_IsPlayerViewingDialog(playerid) // Checks if a player has an active dialog.
{
	if(el_dialog[playerid] != -1) return true;
	else return false;
}

#define iswholenumber el_iswholenumber
stock bool:el_iswholenumber(Float:num)
{
	new string[64];
	format(string, sizeof(string), "%f", num);

	for(new i = 0; i < strlen(string); i++)
	{
	    if(string[i] == '.')
		{
			strmid(string, string, i + 1, strlen(string));
			//strdel(string, 0, i + 1);
			if(strval(string) == 0) return true;
			else return false;
		}
	}
	return true;
}

#define isstrwholenumber el_isstrwholenumber
stock bool:isstrwholenumber(string[])
{
	for(new i = 0; i < strlen(string); i++)
	{
	    if(string[i] == '.')
		{
			strmid(string, string, i + 1, strlen(string), 255);
			//strdel(string, 0, i + 1);
			if(strval(string) == 0) return true;
			else return false;
		}
	}
	return true;
}

#define isnumeric el_isnumeric
stock el_isnumeric(const string[])
{
	new length = strlen(string);
	if(length == 0) return false;
	for(new i = 0; i < length; i++) if ((string[i] > '9' || string[i] < '0' && string[i] != '.' && string[i] != '+' && string[i] != '-') || (string[i] == '+' && i == 0)) return false;
	if(length == 1 && (string[0] == '.' || string[0] == '-' || string[0] == '+')) return false;
	return true;
}

#define roundstrtoint el_roundstrtoint
stock el_roundstrtoint(const string[])
{
	new preDec[32], postDec[32], sum = 0;

	for(new i = 0; i < strlen(string); i++)
	{
		if(!isnumeric(string)) break;
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i));
			strmid(postDec, string, (i + 1), strlen(string));

			sum = strval(preDec);
			if(strval(postDec) >= 5) sum++;
			break;
		}
	}
	return sum;
}

#define roundstruptoint el_roundstruptoint
stock el_roundstruptoint(const string[])
{
	new preDec[32], sum = 0;

	for(new i = 0; i < strlen(string); i++)
	{
		if(!isnumeric(string)) break;
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i - 1));

			sum = strval(preDec) + 1;
			break;
		}
	}
	return sum;
}

#define roundstrdowntoint el_roundstrdowntoint
stock el_roundstrdowntoint(const string[])
{
	new preDec[32], sum = 0;

	for(new i = 0; i < strlen(string); i++)
	{
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i - 1));

			sum = strval(preDec);
			break;
		}
	}
	return sum;
}

#define roundtoint el_roundtoint
stock el_roundtoint(Float:num, round_type=RND_ABS)
{
	new string[64];
	format(string, sizeof(string), "%f", num);
	
	switch(round_type)
	{
		case RND_ABS: return el_roundstrtoint(string);
		case RND_UP: return el_roundstruptoint(string);
		case RND_DOWN: return el_roundstrdowntoint(string);
		default: return 0;
	}
	
	return 0;
}


#define strtok el_strtok
stock el_strtok(const string[], &index, seperator = ' ')
{
	new length = strlen(string);
	new offset = index;
	new result[MAX_STRING];
	while ((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1))) {
		result[index - offset] = string[index];
		index ++;
	}
	result[index - offset] = EOS;
	if ((index < length) && (string[index] == seperator)) {
		index ++;
	}
	return result;
}

#define GetName el_GetName
stock el_GetName(playerid, bool:ensure_caps=false)
{
	new pName[MAX_PLAYER_NAME];
	
	GetPlayerName(playerid, pName, MAX_PLAYER_NAME);
	if(ensure_caps) toupper(pName[0]);

    return pName;
}

#define ispositive el_ispositive
stock bool:el_ispositive(Float:num)
{
	if(num >= 0) return true;
	return false;
}

#define ismenuactive el_ismenuactive
stock bool:el_ismenuactive(Menu:menuid)
{
	if(menuid != Menu:0 || menuid != Menu:-1) return true;
	return false;
}

#define destroymenu el_destroymenu
stock el_destroymenu(&Menu:menuid)
{
	DestroyMenu(menuid);
	menuid = Menu:0;
}

#define createmenu el_createmenu
stock el_createmenu(&Menu:menuid, const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width=0.0, bool:override=false)
{
	if(!ismenuactive(menuid) || override)
	{
		if(ismenuactive(menuid)) destroymenu(menuid);
		menuid = CreateMenu(title, columns, x, y, col1width, col2width);
	}
}

#define isplayerviewingtextdraw el_isplayerviewingtextdraw
stock bool:el_isplayerviewingtextdraw(playerid, textid) {return text_shown[playerid][textid];}
#define isplayerviewingplayertext el_isplayerviewingplayertext
stock bool:el_isplayerviewingplayertext(playerid, textid) {return player_text_shown[playerid][textid];}

#define playertextdrawhide el_playertextdrawhide
stock el_playertextdrawhide(playerid, textid)
{
	player_text_shown[playerid][textid] = false;

	PlayerTextDrawHide(playerid, p_textdraws[playerid][textid]);
}

#define playertextdrawdestroy el_playertextdrawdestroy
stock el_playertextdrawdestroy(playerid, textid)
{
	player_text_shown[playerid][textid] = false;
	playertextdrawhide(p_textdraws[playerid][textid]);

	p_textdraws[playerid][textid] = NULL_PTEXT;
}

#define playertextdrawshow el_playertextdrawshow
stock el_playertextdrawshow(playerid, textid)
{
	playertextdrawhide(playerid, textid);

 	player_text_shown[playerid][textid] = true;
	PlayerTextDrawShow(playerid, p_textdraws[playerid][textid]);
}

#define playertextdrawupdate el_playertextdrawupdate
stock el_playertextdrawupdate(playerid, textid, PlayerText:text)
{
	playertextdrawhide(playerid, textid);
	p_textdraws[playerid][textid] = text;
	playertextdrawshow(playerid, textid);
}

#define getplayertextdrawinfo el_getplayertextdrawinfo
stock PlayerText:getplayertextdrawinfo(playerid, textid) {return p_textdraws[playerid][textid];}

#define createplayertextdraw el_createplayertextdraw
stock el_createplayertextdraw(playerid, textid, &PlayerText:textdrawid, Float:x, Float:y, text[TEXTDRAW_TEXT_LIMIT], bool:override=false)
{
	if(!isplayerviewingplayertext(playerid, textid) || override)
	{
		if(isplayerviewingplayertext(playerid, textid)) playertextdrawhide(playerid, textid);
		textdrawid = CreatePlayerTextDraw(playerid, x, y, text);
		p_textdraws[playerid][textid] = textdrawid;
	}
	
	textdrawid = p_textdraws[playerid][textid];
}

#define istextdrawidactive el_istextdrawidactive
stock bool:el_istextdrawidactive(textid) {return textdraws[textid] == NULL_TEXT ? false : true;}

#define textdrawhideforplayer el_textdrawhideforplayer
stock el_textdrawhideforplayer(playerid, textid)
{
	text_shown[playerid][textid] = false;
	TextDrawHideForPlayer(playerid, textdraws[textid]);
}

#define textdrawdestroy el_textdrawdestroy
stock el_textdrawdestroy(textid)
{
	for(new i = 0; i < MAX_PLAYERS; i++) if(isplayerviewingtextdraw(i, textid)) textdrawhideforplayer(i, textid);

	text = NULL_TEXT;
}

#define textdrawshowforplayer el_textdrawshowforplayer
stock el_textdrawshowforplayer(playerid, textid)
{
	textdrawhideforplayer(playerid, textid);

	text_shown[playerid][textid] = true;
	TextDrawShowForPlayer(playerid, textdraws[textid]);
}

#define textdrawupdate el_textdrawupdate
stock el_textdrawupdate(textid, Text:text)
{
	TextDrawHideForAll(textdraws[textid]);
	textdraws[textid] = text;
	
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(i == INVALID_PLAYER_ID) continue;
		if(isplayerviewingtextdraw(i, textid)) textdrawshowforplayer(i, textid);
	}
	return 1;
}

#define gettextdrawinfo el_gettextdrawinfo
stock Text:gettextdrawinfo(textid) {return textdraws[textid];}

#define textdrawcreate el_textdrawcreate
stock el_textdrawcreate(textid, Float:x, Float:y, text[], bool:override=false)
{
	if(istextdrawidactive(textid))
	{
		if(override) textdrawdestroy(textid);
		else return 0;
	}
	textdraws[textid] = TextDrawCreate(x, y, text);
}

stock IsVehicleModelBicycle(modelid)
{
	switch(modelid) {case 481, 509, 510: return true;}
	return false;
}

stock IsVehicleModelBike(modelid)
{
	switch(modelid) {case 448, 461, 462, 463, 468, 471, 521, 523, 522, 581, 586: return true;}
	return false;
}

stock IsVehicleModelHelicopter(modelid)
{
	switch(modelid) {case 417, 425, 447, 469, 487, 488, 497, 548, 563: return true;}
	return false;
}

stock IsVehicleModelPlane(modelid)
{
	switch(modelid) {case 460, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return true;}
	return false;
}

stock IsVehicleModelAircraft(modelid)
{
	if(IsVehicleModelHelicopter(modelid) || IsVehicleModelPlane(modelid)) return true;
	return false;
}

stock IsVehicleModelBoat(modelid)
{
	switch(modelid) {case 430, 446, 452, 454, 453, 472, 473, 484, 493, 595: return true;}
	return false;
}

stock IsVehicleTrailer(vehicleid)
{
	switch(GetVehicleModel(vehicleid)) {case 435, 450, 584, 591, 606, 607, 608, 610, 611: return true;}
	return false;
}

stock GetPlayerFacingAngleFix(playerid, &Float:ang)
{
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), ang);
	else GetPlayerFacingAngle(playerid, ang);
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y)
{
	new Float:xx, Float:yy, Float:z, Float:a;
	GetPlayerPos(playerid, xx, yy, z);
	GetPlayerFacingAngleFix(playerid, a);

    x = xx + (floatsin(-a, degrees) * 5.0);
	y = yy + (floatcos(-a, degrees) * 5.0);
}

stock Float:GetVehicleMPH(vehicleid)
{
	new Float:x, Float:y, Float:z, Float:ret;

	GetVehicleVelocity(vehicleid, x, y, z);
	ret = floatround(floatsqroot(x * x + y * y + z * z) * SPEED_MULTIPLIER * 1);
	return ret;
}

stock Float:GetVehicleKPH(vehicleid)
{
	new Float:x, Float:y, Float:z, Float:ret;
	GetVehicleVelocity(vehicleid, x, y, z);
	ret = floatround(floatsqroot(x * x + y * y + z * z) * SPEED_MULTIPLIER * 1.6);
	return ret;
}

#define isvalidmeleeweapon el_isvalidmeleeweapon
stock el_isvalidmeleeweapon(weaponid)
{
	if((weaponid > 0 && weaponid < 15) || (weaponid >= 40 && weaponid <= 42)) return true;
	return false;
}

#define isvalidsidearm el_isvalidsidearm
stock el_isvalidsidearm(weaponid)
{
	if((weaponid >= 15 && weaponid <= 23) || weaponid == 25 || weaponid == 27 || weaponid == 31 || weaponid == 38) return true;
	return false;
}

#define isvalidprimary el_isvalidprimary
stock el_isvalidprimary(weaponid)
{
	if(weaponid == 24 || weaponid == 26 || ((weaponid >= 28 && weaponid <= 37) && weaponid != 31)) return true;
	return false;
}
