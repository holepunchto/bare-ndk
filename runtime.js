require.asset = require('require-asset')

const prebuilds = {}

exports.prebuilds = prebuilds

prebuilds['android-x64'] = () => {
  return require.asset('./prebuilds/android-x64/libbare.so', __filename)
}

prebuilds['android-ia32'] = () => {
  return require.asset('./prebuilds/android-ia32/libbare.so', __filename)
}

prebuilds['android-arm64'] = () => {
  return require.asset('./prebuilds/android-arm64/libbare.so', __filename)
}

prebuilds['android-arm'] = () => {
  return require.asset('./prebuilds/android-arm/libbare.so', __filename)
}
