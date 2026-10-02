import NDKObject = require('./object')

/** What covers the window, such as the system bars or the keyboard, as a `WindowInsets`. */
interface NDKWindowInsets extends NDKObject {
  /** How far the parts named by `mask`, `TYPE` flags combined with `|`, reach into the window. */
  getInsets(mask: number): { left: number; top: number; right: number; bottom: number }
}

declare class NDKWindowInsets {
  protected constructor()

  static readonly TYPE: {
    readonly SYSTEM_BARS: number
    readonly DISPLAY_CUTOUT: number
    readonly IME: number
  }
}

export = NDKWindowInsets
