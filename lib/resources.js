const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKResources extends NDKObject {
  get displayMetrics() {
    return binding.resourcesDisplayMetrics(this._tag)
  }

  get configuration() {
    return binding.resourcesConfiguration(this._tag)
  }
}

exports.UI_MODE_NIGHT = {
  MASK: binding.UI_MODE_NIGHT_MASK,
  UNDEFINED: binding.UI_MODE_NIGHT_UNDEFINED,
  NO: binding.UI_MODE_NIGHT_NO,
  YES: binding.UI_MODE_NIGHT_YES
}
