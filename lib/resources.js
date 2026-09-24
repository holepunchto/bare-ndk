const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKResources extends NDKObject {
  get displayMetrics() {
    return binding.resourcesDisplayMetrics(this._tag)
  }
}
