const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKObject = require('./object')
const NDKResources = require('./resources')

// The activity is the one the runtime brought up, so it is a wrapper around
// something that already exists rather than something to construct.
module.exports = exports = new (class NDKActivity extends NDKObject {
  _init() {
    return binding.activityInit()
  }

  get resources() {
    return wrap(NDKResources, binding.activityResources(this._tag))
  }

  contentView(view) {
    binding.activityContentView(this._tag, adopt(view))
    this._retained.add(view)
    return this
  }
})()
