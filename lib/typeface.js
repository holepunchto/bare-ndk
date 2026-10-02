const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKTypeface extends NDKObject {
  // Starting from another typeface, the second argument is a weight rather
  // than one of the four styles.
  static create(family, style = exports.STYLE.NORMAL, italic = false) {
    if (typeof family === 'string' || family === null) {
      return wrap(NDKTypeface, binding.typefaceCreate(family, style))
    }

    return wrap(NDKTypeface, binding.typefaceCreateFromTypeface(adopt(family), style, italic))
  }
}

exports.STYLE = {
  NORMAL: 0,
  BOLD: 1,
  ITALIC: 2,
  BOLD_ITALIC: 3
}
