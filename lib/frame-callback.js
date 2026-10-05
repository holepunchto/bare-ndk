const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKFrameCallback extends NDKObject {
  static _events = {
    frame: binding.FRAME_CALLBACK_EVENT_FRAME
  }

  _init() {
    return binding.frameCallbackInit()
  }

  _eventMask(mask) {
    binding.frameCallbackEventMask(this._tag, mask)
  }
}
