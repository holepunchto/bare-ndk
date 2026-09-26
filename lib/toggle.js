const binding = require('../binding')
const { expose } = require('./handle')
const NDKView = require('./view')

module.exports = exports = class NDKToggle extends NDKView {
  static _events = {
    checked: binding.TOGGLE_EVENT_CHECKED,
    focusChanged: binding.TOGGLE_EVENT_FOCUS_CHANGED
  }

  _init() {
    return binding.toggleInit()
  }

  _eventMask(mask) {
    binding.toggleEventMask(this._tag, mask)
  }

  get checked() {
    return binding.toggleChecked(this._tag)
  }

  set checked(value) {
    binding.toggleChecked(this._tag, value)
  }

  get naturalSize() {
    return binding.toggleNaturalSize(this._tag)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: NDKToggle }
    }
  }
}

expose(exports)
