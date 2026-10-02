import { Wrapper } from 'bare-jni-registry'
import NDKView = require('./view')
import NDKTypeface = require('./typeface')

/** A view that shows text, as an `android.widget.TextView`. */
interface NDKTextView<M extends Record<keyof M, unknown[]> = {}> extends NDKView<M> {
  /** The text. Set it to a string or to an `NDKSpannableStringBuilder` for styled text. */
  get text(): string
  set text(value: string | Wrapper)

  /** The height of each line. */
  set lineHeight(value: number)

  /** Space each line by its natural height times `multiplier`, plus `add`. */
  setLineSpacing(add: number, multiplier: number): this

  /** The size of the text, in pixels. */
  textSize: number

  textColor: number

  get typeface(): NDKTypeface | null
  set typeface(value: Wrapper)

  /** Where the text sits in the view, as `GRAVITY` flags combined with `|`. */
  set gravity(value: number)

  /** Whether lines are stretched to fill the width, as a `JUSTIFICATION_MODE` constant. */
  set justificationMode(value: number)

  set maxLines(value: number)

  /** Where text that does not fit is cut off with "...", such as `'END'`, or `null` for nowhere. */
  set ellipsize(value: string | null)
}

declare class NDKTextView<M extends Record<keyof M, unknown[]> = {}> {
  constructor()

  static readonly GRAVITY: {
    readonly TOP: 48
    readonly BOTTOM: 80
    readonly CENTER_VERTICAL: 16
    readonly LEFT: 3
    readonly RIGHT: 5
    readonly CENTER_HORIZONTAL: 1
    readonly START: 8388611
    readonly END: 8388613
  }

  static readonly JUSTIFICATION_MODE: {
    readonly NONE: 0
    readonly INTER_WORD: 1
  }
}

export = NDKTextView
