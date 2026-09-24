const binding = require('../binding')
const { adopt } = require('./handle')
const NDKViewGroup = require('./view-group')

// Android has no view group that takes an absolute frame. `AbsoluteLayout` was
// deprecated everything since lays out by its own rules, so the one this places
// children with is our own.
module.exports = exports = class NDKFrameGroup extends NDKViewGroup {
  static _events = {
    resize: binding.FRAME_GROUP_EVENT_RESIZE,
    down: binding.FRAME_GROUP_EVENT_DOWN,
    move: binding.FRAME_GROUP_EVENT_MOVE,
    up: binding.FRAME_GROUP_EVENT_UP,
    cancel: binding.FRAME_GROUP_EVENT_CANCEL
  }

  _init() {
    return binding.frameGroupInit()
  }

  _eventMask(mask) {
    binding.frameGroupEventMask(this._tag, mask)
  }

  setFrame(child, x, y, width, height) {
    binding.frameGroupSetFrame(this._tag, adopt(child), x, y, width, height)
    return this
  }
}
