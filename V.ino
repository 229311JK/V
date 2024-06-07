    
    // "V_Face" watchface 4-SQFMI Watchy; https://watchy.sqfmi.com/
    // "V.ino" created 5/25/24: Url:  https://github.com/229311JK/V
    // Watchy HW ver: 2.0;  ESP32 core ver: 2.0.16 
    // IDE ver: 2.3.2; CLI ver: 0.35.3.


#include "V.h"
#include "V_Settings.h"

V watchy(settings);

void setup()  {
    watchy.init();
    }

void loop() {}
