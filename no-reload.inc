// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_rapid_fire
	#undef _inc_rapid_fire
#endif
// custom include-guard to ensure we don't duplicate
#if defined _rapid_fire_included
	#endinput
#endif
#define _rapid_fire_included

#include <a_samp>


#define MAX_NORELOAD_INFRACTIONS (1)

forward OnAntiCheatNoReload(playerid, roundsfired);

static WeaponMagSizes[17] = {
	// Pistols
	017, // 22 M9 x2 WHEN DUAL
	017, // 23 M9 SD
	007, // 24 Desert Eagle

	// Shotgun
	001, // 25 Shotgun
	002, // 26 Sawnoff x2 WHEN DUAL
	007, // 27 Spas 12

	// Automatic
	050, // 28 Mac 10 x2 WHEN DUAL
	030, // 29 MP5
	030, // 30 AK-47
	050, // 31 M16
	050, // 32 Tec 9 x2 WHEN DUAL

	// Rifle
	001, // 33 Rifle
	001, // 34 Sniper

	// Heavy
	001, // 35 RPG
	001, // 36 Heatseeker
	500, // 37 Flamer
	500 // 38 Minigun
};

static
 	infractions[MAX_PLAYERS],
	shotCounter[MAX_PLAYERS],
	skillLevel[MAX_PLAYERS] = {999, ...};


public OnPlayerUpdate(playerid) {
	static lastweapon;
	new currentweapon = GetPlayerWeapon(playerid);

	if(lastweapon != currentweapon) {
		// Player reloaded by quick-switching
		shotCounter[playerid] = 0;
		lastweapon = currentweapon;
	}

	#if defined AC_NR_OnPlayerUpdate
		return AC_NR_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate AC_NR_OnPlayerUpdate
#if defined AC_NR_OnPlayerUpdate
	forward AC_NR_OnPlayerUpdate(playerid);
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	// If the server isn't performing well, updates to this callback will be
	// delayed and could stack up resulting in a sudden mass-call of this
	// callback which can cause false positives.
	// More research needed into this though as player lag can also cause this,
	// possibly a ping check or packet loss check would work.
	if(GetServerTickRate() < 100) {
		return 1;
	}

	new
		magsize = WeaponMagSizes[weaponid - 22],
		weaponstate = GetPlayerWeaponState(playerid);

	shotCounter[playerid]++;

	// Check if the player is using dual weapons
	if(skillLevel[playerid] == 999) {
		if(weaponid == 22 || weaponid == 26 || weaponid == 28 || weaponid == 32) {
			magsize *= 2;
		}
	}

	// If the amount of fired shots exceeds the magazine size for the weapon
	// the player is probably using an infinite ammo mod.
	// Ignores weapons that have a magsize of 1 (shotgun, rifles)
	if(shotCounter[playerid] == magsize && magsize > 1) {
		if(weaponstate != 1) {
			infractions[playerid]++;

			if(infractions[playerid] == MAX_NORELOAD_INFRACTIONS) {
				CallLocalFunction("OnAntiCheatNoReload", "ii", playerid, shotCounter[playerid]);
			}
		} else {
			shotCounter[playerid] = 0;
		}

		return 0;
	}

	#if defined AC_NR_OnPlayerWeaponShot
		return AC_NR_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot AC_NR_OnPlayerWeaponShot
#if defined AC_NR_OnPlayerWeaponShot
	forward AC_NR_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif


stock AC_NR_SetPlayerSkillLevel(playerid, skill, level) {
	skillLevel[playerid] = level;

	return SetPlayerSkillLevel(playerid, skill, level);
}
#if defined _ALS_SetPlayerSkillLevel
	#undef SetPlayerSkillLevel
#else
	#define _ALS_SetPlayerSkillLevel
#endif
#define SetPlayerSkillLevel AC_NR_SetPlayerSkillLevel
