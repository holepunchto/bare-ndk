const binding = require('../binding')

exports.setApplicationNightMode = function setApplicationNightMode(mode) {
  binding.uiModeManagerApplicationNightMode(mode)
}

exports.MODE_NIGHT = {
  AUTO: binding.UI_MODE_MANAGER_MODE_NIGHT_AUTO,
  CUSTOM: binding.UI_MODE_MANAGER_MODE_NIGHT_CUSTOM,
  NO: binding.UI_MODE_MANAGER_MODE_NIGHT_NO,
  YES: binding.UI_MODE_MANAGER_MODE_NIGHT_YES
}
