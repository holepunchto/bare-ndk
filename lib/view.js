const binding = require('../binding')
const wrap = require('./wrap')
const { adopt, expose } = require('./handle')
const NDKObject = require('./object')
const NDKWindowInsets = require('./window-insets')

module.exports = exports = class NDKView extends NDKObject {
  get width() {
    return binding.viewWidth(this._tag)
  }

  get height() {
    return binding.viewHeight(this._tag)
  }

  get scrollX() {
    return binding.viewScrollX(this._tag)
  }

  get scrollY() {
    return binding.viewScrollY(this._tag)
  }

  setPadding(left, top, right, bottom) {
    binding.viewSetPadding(this._tag, left, top, right, bottom)

    return this
  }

  scrollTo(x, y) {
    binding.viewScrollTo(this._tag, x, y)

    return this
  }

  get rootWindowInsets() {
    return wrap(NDKWindowInsets, binding.viewRootWindowInsets(this._tag))
  }

  get enabled() {
    return binding.viewEnabled(this._tag)
  }

  set enabled(value) {
    binding.viewEnabled(this._tag, value)
  }

  set defaultFocusHighlight(value) {
    binding.viewDefaultFocusHighlight(this._tag, value)
  }

  set visible(value) {
    binding.viewVisible(this._tag, value)
  }

  set alpha(value) {
    binding.viewAlpha(this._tag, value)
  }

  set translationX(value) {
    binding.viewTranslationX(this._tag, value)
  }

  set translationY(value) {
    binding.viewTranslationY(this._tag, value)
  }

  set translationZ(value) {
    binding.viewTranslationZ(this._tag, value)
  }

  set scaleX(value) {
    binding.viewScaleX(this._tag, value)
  }

  set scaleY(value) {
    binding.viewScaleY(this._tag, value)
  }

  set rotation(value) {
    binding.viewRotation(this._tag, value)
  }

  set rotationX(value) {
    binding.viewRotationX(this._tag, value)
  }

  set rotationY(value) {
    binding.viewRotationY(this._tag, value)
  }

  set pivotX(value) {
    binding.viewPivotX(this._tag, value)
  }

  set pivotY(value) {
    binding.viewPivotY(this._tag, value)
  }

  set cameraDistance(value) {
    binding.viewCameraDistance(this._tag, value)
  }

  set elevation(value) {
    binding.viewElevation(this._tag, value)
  }

  set outlineAmbientShadowColor(value) {
    binding.viewOutlineAmbientShadowColor(this._tag, value | 0)
  }

  set outlineSpotShadowColor(value) {
    binding.viewOutlineSpotShadowColor(this._tag, value | 0)
  }

  set clipToOutline(value) {
    binding.viewClipToOutline(this._tag, value)
  }

  set background(value) {
    binding.viewBackground(this._tag, adopt(value))
  }

  // An Android colour is packed ARGB, which is exactly the 32 bits of a signed
  // integer, so the sign is reinterpreted rather than the value truncated.
  set backgroundColor(value) {
    binding.viewBackgroundColor(this._tag, value | 0)
  }
}

expose(exports)
