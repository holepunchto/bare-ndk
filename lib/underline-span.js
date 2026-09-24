const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKUnderlineSpan extends NDKObject {
  _init() {
    return binding.underlineSpanInit()
  }
}
