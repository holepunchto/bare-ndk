const binding = require('../binding')
const { expose } = require('./handle')
const wrap = require('./wrap')
const NDKView = require('./view')
const NDKWebSettings = require('./web-settings')

module.exports = exports = class NDKWebView extends NDKView {
  _init() {
    return binding.webViewInit()
  }

  static debuggingEnabled(enabled = true) {
    binding.webViewDebuggingEnabled(enabled)
    return this
  }

  get settings() {
    return wrap(NDKWebSettings, binding.webViewSettings(this._tag))
  }

  loadURL(url) {
    binding.webViewLoadURL(this._tag, url)
    return this
  }

  loadData(data, mimeType = 'text/html', encoding = 'utf-8') {
    binding.webViewLoadData(this._tag, data, mimeType, encoding)
    return this
  }

  loadDataWithBaseURL(
    baseURL,
    data,
    mimeType = 'text/html',
    encoding = 'utf-8',
    historyURL = baseURL
  ) {
    binding.webViewLoadDataWithBaseURL(this._tag, baseURL, data, mimeType, encoding, historyURL)
    return this
  }
}

expose(exports)
