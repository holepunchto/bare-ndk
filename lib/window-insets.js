const binding = require('../binding')
const NDKObject = require('./object')

// Read from a view rather than constructed, and only meaningful while that view
// is attached to a window.
module.exports = exports = class NDKWindowInsets extends NDKObject {
  getInsets(mask) {
    return binding.windowInsetsInsets(this._tag, mask)
  }
}

exports.TYPE = {
  SYSTEM_BARS: binding.WINDOW_INSETS_TYPE_SYSTEM_BARS,
  DISPLAY_CUTOUT: binding.WINDOW_INSETS_TYPE_DISPLAY_CUTOUT,
  IME: binding.WINDOW_INSETS_TYPE_IME
}
