const binding = require('../binding')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKTypeface extends NDKObject {
  static create(family, style = exports.STYLE.NORMAL) {
    return wrap(NDKTypeface, binding.typefaceCreate(family, style))
  }
}

exports.STYLE = {
  NORMAL: 0,
  BOLD: 1,
  ITALIC: 2,
  BOLD_ITALIC: 3
}
