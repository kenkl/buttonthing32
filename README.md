# buttonthing32

This is a kind of fork of the [buttonthing](https://github.com/kenkl/buttonthing) project adapted for the [Adafruit HUZZAH32 ESP32 Feather Board](https://www.adafruit.com/product/3405). See the original [buttonthing](https://github.com/kenkl/buttonthing) project for details, but in short, buttonthing32 calls predefined scripts in my [lights](https://github.com/kenkl/lights) application to trigger various scenes created by the Hue lights in my home.

Adapting buttonthings to the ESP32 platform is remarkably simple; the only major change required is the inclusion of the correct WiFi library. On ESP8266, we include ESP8266WiFi.h, but on ESP32, the more general WiFi library is used instead:

```C++
#include <WiFi.h>
```

I've cleared out the 'extra' buttons and cleaned up some other bits and pieces, but the core of this version is effectively identical to [buttonthing](https://github.com/kenkl/buttonthing). As such, this is simply a demonstration of another way to implement a buttonthing-like thing.
