import NDKObject = require('./object')

/** A span that underlines the text it covers, as an `UnderlineSpan`. Add it with `NDKSpannableStringBuilder.setSpan()`. */
interface NDKUnderlineSpan extends NDKObject {}

declare class NDKUnderlineSpan {
  constructor()
}

export = NDKUnderlineSpan
