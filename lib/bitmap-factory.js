const binding = require('../binding')
const wrap = require('./wrap')
const NDKBitmap = require('./bitmap')

// `BitmapFactory` is static methods and nothing else, so there is no instance
// to wrap; what it makes is a `Bitmap`.
exports.decodeFile = function decodeFile(path) {
  return wrap(NDKBitmap, binding.bitmapFactoryDecodeFile(path))
}
