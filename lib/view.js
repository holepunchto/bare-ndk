const binding = require('../binding')
const wrap = require('./wrap')
const { adopt } = require('./handle')
const NDKObject = require('./object')
const NDKDrawable = require('./drawable')
const NDKWindowInsets = require('./window-insets')
const NDKWindowInsetsController = require('./window-insets-controller')

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

  get windowInsetsController() {
    return wrap(NDKWindowInsetsController, binding.viewWindowInsetsController(this._tag))
  }

  get locationInWindow() {
    return binding.viewLocationInWindow(this._tag)
  }

  dispatchTouchEvent(event) {
    return binding.viewDispatchTouchEvent(this._tag, adopt(event))
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

  get defaultFocusHighlight() {
    return binding.viewDefaultFocusHighlight(this._tag)
  }

  set defaultFocusHighlight(value) {
    binding.viewDefaultFocusHighlight(this._tag, value)
  }

  get visible() {
    return binding.viewVisible(this._tag)
  }

  set visible(value) {
    binding.viewVisible(this._tag, value)
  }

  get alpha() {
    return binding.viewAlpha(this._tag)
  }

  set alpha(value) {
    binding.viewAlpha(this._tag, value)
  }

  get translationX() {
    return binding.viewTranslationX(this._tag)
  }

  set translationX(value) {
    binding.viewTranslationX(this._tag, value)
  }

  get translationY() {
    return binding.viewTranslationY(this._tag)
  }

  set translationY(value) {
    binding.viewTranslationY(this._tag, value)
  }

  get translationZ() {
    return binding.viewTranslationZ(this._tag)
  }

  set translationZ(value) {
    binding.viewTranslationZ(this._tag, value)
  }

  get scaleX() {
    return binding.viewScaleX(this._tag)
  }

  set scaleX(value) {
    binding.viewScaleX(this._tag, value)
  }

  get scaleY() {
    return binding.viewScaleY(this._tag)
  }

  set scaleY(value) {
    binding.viewScaleY(this._tag, value)
  }

  get rotation() {
    return binding.viewRotation(this._tag)
  }

  set rotation(value) {
    binding.viewRotation(this._tag, value)
  }

  get rotationX() {
    return binding.viewRotationX(this._tag)
  }

  set rotationX(value) {
    binding.viewRotationX(this._tag, value)
  }

  get rotationY() {
    return binding.viewRotationY(this._tag)
  }

  set rotationY(value) {
    binding.viewRotationY(this._tag, value)
  }

  get pivotX() {
    return binding.viewPivotX(this._tag)
  }

  set pivotX(value) {
    binding.viewPivotX(this._tag, value)
  }

  get pivotY() {
    return binding.viewPivotY(this._tag)
  }

  set pivotY(value) {
    binding.viewPivotY(this._tag, value)
  }

  get cameraDistance() {
    return binding.viewCameraDistance(this._tag)
  }

  set cameraDistance(value) {
    binding.viewCameraDistance(this._tag, value)
  }

  get elevation() {
    return binding.viewElevation(this._tag)
  }

  set elevation(value) {
    binding.viewElevation(this._tag, value)
  }

  get outlineAmbientShadowColor() {
    return binding.viewOutlineAmbientShadowColor(this._tag)
  }

  set outlineAmbientShadowColor(value) {
    binding.viewOutlineAmbientShadowColor(this._tag, value | 0)
  }

  get outlineSpotShadowColor() {
    return binding.viewOutlineSpotShadowColor(this._tag)
  }

  set outlineSpotShadowColor(value) {
    binding.viewOutlineSpotShadowColor(this._tag, value | 0)
  }

  get clipToOutline() {
    return binding.viewClipToOutline(this._tag)
  }

  set clipToOutline(value) {
    binding.viewClipToOutline(this._tag, value)
  }

  get background() {
    return wrap(NDKDrawable, binding.viewBackground(this._tag))
  }

  set background(value) {
    binding.viewBackground(this._tag, adopt(value))
  }

  // An Android colour is ARGB packed into a signed 32 bit integer.
  set backgroundColor(value) {
    binding.viewBackgroundColor(this._tag, value | 0)
  }
}
