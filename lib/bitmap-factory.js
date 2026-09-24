const binding = require('../binding')
const wrap = require('./wrap')
const NDKBitmap = require('./bitmap')

exports.decodeFile = function decodeFile(path) {
  return wrap(NDKBitmap, binding.bitmapFactoryDecodeFile(path))
}
