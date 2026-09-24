import NDKObject = require('./object')

/** The settings of a web view, as an `android.webkit.WebSettings`. */
interface NDKWebSettings extends NDKObject {
  javaScriptEnabled: boolean

  domStorageEnabled: boolean

  userAgentString: string
}

declare class NDKWebSettings {
  protected constructor()
}

export = NDKWebSettings
