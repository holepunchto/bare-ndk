const { test } = require('bare-tap')
const { afterAnimationFrame } = require('bare-animation-frame')
const { Activity, DisplayMetrics, EditField, FrameGroup, Resources, WindowInsets } = require('..')
const UIModeManager = require('../lib/ui-mode-manager')
const { mount, root } = require('./helpers')

// Insets arrive several times as the keyboard animates, so this waits for the
// one that settles the question.
function insets(group, settled) {
  return new Promise((resolve) => {
    const onchange = () => {
      const keyboard = group.rootWindowInsets.getInsets(WindowInsets.TYPE.IME).bottom

      if (!settled(keyboard)) return

      group.off('insetsChanged', onchange)
      resolve(keyboard)
    }

    group.on('insetsChanged', onchange)
  })
}

test('reads the display metrics', (t) => {
  const { density, densityDpi, widthPixels, heightPixels } = Activity.resources.displayMetrics

  t.ok(density > 0, 'a density')
  t.equal(density * DisplayMetrics.DENSITY_DEFAULT, densityDpi, 'counted against the default')
  t.ok(widthPixels > 0 && heightPixels > 0, 'a size')
})

test('reads the configuration', (t) => {
  const { configuration } = Activity.resources
  const { MASK, NO, YES } = Resources.UI_MODE_NIGHT

  t.ok(configuration.fontScale > 0, 'a font scale')
  t.ok(configuration.screenWidthDp > 0, 'a width')
  t.ok([NO, YES].includes(configuration.uiMode & MASK), 'light or dark')
})

test('keeps the resources wrapper', (t) => {
  t.ok(Activity.resources === Activity.resources)
})

test('reads a colour from the theme', (t) => {
  const color = Activity.themeColor('colorBackground')

  t.equal(color >>> 24, 0xff)
})

test('reports the insets once attached', async (t) => {
  const group = new FrameGroup()

  t.equal(group.rootWindowInsets, null, 'none before')
  t.equal(group.windowInsetsController, null, 'no controller before')

  await mount(t, group)

  const insets = group.rootWindowInsets

  t.ok(insets instanceof WindowInsets, 'insets')
  t.ok(group.windowInsetsController !== null, 'a controller')

  const { left, top, right, bottom } = insets.getInsets(WindowInsets.TYPE.SYSTEM_BARS)

  t.ok(
    [left, top, right, bottom].every((inset) => inset >= 0),
    'system bars'
  )
})

test('shows and hides the keyboard', async (t) => {
  const field = new EditField()
  const group = await mount(t, field)
  const controller = field.windowInsetsController
  const { IME } = WindowInsets.TYPE

  t.teardown(() => {
    controller.hide(IME)
  })

  field.requestFocus()

  await afterAnimationFrame()

  let shown = insets(group, (keyboard) => keyboard > 0)

  t.ok(controller.show(IME) === controller, 'returns the controller')
  t.ok((await shown) > 0, 'shown')

  const hidden = insets(group, (keyboard) => keyboard === 0)

  controller.hide(IME)

  t.equal(await hidden, 0, 'hidden')

  shown = insets(group, (keyboard) => keyboard > 0)

  controller.show(IME)

  t.ok((await shown) > 0, 'shown again')
})

test('switches between light and dark mode', async (t) => {
  const group = root()
  const { MASK, YES, NO } = Resources.UI_MODE_NIGHT
  const { MODE_NIGHT } = UIModeManager

  const night = () => Activity.resources.configuration.uiMode & MASK
  const changed = () => new Promise((resolve) => group.once('configurationChanged', resolve))

  const original = night()
  const dark = original !== YES

  let change = changed()

  UIModeManager.setApplicationNightMode(dark ? MODE_NIGHT.YES : MODE_NIGHT.NO)

  await change

  t.equal(night(), dark ? YES : NO, 'switched')

  // Android keeps the mode of an app across launches, so the run leaves it
  // following the system again.
  change = changed()

  UIModeManager.setApplicationNightMode(MODE_NIGHT.AUTO)

  await change

  t.equal(night(), original, 'follows the system')
})
