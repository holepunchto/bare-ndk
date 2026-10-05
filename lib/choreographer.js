const binding = require('../binding')
const { adopt } = require('./handle')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKChoreographer extends NDKObject {
  static getInstance() {
    return wrap(NDKChoreographer, binding.choreographerGetInstance())
  }

  postFrameCallback(callback) {
    binding.choreographerPostFrameCallback(this._tag, adopt(callback))
    return this
  }

  removeFrameCallback(callback) {
    binding.choreographerRemoveFrameCallback(this._tag, adopt(callback))
    return this
  }
}
