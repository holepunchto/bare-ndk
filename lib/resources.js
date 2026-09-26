const binding = require('../binding')
const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKResources extends NDKObject {
  get displayMetrics() {
    return binding.resourcesDisplayMetrics(this._tag)
  }
}

expose(exports)
