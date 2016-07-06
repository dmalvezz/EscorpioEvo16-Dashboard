
#include "StrategySettings.h"
#include "ConsoleForm.h"

void StrategySettingsClass::init(){
	loadStrategy();
	loadGPSSettings();
}

void StrategySettingsClass::loadGPSSettings(){
	Configuration cfg;
	float lat, lon, radius, time, space;
	int isReference;

	if (cfg.loadFromFile(GPS_CONFIG_FILE) == FILE_VALID){
		gpsWayPoint.resize(cfg.getPropertyCount() / WAYPOINT);
		for (int i = 0; i<gpsWayPoint.getCapacity(); i++){
			lat = cfg[WAYPOINT * i + WAY_LAT].asFloat();
			lon = cfg[WAYPOINT * i + WAY_LON].asFloat();
			radius = cfg[WAYPOINT * i + WAY_RAD].asFloat();
			space = cfg[WAYPOINT * i + WAY_DIST].asFloat();
			time = cfg[WAYPOINT * i + WAY_TIME].asFloat();
			isReference = cfg[WAYPOINT * i + WAY_REF].asInt();
			gpsWayPoint[i].init(lat, lon, radius, time, space, (isReference == 0) ? false : true);
		}
	}
	else{
		consoleForm.println(cfg.getErrorMsg());
		Log.assert(false, cfg.getErrorMsg());
	}
}

void StrategySettingsClass::debugGPSSettings(){
	WayPoint w;

	Log.i(STRAT_TAG) << F("Waypoints: ") << gpsWayPoint.getCapacity() << Endl;
	for (int i = 0; i < gpsWayPoint.getCapacity(); i++){
		w = gpsWayPoint[i];

		Log.i(STRAT_TAG) << F("Waypoint ") << i << " "
			<< w.getLat() << " "
			<< w.getLon() << " "
			<< w.getRadius() << " "
			<< w.getSpaceReference() << " "
			<< w.getTime() << " "
			<< w.isReference() << Endl;
	}
	
}

void StrategySettingsClass::debugTrackSettings(){
	Log.i(STRAT_TAG) << trackData.trackLenght << " "
		<< trackData.trackFinish << " "
		<< trackData.raceLaps << " "
		<< trackData.raceTime << " "
		<< trackData.firstLapTime << " "
		<< trackData.generalLapTime << " "
		<< trackData.lastLapTime << Endl;
}


void StrategySettingsClass::loadStrategy(){
	Configuration cfg;

	if (cfg.loadFromFile(STRATEGY_CONFIG_FILE) == FILE_VALID){	
		//Load track data
		trackData.trackLenght = cfg.getProperty(TRACK_LENGHT).asInt();
		trackData.trackFinish= cfg.getProperty(TRACK_FINISH).asInt();

		trackData.raceLaps = cfg.getProperty(RACE_LAPS).asInt();
		trackData.raceTime = cfg.getProperty(RACE_TIME).asInt();

		trackData.firstLapTime = cfg.getProperty(T_FIRST_LAP).asInt();
		trackData.generalLapTime = cfg.getProperty(T_LAP).asInt();
		trackData.lastLapTime = cfg.getProperty(T_LAST_LAP).asInt();

		//Load lap
		loadLapProfile(STRATEGY_FIRSTLAP_FILE, firstLap, trackData.trackLenght + 1);
		consoleForm.println(F("First lap profile OK"));
		Log.i(STRAT_TAG) << F("First lap profile OK") << Endl;

		loadLapProfile(STRATEGY_FIRSTLAP_FILE, generalLap, trackData.trackLenght + 1);
		consoleForm.println(F("General lap profile OK"));
		Log.i(STRAT_TAG) << F("General lap profile OK") << Endl;

		loadLapProfile(STRATEGY_FIRSTLAP_FILE, lastLap, trackData.trackLenght + 1);
		consoleForm.println(F("Last lap profile OK"));
		Log.i(STRAT_TAG) << F("Last lap profile OK") << Endl;

	}
	else{
		consoleForm.println(cfg.getErrorMsg());
		Log.assert(false, cfg.getErrorMsg());
	}

}

void StrategySettingsClass::loadLapProfile(const char* filePath, LapProfile& profile, int len){
	if (SD.exists(filePath)){
		File config = SD.open(filePath, O_READ);
		if (config){
			config.setTimeout(0);

			config.readStringUntil(',');
			for (int i = 0; i < len; i++){
				profile.time[i] = config.readStringUntil(',').toInt();
			}

			config.readStringUntil('\n');

			config.readStringUntil(',');
			for (int i = 0; i < len; i++){
				profile.space[i] = config.readStringUntil(',').toInt();
			}
		}
		else{
			consoleForm.println(String(filePath) + F(" error on opening!"));
			Log.assert(false, String(filePath) + F(" error on opening!"));
		}

	}
	else{
		consoleForm.println(String(filePath) + F(" file not found!"));
		Log.assert(false, String(filePath) + F(" file not found!"));
	}
}

StrategySettingsClass strategySettings;
