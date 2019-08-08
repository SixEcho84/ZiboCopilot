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

#include "EngineStartProcedure.h"
#include "DataRefList.h"

int EngineStartProcedure::engineStartProcedure(int stage)
{
	if (stage == 0) { //PACK 1 OFF
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/l_pack_up"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/l_pack_up"));
		return 1;
	}
	else if (stage == 1) { //PACK 2 OFF
		Sleep(500);
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/r_pack_up"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/r_pack_up"));
		return 1;
	}
	else if (stage == 2) { //BCL ON
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[21])) == 0)
		{
			Sleep(1200);
			XPLMCommandOnce(XPLMFindCommand("sim/lights/beacon_lights_toggle"));
		}
		return 1;
	}
	else if (stage == 3) { //END
		Sleep(500);
		XPLMSpeakString("Engine Ready for Startup");
		return 2;
	}

	return 0;
}

int EngineStartProcedure::startEng2(int stage)
{

	if (stage == 0) {
		XPLMSpeakString("Starting Right Engine");
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/knob/eng2_start_left"));
		return 1;
	}
	else if (stage == 1 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[30])) == 0) { //CALLOUT CUTOUT
		XPLMSpeakString("Starter Cutout");
		return 2;
	}
	return 0;
}

int EngineStartProcedure::startEng1(int stage)
{

	if (stage == 0) {
		XPLMSpeakString("Starting Left Engine");
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/knob/eng1_start_left"));
		return 1;
	}
	else if (stage == 1 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[31])) == 0) { //CALLOUT CUTOUT
		XPLMSpeakString("Starter Cutout");
		return 2;
	}
	return 0;
}