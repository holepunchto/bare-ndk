const binding = require('../binding')

class NDKActivity {
  constructor() {
    this._handle = binding.activityInit()
  }

  contentView(view) {
    binding.activityContentView(this._handle, view._handle)
  }
}

module.exports = new NDKActivity()
