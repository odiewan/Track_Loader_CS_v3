# 1 "C:\\Users\\Odie\\source\\repos\\Arduino Projects\\Track_Loader_CS_v3\\Track_Loader_CS_v3\\Track_Loader_CS_v3.ino"


# 4 "C:\\Users\\Odie\\source\\repos\\Arduino Projects\\Track_Loader_CS_v3\\Track_Loader_CS_v3\\Track_Loader_CS_v3.ino" 2

# 6 "C:\\Users\\Odie\\source\\repos\\Arduino Projects\\Track_Loader_CS_v3\\Track_Loader_CS_v3\\Track_Loader_CS_v3.ino" 2
// #include <abstractLIS3MDL.h>
# 8 "C:\\Users\\Odie\\source\\repos\\Arduino Projects\\Track_Loader_CS_v3\\Track_Loader_CS_v3\\Track_Loader_CS_v3.ino" 2
// #include <rxToSrvo.h>
# 29 "C:\\Users\\Odie\\source\\repos\\Arduino Projects\\Track_Loader_CS_v3\\Track_Loader_CS_v3\\Track_Loader_CS_v3.ino"
String AppTitle;
String AppVersion;

char ledState = 0;
int icount = 0;
int toggle = 0;
int serialOk = 0;
char imuOK = 0;
int imuX;
int imuY;
int imuZ;
float azim;
float dAzim;
float dAzim0;
float azim0;
uint8_t rxVal00;
uint8_t rxVal01;
uint8_t rxVal02;
// abstractLIS3MDL *lis3mdl;

PWMServo svoOut00;
PWMServo rxChanIn00;
PWMServo rxChanIn01;
PWMServo rxChanIn02;

// rxToSrvo *rtsRud;
// rxToSrvo *rtsEle;
// rxToSrvo *rtsAil;
// rxToSrvo *rtsThr;

//-----------------------------------------------------------------------------
void serPringCompassObj() {

  if(imuOK) {

    // serPrntVNL("X", imuX);
    // serPrntVNL("Y", imuY);
    // serPrntVNL("Z", imuZ);

    serPrntVNL("Azim:", azim);
    serPrntVNL("dAzim:", dAzim);
    serPrntVNL("dAzim0:", dAzim0);
    // serPrintN();
  }
}

// //-----------------------------------------------------------------------------
// void serPrintRtsObjTelem(rxToSrvo &rts)
// {
//   serPrnt("<");
//   // serPrnt(":" + rts.rtsName);
//   // serPrintIntN("RxPin", rts.rtsRxInPin);
//   // serPrintIntN("SvoPin", rts.rtsSvoOutPin);

//   serPrntVNL(rts.rtsName, rts.rtsRxVal);
//   // serPrintFltN("Gain", rts.rtsGain);
//   // serPrintIntN("Offset", rts.rtsOffset);
//   // serPrintIntN("Dir", rts.rtsDir);
//   // serPrintIntN("Center", rts.rtsSvoCenter);
//   serPrntVNL(">Src", rts.rtsSvoCmdPreMix);
//   serPrntVNL("+Mix", rts.rtsMixComponent);
//   serPrntVNL("=Cmd", rts.rtsSvoCmd, "> ");

// }

//-----------------------------------------------------------------------------
void initSerial() {
  int tmr = 0;
  Serial.begin(9600);
  tmr = 3;
  while (tmr > 0 && serialOk == 0)
  {
    if (Serial)
      serialOk = 1;
    delay(1000);

    digitalWrite((13) /* 13 */, toggle);
    tmr--;
  }
  serPrntNL("Serial Ready");
  Serial.println(AppTitle);
  Serial.println(AppVersion);
}

