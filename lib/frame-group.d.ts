import { Wrapper } from 'bare-jni-registry'
import NDKViewGroup = require('./view-group')

/**
 * A view group that places each child at an exact frame. Android's own groups place children
 * by their own rules.
 */
interface NDKFrameGroup extends NDKViewGroup<NDKFrameGroup.Events> {
  /** Place `child`, which must already be added, at an exact frame. */
  setFrame(child: Wrapper, x: number, y: number, width: number, height: number): this
}

declare class NDKFrameGroup {
  constructor()
}

declare namespace NDKFrameGroup {
  export interface Events {
    sizeChanged: [width: number, height: number]

    /** A finger touched down. `pointer` tells fingers apart. */
    down: [x: number, y: number, pointer: number]
    move: [x: number, y: number, pointer: number]
    up: [x: number, y: number, pointer: number]
    cancel: [x: number, y: number, pointer: number]

    /** What covers the window changed, for example because the keyboard was shown. */
    insetsChanged: []

    /** The configuration changed, for example because dark mode was turned on. */
    configurationChanged: []
  }
}

export = NDKFrameGroup
