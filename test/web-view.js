const { test } = require('bare-tap')
const { BitmapFactory, WebView } = require('..')

test('rejects a URL with a NUL', (t) => {
  const view = new WebView()

  t.throws(() => view.loadURL('https://attacker.example\0.trusted.example'), TypeError)
  t.throws(
    () => view.loadDataWithBaseURL('https://attacker.example\0.trusted.example', ''),
    TypeError
  )
})

test('rejects a bitmap path with a NUL', (t) => {
  t.throws(() => BitmapFactory.decodeFile('/data/local/tmp/image.png\0.txt'), TypeError)
})
