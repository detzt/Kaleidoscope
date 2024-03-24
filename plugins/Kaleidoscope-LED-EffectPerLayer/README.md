# LEDEffectPerLayer

This plugin allows you to configure a LED effect for each layer.

If an effect is set for a layer, it will be used when that layer is active.\
If no effect is set for a layer (value kUnsetLEDMode == -1), the default effect
will be used, which can be configured using the DefaultLEDModeConfig plugin.\
When you cycle through the LED effects using the next/previous led effect keys,
this applies to all layers that have no specific effect set.

## Using the extension

To use the plugin, one needs to include the header, and activate the plugin.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-Colormap.h"

KALEIDOSCOPE_INIT_PLUGINS(LEDControl,
                          LEDRainbowWaveEffect,
                          LEDColormap,
                          LEDEffectPerLayer);

void setup () {
  Kaleidoscope.setup ();

  /* LED mode plugins setup */

  // Tell the plugin to use the Colormap effect on all layers
  LEDEffectPerLayer.setLEDModeForAllLayers(ColormapEffect);
  // Set a specific effect for layer 1
  LEDEffectPerLayer.setLEDMode(1, LEDRainbowWaveEffect);
  // Unset the effect for the base layer to allow cycling through all effects
  LEDEffectPerLayer.setLEDMode(0, LEDEffectPerLayer.kUnsetLEDMode);
  // Activate the plugin
  LEDEffectPerLayer.activate();
}
```

## Plugin methods

### setLEDMode(layer, led_mode);

> Sets the led mode to use on the given layer by referencing the plugin.

### setLEDMode(layer, led_mode_index);

> Sets the led mode to use on the given layer by led mode index.
> Passing -1 as the led_mode_index will unset the effect for the layer.

### setLEDModeForAllLayers(led_mode);

> Sets the led mode to use on all layers by referencing the plugin.

### setLEDModeForAllLayers(led_mode_index);

> Sets the led mode to use on all layers by led mode index.
> Passing -1 as the led_mode_index will unset the effect for all layers.
