#if APL
#if defined(__MACH__)
#include <Carbon/Carbon.h>
#endif
#endif
#include "XPLMMenus.h"
#include <cstdio>
#include <string>
#if IBM
#include <windows.h>
#endif
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMScenery.h"
#include "XPLMDataAccess.h"
#include <cstdlib>

using namespace std;

#include "DataRefList.h"
#include "BeforeTaxiProcedure.h"

int BeforeTaxiProcedure::beforeTaxiProcedure(int stage)
{
	if (stage == 0) {
		XPLMCommandBegin(XPLMFindCommand("laminar/B738/toggle_switch/gen2_dn"));
		return 1;
	}
	else if (stage == 1) {
		XPLMCommandEnd(XPLMFindCommand("laminar/B738/toggle_switch/gen2_dn"));
		return 1;
	}
	else if (stage == 2) {
		XPLMCommandBegin(XPLMFindCommand("laminar/B738/toggle_switch/gen1_dn"));
		return 1;
	}
	else if (stage == 3) {
		XPLMCommandEnd(XPLMFindCommand("laminar/B738/toggle_switch/gen1_dn"));
		return 1;
	}
	else if (stage == 4) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/knob/eng1_start_right"));
		return 1;
	}
	else if (stage == 5) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/knob/eng2_start_right"));
		return 1;
	}
	else if (stage == 6) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/spring_toggle_switch/APU_start_pos_up"));
		return 1;
	}
	else if (stage == 7) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/l_pack_dn"));
		return 1;
	}
	else if (stage == 8) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/iso_valve_up"));
		return 1;
	}
	else if (stage == 9) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/r_pack_dn"));
		return 1;
	}
	else if (stage == 10) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/bleed_air_apu"));
		return 1;
	}
	else if (stage == 11) {
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[24])) < 1)
			XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/fo_probes_pos"));
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[23])) < 1)
			XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/capt_probes_pos"));
		return 1;
	}
	else if (stage == 12) {
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/taxi_light_brightness_pos_dn"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/taxi_light_brightness_pos_dn"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/switch/rwy_light_left_on"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/switch/rwy_light_right_on"));
		return 1;
	}
	else if (stage == 13) { //SET T/O FLAPS
		
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[29])) == 1)
		{
			XPLMSetDataf(XPLMFindDataRef(DataRefList::dataRefList[26]), 0);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
		}

		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[29])) == 5)
		{
			XPLMSetDataf(XPLMFindDataRef(DataRefList::dataRefList[26]), 0);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
		}

		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[29])) == 15)
		{
			XPLMSetDataf(XPLMFindDataRef(DataRefList::dataRefList[26]), 0);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
			Sleep(500);
			XPLMCommandOnce(XPLMFindCommand("sim/flight_controls/flaps_down"));
		}			
		return 1;
	}
	else if (stage == 14) { //END
		XPLMSpeakString("Before Taxi Procedures Completed");
		return 2;
	}
	return 0;
}
