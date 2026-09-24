import NDKTextView = require('./text-view')

/** A view for editing text, as an `android.widget.EditText`. */
interface NDKEditField extends NDKTextView<NDKEditField.Events> {
  /** Text shown while the field is empty. */
  set hint(value: string)

  /**
   * The kind of text, as one `INPUT_TYPE.CLASS_*` combined with flags and a variation. Compare
   * `inputType & INPUT_TYPE.MASK_CLASS` against a class, because the classes share bits.
   */
  inputType: number

  /** What the return key of the soft keyboard does, as an `IME_OPTIONS` constant. */
  imeOptions: number

  /** The selected range. With nothing selected, both are at the caret. */
  get selection(): { start: number; end: number }
  set selection(selection: { start?: number; end?: number })

  /** Take the focus and show the soft keyboard. */
  requestFocus(): this

  /** Give up the focus and hide the soft keyboard. */
  clearFocus(): this
}

declare class NDKEditField {
  constructor()

  static readonly INPUT_TYPE: {
    readonly MASK_CLASS: number
    readonly CLASS_TEXT: number
    readonly CLASS_NUMBER: number
    readonly CLASS_PHONE: number
    readonly NUMBER_FLAG_DECIMAL: number
    readonly TEXT_FLAG_CAP_SENTENCES: number
    readonly TEXT_FLAG_CAP_WORDS: number
    readonly TEXT_FLAG_CAP_CHARACTERS: number
    readonly TEXT_FLAG_NO_SUGGESTIONS: number
    readonly TEXT_FLAG_MULTI_LINE: number
    readonly TEXT_VARIATION_PASSWORD: number
    readonly TEXT_VARIATION_EMAIL_ADDRESS: number
    readonly TEXT_VARIATION_URI: number
  }

  static readonly IME_OPTIONS: {
    readonly ACTION_UNSPECIFIED: number
    readonly ACTION_DONE: number
    readonly ACTION_GO: number
    readonly ACTION_NEXT: number
    readonly ACTION_SEARCH: number
    readonly ACTION_SEND: number
  }
}

declare namespace NDKEditField {
  export interface Events {
    /** The text changed. */
    changed: []

    /** The text from `start` to `end` is being replaced by `text`. */
    replacing: [text: string, start: number, end: number]

    selectionChanged: [start: number, end: number]

    /** The field got or lost the focus. `focused` is 1 or 0. */
    focusChanged: [focused: number]

    /** The user pressed the return key of the soft keyboard. */
    action: []
  }
}

export = NDKEditField
