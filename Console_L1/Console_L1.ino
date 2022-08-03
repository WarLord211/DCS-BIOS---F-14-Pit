
#define DCSBIOS_IRQ_SERIAL
#include <DcsBios.h>

void onAcftNameChange(char* newValue) {
  // Change of Aircraft
  DcsBios::resetAllStates();
}
DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);

unsigned int posLightsMap(unsigned int dcsValue)
{
    if( dcsValue == 0 )
        return 0;
    else if( dcsValue == 39321 )
        return 110;
    else // if( dcsValue == 65535 )
        return 255;
}
DcsBios::Dimmer extPositionLightsWingsD(0x14b6, 10, posLightsMap);
DcsBios::Dimmer extPositionLightsBodyD(0x14b4, 11, posLightsMap);
DcsBios::Switch2Pos pltHydHandPump("PLT_HYD_HAND_PUMP", 6);

const byte pltTacanDialOnesPins[10] = {7, 8, 9, 12, 14, 15, 16, 17, 18, 19};
DcsBios::SwitchMultiPos pltTacanDialOnes("PLT_TACAN_DIAL_ONES", pltTacanDialOnesPins, 10);

const byte pltTacanModePins[4] = {2, 3, 4, 5};
DcsBios::SwitchMultiPos pltTacanMode("PLT_TACAN_MODE", pltTacanModePins, 4);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
