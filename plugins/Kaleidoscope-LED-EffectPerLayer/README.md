# DefaultLayerLEDEffect

This plugin makes it possible to set a specific LED mode on all but the default
layer.

## Using the extension

To use the plugin, one needs to include the header, and activate the plugin.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-ActiveLayerColor.h"

KALEIDOSCOPE_INIT_PLUGINS(LEDControl,
                          LEDRainbowWaveEffect,
                          LEDActiveLayerColorEffect);

void setup () {
  Kaleidoscope.setup ();

  /* LED mode plugins setup */

  // Tell the plugin what the default layer is
  DefaultLayerLEDEffect.setDefaultLayer(0);
  // Tell the plugin to use ActiveLayerColor on all other layers
  DefaultLayerLEDEffect.setStaticLEDMode(LEDActiveLayerColorEffect);
  // Activate RainbowWaveEffect
  LEDRainbowWaveEffect.activate();
}
```

## Plugin methods

### setStaticLEDMode(static_led_mode);

> Sets the led mode to use on all but the primary layer by referencing the
> plugin.

### setStaticLEDMode(static_led_mode_index);

> Sets the led mode to use on all but the primary layer by led mode index.
