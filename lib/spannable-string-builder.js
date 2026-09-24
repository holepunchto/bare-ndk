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
    // The span outlives this call on the Java side, so the registry has to
    // keep it reachable for as long as the builder is.
    this._retained.add(span)

    binding.spannableStringBuilderSetSpan(this._tag, adopt(span), start, end, flags)

    return this
  }
}
