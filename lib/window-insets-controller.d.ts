import NDKObject = require('./object')

/**
 * Shows and hides parts of the window, as a `WindowInsetsController`. Hiding the keyboard this
 * way works without knowing which view showed it.
 */
interface NDKWindowInsetsController extends NDKObject {
  /** Show the parts named by `types`, `NDKWindowInsets.TYPE` flags combined with `|`. */
  show(types: number): this

  /** Hide the parts named by `types`, `NDKWindowInsets.TYPE` flags combined with `|`. */
  hide(types: number): this
}

declare class NDKWindowInsetsController {
  protected constructor()
}

export = NDKWindowInsetsController
