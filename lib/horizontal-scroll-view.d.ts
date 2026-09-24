import NDKViewGroup = require('./view-group')

/** A view group that scrolls its child horizontally, as an `android.widget.HorizontalScrollView`. */
interface NDKHorizontalScrollView extends NDKViewGroup<NDKHorizontalScrollView.Events> {}

declare class NDKHorizontalScrollView {
  constructor()
}

declare namespace NDKHorizontalScrollView {
  export interface Events {
    scrollChanged: [x: number, y: number]
  }
}

export = NDKHorizontalScrollView
