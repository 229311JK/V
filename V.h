#ifndef V_H
#define V_H

#include <Watchy.h>
#include "SerifBold22.h"
#include "SerifBold30.h"
#include "V_Face.h"
#include "Vcons.h"

          class V : public Watchy   {
          using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawDate();
        void drawTime();
        void drawBattery();
  };

#endif
