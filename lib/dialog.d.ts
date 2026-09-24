import NDKObject = require('./object')

/**
 * An alert dialog, as an `android.app.AlertDialog`. It cannot be changed once it is made, so it
 * is described all at once. A button that is `null` is not shown.
 */
interface NDKDialog extends NDKObject<NDKDialog.Events> {
  show(): this
}

declare class NDKDialog {
  constructor(opts?: {
    title?: string
    message?: string | null
    positive?: string | null
    negative?: string | null
    neutral?: string | null
  })

  /** The buttons a response can come from, and `DISMISSED` for a dialog closed without one. */
  static readonly BUTTON: {
    readonly DISMISSED: 0
    readonly POSITIVE: number
    readonly NEGATIVE: number
    readonly NEUTRAL: number
  }
}

declare namespace NDKDialog {
  export interface Events {
    /** The dialog closed. `button` is a `BUTTON` constant. */
    response: [button: number]
  }
}

export = NDKDialog
