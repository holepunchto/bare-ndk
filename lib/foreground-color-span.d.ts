import NDKObject = require('./object')

/** A span that colours the text it covers, as a `ForegroundColorSpan`. Add it with `NDKSpannableStringBuilder.setSpan()`. */
interface NDKForegroundColorSpan extends NDKObject {}

declare class NDKForegroundColorSpan {
  constructor(opts?: { color?: number })
}

export = NDKForegroundColorSpan
