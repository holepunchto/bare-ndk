const binding = require('../binding')
const { adopt } = require('./handle')
const NDKView = require('./view')
const { hold, drop } = require('./reachable')

module.exports = exports = class NDKViewGroup extends NDKView {
  addView(child, index = -1) {
    binding.viewGroupAddView(this._tag, adopt(child), index)

    hold(this, child)

    return this
  }

  removeView(child) {
    binding.viewGroupRemoveView(this._tag, adopt(child))

    drop(this, child)

    return this
  }
}
