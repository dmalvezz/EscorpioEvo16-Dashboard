// DebugForm.h

#ifndef _DEBUGFORM_h
#define _DEBUGFORM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BMSInterface.h"
#include "CanInterface.h"
#include "ChannelsBuffer.h"
#include "DisplayInterface.h"
#include "HWConfig.h"
#include "LCDForm.h"
#include "PhoneInterface.h"

//Widget index
//Can
#define CAN_ON_BLUETOOTH_BUTTON	0
#define CAN_ON_SERIAL_BUTTON	1
#define CAN_STOP_BUTTON			2
//Driver
#define DRIVER_MAP_DIGIT		7
#define DRIVER_SETTING_BUTTON	12
//BMS
#define BMS_STATUS_STRING	3
#define CELLS_BARS			0
#define CELLS_BARS_NUM		12
#define CELLS_MAX_VOLT		4.2
#define BATTERY_V_DIGITS	6
#define BMS_DEBUG_BUTTON	14

class DebugFormClass : public LCDForm{

public:
	void init(Genie &genie);
	void update(Genie &genie);
	void onEvent(Genie& genie, genieFrame& evt);

	int getFormIndex(){ return 2; }

private:

};

extern DebugFormClass debugForm;


#endif

