import NDKViewGroup = require('./view-group')

/** A view group that scrolls its child vertically, as an `android.widget.ScrollView`. */
interface NDKScrollView extends NDKViewGroup<NDKScrollView.Events> {}

declare class NDKScrollView {
  constructor()
}

declare namespace NDKScrollView {
  export interface Events {
    scrollChanged: [x: number, y: number]
  }
}

export = NDKScrollView
