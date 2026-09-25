const binding = require('../binding')
const { adopt } = require('./handle')
const NDKView = require('./view')

module.exports = exports = class NDKImageView extends NDKView {
  _init() {
    return binding.imageViewInit()
  }

  get scaleType() {
    return binding.imageViewScaleType(this._tag)
  }

  set scaleType(value) {
    binding.imageViewScaleType(this._tag, value)
  }

  setImageBitmap(bitmap) {
    binding.imageViewSetImageBitmap(this._tag, bitmap === null ? null : adopt(bitmap))

    return this
  }
}

// `ScaleType` is an enum rather than a set of flags, and its constants have no
// numbering of their own, so each one stands for itself.
exports.SCALE_TYPE = {
  MATRIX: 'MATRIX',
  FIT_XY: 'FIT_XY',
  FIT_START: 'FIT_START',
  FIT_CENTER: 'FIT_CENTER',
  FIT_END: 'FIT_END',
  CENTER: 'CENTER',
  CENTER_CROP: 'CENTER_CROP',
  CENTER_INSIDE: 'CENTER_INSIDE'
}
