#define DCSBIOS_IRQ_SERIAL
#include <DcsBios.h>
#define MIDPOINT 32774

int LEDBrightness = 10;

void onAcftNameChange(char* newValue) {
  // Change of Aircraft
  DcsBios::resetAllStates();
}
DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);

unsigned int leftMap(unsigned int dcsValue)
{
  if( dcsValue >= MIDPOINT ) {
    return 0; // Gauge is right
  }

  return map(dcsValue, MIDPOINT, 0, 0, 50);
}

unsigned int rightMap(unsigned int dcsValue)
{
  if( dcsValue <= MIDPOINT ) {
    return 0; // Gauge is left
  }

  return map(dcsValue, MIDPOINT, 2*MIDPOINT, 0, 50);
}

DcsBios::Dimmer LpltCompSyncNeedle(0x1340, 6, &leftMap);
DcsBios::Dimmer RpltCompSyncNeedle(0x1340, 5, &rightMap);
DcsBios::RotaryEncoder pltAhrsHemisphere("PLT_AHRS_HEMISPHERE", "DEC", "INC", 4, 2);
DcsBios::Switch3Pos pltAhrsMode("PLT_AHRS_MODE", 8, 7);
DcsBios::Switch2Pos pltAhrsHdgPush("PLT_AHRS_HDG_PUSH", 12);
DcsBios::Potentiometer pltAhrsHdgKnob("PLT_AHRS_HDG_KNOB", A6);
DcsBios::Potentiometer pltAhrsLat("PLT_AHRS_LAT", A7);

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
DcsBios::Switch2Pos pltCanopyJett("PLT_CANOPY_JETT", 14);

unsigned int FloodMap(unsigned int dcsValue)
{
    if( dcsValue == 0 )
        return 0;
    else if((dcsValue > 13000) & (dcsValue < 17000))
        return 128;
    else // if( dcsValue > 18000)
        return 255;
}
DcsBios::Dimmer internalFloodRedL(0x14be, 3, FloodMap);

  void onPltLightIntentConsoleChange(unsigned int newValue) {
    LEDBrightness = newValue * 31;
}
DcsBios::IntegerBuffer pltLightIntentConsoleBuffer(0x121e, 0xf000, 12, onPltLightIntentConsoleChange);

void setup() {
  pinMode(9, OUTPUT);
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
  analogWrite(9, LEDBrightness);
}
