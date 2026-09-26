const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKBitmap extends NDKObject {
  get width() {
    return binding.bitmapWidth(this._tag)
  }

  get height() {
    return binding.bitmapHeight(this._tag)
  }

  get density() {
    return binding.bitmapDensity(this._tag)
  }

  set density(value) {
    binding.bitmapDensity(this._tag, value)
  }
}

expose(exports)
