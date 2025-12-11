const binding = require('../binding')
const NDKActivity = require('./activity')
const NDKView = require('./view')

module.exports = class NDKWebView extends NDKView {
  constructor() {
    super()

    this._handle = binding.webViewInit(NDKActivity._handle, this)
  }

  static debuggingEnabled(enabled = true) {
    binding.webViewDebuggingEnabled(NDKActivity._handle, enabled)
    return this
  }

  javaScriptEnabled(enabled = true) {
    binding.webViewJavaScriptEnabled(this._handle, enabled)
    return this
  }

  loadURL(url) {
    binding.webViewLoadURL(this._handle, url)
    return this
  }

  loadData(data, mimeType, encoding, baseURL = 'about:blank', historyURL = baseURL) {
    binding.webViewLoadData(
      this._handle,
      data,
      mimeType || 'text/html; charset=utf-8',
      encoding || 'UTF-8',
      baseURL,
      historyURL
    )
    return this
  }
}
