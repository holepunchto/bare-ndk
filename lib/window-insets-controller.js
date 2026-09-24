const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKWindowInsetsController extends NDKObject {
  show(types) {
    binding.windowInsetsControllerShow(this._tag, types)

    return this
  }

  hide(types) {
    binding.windowInsetsControllerHide(this._tag, types)

    return this
  }
}
