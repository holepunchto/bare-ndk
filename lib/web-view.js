const binding = require('../binding')
const NDKActivity = require('./activity')
const NDKView = require('./view')

module.exports = class NDKWebView extends NDKView {
  constructor() {
    super()

    this._handle = binding.webViewInit(NDKActivity._handle, this)
  }

  loadURL(url) {
    binding.webViewLoadURL(this._handle, url)
    return this
  }
}
