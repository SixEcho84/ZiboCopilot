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

#include "StartApuProcedure.h"
#include "DataRefList.h"

int StartApuProcedure::startApuProcedure(int stage)
{
	if (stage == 0) { //APU
		XPLMCommandOnce(XPLMFindCommand("laminar/B738/spring_toggle_switch/APU_start_pos_dn"));
		return 1;
	}
	else if (stage == 1)
	{
		XPLMCommandBegin(XPLMFindCommand("laminar/B738/spring_toggle_switch/APU_start_pos_dn"));
		return 1;
	}
	else if (stage == 2) // APU BUTTON RELEASE
	{
		XPLMCommandEnd(XPLMFindCommand("laminar/B738/spring_toggle_switch/APU_start_pos_dn"));
		return 1;
	}

	else if (stage == 3 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[25])) == 1) { //APU BLEED ON
		if (XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[20])) == 0)
			XPLMCommandOnce(XPLMFindCommand("laminar/B738/toggle_switch/bleed_air_apu"));
		return 1;
	}

	else if (stage == 4 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[25])) == 1) { //APU GEN 1 PRESS
		XPLMCommandBegin(XPLMFindCommand("laminar/B738/toggle_switch/apu_gen1_dn"));
		return 1;
	}
	else if (stage == 5) { //APU GEN 1 RELEASE
		XPLMCommandEnd(XPLMFindCommand("laminar/B738/toggle_switch/apu_gen1_dn"));
		return 1;
	}
	else if (stage == 6 && XPLMGetDatai(XPLMFindDataRef(DataRefList::dataRefList[25])) == 1) { //APU GEN 2 PRESS
		XPLMCommandBegin(XPLMFindCommand("laminar/B738/toggle_switch/apu_gen2_dn"));
		return 1;
	}
	else if (stage == 7) { //APU GEN 2 RELEASE
		XPLMCommandEnd(XPLMFindCommand("laminar/B738/toggle_switch/apu_gen2_dn"));
		return 1;
	}
	else if (stage == 8) { //END
			XPLMSpeakString("APU Start Completed");
		return 2;
	}

	return 0;
}
