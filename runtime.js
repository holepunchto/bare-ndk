const { type } = require('bare-build/constants')

const { SHARED_LIBRARY } = type

require.asset = require('require-asset')

const prebuilds = {}

exports.prebuilds = prebuilds

prebuilds['android-x64'] = () => {
  return {
    type: SHARED_LIBRARY,
    path: require.asset('./prebuilds/android-x64/libbare.so', __filename),
    dependencies: [
      require.asset('./prebuilds/android-x64/bare/classes.dex', __filename),
      require.asset('./prebuilds/android-x64/bare/libc++_shared.so', __filename)
    ]
  }
}

prebuilds['android-ia32'] = () => {
  return {
    type: SHARED_LIBRARY,
    path: require.asset('./prebuilds/android-ia32/libbare.so', __filename),
    dependencies: [
      require.asset('./prebuilds/android-ia32/bare/classes.dex', __filename),
      require.asset('./prebuilds/android-ia32/bare/libc++_shared.so', __filename)
    ]
  }
}

prebuilds['android-arm64'] = () => {
  return {
    type: SHARED_LIBRARY,
    path: require.asset('./prebuilds/android-arm64/libbare.so', __filename),
    dependencies: [
      require.asset('./prebuilds/android-arm64/bare/classes.dex', __filename),
      require.asset('./prebuilds/android-arm64/bare/libc++_shared.so', __filename)
    ]
  }
}

prebuilds['android-arm'] = () => {
  return {
    type: SHARED_LIBRARY,
    path: require.asset('./prebuilds/android-arm/libbare.so', __filename),
    dependencies: [
      require.asset('./prebuilds/android-arm/bare/classes.dex', __filename),
      require.asset('./prebuilds/android-arm/bare/libc++_shared.so', __filename)
    ]
  }
}
