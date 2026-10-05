import NDKObject = require('./object')

/**
 * What a choreographer calls for a frame it is posted for, as an
 * `android.view.Choreographer.FrameCallback`.
 */
interface NDKFrameCallback extends NDKObject<NDKFrameCallback.Events> {}

declare class NDKFrameCallback {
  constructor()
}

declare namespace NDKFrameCallback {
  export interface Events {
    /** A frame is starting. `frameTimeNanos` is when, on the monotonic clock. */
    frame: [frameTimeNanos: number]
  }
}

export = NDKFrameCallback
