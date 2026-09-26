const binding = require('../binding')
const { expose } = require('./handle')
const NDKDrawable = require('./drawable')

module.exports = exports = class NDKGradientDrawable extends NDKDrawable {
  _init() {
    return binding.gradientDrawableInit()
  }

  setColor(color) {
    binding.gradientDrawableColor(this._tag, color | 0)
    return this
  }

  setCornerRadius(radius) {
    binding.gradientDrawableCornerRadius(this._tag, radius)
    return this
  }

  setStroke(width, color) {
    binding.gradientDrawableStroke(this._tag, width, color | 0)
    return this
  }
}

expose(exports)
