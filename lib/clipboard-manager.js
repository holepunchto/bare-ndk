const binding = require('../binding')
const wrap = require('./wrap')
const NDKClipData = require('./clip-data')

exports.setPrimaryClip = function setPrimaryClip(clip) {
  binding.clipboardManagerSetPrimaryClip(clip._tag)
}

exports.getPrimaryClip = function getPrimaryClip() {
  return wrap(NDKClipData, binding.clipboardManagerGetPrimaryClip())
}

exports.hasPrimaryClip = function hasPrimaryClip() {
  return binding.clipboardManagerHasPrimaryClip()
}

exports.clearPrimaryClip = function clearPrimaryClip() {
  binding.clipboardManagerClearPrimaryClip()
}
