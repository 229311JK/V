#include "V.h"


const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;

RTC_DATA_ATTR uint8_t vfaceNum;   

void V::drawWatchFace()   {
    
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    drawTime();
    drawDate();
    drawBattery();
}
void V::drawTime()  {

    // Watchface time change structure...
 if (currentTime.Minute % 60 == 0 || currentTime.Minute % 60 == 30)  { 
  vfaceNum = (0);
    } else {
  vfaceNum = (1);
    }

 switch(vfaceNum) {

case 0:
      display.drawBitmap(0, 22, V_Reaper, 80, 80, GxEPD_WHITE);
    break;

case 1: 
      display.drawBitmap(0, 0, V_Main, 200, 200, GxEPD_WHITE);
    break;
 }

      //  Time settings...
    display.setFont(&SerifBold30);
    display.setCursor(35, 145);
      
    int displayHour;
    if(HOUR_12_24==12)  {
      displayHour = ((currentTime.Hour+11)%12)+1;
    } else {
      displayHour = currentTime.Hour;
    }
    if(displayHour < 10)  {
        display.print("0");
    }
    display.print(displayHour);
    display.print(":");
    if(currentTime.Minute < 10) {
        display.print("0");
    }
    display.println(currentTime.Minute);
}

void V::drawDate()    {
    display.setFont(&SerifBold22);

      int16_t  x1, y1;
      uint16_t w, h;

      String monthStr = String(currentTime.Month);
      String dayStr = String(currentTime.Day);

      monthStr = currentTime.Month < 10 ? "" + monthStr : monthStr;
      dayStr = currentTime.Day < 10 ? "" + dayStr : dayStr;
      String dateStr = monthStr + "/" + dayStr;

    display.getTextBounds(String(dateStr), 0, 0, &x1, &y1, &w, &h);
    display.setCursor(110 - w/2, 88);
    display.println(String(dateStr));

}

void V::drawBattery()   {
    display.drawBitmap(154, 13, battery, 37, 21, GxEPD_WHITE);
    display.fillRect(159, 18, 27, BATTERY_SEGMENT_HEIGHT, GxEPD_BLACK);
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
        if(VBAT > 4.1){
        batteryLevel = 3;
    }
        else if(VBAT > 3.95 && VBAT <= 4.1){
        batteryLevel = 2;
    }
        else if(VBAT > 3.80 && VBAT <= 3.95){
        batteryLevel = 1;
    }
        else if(VBAT <= 3.80){
        batteryLevel = 0;
    }

      for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
          display.fillRect(159 + (batterySegments * BATTERY_SEGMENT_SPACING), 18, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, GxEPD_WHITE);
    }
}