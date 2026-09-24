const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKTypeface extends NDKObject {
  // `Typeface.create` is overloaded on whether it starts from a family name or
  // from another typeface, and only the second form takes a numeric weight.
  static create(family, style = exports.STYLE.NORMAL) {
    return wrap(NDKTypeface, binding.typefaceCreate(family, style))
  }

  static createFromTypeface(family, weight, italic) {
    return wrap(NDKTypeface, binding.typefaceCreateFromTypeface(adopt(family), weight, italic))
  }
}

exports.STYLE = {
  NORMAL: 0,
  BOLD: 1,
  ITALIC: 2,
  BOLD_ITALIC: 3
}
