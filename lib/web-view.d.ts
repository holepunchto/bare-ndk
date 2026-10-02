import NDKView = require('./view')
import NDKWebSettings = require('./web-settings')

/** A view that shows web content, as an `android.webkit.WebView`. */
interface NDKWebView extends NDKView {
  readonly settings: NDKWebSettings

  loadURL(url: string): this

  /** Load `data` as the page. `mimeType` defaults to `text/html` and `encoding` to `utf-8`. */
  loadData(data: string, mimeType?: string, encoding?: string): this

  /**
   * Load `data` as the page, with relative links resolving against `baseURL`. `historyURL`, which
   * defaults to `baseURL`, is what going back returns to.
   */
  loadDataWithBaseURL(
    baseURL: string,
    data: string,
    mimeType?: string,
    encoding?: string,
    historyURL?: string
  ): this
}

declare class NDKWebView {
  constructor()

  /** Let Chrome's DevTools inspect every web view in the app. */
  static debuggingEnabled(enabled?: boolean): typeof NDKWebView
}

export = NDKWebView
