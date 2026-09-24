const binding = require('../binding')
const NDKObject = require('./object')

module.exports = exports = class NDKWebSettings extends NDKObject {
  get javaScriptEnabled() {
    return binding.webSettingsJavaScriptEnabled(this._tag)
  }

  set javaScriptEnabled(value) {
    binding.webSettingsJavaScriptEnabled(this._tag, value)
  }

  get domStorageEnabled() {
    return binding.webSettingsDomStorageEnabled(this._tag)
  }

  set domStorageEnabled(value) {
    binding.webSettingsDomStorageEnabled(this._tag, value)
  }

  get userAgentString() {
    return binding.webSettingsUserAgentString(this._tag)
  }

  set userAgentString(value) {
    binding.webSettingsUserAgentString(this._tag, value)
  }
}
