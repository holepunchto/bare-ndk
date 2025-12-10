const binding = require('../binding')

class NDKActivity {
  constructor() {
    this._handle = binding.activityInit()
  }
}

module.exports = new NDKActivity()
