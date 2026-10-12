const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const { Activity, BitmapFactory, Choreographer, FrameCallback, ImageView, WebView } = require('..')
const ClipData = require('../lib/clip-data')
const Dialog = require('../lib/dialog')
const ClipboardManager = require('../lib/clipboard-manager')
const { mount } = require('./helpers')

const fixture = require.asset('./fixtures/image.png', __filename)

test('calls a frame callback once per post', async (t) => {
  const choreographer = Choreographer.getInstance()
  const callback = new FrameCallback()

  t.ok(Choreographer.getInstance() === choreographer, 'same choreographer wrapper')

  const times = []

  await new Promise((resolve) => {
    callback.on('frame', (time) => {
      times.push(time)

      if (times.length === 2) resolve()
      else choreographer.postFrameCallback(callback)
    })

    choreographer.postFrameCallback(callback)
  })

  t.ok(times[1] > times[0])
})

test('takes back a frame callback', async (t) => {
  const choreographer = Choreographer.getInstance()
  const removed = new FrameCallback()
  const kept = new FrameCallback()

  let called = false

  removed.on('frame', () => {
    called = true
  })

  const frame = new Promise((resolve) => kept.on('frame', resolve))

  choreographer.postFrameCallback(removed).postFrameCallback(kept)
  choreographer.removeFrameCallback(removed)

  await frame

  t.notOk(called)
})

test('puts text on the clipboard', (t) => {
  ClipboardManager.setPrimaryClip(ClipData.newPlainText('Test', 'Grüße 👋'))

  t.ok(ClipboardManager.hasPrimaryClip(), 'has a clip')

  const clip = ClipboardManager.getPrimaryClip()

  t.equal(clip.itemCount, 1, 'one item')
  t.equal(clip.getItemAt(0).coerceToText(Activity), 'Grüße 👋', 'the text')

  ClipboardManager.clearPrimaryClip()

  t.notOk(ClipboardManager.hasPrimaryClip(), 'cleared')
})

test('decodes an image file', (t) => {
  const bitmap = BitmapFactory.decodeFile(fixture)

  t.equal(bitmap.width, 40, 'width')
  t.equal(bitmap.height, 20, 'height')

  bitmap.density = 320

  t.equal(bitmap.density, 320, 'density')
  t.equal(BitmapFactory.decodeFile('/missing.png'), null, 'a missing file')
})

test('shows a bitmap', async (t) => {
  const view = new ImageView()

  t.equal(view.scaleType, ImageView.SCALE_TYPE.FIT_CENTER, 'fits by default')

  view.scaleType = ImageView.SCALE_TYPE.CENTER_CROP
  view.imageTint = 0xffff0000
  view.imageTint = null
  view.setImageBitmap(BitmapFactory.decodeFile(fixture))

  await mount(t, view)

  t.equal(view.scaleType, ImageView.SCALE_TYPE.CENTER_CROP, 'scale type')

  t.ok(view.setImageBitmap(null) === view, 'cleared')
})

test('sets the settings of a web view', (t) => {
  const view = new WebView()
  const settings = view.settings

  t.ok(view.settings === settings, 'same settings wrapper')
  t.ok(settings.userAgentString.length > 0, 'a user agent')

  settings.javaScriptEnabled = true
  settings.domStorageEnabled = true
  settings.userAgentString = 'Test'

  t.equal(settings.javaScriptEnabled, true, 'JavaScript')
  t.equal(settings.domStorageEnabled, true, 'DOM storage')
  t.equal(settings.userAgentString, 'Test', 'user agent')
})

test('loads a page into a web view', async (t) => {
  const view = new WebView()

  t.ok(WebView.debuggingEnabled() === WebView, 'returns the class')

  view.loadData('<p>Hello</p>')
  view.loadDataWithBaseURL('https://example.com/', '<p>Hello</p>')
  view.loadURL('about:blank')

  await mount(t, view)

  t.equal(view.width, 400)
})

test('shows and cancels a dialog', async (t) => {
  const dialog = new Dialog({
    title: 'Title',
    message: 'Message',
    positive: 'OK',
    negative: 'Cancel'
  })

  const response = new Promise((resolve) => dialog.once('response', resolve))

  t.ok(dialog.show() === dialog, 'returns the dialog')

  await afterAnimationFrame()

  t.ok(dialog.cancel() === dialog, 'returns the dialog')
  t.equal(await response, Dialog.BUTTON.DISMISSED, 'dismissed')
})
