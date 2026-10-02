import NDKObject = require('./object')

/** Something on the clipboard, as an `android.content.ClipData`. */
interface NDKClipData extends NDKObject {
  readonly itemCount: number

  getItemAt(index: number): NDKClipData.Item | null
}

declare class NDKClipData {
  protected constructor()

  /** Create clip data that holds `text`, described by `label`. */
  static newPlainText(label: string, text: string): NDKClipData | null
}

declare namespace NDKClipData {
  /** One item of clip data, as an `android.content.ClipData.Item`. */
  interface Item extends NDKObject {
    /** The item as text, whatever it holds, or `null`. Pass the activity as `context`. */
    coerceToText(context: NDKObject): string | null
  }

  class Item {
    protected constructor()
  }
}

export = NDKClipData
