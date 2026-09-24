const binding = require('../binding')
const { adopt } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKSpannableStringBuilder extends NDKObject {
  _init() {
    return binding.spannableStringBuilderInit()
  }

  get length() {
    return binding.spannableStringBuilderLength(this._tag)
  }

  append(text) {
    binding.spannableStringBuilderAppend(this._tag, typeof text === 'string' ? text : adopt(text))
    return this
  }

  setSpan(span, start, end, flags) {
    // Java keeps the span, so it has to stay reachable as long as the builder.
    this._retained.add(span)

    binding.spannableStringBuilderSetSpan(this._tag, adopt(span), start, end, flags)

    return this
  }
}
