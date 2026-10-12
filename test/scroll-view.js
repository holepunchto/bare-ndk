const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const { FrameGroup, HorizontalScrollView, ScrollView, View } = require('..')
const { mount } = require('./helpers')

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

test('stops at the end of the content', async (t) => {
  const { scroller } = scrolling(ScrollView, 400, 500)

  await mount(t, scroller)

  scroller.scrollTo(0, 1000)

  t.equal(scroller.scrollY, 200)
})

test('is a view group', (t) => {
  t.ok(new ScrollView() instanceof View)
})
