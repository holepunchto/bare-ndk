const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const Pointer = require('bare-pointer')
const { EditField, FrameGroup, ProgressBar, Toggle } = require('..')
const { mount, place } = require('./helpers')

test('emits when the text of a field changes', (t) => {
  const field = new EditField()

  const events = []

  field.on('changed', () => events.push('changed'))
  field.on('replacing', (text, start, end) => events.push(['replacing', text, start, end]))

  field.text = 'Hello'

  t.equal(field.text, 'Hello', 'text')
  t.ok(events.includes('changed'), 'changed')
  t.deepStrictEqual(
    events.find((event) => event[0] === 'replacing'),
    ['replacing', 'Hello', 0, 0],
    'replacing'
  )
})

test('stops reporting once nothing listens', (t) => {
  const field = new EditField()

  let changes = 0

  const onchanged = () => changes++

  field.on('changed', onchanged)
  field.text = 'a'
  field.off('changed', onchanged)
  field.text = 'b'

  t.equal(changes, 1)
})

test('selects text in a field', (t) => {
  const field = new EditField()

  field.text = 'Hello'

  const events = []

  field.on('selectionChanged', (start, end) => events.push([start, end]))

  field.selection = { start: 1, end: 3 }

  t.deepStrictEqual(field.selection, { start: 1, end: 3 }, 'selected')

  field.selection = { start: 2 }

  t.deepStrictEqual(field.selection, { start: 2, end: 2 }, 'a caret')
  t.deepStrictEqual(
    events,
    [
      [1, 3],
      [2, 2]
    ],
    'emitted'
  )
})

test('sets the hints of a field', (t) => {
  const field = new EditField()
  const { INPUT_TYPE, IME_OPTIONS } = EditField

  const type = INPUT_TYPE.CLASS_TEXT | INPUT_TYPE.TEXT_VARIATION_EMAIL_ADDRESS

  t.equal(field.hint, null, 'no hint')

  field.hint = 'Email'
  field.inputType = type
  field.imeOptions = IME_OPTIONS.ACTION_SEND

  t.equal(field.hint, 'Email', 'hint')
  t.equal(field.inputType, type, 'input type')
  t.equal(field.inputType & INPUT_TYPE.MASK_CLASS, INPUT_TYPE.CLASS_TEXT, 'class')
  t.equal(field.imeOptions, IME_OPTIONS.ACTION_SEND, 'action')
})

test('reports focus moving between fields', async (t) => {
  const group = new FrameGroup()
  const a = new EditField()
  const b = new EditField()

  group.addView(a)
  group.addView(b)
  group.setFrame(a, 0, 0, 400, 100)
  group.setFrame(b, 0, 100, 400, 100)

  await mount(t, group)

  const events = []

  a.on('focusChanged', (focused) => events.push(focused))

  a.requestFocus()

  await afterAnimationFrame()

  b.requestFocus()

  await afterAnimationFrame()

  t.deepStrictEqual(events, [1, 0])
})

test('gives up the focus', async (t) => {
  const field = new EditField()

  await mount(t, field)

  field.requestFocus()

  await afterAnimationFrame()

  const events = []

  field.on('focusChanged', (focused) => events.push(focused))

  t.ok(field.clearFocus() === field, 'returns the field')

  await afterAnimationFrame()

  t.deepStrictEqual(events, [0], 'lost the focus')
})

test('focuses a field with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const field = new EditField()

  await place(t, field, 300, 100)

  const events = []

  field.on('focusChanged', (focused) => events.push(focused))

  await pointer.tap(field)

  t.deepStrictEqual(events, [1])
})

test('emits when a switch is toggled', (t) => {
  const toggle = new Toggle()

  let changes = 0

  toggle.on('checked', () => changes++)

  t.equal(toggle.checked, false, 'off')

  toggle.checked = true

  t.equal(toggle.checked, true, 'on')
  t.equal(changes, 1, 'emitted for a change from code')

  toggle.checked = true

  t.equal(changes, 1, 'not for the same value')
})

test('toggles a switch with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const toggle = new Toggle()
  const { width, height } = toggle.naturalSize

  await place(t, toggle, width, height)

  let changes = 0

  toggle.on('checked', () => changes++)

  await pointer.tap(toggle)

  t.equal(changes, 1, 'changed')
  t.equal(toggle.checked, true, 'on')
})

test('has a natural size', (t) => {
  const { width, height } = new Toggle().naturalSize

  t.ok(width > 0 && height > 0)
})

test('disables a switch', (t) => {
  const toggle = new Toggle()

  toggle.enabled = false

  t.equal(toggle.enabled, false)
})

test('does not toggle a disabled switch with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const toggle = new Toggle()
  const { width, height } = toggle.naturalSize

  toggle.enabled = false

  await place(t, toggle, width, height)

  let changes = 0

  toggle.on('checked', () => changes++)

  await pointer.tap(toggle)

  t.equal(changes, 0, 'not changed')
  t.equal(toggle.checked, false, 'off')
})

test('spins a progress bar', (t) => {
  const bar = new ProgressBar()

  bar.indeterminate = true

  t.equal(bar.indeterminate, true, 'spinning')

  bar.indeterminateTint = 0xffff0000
  bar.indeterminateTint = null

  t.pass('takes a tint and clears it')
})
