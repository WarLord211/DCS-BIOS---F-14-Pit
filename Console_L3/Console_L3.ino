
#define DCSBIOS_IRQ_SERIAL
#include <DcsBios.h>

int LEDBrightness = 30;

void onAcftNameChange(char* newValue) {  // Change of Aircraft
  DcsBios::resetAllStates();
}
DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);

void onPltLightIntentConsoleChange(unsigned int newValue) {
    LEDBrightness = newValue * 31;
}
DcsBios::IntegerBuffer pltLightIntentConsoleBuffer(0x121e, 0xf000, 12, onPltLightIntentConsoleChange);

 DcsBios::Switch3Pos pltIcsFuncSel("PLT_ICS_FUNC_SEL", 4, 2);
 DcsBios::Switch3Pos pltIcsAmpSel("PLT_ICS_AMP_SEL", 7, 8);
 DcsBios::Potentiometer pltIcsVol("PLT_ICS_VOL", A7);
 DcsBios::Switch2Pos pltParkBrake("PLT_PARK_BRAKE", 12, true);
 //DcsBios::Switch2Pos pltLaunchbarAbort("PLT_LAUNCHBAR_ABORT", 6);
 DcsBios::SwitchWithCover2Pos pltLaunchbarAbort("PLT_LAUNCHBAR_ABORT", "PLT_LAUNCHBAR_ABORT_COVER", 6);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
  analogWrite(3, LEDBrightness);
  analogWrite(5, LEDBrightness);
}
