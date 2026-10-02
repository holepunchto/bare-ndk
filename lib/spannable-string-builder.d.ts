import { Wrapper } from 'bare-jni-registry'
import NDKObject = require('./object')

/** Builds styled text out of spans, as an `android.text.SpannableStringBuilder`. */
interface NDKSpannableStringBuilder extends NDKObject {
  readonly length: number

  /** Add a string or another builder at the end. */
  append(text: string | Wrapper): this

  /**
   * Style the text from `start` to `end` with `span`. `flags` is a `SPAN` constant from
   * `bare-ndk/spanned` and decides whether text typed at either end is styled too.
   */
  setSpan(span: Wrapper, start: number, end: number, flags: number): this
}

declare class NDKSpannableStringBuilder {
  constructor()
}

export = NDKSpannableStringBuilder
