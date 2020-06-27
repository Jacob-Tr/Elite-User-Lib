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
	#define SCL(%0,%1) printf("[%s]: %s", (%0), (%1))
#endif

#if defined TEXTDRAW_TEXT_LIMIT
	#undef TEXTDRAW_TEXT_LIMIT
#endif

#define TEXTDRAW_TEXT_LIMIT 255

#define SPEED_MULTIPLIER 140

new e_dialog[MAX_PLAYERS];

#define ShowPlayerDialog2 e_ShowPlayerDialog2
stock e_ShowPlayerDialog2(playerid, dialogid, style, caption[], info[], button1[], button2[]) // Creates a dialog as-well as keeping track of stats.
{
	e_dialog[playerid] = ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
	return 1;
}

#define HidePlayerDialog e_HidePlayerDialog
stock e_HidePlayerDialog(playerid) // Ensures that the player does not have an active dialog.
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", "", "");
	e_dialog[playerid] = 0;
}

#define IsPlayerViewingDialog e_IsPlayerViewingDialog
stock e_IsPlayerViewingDialog(playerid) // Checks if a player has an active dialog.
{
	if(e_dialog[playerid] != Dialog:0) return true;
	else return false;
}

#define iswholenumber e_iswholenumber
stock bool:e_iswholenumber(Float:num)
{
	new string[50];
	format(string, sizeof(string), "%f", num);

	for(new i = 0; i <= strlen(string) - 1; i++)
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

#define isstrwholenumber e_isstrwholenumber
stock bool:isstrwholenumber(string[])
{
	for(new i = 0; i <= strlen(string) - 1; i++)
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

#define roundtoint e_roundtoint
stock e_roundtoint(Float:num)
{
	new string[64], preDec[32], postDec[32], sum;
	format(string, sizeof(string), "%f", num);
	
	for(new i = 0; i <= strlen(string) - 1; i++)
	{
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i - 1));
			strmid(postDec, string, (i + 1), strlen(string));
			
			sum = strval(preDec);
			if(strval(postDec) >= 5) sum++;
			break;
		}
	}
	return sum;
}

#define RoundDownToInt e_roundtoint
stock e_RoundDownToInt(Float:num)
{
	new string[64], preDec[32], postDec[32], sum;
	format(string, sizeof(string), "%f", num);
	
	for(new i = 0; i <= strlen(string) - 1; i++)
	{
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i - 1));
			strmid(postDec, string, (i + 1), strlen(string));
			
			sum = strval(preDec);
			break;
		}
	}
	return sum;
}

#define roundstrtoint e_roundtoint
stock e_roundstrtoint(const string[])
{
	new string[64], preDec[32], postDec[32], sum;
	
	for(new i = 0; i <= strlen(string) - 1; i++)
	{
		if(!isnumeric(string)) break;
		if(string[i] == '.')
		{
			strmid(preDec, string, 0, (i - 1));
			strmid(postDec, string, (i + 1), strlen(string));
			
			sum = strval(preDec);
			if(strval(postDec) >= 5) sum++;
			break;
		}
	}
	return sum;
}


#define strtok e_strtok
stock e_strtok(const string[], &index, seperator = ' ')
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

#if !defined isnumeric
	#define isnumeric e_isnumeric
#endif
stock e_isnumeric(const string[])
{
	new length = strlen(string);
	if(length == 0) return false;
	for(new i = 0; i < length; i++) if ((string[i] > '9' || string[i] < '0' && string[i] != '.' && string[i] != '+' && string[i] != '-') || (string[i] == '+' && i == 0)) return false;
	if(length == 1 && (string[0] == '.' || string[0] == '-' || string[0] == '+')) return false;
	return true;
}

#define GetName e_GetName
stock e_GetName(playerid, bool:ensure_caps=false)
{
	new pName[MAX_PLAYER_NAME];
	
	GetPlayerName(playerid, pName, MAX_PLAYER_NAME);
	if(ensure_caps) toupper(pName[0]);

    return pName;
}

#define ispositive e_ispositive
stock bool:e_ispositive(Float:num)
{
	if(num >= 0) return true;
	return false;
}

#define ismenuactive e_ismenuactive
stock bool:e_ismenuactive(Menu:menuid)
{
	if(menuid != Menu:0 || menuid != Menu:-1) return true;
	return false;
}

#define destroymenu e_destroymenu
stock e_destroymenu(&Menu:menuid)
{
	DestroyMenu(menuid);
	menuid = Menu:0;
}

#define createmenu e_createmenu
stock e_createmenu(&Menu:menuid, const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width=0.0, bool:override=false)
{
	if(!ismenuactive(menuid) || override)
	{
		if(ismenuactive(menuid)) destroymenu(menuid);
		menuid = CreateMenu(title, columns, x, y, col1width, col2width);
	}
}

#define istextdrawactive e_istextdrawactive
stock bool:e_istextdrawactive(PlayerText:textdrawid)
{
	if(textdrawid != PlayerText:-1 || textdrawid != PlayerText:0) return true;
	return false;
}

#define destroyplayertextdraw e_destroyplayertextdraw
stock e_destroyplayertextdraw(playerid, &PlayerText:textdrawid)
{
	if(istextdrawactive(textdrawid)) PlayerTextDrawDestroy(playerid, textdrawid);
	textdrawid = PlayerText:-1;
}

#define createplayertextdraw e_createplayertextdraw
stock e_createplayertextdraw(playerid, &PlayerText:textdrawid, Float:x, Float:y, text[TEXTDRAW_TEXT_LIMIT], bool:override=false)
{
	if(!istextdrawactive(textdrawid) || override)
	{
		if(istextdrawactive(textdrawid)) destroyplayertextdraw(playerid, textdrawid);
		textdrawid = CreatePlayerTextDraw(playerid, x, y, text);
	}
}

stock IsVehicleModelBicycle(modelid)
{
	switch (modelid) {case 481, 509, 510: return true;}
	return false;
}

stock IsVehicleModelBike(modelid)
{
	switch (modelid) {case 448, 461, 462, 463, 468, 471, 521, 523, 522, 581, 586: return true;}
	return false;
}

stock IsVehicleModelHelicopter(modelid)
{
	switch (modelid) {case 417, 425, 447, 469, 487, 488, 497, 548, 563: return true;}
	return false;
}

stock IsVehicleModelPlane(modelid)
{
	switch (modelid) {case 460, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return true;}
	return false;
}

stock IsVehicleModelAircraft(modelid)
{
	if (IsVehicleModelHelicopter(modelid) || IsVehicleModelPlane(modelid)) return true;
	return false;
}

stock IsVehicleModelBoat(modelid)
{
	switch (modelid) {case 430, 446, 452, 454, 453, 472, 473, 484, 493, 595: return true;}
	return false;
}

stock IsVehicleTrailer(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {case 435, 450, 584, 591, 606, 607, 608, 610, 611: return true;}
	return false;
}

stock GetPlayerFacingAngleFix(playerid, &Float:ang)
{
	if (IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), ang);
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










