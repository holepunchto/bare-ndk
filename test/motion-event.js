const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const { FrameGroup, MotionEvent, SystemClock, Toggle } = require('..')
const { mount } = require('./helpers')

const { ACTION } = MotionEvent

function tap(view, x, y) {
  const time = SystemClock.uptimeMillis()

  const handled = []

  for (const action of [ACTION.DOWN, ACTION.UP]) {
    const event = MotionEvent.obtain(time, time, action, x, y)

    handled.push(view.dispatchTouchEvent(event))

    event.recycle()
  }

  return handled
}

test('the uptime clock moves forward', async (t) => {
  const before = SystemClock.uptimeMillis()

  await afterAnimationFrame()

  t.ok(before > 0 && SystemClock.uptimeMillis() >= before)
})

test('obtains an event', (t) => {
  const time = SystemClock.uptimeMillis()

  const event = MotionEvent.obtain(time - 10, time, ACTION.MOVE, 12.5, 34)

  t.deepStrictEqual(
    {
      action: event.action,
      x: event.x,
      y: event.y,
      downTime: event.downTime,
      eventTime: event.eventTime
    },
    { action: ACTION.MOVE, x: 12.5, y: 34, downTime: time - 10, eventTime: time }
  )

  event.recycle()
})

test('dispatches a touch to the view under it', async (t) => {
  const group = new FrameGroup()
  const child = new FrameGroup()

  group.addView(child)
  group.setFrame(child, 30, 40, 50, 60)

  const events = []

  child.on('down', (x, y) => events.push(['down', x, y]))
  child.on('up', (x, y) => events.push(['up', x, y]))

  await mount(t, group)

  t.deepStrictEqual(tap(group, 50, 60), [true, true], 'handled')
  t.deepStrictEqual(events, [
    ['down', 20, 20],
    ['up', 20, 20]
  ])
})

test('a touch outside every child is not handled', async (t) => {
  const group = new FrameGroup()

  await mount(t, group)

  t.deepStrictEqual(tap(group, 10, 10), [false, false])
})

test('tapping a switch toggles it', async (t) => {
  const group = new FrameGroup()
  const toggle = new Toggle()

  const { width, height } = toggle.naturalSize

  group.addView(toggle)
  group.setFrame(toggle, 0, 0, width, height)

  await mount(t, group)

  tap(group, width / 2, height / 2)

  // A click is posted to the next turn of the looper.
  await afterAnimationFrame()

  t.equal(toggle.checked, true)
})
