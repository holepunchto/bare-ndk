const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKTypeface = require('./typeface')
const NDKView = require('./view')

module.exports = exports = class NDKTextView extends NDKView {
  _init() {
    return binding.textViewInit()
  }

  set text(value) {
    binding.textViewText(this._tag, value)
  }

  get textSize() {
    return binding.textViewTextSize(this._tag)
  }

  set textSize(value) {
    binding.textViewTextSize(this._tag, value)
  }

  get textColor() {
    return binding.textViewTextColor(this._tag)
  }

  set textColor(value) {
    binding.textViewTextColor(this._tag, value | 0)
  }

  get typeface() {
    return wrap(NDKTypeface, binding.textViewTypeface(this._tag))
  }

  set typeface(value) {
    binding.textViewTypeface(this._tag, adopt(value))
  }

  set gravity(value) {
    binding.textViewGravity(this._tag, value)
  }

  set justificationMode(value) {
    binding.textViewJustificationMode(this._tag, value)
  }
}

exports.GRAVITY = {
  LEFT: 3,
  RIGHT: 5,
  CENTER_HORIZONTAL: 1,
  START: 8388611,
  END: 8388613
}

exports.JUSTIFICATION_MODE = {
  NONE: 0,
  INTER_WORD: 1
}
