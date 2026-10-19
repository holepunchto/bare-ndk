const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const Pointer = require('bare-pointer')
const { FrameGroup, GradientDrawable, View } = require('..')
const { mount, place } = require('./helpers')

test('cannot construct a plain view', (t) => {
  t.throws(() => new View(), TypeError)
})

test('has no size until laid out', async (t) => {
  const group = new FrameGroup()

  t.equal(group.width, 0, 'no width')
  t.equal(group.height, 0, 'no height')

  await mount(t, group, 200, 100)

  t.equal(group.width, 200, 'width')
  t.equal(group.height, 100, 'height')
})

test('places a child at an exact frame', async (t) => {
  const group = new FrameGroup()
  const child = new FrameGroup()

  group.addView(child)
  group.setFrame(child, 30, 40, 50, 60)

  await mount(t, group)

  const outer = group.locationInWindow
  const inner = child.locationInWindow

  t.deepStrictEqual(
    { x: inner.x - outer.x, y: inner.y - outer.y, width: child.width, height: child.height },
    { x: 30, y: 40, width: 50, height: 60 }
  )
})

test('finds the root of its hierarchy', async (t) => {
  const group = new FrameGroup()
  const child = new FrameGroup()

  group.addView(child)

  t.ok(child.rootView === group, 'the topmost group before attaching')

  await mount(t, group)

  const root = child.rootView

  t.ok(root !== group, 'the window once attached')
  t.ok(group.rootView === root, 'the same for every view in it')
  t.ok(root.width >= group.width && root.height >= group.height, 'around the group')
})

test('emits when the size of a group changes', async (t) => {
  const group = new FrameGroup()

  const sizes = []

  group.on('sizeChanged', (width, height) => sizes.push([width, height]))

  const root = await mount(t, group, 200, 100)

  root.setFrame(group, 0, 0, 300, 150)

  await afterAnimationFrame()

  t.deepStrictEqual(sizes, [
    [200, 100],
    [300, 150]
  ])
})

test('adds a child at an index', async (t) => {
  const group = new FrameGroup()
  const a = new FrameGroup()
  const b = new FrameGroup()

  t.ok(group.addView(a) === group, 'returns the group')

  group.addView(b, 0)
  group.setFrame(a, 0, 0, 10, 10)
  group.setFrame(b, 0, 0, 20, 20)

  await mount(t, group)

  t.equal(a.width, 10, 'first')
  t.equal(b.width, 20, 'second')

  t.ok(group.removeView(a) === group, 'returns the group')
})

test('scrolls the content of a view', async (t) => {
  const group = new FrameGroup()

  await mount(t, group)

  t.ok(group.scrollTo(10, 20) === group, 'returns the view')
  t.equal(group.scrollX, 10, 'x')
  t.equal(group.scrollY, 20, 'y')
})

test('disables a view', (t) => {
  const group = new FrameGroup()

  t.equal(group.enabled, true, 'enabled')

  group.enabled = false

  t.equal(group.enabled, false, 'disabled')
})

test('sets the look of a view', (t) => {
  const group = new FrameGroup()

  t.equal(group.background, null, 'no background')
  t.equal(group.visible, true, 'visible')
  t.equal(group.alpha, 1, 'opaque')

  group.alpha = 0.5
  group.visible = false
  group.elevation = 4
  group.outlineAmbientShadowColor = 0xff102030
  group.outlineSpotShadowColor = 0xff405060
  group.clipToOutline = true
  group.clipChildren = false
  group.defaultFocusHighlight = false

  t.equal(group.alpha, 0.5, 'alpha')
  t.equal(group.visible, false, 'hidden')
  t.equal(group.elevation, 4, 'elevation')
  t.equal(group.outlineAmbientShadowColor >>> 0, 0xff102030, 'ambient shadow')
  t.equal(group.outlineSpotShadowColor >>> 0, 0xff405060, 'spot shadow')
  t.equal(group.clipToOutline, true, 'clipped to the outline')
  t.equal(group.clipChildren, false, 'children not clipped')
  t.equal(group.defaultFocusHighlight, false, 'no focus highlight')
})

test('keeps the background wrapper', (t) => {
  const group = new FrameGroup()
  const background = new GradientDrawable()

  background.setColor(0xff0000ff).setCornerRadius(4).setStroke(1, 0xff000000, 2, 2)
  background.setCornerRadii([1, 1, 2, 2, 3, 3, 4, 4])

  group.background = background

  t.ok(group.background === background)
})

test('transforms a view', (t) => {
  const group = new FrameGroup()

  group.translationX = 1
  group.translationY = 2
  group.translationZ = 3
  group.scaleX = 2
  group.scaleY = 0.5
  group.rotation = 45
  group.rotationX = 10
  group.rotationY = 20
  group.pivotX = 5
  group.pivotY = 6
  group.cameraDistance = 1000

  t.deepStrictEqual(
    {
      translationX: group.translationX,
      translationY: group.translationY,
      translationZ: group.translationZ,
      scaleX: group.scaleX,
      scaleY: group.scaleY,
      rotation: group.rotation,
      rotationX: group.rotationX,
      rotationY: group.rotationY,
      pivotX: group.pivotX,
      pivotY: group.pivotY
    },
    {
      translationX: 1,
      translationY: 2,
      translationZ: 3,
      scaleX: 2,
      scaleY: 0.5,
      rotation: 45,
      rotationX: 10,
      rotationY: 20,
      pivotX: 5,
      pivotY: 6
    },
    'each part'
  )

  // Android keeps the distance divided by the density of the display.
  t.equal(Math.round(group.cameraDistance), 1000, 'camera distance')
})

test('pads a view', (t) => {
  const group = new FrameGroup()

  t.ok(group.setPadding(1, 2, 3, 4) === group, 'returns the view')

  group.backgroundColor = 0x80ff0000

  t.pass('takes a background colour')
})

test('touches a view with the pointer', async (t) => {
  const pointer = new Pointer()

  t.teardown(() => pointer.destroy())

  const view = new FrameGroup()

  await place(t, view, 200, 150)

  const events = []

  for (const name of ['down', 'move', 'up']) {
    view.on(name, (x, y) => events.push([name, x, y]))
  }

  await pointer.down(view, 10, 10)
  await pointer.move(view, 50, 40)
  await pointer.move(view, 90, 70)
  await pointer.up()

  t.deepStrictEqual(events, [
    ['down', 10, 10],
    ['move', 50, 40],
    ['move', 90, 70],
    ['up', 90, 70]
  ])
})
