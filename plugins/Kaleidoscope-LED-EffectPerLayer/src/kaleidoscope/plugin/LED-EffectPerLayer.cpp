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

  // initialize all layers to "unset"
  setLEDModeForAllLayers(kUnsetLEDMode);
}

// Basic plugin status functions.

// Enables the plugin.
void LEDEffectPerLayer::enable() { enabled_ = true; }

// Disables the plugin.
void LEDEffectPerLayer::disable() { enabled_ = false; }

// Returns true if the plugin is enabled.
bool LEDEffectPerLayer::active() { return enabled_; }

// Plugin configuration.

// Sets the LED mode for the given layer.
void LEDEffectPerLayer::setLEDMode(uint8_t layer, int8_t led_mode_index) {
  if (layer >= MAX_ACTIVE_LAYERS) {
    return;
  }
  layer_led_mode_indices_[layer] = led_mode_index;
}

// Sets the LED mode for the given layer.
void LEDEffectPerLayer::setLEDMode(uint8_t layer, LEDModeInterface &led_mode) {
  setLEDMode(layer, getIndexOfLEDMode(led_mode));
}

// Sets the LED mode for all layers.
void LEDEffectPerLayer::setLEDModeForAllLayers(int8_t led_mode_index) {
  for (uint8_t i = 0; i < MAX_ACTIVE_LAYERS; i++) {
    layer_led_mode_indices_[i] = led_mode_index;
  }
}

// Sets the LED mode for all layers.
void LEDEffectPerLayer::setLEDModeForAllLayers(LEDModeInterface &led_mode) {
  setLEDModeForAllLayers(getIndexOfLEDMode(led_mode));
}

// Event handlers.

EventHandlerResult LEDEffectPerLayer::onLayerChange() {
  if (!enabled_) {
    return EventHandlerResult::OK;
  }

  // Collect information.
  uint8_t current_layer = Layer.mostRecent();
  int8_t previous_effect = layer_led_mode_indices_[last_active_layer_];
  int8_t current_effect = layer_led_mode_indices_[current_layer];
  last_active_layer_ = current_layer;

  // If nothing changed, return.
  if (previous_effect == current_effect) {
    return EventHandlerResult::OK;
  }

  // If coming from an unset layer, save the current LED mode.
  if (previous_effect == kUnsetLEDMode) {
    last_active_led_mode_index_ = ::LEDControl.get_mode_index();
  }

  // If the new layer is unset, switch back to the saved LED mode.
  if (current_effect == kUnsetLEDMode) {
    ::LEDControl.set_mode(last_active_led_mode_index_);
  } else {
    // Otherwise, switch to the configured LED mode for the new layer.
    ::LEDControl.set_mode(current_effect);
  }

  return EventHandlerResult::OK;
}

// Private helper functions.

// Returns the index of the given LED mode.
uint8_t LEDEffectPerLayer::getIndexOfLEDMode(LEDModeInterface &led_mode) {
  // This is a hack, because the API doesn't offer a way to find the index for
  // a given LEDMode
  uint8_t current_index = ::LEDControl.get_mode_index();
  led_mode.activate();
  uint8_t index = ::LEDControl.get_mode_index();
  ::LEDControl.set_mode(current_index);
  return index;
}

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::LEDEffectPerLayer LEDEffectPerLayer;
