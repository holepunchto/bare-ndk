const binding = require('../binding')

exports.uptimeMillis = function uptimeMillis() {
  return binding.systemClockUptimeMillis()
}
