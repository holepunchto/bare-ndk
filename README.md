# bare-ndk

Android views for Bare. It gives you Android's own views in JavaScript, along with a runtime that starts the activity for you, so a Bare app can have a native Android screen.

```
npm i bare-ndk
```

## Usage

```js
const { Activity, FrameGroup, TextView } = require('bare-ndk')

const root = new FrameGroup()

const label = new TextView()

label.text = 'Hello'
label.textSize = 48
label.gravity = TextView.GRAVITY.CENTER_HORIZONTAL | TextView.GRAVITY.CENTER_VERTICAL

root.addView(label)

// A frame group places each child at an exact frame, so the label follows the screen.
root.on('sizeChanged', (width, height) => {
  root.setFrame(label, 0, 0, width, height)
})

Activity.contentView(root)
```

Build the app with `bare-build` and this runtime:

```console
bare-build --host android-arm64 --runtime bare-ndk/runtime --identifier com.example.hello index.js
```

Lengths are in physical pixels, and colours are ARGB numbers, such as `0xff0000ff` for blue. Objects that have events, such as frame groups, edit fields and switches, emit them as ordinary events. Android is only asked to report an event while something listens to it.

## License

Apache-2.0
