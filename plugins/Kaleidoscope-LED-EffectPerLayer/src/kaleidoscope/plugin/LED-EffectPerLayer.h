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

#include "kaleidoscope/KeyAddr.h"                 // for KeyAddr
#include "kaleidoscope/event_handler_result.h"    // for EventHandlerResult
#include "kaleidoscope/plugin/LEDControl.h"       // for LEDControl
#include "kaleidoscope/plugin/LEDModeInterface.h" // for LEDModeInterface

namespace kaleidoscope {
namespace plugin {

class LEDEffectPerLayer : public kaleidoscope::Plugin {
public:
  LEDEffectPerLayer();
  void enable();
  void disable();
  bool active();
  void setDefaultLayer(uint8_t layer);
  void setStaticLEDMode(LEDModeInterface &static_led_mode);
  void setStaticLEDMode(uint8_t static_led_mode_index);

  EventHandlerResult onLayerChange();

private:
  uint8_t default_layer_;
  uint8_t last_active_led_mode_index_;
  uint8_t static_led_mode_index_;
  bool enabled_ = false;
};

} // namespace plugin
} // namespace kaleidoscope

extern kaleidoscope::plugin::LEDEffectPerLayer LEDEffectPerLayer;
