import { Wrapper } from 'bare-jni-registry'
import NDKObject = require('./object')

/** A span that sets the typeface of the text it covers, as a `TypefaceSpan`. */
interface NDKTypefaceSpan extends NDKObject {}

declare class NDKTypefaceSpan {
  constructor(opts: { typeface: Wrapper })
}

export = NDKTypefaceSpan
