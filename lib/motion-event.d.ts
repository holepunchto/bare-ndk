import NDKObject = require('./object')

/** A touch, as an `android.view.MotionEvent`. */
interface NDKMotionEvent extends NDKObject {
  /** An `ACTION` constant. */
  readonly action: number

  /** Where the touch is, relative to the view it was dispatched to. */
  readonly x: number
  readonly y: number

  /** When the gesture began, in the time base of `SystemClock.uptimeMillis()`. */
  readonly downTime: number

  /** When this event happened, in the time base of `SystemClock.uptimeMillis()`. */
  readonly eventTime: number

  /** Return the event to the pool it came from. It cannot be used afterwards. */
  recycle(): void
}

declare class NDKMotionEvent {
  protected constructor()

  /**
   * Create an event for a single pointer at `x` and `y`. Both times are in the time base of
   * `SystemClock.uptimeMillis()`, and `action` is an `ACTION` constant.
   */
  static obtain(
    downTime: number,
    eventTime: number,
    action: number,
    x: number,
    y: number,
    metaState?: number
  ): NDKMotionEvent | null

  static readonly ACTION: {
    readonly DOWN: number
    readonly UP: number
    readonly MOVE: number
    readonly CANCEL: number
  }
}

export = NDKMotionEvent
