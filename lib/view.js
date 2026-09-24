const binding = require('../binding')
const wrap = require('./wrap')
const { adopt } = require('./handle')
const NDKObject = require('./object')
const NDKWindowInsets = require('./window-insets')

module.exports = exports = class NDKView extends NDKObject {
  get width() {
    return binding.viewWidth(this._tag)
  }

  get height() {
    return binding.viewHeight(this._tag)
  }

  get rootWindowInsets() {
    return wrap(NDKWindowInsets, binding.viewRootWindowInsets(this._tag))
  }

  set alpha(value) {
    binding.viewAlpha(this._tag, value)
  }

  set clipToOutline(value) {
    binding.viewClipToOutline(this._tag, value)
  }

  set background(value) {
    binding.viewBackground(this._tag, adopt(value))
  }

  // An Android colour is packed ARGB, which is exactly the 32 bits of a signed
  // integer, so the sign is reinterpreted rather than the value truncated.
  set backgroundColor(value) {
    binding.viewBackgroundColor(this._tag, value | 0)
  }
}
