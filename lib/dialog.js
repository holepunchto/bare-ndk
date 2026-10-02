const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKDialog extends NDKObject {
  _init(opts) {
    const { title = '', message = null, positive = null, negative = null, neutral = null } = opts

    return binding.dialogInit(title, message, positive, negative, neutral)
  }

  show() {
    binding.dialogShow(this._tag)

    return this
  }
}

exports.BUTTON = {
  DISMISSED: 0,
  POSITIVE: binding.DIALOG_INTERFACE_BUTTON_POSITIVE,
  NEGATIVE: binding.DIALOG_INTERFACE_BUTTON_NEGATIVE,
  NEUTRAL: binding.DIALOG_INTERFACE_BUTTON_NEUTRAL
}
