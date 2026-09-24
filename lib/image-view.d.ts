import { Wrapper } from 'bare-jni-registry'
import NDKView = require('./view')

/** A view that shows an image, as an `android.widget.ImageView`. */
interface NDKImageView extends NDKView {
  /** How the image is fitted to the view, as a `SCALE_TYPE` constant. */
  scaleType: string

  /** A colour drawn over the image, or `null` for none. */
  set imageTint(value: number | null)

  /** Show `bitmap`, or nothing when it is `null`. */
  setImageBitmap(bitmap: Wrapper | null): this
}

declare class NDKImageView {
  constructor()

  static readonly SCALE_TYPE: {
    readonly MATRIX: 'MATRIX'
    readonly FIT_XY: 'FIT_XY'
    readonly FIT_START: 'FIT_START'
    readonly FIT_CENTER: 'FIT_CENTER'
    readonly FIT_END: 'FIT_END'
    readonly CENTER: 'CENTER'
    readonly CENTER_CROP: 'CENTER_CROP'
    readonly CENTER_INSIDE: 'CENTER_INSIDE'
  }
}

export = NDKImageView
