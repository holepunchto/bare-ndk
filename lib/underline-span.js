const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKUnderlineSpan extends NDKObject {
  _init() {
    return binding.underlineSpanInit()
  }
}

expose(exports)
