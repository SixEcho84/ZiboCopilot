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

#include "PowerUpProcedure.h"
#include "DataRefList.h"

int PowerUpProcedure::powerUpProcedure(int stage)
{
	if (stage == 0) { //BATTERY ON AND COVER
		XPLMCommandOnce(XPLMFindCommand("sim/electrical/battery_1_on"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/button_switch_cover02"));
		XPLMSetDataf(XPLMFindDataRef(DataRefList::dataRefList[32]), 1);
		return 1;
	}
	else if (stage == 1) { //STANDBY POWER ON
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/switch/standby_bat_on"));
		//XPLMCommandOnce(XPLMFindCommand("laminar/B738/button_switch_cover03"));
		return 1;
	}
	else if (stage == 2 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[28])) == 1) { //GPU ON
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/gpu_dn"));
		return 1;
	}
	else if (stage == 3) // LEFT IRS TO NAV
	{
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[0])) == 3)
			XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_L_left"));
		else
			while (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[0])) != 2) {
				XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_L_right"));
			}
		return 1;
	}
	else if (stage == 4)  // RIGHT IRS TO NAV
	{
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[1])) == 3)
			XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_R_left"));
		else
			while (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[1])) != 2) {
				XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_R_right"));
			}
		return 1;
	}

	else if (stage == 5) { //IRS DISPLAY
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_dspl_sel_right"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_dspl_sel_right"));
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/irs_dspl_sel_right"));
		return 1;
	}

	else if (stage == 6) { //END
		XPLMSpeakString("Powerup Procedures Completed");
		return 2;
	}

	return 0;
}
