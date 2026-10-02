import { Wrapper } from 'bare-jni-registry'
import NDKObject = require('./object')
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

  /** What covers the window, such as the system bars. `null` until the view is attached. */
  readonly rootWindowInsets: NDKWindowInsets | null

  enabled: boolean

  /** Whether Android draws its highlight over the view when it has focus. */
  set defaultFocusHighlight(value: boolean)

  /** Whether the view is shown. A hidden view still keeps its place in the layout. */
  set visible(value: boolean)

  /** How opaque the view is, from 0 to 1. */
  set alpha(value: number)

  set translationX(value: number)

  set translationY(value: number)

  set translationZ(value: number)

  set scaleX(value: number)

  set scaleY(value: number)

  /** The rotation in degrees. */
  set rotation(value: number)

  set rotationX(value: number)

  set rotationY(value: number)

  /** The point the view is scaled and rotated around. */
  set pivotX(value: number)

  set pivotY(value: number)

  /** How far the camera is from the view, for `rotationX` and `rotationY`. */
  set cameraDistance(value: number)

  /** How far the view is raised, which decides its shadow. */
  set elevation(value: number)

  set outlineAmbientShadowColor(value: number)

  set outlineSpotShadowColor(value: number)

  /** Whether the view is clipped to the outline of its background. */
  set clipToOutline(value: boolean)

  /** What the view draws behind its content, such as a `NDKGradientDrawable`. */
  set background(value: Wrapper)

  set backgroundColor(value: number)
}

declare class NDKView<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = NDKView
