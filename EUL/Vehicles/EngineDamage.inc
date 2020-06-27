// Functions
/*
	- TripMeterStart
	- TripMeterPause
	- TripMeterResume
	- ResetTripMeter
	
	- GetVehicleTripKMs
	- SetVehicleTripKMs
	
	- IsTripMeterStarted
	- IsTripMeterPaused
	
	- DamageEngine
	- RepairEngine

	- SetEngineGrade
	- SetEngineHealth
	- GetEngineGrade
	- GetEngineHealth
*/
#IF !DEFINED sVehicle_File
	#define Veh_File "SCars/%d.ini"
#ENDIF

#IF !DEFINED INI_Exists(%0)
	#define INI_Exists(%0)  fexist(%0)
#ENDIF

main()
{
	new change[4], vFile[45], model;

	for(new i = 400; i <= 611; i++)
	{
	    model = i;
	    format(change, sizeof(change), "%d", model);

	    format(vFile, 45, Veh_File, change);
	    if(INI_Exists(vFile)) INI_ParseFile(vFile, "LoadEngines", .bExtra = true, .extra = model);
	    else continue;
	}
	return 1;
}

// Defines

enum data
{
	TopSpeed,
	EngineType,
	Price,
	Gears,
	First,
	Second,
	Third,
	Fourth,
	Fifth
}
new Float:vehData[211][Data];

forward TrackKMs(vehicleid);
forward RunEngine(vehicleid);
forward LoadEngines(model, name[], value[]);

#define SpeedMultiplier 140.0

#IF !DEFINED PRESSED
	#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#ENDIF

#IF !DEFINED RELEASED
	#define RELEASED(%0) \
		(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#ENDIF

// Global Variables

new Float:EngineGrade[MAX_VEHICLES];

new Float:EngineHealth[MAX_VEHICLES];

new Float:Kilo[MAX_VEHICLES];

new Timer[MAX_VEHICLES];

new engineTimer[MAX_VEHICLES];

new rpm[MAX_VEHICLES];

new bool:Paused[MAX_VEHICLES];

new bool:standard = true;

new bool:enginesLoaded;

stock Float:GetVehicleMPH(vehicleid)
{
	new Float:x, Float:y, Float:z, Float:ret;

	GetVehicleVelocity(vehicleid, x, y, z);
	ret = floatround(floatsqroot(x * x + y * y + z * z) * SpeedMultiplier * 1);
	return ret;
}

stock Float:GetVehicleKPH(vehicleid)
{
	new Float:x, Float:y, Float:z, Float:ret;
	GetVehicleVelocity(vehicleid, x, y, z);
	ret = floatround(floatsqroot(x * x + y * y + z * z) * SpeedMultiplier * 1.6);
	return ret;
}

stock STripMeterStart(vehicleid)
{
	Kilo[vehicleid] = 0;
	Paused[vehicleid] = false;
	Timer[vehicleid] = SetTimerEx("TrackKMs", 1000, 1, "i", vehicleid);
	return 1;
}

stock TripMeterPause(vehicleid)
{
	KillTimer(Timer[vehicleid]);
	Paused[vehicleid] = true;
	return 1;
}

stock TripMeterResume(vehicleid)
{
	Timer[vehicleid] = SetTimerEx("TrackKMs", 1000, 1, "i", vehicleid);
	Paused[vehicleid] = false;
	return 1;
}

stock bool:IsTripMeterStarted(vehicleid)
{
	if(Kilo[vehicleid] != 0 && Kilo[vehicleid] != -1) return true;
	else return false;
}

stock IsTripMeterPaused(vehicleid)
{
	return Paused[vehicleid];
}

stock ResetTripMeter(vehicleid)
{
	Kilo[vehicleid] = 0;
	return 1;
}
	
public TrackKMs(vehicleid)
{
	new Float:vel;
	
	vel = GetVehicleKPH(vehicleid);
	if(vel > 0)
	{
	    Kilo[vehicleid] = Kilo[vehicleid] + (vel / 3600);
	}
	return 1;
}

public RunEngine(vehicleid)
{
	new playerid, condition, Float:engineHealth, engine, lights, doors, objective, bool:driver = false, bonnet, boot, alarm;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine == 0)
	{
		KillTimer(engineTimer(vehicleid));
		return 0;
	}
	
	playerid = GetVehicleDriveID(vehicleid);
	GetEngineHealth(vehicleid, engineHealth);
	condition = DetermineRunningcondition(engineHealth);
	
	if(condition == 0) return 1;
	if(playerid != -1) driver = true;

	switch(condition)
	{
	    case 1:
	    {
	        if(driver)
	        {
				if(PRESSED == KEY_UP && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) rpm++;
				else if(PRESSED == KEY_DOWN) rpm += -2;
				else rpm--;
			}
		{
	}
}

public compressionCycle(vehicleid, stroke)
{
	switch(engineType
}

public LoadEngines(model, name[], value[])
{
	INI_Int("TopSpeed", vehData[model][TopSpeed]);
	INI_Int("EngineType", vehData[model][EngineType]);
	INI_Int("Price", vehData[model][Price]);
	INI_Int("Gears", vehData[model][Gears]);
	INI_Int("First", vehData[model][First);
	INI_Int("Second", vehData[model][Second);
	INI_Int("Third", vehData[model][Third);
	INI_Int("Fourth", vehData[model][Fourth);
	INI_Int("Fifth", vehData[model][Fifth]021);
	return 1;
}

// Stock Functions

stock startVehicle(vehicleid)
{
	new engine, doors, lights, bonnet, boot, alarm, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, 1, lights, alarm, dorrs, bonnet, boot, objective);
	engineTimer[vehicleid] = SetTimerEx("runEngine", 0, 1, "i", vehicleid);

stock Transmission(vehicleid)
{
	if(standard)
	{
	
	}
}

stock GetVehicleDriverID(vehicleid)
{
	for(new i = 0; i <= MAX_PLAYERS; i++)
	{
	    if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid) return i;
	}
	return -1;
}

stock DetermineRunningCondition(Float:engineHealth)
{
	if(engineHealth > 1500) return 0;
	if(engineHealth < 1300) return 1;
	if(engineHealth < 1100) return 2;
	if(engineHealth < 1000) return 3;
	if(engineHealth < 500) return 4;
	if(engineHealth < 200) return 5;
	if(engineHealth <= 0) return 6;
}

stock DamageEngine(vehicleid, Float:amount)
{
	EngineHealth[vehicleid] = EngineHealth[vehicleid] - amount;
	return 1;
}

stock RepairEngine(vehicleid, Float:amount)
{
	new Float:vHealth;
	
	EngineHealth[vehicleid] = EngineHealth[vehicleid] + vHealth;
	return 1;
}

stock SetEngineGrade(vehicleid, Float:amount)
{
	EngineGrade[vehicleid] = amount;
	return 1;
}

stock SetEngineHealth(vehicleid, Float:amount)
{
	EngineHealth[vehicleid] = amount;
	return 1;
}

stock Float:GetEngineGrade(vehicleid, &engineHealth)
{
	new Float:vHealth;

	vHealth = EngineGrade[vehicleid];
	
	return vHealth;
}

stock Float:GetEngineHealth(vehicleid)
{
	new Float:vHealth, string[128];
	
	format(string, sizeof(string), "%.2f", EngineHealth[vehicleid]);
	vHealth = strval(string);
	
	return vHealth;
}

stock Float:GetVehicleTripKMs(vehicleid)
{
	return Kilo[vehicleid];
}

stock SetVehicleTripKMs(vehicleid, amount)
{
	Kilo[vehicleid] = amount;
	return 1;
}
