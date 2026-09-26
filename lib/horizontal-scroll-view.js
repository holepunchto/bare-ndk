const binding = require('../binding')
const { expose } = require('./handle')
const NDKViewGroup = require('./view-group')

module.exports = exports = class NDKHorizontalScrollView extends NDKViewGroup {
  static _events = {
    scrollChanged: binding.SCROLL_VIEW_EVENT_SCROLL_CHANGED
  }

  _init() {
    return binding.horizontalScrollViewInit()
  }

  _eventMask(mask) {
    binding.scrollViewEventMask(this._tag, mask)
  }
}

expose(exports)
