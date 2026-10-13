const binding = require('../binding')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKMotionEvent extends NDKObject {
  static obtain(downTime, eventTime, action, x, y, metaState = 0) {
    return wrap(
      NDKMotionEvent,
      binding.motionEventObtain(downTime, eventTime, action, x, y, metaState)
    )
  }

  get action() {
    return binding.motionEventAction(this._tag)
  }

  get x() {
    return binding.motionEventX(this._tag)
  }

  get y() {
    return binding.motionEventY(this._tag)
  }

  get downTime() {
    return binding.motionEventDownTime(this._tag)
  }

  get eventTime() {
    return binding.motionEventEventTime(this._tag)
  }

  recycle() {
    binding.motionEventRecycle(this._tag)
  }
}

exports.ACTION = {
  DOWN: binding.MOTION_EVENT_ACTION_DOWN,
  UP: binding.MOTION_EVENT_ACTION_UP,
  MOVE: binding.MOTION_EVENT_ACTION_MOVE,
  CANCEL: binding.MOTION_EVENT_ACTION_CANCEL
}
