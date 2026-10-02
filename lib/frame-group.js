const binding = require('../binding')
const { adopt } = require('./handle')
const NDKViewGroup = require('./view-group')

module.exports = exports = class NDKFrameGroup extends NDKViewGroup {
  static _events = {
    sizeChanged: binding.FRAME_GROUP_EVENT_SIZE_CHANGED,
    down: binding.FRAME_GROUP_EVENT_DOWN,
    move: binding.FRAME_GROUP_EVENT_MOVE,
    up: binding.FRAME_GROUP_EVENT_UP,
    cancel: binding.FRAME_GROUP_EVENT_CANCEL,
    insetsChanged: binding.FRAME_GROUP_EVENT_INSETS_CHANGED,
    configurationChanged: binding.FRAME_GROUP_EVENT_CONFIGURATION_CHANGED
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
