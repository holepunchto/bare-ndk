const path = require('path')

exports.paths = function paths(list) {
  return list.map((p) =>
    path.normalize(p.replace(/\.\.[/\\]bare-build-[a-f0-9]+/g, '<tmp>'))
  )
}