//-----------------------------------------------------------------------------
void setup()
{
  ledState = 0;
  icount = 0;

  AppTitle = "Track Loader CS v3";
  AppVersion = "v0.0.1";

  pinMode((13) /* 13 */, 1);
  pinMode(23 /*---El   Th*/, 0);
  pinMode(22 /*---     Ail*/, 0);
  pinMode(21 /*---Rud  Elev*/, 0);

  initSerial();

  svoOut00.attach(3 /*---*/);

  // rxChanIn00.attach(RX_CH0_PIN);
  // rxChanIn00.attach(RX_CH1_PIN);
  // rxChanIn00.attach(RX_CH2_PIN);

  // rtsThr = new rxToSrvo("Thr", RX_CH0_PIN, SVO_3_PIN, 1);
  // rtsAil = new rxToSrvo("Ail", RX_CH1_PIN, SVO_0_PIN, 1);
  // rtsEle = new rxToSrvo("Ele", RX_CH2_PIN, SVO_1_PIN, 1);
  // rtsRud = new rxToSrvo("Rud", RX_CH3_PIN, SVO_2_PIN, 1);
  // rtsThr = new rxToSrvo("Thr", RX_CH0_PIN, SVO_3_PIN, SVO_CMD_GAIN_INV, SVO_CMD_OFFSET, 1);
  // rtsAil = new rxToSrvo("Ail", RX_CH1_PIN, SVO_0_PIN, SVO_CMD_GAIN_INV, SVO_CMD_OFFSET, 1);
  // rtsEle = new rxToSrvo("Ele", RX_CH2_PIN, SVO_1_PIN, SVO_CMD_GAIN_INV, SVO_CMD_OFFSET, 1);
  // rtsRud = new rxToSrvo("Rud", RX_CH3_PIN, SVO_2_PIN, SVO_CMD_GAIN_INV, SVO_CMD_OFFSET, 1);

  // lis3mdl = new abstractLIS3MDL();
  // imuOK = lis3mdl->alsStatus;
}


//-----------------------------------------------------------------------------
uint8_t isNearValue(unsigned long valIn, unsigned long trgVal)
{
  unsigned long minTol = trgVal - (100 / 2);
  unsigned long maxTol = trgVal + (100 / 2);

  if (valIn > minTol && valIn < maxTol)
    return 1;
  else
    return 0;
}

//-----------------------------------------------------------------
void taskIMU()
{
  // if (imuOK)
  // {
  //   static float azimShadow = 0;
  //   static float tempAz = 0;
  //   lis3mdl->readXYZ(); // get X Y and Z data at once
  //   imuX = lis3mdl->alsX;
  //   imuY = lis3mdl->alsY;
  //   imuZ = lis3mdl->alsZ;
  //   tempAz = lis3mdl->calcHeading();
  //   azim = -1 * tempAz;
  //   dAzim = azim - azimShadow;
  //   dAzim0 = azim - azim0;

  //   if (icount == 0)
  //     azim0 = azim;

  //   azimShadow = azim;
  // }
}

//-----------------------------------------------------------------------------
void loop()
{


  int tempThr = 0;
  int tempAil = 0;
  int tempEle = 0;
  int tempRud = 0;

  taskIMU();
  rxVal00 = pulseIn(23 /*---El   Th*/, 1, 25);
  rxVal01 = pulseIn(22 /*---     Ail*/, 1, 25);
  rxVal02 = pulseIn(21 /*---Rud  Elev*/, 1, 25);

  if (icount % 10 == 0) {
    serPrntV("i", icount);

    // serPrintRtsObjTelem(*rtsRud);
    // serPrintRtsObjTelem(*rtsEle);
    // serPrintRtsObjTelem(*rtsAil);
    // serPrintRtsObjTelem(*rtsThr);

    // Serial.print(" C:");
    // Serial.print(isNearValue(ch0Val, PULSE_MID));
    // serPrintChar("L", ledState);

    // serPringCompassObj();
    serPrntV("rxVal00:", rxVal00, ">");
    serPrntV("rxVal01:", rxVal01, ">");
    serPrntVNL("rxVal02:", rxVal02, ">");
  }

  // if(isNearValue(ch0Val, PULSE_POS0)) {
  //   ledState = 0;
  // }
  // else if(isNearValue(ch0Val, PULSE_POS1)) {
  //   ledState = 127;

  // }
  // else if(isNearValue(ch0Val, PULSE_POS2)) {
  //   ledState = 255;
  //   // if(i % 6 == 0)
  //   //   ledState = 0;
  //   // else
  //   //   ledState = 1;
  // }
  // else
  //   ledState = 0;

  // analogWrite(STAT_OUT_PIN, ledState);

  // tempThr = rtsThr->processChanR();
  // tempEle = rtsEle->processChanR();
  // tempAil = rtsAil->processChanR();
  // tempRud = rtsRud->processChanR();

  // rtsEle->applyMix(tempAil);
  // rtsAil->applyMix(-tempEle);

  icount++;
}
