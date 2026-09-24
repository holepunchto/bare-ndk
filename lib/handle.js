const binding = require('../binding')
const registry = require('bare-jni-registry')

exports.adopt = function adopt(object) {
  return registry.adopt(binding, object)
}
