import NDKView = require('./view')

/** An on and off switch, as an `android.widget.Switch`. */
interface NDKToggle extends NDKView<NDKToggle.Events> {
  checked: boolean

  /** The size the switch draws itself at. */
  readonly naturalSize: { width: number; height: number }
}

declare class NDKToggle {
  constructor()
}

declare namespace NDKToggle {
  export interface Events {
    /** `checked` changed. */
    checked: []

    /** The switch got or lost the focus. `focused` is 1 or 0. */
    focusChanged: [focused: number]
  }
}

export = NDKToggle
