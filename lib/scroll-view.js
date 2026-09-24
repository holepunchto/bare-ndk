const binding = require('../binding')
const NDKViewGroup = require('./view-group')

module.exports = exports = class NDKScrollView extends NDKViewGroup {
  static _events = {
    scroll: binding.SCROLL_VIEW_EVENT_SCROLL
  }

  _init() {
    return binding.scrollViewInit()
  }

  _eventMask(mask) {
    binding.scrollViewEventMask(this._tag, mask)
  }

  get scrollPosition() {
    return binding.viewScrollPosition(this._tag)
  }

  set scrollPosition({ x = 0, y = 0 }) {
    binding.viewScrollPosition(this._tag, x, y)
  }
}
