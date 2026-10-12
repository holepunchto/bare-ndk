const { afterAnimationFrame } = require('bare-animation-frame')
const { Activity, FrameGroup } = require('..')

// The activity has one content view, so the tests share a root and swap what
// is inside it.
let root = null

exports.root = function shared() {
  if (root === null) {
    root = new FrameGroup()

    Activity.contentView(root)
  }

  return root
}

exports.mount = async function mount(t, child, width = 400, height = 300) {
  const root = exports.root()

  root.addView(child)
  root.setFrame(child, 0, 0, width, height)

  t.teardown(() => {
    root.removeView(child)
  })

  // Android only lays out new content on its next frame.
  await afterAnimationFrame()

  return root
}
