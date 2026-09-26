const binding = require('../binding')
const { expose } = require('./handle')
const NDKView = require('./view')

module.exports = exports = class NDKProgressBar extends NDKView {
  _init() {
    return binding.progressBarInit()
  }

  set indeterminate(value) {
    binding.progressBarIndeterminate(this._tag, value)
  }

  set indeterminateTint(value) {
    binding.progressBarIndeterminateTint(this._tag, value)
  }

  [Symbol.for('bare.inspect')]() {
    return {
      __proto__: { constructor: NDKProgressBar }
    }
  }
}

expose(exports)
