const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKStrikethroughSpan extends NDKObject {
  _init() {
    return binding.strikethroughSpanInit()
  }
}

expose(exports)
