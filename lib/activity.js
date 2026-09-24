const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKObject = require('./object')
const NDKResources = require('./resources')

module.exports = exports = new (class NDKActivity extends NDKObject {
  _init() {
    return binding.activityInit()
  }

  get resources() {
    return wrap(NDKResources, binding.activityResources(this._tag))
  }

  themeColor(attribute) {
    return binding.activityThemeColor(attribute)
  }

  contentView(view) {
    binding.activityContentView(this._tag, adopt(view))
    this._retained.add(view)
    return this
  }
})()
