import { Wrapper } from 'bare-jni-registry'
import NDKObject = require('./object')
import NDKDrawable = require('./drawable')
import NDKMotionEvent = require('./motion-event')
import NDKWindowInsets = require('./window-insets')
import NDKWindowInsetsController = require('./window-insets-controller')

/** The base of every view, as an `android.view.View`. */
interface NDKView<M extends Record<keyof M, unknown[]> = {}> extends NDKObject<M> {
  readonly width: number

  readonly height: number

  readonly scrollX: number

  readonly scrollY: number

  setPadding(left: number, top: number, right: number, bottom: number): this

  scrollTo(x: number, y: number): this

  /** Shows and hides parts of the window, such as the keyboard. `null` until the view is attached. */
  readonly windowInsetsController: NDKWindowInsetsController | null

  /** Where the view is in its window. */
  readonly locationInWindow: { x: number; y: number }

  /** Pass a touch down to the view, or the child under it. `true` if something handled it. */
  dispatchTouchEvent(event: NDKMotionEvent): boolean

  /** The topmost view of the hierarchy the view is in, which is the view itself if it has no parent. */
  readonly rootView: NDKView

  /** What covers the window, such as the system bars. `null` until the view is attached. */
  readonly rootWindowInsets: NDKWindowInsets | null

  enabled: boolean

  /** Whether Android draws its highlight over the view when it has focus. */
  defaultFocusHighlight: boolean

  /** Whether the view is shown. A hidden view still keeps its place in the layout. */
  visible: boolean

  /** How opaque the view is, from 0 to 1. */
  alpha: number

  translationX: number

  translationY: number

  translationZ: number

  scaleX: number

  scaleY: number

  /** The rotation in degrees. */
  rotation: number

  rotationX: number

  rotationY: number

  /** The point the view is scaled and rotated around. */
  pivotX: number

  pivotY: number

  /** How far the camera is from the view, for `rotationX` and `rotationY`. */
  cameraDistance: number

  /** How far the view is raised, which decides its shadow. */
  elevation: number

  outlineAmbientShadowColor: number

  outlineSpotShadowColor: number

  /** Whether the view is clipped to the outline of its background. */
  clipToOutline: boolean

  /** What the view draws behind its content, such as a `NDKGradientDrawable`. */
  get background(): NDKDrawable | null
  set background(value: Wrapper)

  set backgroundColor(value: number)
}

declare class NDKView<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = NDKView
