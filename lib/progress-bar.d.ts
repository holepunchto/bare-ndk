import NDKView = require('./view')

/** A progress indicator, as an `android.widget.ProgressBar`. */
interface NDKProgressBar extends NDKView {
  /** Whether the bar spins instead of showing an amount. */
  set indeterminate(value: boolean)

  /** The colour of the spinning bar, or `null` for the colour of the theme. */
  set indeterminateTint(value: number | null)
}

declare class NDKProgressBar {
  constructor()
}

export = NDKProgressBar
