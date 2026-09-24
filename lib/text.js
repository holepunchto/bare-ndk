const binding = require('../binding')
const { adopt } = require('./handle')

const cache = new Map()

const CACHE_LIMIT = 4096

exports.measure = function measure(text, style = {}, width = Infinity) {
  const { family = null, size = 0 } = style

  const key = `${family}\u0000${size}\u0000${width}\u0000${text}`

  let result = cache.get(key)

  if (result === undefined) {
    result = binding.textMeasure(text, family, size, width)

    if (cache.size === CACHE_LIMIT) cache.delete(cache.keys().next().value)

    cache.set(key, result)
  }

  return result
}

// Text built out of spans carries its own style, so there is nothing to key a
// shared cache on. Whatever holds the spans holds the measurement too.
exports.measureSpanned = function measureSpanned(text, width = Infinity) {
  return binding.textMeasureSpanned(adopt(text), width)
}
