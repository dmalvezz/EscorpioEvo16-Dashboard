// PhoneInterface.h

#ifndef _PHONEINTERFACE_h
#define _PHONEINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ByteBuffer.h>
#include <Configuration.h>
#include <ConsoleForm.h>

#include "HWConfig.h"

#define PHONE_TAG	F("PHN")
#define PHONE_CFG_FILE	"PHONE.CFG"
#define PHONE_RX_BUFFER_SIZE	128

#define INFO_PACKET	"INF"
#define GPS_PACKET	"GPS"
#define ACC_PACKET	"ACC"
#define CALL_PACKET	"CALL"

#define CALL_CMD	"TEL:"
#define DEFAULT_PHONE_NUM F("+393663154577")

#pragma pack(push, 1)
typedef struct InfoData{
	char date[8];
	char time[8];
}InfoData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct GpsData{
	double latitude;
	double longitude;
	double altitude;
	double accuracy;
	double speed;
}GpsData;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct AccData{
	byte status;
	double x;
	double y;
	double z;
}AccData;
#pragma pack(pop)

//Events handler
typedef void(*GpsDataHandler)(GpsData&);
//typedef void(*AccelerometerDataHandler)(AccData&);


class PhoneInterfaceClass{

public:
	void init();
	void update();
	void call();

	void setGpsDataHandler(GpsDataHandler);

	boolean isCallActive(){ return callActive; }

	friend void onCallButtonPress(void* data);

private:
	enum Attr : byte{
		PHONE_NUM
	};

	boolean callActive;
	String phoneToCall;

	InfoData info;
	GpsData gps;
	AccData acc;

	GpsDataHandler gpsHandler;

	ByteBuffer rxBuffer;

	boolean parsePacket(const char* header, byte* buffer, int size);
};

extern PhoneInterfaceClass phoneInterface;


#endif

