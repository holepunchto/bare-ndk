const { expose } = require('./handle')
const NDKObject = require('./object')

module.exports = exports = class NDKDrawable extends NDKObject {}

expose(exports)
