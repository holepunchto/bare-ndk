const binding = require('../binding')
const wrap = require('./wrap')
const NDKBitmap = require('./bitmap')
const { validateNoNullBytes } = require('./validate')

exports.decodeFile = function decodeFile(path) {
  validateNoNullBytes(path, 'path')

  return wrap(NDKBitmap, binding.bitmapFactoryDecodeFile(path))
}
