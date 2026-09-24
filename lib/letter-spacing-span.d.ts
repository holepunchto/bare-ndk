import NDKObject = require('./object')

/** A span that spaces out the characters it covers. Android has no such span, so this one is its own. Add it with `NDKSpannableStringBuilder.setSpan()`. */
interface NDKLetterSpacingSpan extends NDKObject {}

declare class NDKLetterSpacingSpan {
  /** `spacing` is the extra space between characters, in pixels. */
  constructor(opts?: { spacing?: number })
}

export = NDKLetterSpacingSpan
