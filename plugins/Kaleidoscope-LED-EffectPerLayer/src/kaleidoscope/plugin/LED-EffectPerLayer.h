/* Kaleidoscope-LED-EffectPerLayer - A Kaleidoscope plugin that allows setting
 * a LED effect for each layer.
 * Copyright (C) 2024 Aaron Grabowy
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h> // for uint8_t

#include "kaleidoscope/event_handler_result.h"    // for EventHandlerResult
#include "kaleidoscope/plugin/LEDControl.h"       // for LEDControl
#include "kaleidoscope/plugin/LEDModeInterface.h" // for LEDModeInterface

namespace kaleidoscope {
namespace plugin {

class LEDEffectPerLayer : public kaleidoscope::Plugin {
public:
  // The value that signifies that the LED mode on a layer is unset.
  static const int8_t kUnsetLEDMode = -1;

  LEDEffectPerLayer();
  void enable();
  void disable();
  bool active();
  void setLEDMode(uint8_t layer, int8_t led_mode_index);
  void setLEDMode(uint8_t layer, LEDModeInterface &led_mode);
  void setLEDModeForAllLayers(int8_t led_mode_index);
  void setLEDModeForAllLayers(LEDModeInterface &led_mode);

  EventHandlerResult onLayerChange();

private:
  // The configured LED mode for each layer.
  int8_t layer_led_mode_indices_[MAX_ACTIVE_LAYERS];
  // The LED mode index on unset layers.
  uint8_t last_active_led_mode_index_;
  // The previously active layer.
  uint8_t last_active_layer_;
  // The plugin status.
  bool enabled_ = false;

  uint8_t getIndexOfLEDMode(LEDModeInterface &led_mode);
};

} // namespace plugin
} // namespace kaleidoscope

extern kaleidoscope::plugin::LEDEffectPerLayer LEDEffectPerLayer;
