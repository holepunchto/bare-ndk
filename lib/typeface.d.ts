import NDKObject = require('./object')

/** A font, as an `android.graphics.Typeface`. */
interface NDKTypeface extends NDKObject {}

declare class NDKTypeface {
  protected constructor()

  /** The typeface of a font family, such as `'sans-serif'`, or the default when `null`, in a `STYLE`. */
  static create(family: string | null, style?: number): NDKTypeface | null

  /** A typeface based on another, with a numeric `weight` from 1 to 1000. */
  static create(family: NDKTypeface, weight: number, italic?: boolean): NDKTypeface | null

  static readonly STYLE: {
    readonly NORMAL: 0
    readonly BOLD: 1
    readonly ITALIC: 2
    readonly BOLD_ITALIC: 3
  }
}

export = NDKTypeface
