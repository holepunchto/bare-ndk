const test = require('brittle')
const path = require('path')
const build = require('bare-build')
const runtime = require('bare-ndk/runtime')
const { paths } = require('./test/helpers')

const fixtures = path.resolve(__dirname, 'test', 'fixtures')

test('basic, android-arm64', async (t) => {
  const out = await t.tmp()
  const result = []

  for await (const resource of build(path.join(fixtures, 'basic', 'app.js'), {
    out,
    runtime,
    base: path.join(fixtures, 'basic'),
    identifier: 'my.app',
    hosts: ['android-arm64']
  })) {
    result.push(path.relative(out, resource))
  }

  t.alike(
    paths(result),
    paths([
      '<tmp>/dex/classes.dex',
      '<tmp>/lib/arm64-v8a/libc++_shared.so',
      '<tmp>/lib/arm64-v8a/libbare.so',
      '<tmp>/assets/app.bundle',
      '<tmp>/AndroidManifest.xml',
      '<tmp>/My App.aab',
      'My App.apk'
    ])
  )
})

test('basic, android-arm64 + android-x64', async (t) => {
  const out = await t.tmp()
  const result = []

  for await (const resource of build(path.join(fixtures, 'basic', 'app.js'), {
    out,
    runtime,
    base: path.join(fixtures, 'basic'),
    identifier: 'my.app',
    hosts: ['android-arm64', 'android-x64']
  })) {
    result.push(path.relative(out, resource))
  }

  t.alike(
    paths(result),
    paths([
      '<tmp>/dex/classes.dex',
      '<tmp>/lib/arm64-v8a/libc++_shared.so',
      '<tmp>/lib/arm64-v8a/libbare.so',
      '<tmp>/lib/x86_64/libc++_shared.so',
      '<tmp>/lib/x86_64/libbare.so',
      '<tmp>/assets/app.bundle',
      '<tmp>/AndroidManifest.xml',
      '<tmp>/My App.aab',
      'My App.apk'
    ])
  )
})

test('addon, android-arm64', async (t) => {
  const out = await t.tmp()
  const result = []

  for await (const resource of build(path.join(fixtures, 'addon', 'app.js'), {
    out,
    runtime,
    base: path.join(fixtures, 'addon'),
    identifier: 'my.app',
    hosts: ['android-arm64']
  })) {
    result.push(path.relative(out, resource))
  }

  t.alike(
    paths(result),
    paths([
      '<tmp>/lib/arm64-v8a/libbare-os.3.9.1.so',
      '<tmp>/dex/classes.dex',
      '<tmp>/lib/arm64-v8a/libc++_shared.so',
      '<tmp>/lib/arm64-v8a/libbare.so',
      '<tmp>/assets/app.bundle',
      '<tmp>/AndroidManifest.xml',
      '<tmp>/My App.aab',
      'My App.apk'
    ])
  )
})

test('addon, android-arm64 + android-x64', async (t) => {
  const out = await t.tmp()
  const result = []

  for await (const resource of build(path.join(fixtures, 'addon', 'app.js'), {
    out,
    runtime,
    base: path.join(fixtures, 'addon'),
    identifier: 'my.app',
    hosts: ['android-arm64', 'android-x64']
  })) {
    result.push(path.relative(out, resource))
  }

  t.alike(
    paths(result),
    paths([
      '<tmp>/lib/arm64-v8a/libbare-os.3.9.1.so',
      '<tmp>/lib/x86_64/libbare-os.3.9.1.so',
      '<tmp>/dex/classes.dex',
      '<tmp>/lib/arm64-v8a/libc++_shared.so',
      '<tmp>/lib/arm64-v8a/libbare.so',
      '<tmp>/lib/x86_64/libc++_shared.so',
      '<tmp>/lib/x86_64/libbare.so',
      '<tmp>/assets/app.bundle',
      '<tmp>/AndroidManifest.xml',
      '<tmp>/My App.aab',
      'My App.apk'
    ])
  )
})

test('asset, android-arm64', async (t) => {
  const out = await t.tmp()
  const result = []

  for await (const resource of build(path.join(fixtures, 'asset', 'app.js'), {
    out,
    runtime,
    base: path.join(fixtures, 'asset'),
    identifier: 'my.app',
    hosts: ['android-arm64']
  })) {
    result.push(path.relative(out, resource))
  }

  t.alike(
    paths(result),
    paths([
      '<tmp>/dex/classes.dex',
      '<tmp>/lib/arm64-v8a/libc++_shared.so',
      '<tmp>/lib/arm64-v8a/libbare.so',
      '<tmp>/assets/app/foo.txt',
      '<tmp>/assets/app.bundle',
      '<tmp>/AndroidManifest.xml',
      '<tmp>/My App.aab',
      'My App.apk'
    ])
  )
})
