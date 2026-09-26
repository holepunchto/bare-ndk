const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKLetterSpacingSpan extends NDKObject {
  _init(opts) {
    const { spacing = 0 } = opts

    return binding.letterSpacingSpanInit(spacing)
  }
}

expose(exports)
