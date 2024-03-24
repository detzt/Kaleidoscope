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

#include "kaleidoscope/plugin/LED-EffectPerLayer.h"

#include <stdint.h> // for uint8_t

#include "kaleidoscope/event_handler_result.h"    // for EventHandlerResult
#include "kaleidoscope/layers.h"                  // for Layer
#include "kaleidoscope/plugin/LEDControl.h"       // for LEDControl
#include "kaleidoscope/plugin/LEDModeInterface.h" // for LEDModeInterface

namespace kaleidoscope {
namespace plugin {

LEDEffectPerLayer::LEDEffectPerLayer() {
  // Respect the configured default LED mode
  last_active_led_mode_index_ = ::LEDControl.get_mode_index();
}

// Basic plugin status functions.

// Enables the plugin.
void LEDEffectPerLayer::enable() { enabled_ = true; }

// Disables the plugin.
void LEDEffectPerLayer::disable() { enabled_ = false; }

// Returns true if the plugin is enabled.
bool LEDEffectPerLayer::active() { return enabled_; }

// Plugin configuration.

void LEDEffectPerLayer::setDefaultLayer(uint8_t layer) {
  default_layer_ = layer;
}

void LEDEffectPerLayer::setStaticLEDMode(
    LEDModeInterface &static_led_mode) {
  // This is a hack, because the API doesn't offer a way to find the index for
  // a given LEDMode
  static_led_mode.activate();
  static_led_mode_index_ = ::LEDControl.get_mode_index();
  ::LEDControl.set_mode(last_active_led_mode_index_);
}

void LEDEffectPerLayer::setStaticLEDMode(uint8_t static_led_mode_index) {
  static_led_mode_index_ = static_led_mode_index;
}

// Event handlers.

EventHandlerResult LEDEffectPerLayer::onLayerChange() {
  if (!enabled_) {
    return EventHandlerResult::OK;
  }

  if (Layer.mostRecent() == default_layer_) {
    // If on base layer, switch back to previously saved LED mode.
    ::LEDControl.set_mode(last_active_led_mode_index_);
    return EventHandlerResult::OK;
  } else {
    // On all other layers,
    // first save the LED mode that was active if it's not the static led mode
    if (::LEDControl.get_mode_index() != static_led_mode_index_) {
      last_active_led_mode_index_ = ::LEDControl.get_mode_index();
    }
    // then switch to the Colormap effect.
    ::LEDControl.set_mode(static_led_mode_index_);
  }
  return EventHandlerResult::OK;
}

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::LEDEffectPerLayer LEDEffectPerLayer;
