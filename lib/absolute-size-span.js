const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKAbsoluteSizeSpan extends NDKObject {
  _init(opts) {
    const { size = 0, dip = false } = opts

    return binding.absoluteSizeSpanInit(Math.round(size), dip)
  }
}

expose(exports)
