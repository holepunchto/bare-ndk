const binding = require('../binding')
const { adopt } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKTypefaceSpan extends NDKObject {
  _init(opts) {
    const { typeface } = opts

    this._retained.add(typeface)

    return binding.typefaceSpanInit(adopt(typeface))
  }
}
