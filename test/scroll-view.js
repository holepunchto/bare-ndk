const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const Pointer = require('bare-pointer')
const { FrameGroup, HorizontalScrollView, ScrollView, View } = require('..')
const { mount, place } = require('./helpers')

function scrolling(Scroller, width, height) {
  const scroller = new Scroller()
  const content = new FrameGroup()
  const inner = new FrameGroup()

  content.addView(inner)
  content.setFrame(inner, 0, 0, width, height)

  scroller.addView(content)

  return { scroller, content }
}

test('scrolls vertically', async (t) => {
  const { scroller } = scrolling(ScrollView, 400, 1000)

  await mount(t, scroller)

  const events = []

  scroller.on('scrollChanged', (x, y) => events.push([x, y]))

  scroller.scrollTo(0, 100)

  await afterAnimationFrame()

  t.equal(scroller.scrollY, 100, 'scrolled')
  t.deepStrictEqual(events, [[0, 100]], 'emitted')
})

test('scrolls horizontally', async (t) => {
  const { scroller } = scrolling(HorizontalScrollView, 1000, 300)

  await mount(t, scroller)

  const events = []

  scroller.on('scrollChanged', (x, y) => events.push([x, y]))

  scroller.scrollTo(100, 0)

  await afterAnimationFrame()

  t.equal(scroller.scrollX, 100, 'scrolled')
  t.deepStrictEqual(events, [[100, 0]], 'emitted')
})

test('scrolls vertically with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const { scroller } = scrolling(ScrollView, 300, 1000)

  // The content moves with the touch, so the touch is placed relative to the root.
  const root = await place(t, scroller, 300, 250)

  let scrolls = 0

  scroller.on('scrollChanged', () => scrolls++)

  await pointer.down(root, 190, 250)

  for (let y = 230; y >= 50; y -= 20) await pointer.move(root, 190, y)

  await pointer.up()

  t.ok(scrolls > 0, 'scrolled')
  t.ok(scroller.scrollY > 100, 'down the content')
})

test('scrolls horizontally with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const { scroller } = scrolling(HorizontalScrollView, 1000, 250)

  const root = await place(t, scroller, 300, 250)

  let scrolls = 0

  scroller.on('scrollChanged', () => scrolls++)

  await pointer.down(root, 320, 150)

  for (let x = 300; x >= 60; x -= 20) await pointer.move(root, x, 150)

  await pointer.up()

  t.ok(scrolls > 0, 'scrolled')
  t.ok(scroller.scrollX > 100, 'along the content')
})

test('stops at the end of the content', async (t) => {
  const { scroller } = scrolling(ScrollView, 400, 500)

  await mount(t, scroller)

  scroller.scrollTo(0, 1000)

  t.equal(scroller.scrollY, 200)
})

test('is a view group', (t) => {
  t.ok(new ScrollView() instanceof View)
})
