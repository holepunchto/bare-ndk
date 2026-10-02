import NDKObject = require('./object')

/** An image in memory, as an `android.graphics.Bitmap`. */
interface NDKBitmap extends NDKObject {
  readonly width: number

  readonly height: number

  /** The density the image was made for, in dots per inch. */
  density: number
}

declare class NDKBitmap {
  protected constructor()
}

export = NDKBitmap
