
#define DCSBIOS_IRQ_SERIAL
#include <DcsBios.h>

int LEDBrightness = 10;

void onAcftNameChange(char* newValue) {
  // Change of Aircraft
  DcsBios::resetAllStates();
}
DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);

void onPltLightIntentConsoleChange(unsigned int newValue) {
    LEDBrightness = newValue * 31;
}
DcsBios::IntegerBuffer pltLightIntentConsoleBuffer(0x121e, 0xf000, 12, onPltLightIntentConsoleChange);

unsigned int FloodMap(unsigned int dcsValue)
{
    if( dcsValue == 0 )
        return 0;
    else if((dcsValue > 13000) & (dcsValue < 17000))
        return 128;
    else // if( dcsValue > 18000)
        return 255;
}
DcsBios::Dimmer internalFloodWhtL(0x14c0, 11, FloodMap);
DcsBios::Dimmer internalFloodRedL(0x14be, 6, FloodMap);
DcsBios::Switch2Pos pltEmergStoreJett("PLT_EMERG_STORE_JETT", 12);   
DcsBios::Potentiometer pltTacanVolume("PLT_TACAN_VOLUME", A7);

const byte pltTacanDialTensPins[13] = {2, 3, 4, 7, 8, 9, 10, 14, 15, 16, 17, 18, 19};
DcsBios::SwitchMultiPos pltTacanDialTens("PLT_TACAN_DIAL_TENS", pltTacanDialTensPins, 13);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
  analogWrite(5, LEDBrightness);
}
