import NDKObject = require('./object')

/** Something that can be drawn, such as a background, as an `android.graphics.drawable.Drawable`. */
interface NDKDrawable extends NDKObject {}

declare class NDKDrawable {
  protected constructor()
}

export = NDKDrawable
