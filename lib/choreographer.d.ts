import NDKObject = require('./object')
import NDKFrameCallback = require('./frame-callback')

/** What times the frames of a thread, as an `android.view.Choreographer`. */
interface NDKChoreographer extends NDKObject {
  /** Call `callback` once, at the start of the next frame. */
  postFrameCallback(callback: NDKFrameCallback): this

  /** Take back a `postFrameCallback()` that has not been called yet. */
  removeFrameCallback(callback: NDKFrameCallback): this
}

declare class NDKChoreographer {
  protected constructor()

  /** The choreographer of the thread the engine runs on. */
  static getInstance(): NDKChoreographer
}

export = NDKChoreographer
