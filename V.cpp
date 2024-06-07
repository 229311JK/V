#include "V.h"


const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;

void V::drawWatchFace()   {
  if(currentTime.Minute >= 29)    {
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, V_Face, 200, 200, GxEPD_WHITEK);
    }
    
  
  if(currentTime.Minute <= 31)    {
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, V_Face, 200, 200, GxEPD_WHITE);
    }
    drawDate();
    drawTime();
    drawBattery();

    for (uint8_t i=0; i<3; i++) {
        // Reduce ghosting
        display.display(true);
    }
}

void V::drawDate()    {
    display.setFont(&SerifBold22);
    display.setTextColor(GxEPD_WHITE);

      int16_t  x1, y1;
      uint16_t w, h;

      String monthStr = String(currentTime.Month);
      String dayStr = String(currentTime.Day);

      monthStr = currentTime.Month < 10 ? "" + monthStr : monthStr;
      dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
      String dateStr = monthStr + "/" + dayStr;

    display.getTextBounds(String(dateStr), 0, 0, &x1, &y1, &w, &h);
    display.setCursor(110 - w/2, 88);
    display.println(String(dateStr));

    }

void V::drawTime()  {
    display.setFont(&SerifBold30);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(35, 145);

    int displayHour;

        if(HOUR_12_24==12)  {
           displayHour = ((currentTime.Hour+11)%12)+1;
      } else {
           displayHour = currentTime.Hour;
    }
        if (currentTime.Hour < 10) {
            display.print("0");
    }
    display.print(currentTime.Hour);
    display.print(":");

        if (currentTime.Minute < 10) {
            display.print("0");
    }
    display.print(currentTime.Minute);
  }

void V::drawBattery()   {
    display.drawBitmap(154, 13, battery, 37, 21, GxEPD_BLACK);
    display.fillRect(159, 18, 27, BATTERY_SEGMENT_HEIGHT, GxEPD_WHITE);
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
        if(VBAT > 4.0){
        batteryLevel = 3;
    }
        else if(VBAT > 3.90 && VBAT <= 4.0){
        batteryLevel = 2;
    }
        else if(VBAT > 3.80 && VBAT <= 3.90){
        batteryLevel = 1;
    }
        else if(VBAT <= 3.80){
        batteryLevel = 0;
    }

      for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
          display.fillRect(159 + (batterySegments * BATTERY_SEGMENT_SPACING), 18, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, GxEPD_BLACK);
    }
}
