const binding = require('../binding')
const NDKViewGroup = require('./view-group')

module.exports = exports = class NDKScrollView extends NDKViewGroup {
  static _events = {
    scrollChanged: binding.SCROLL_VIEW_EVENT_SCROLL_CHANGED
  }

  _init() {
    return binding.scrollViewInit()
  }

  _eventMask(mask) {
    binding.scrollViewEventMask(this._tag, mask)
  }
}
