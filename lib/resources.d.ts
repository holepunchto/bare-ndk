import NDKObject = require('./object')

/** The resources of the app, as an `android.content.res.Resources`. */
interface NDKResources extends NDKObject {
  readonly displayMetrics: NDKResources.DisplayMetrics

  readonly configuration: NDKResources.Configuration
}

declare class NDKResources {
  protected constructor()

  /** The night bits of `configuration.uiMode`. Mask with `MASK` before comparing. */
  static readonly UI_MODE_NIGHT: {
    readonly MASK: number
    readonly UNDEFINED: number
    readonly NO: number
    readonly YES: number
  }
}

declare namespace NDKResources {
  export interface DisplayMetrics {
    /** Physical pixels per density independent pixel. */
    density: number
    densityDpi: number
    scaledDensity: number
    widthPixels: number
    heightPixels: number
    xdpi: number
    ydpi: number
  }

  export interface Configuration {
    densityDpi: number
    fontScale: number
    orientation: number
    screenWidthDp: number
    screenHeightDp: number
    smallestScreenWidthDp: number
    uiMode: number
  }
}

export = NDKResources
