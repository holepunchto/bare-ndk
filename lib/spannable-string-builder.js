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
    binding.spannableStringBuilderAppend(this._tag, text)
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

// `Spanned`'s flags, which say what happens to a span when text is inserted at
// either of its ends.
exports.SPAN = {
  INCLUSIVE_EXCLUSIVE: 0x11,
  INCLUSIVE_INCLUSIVE: 0x12,
  EXCLUSIVE_EXCLUSIVE: 0x21,
  EXCLUSIVE_INCLUSIVE: 0x22
}
