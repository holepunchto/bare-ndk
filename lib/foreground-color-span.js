const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKForegroundColorSpan extends NDKObject {
  _init(opts) {
    const { color = 0 } = opts

    return binding.foregroundColorSpanInit(color | 0)
  }
}

expose(exports)
