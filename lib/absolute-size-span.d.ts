import NDKObject = require('./object')

/** A span that sets the size of the text it covers, as an `AbsoluteSizeSpan`. Add it with `NDKSpannableStringBuilder.setSpan()`. */
interface NDKAbsoluteSizeSpan extends NDKObject {}

declare class NDKAbsoluteSizeSpan {
  /** `size` is in pixels, or in density independent pixels when `dip` is `true`. */
  constructor(opts?: { size?: number; dip?: boolean })
}

export = NDKAbsoluteSizeSpan
