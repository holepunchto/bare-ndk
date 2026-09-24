const binding = require('../binding')
const wrap = require('./wrap')
const NDKObject = require('./object')

module.exports = exports = class NDKClipData extends NDKObject {
  static newPlainText(label, text) {
    return wrap(NDKClipData, binding.clipDataNewPlainText(label, text))
  }

  get itemCount() {
    return binding.clipDataItemCount(this._tag)
  }

  getItemAt(index) {
    return wrap(NDKClipDataItem, binding.clipDataGetItemAt(this._tag, index))
  }
}

class NDKClipDataItem extends NDKObject {
  coerceToText(context) {
    return binding.clipDataItemCoerceToText(this._tag, context._tag)
  }
}

exports.Item = NDKClipDataItem
