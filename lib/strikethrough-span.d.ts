import NDKObject = require('./object')

/** A span that strikes through the text it covers, as a `StrikethroughSpan`. Add it with `NDKSpannableStringBuilder.setSpan()`. */
interface NDKStrikethroughSpan extends NDKObject {}

declare class NDKStrikethroughSpan {
  constructor()
}

export = NDKStrikethroughSpan
