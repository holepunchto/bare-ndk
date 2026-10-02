import { Wrapper } from 'bare-jni-registry'
import NDKView = require('./view')

/** A view that holds other views, as an `android.view.ViewGroup`. */
interface NDKViewGroup<M extends Record<keyof M, unknown[]> = {}> extends NDKView<M> {
  /** Whether children are clipped to the bounds of the group. */
  set clipChildren(value: boolean)

  /** Add `child` at `index`. -1, the default, adds it last. */
  addView(child: Wrapper, index?: number): this

  removeView(child: Wrapper): this
}

declare class NDKViewGroup<M extends Record<keyof M, unknown[]> = {}> {
  protected constructor()
}

export = NDKViewGroup
