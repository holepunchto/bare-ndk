const binding = require('../binding')
const { expose } = require('./handle')
const NDKTextView = require('./text-view')

// An `EditText` is a `TextView`, so what it draws text with is already there
// and what is here is what makes it editable.
module.exports = exports = class NDKEditField extends NDKTextView {
  static _events = {
    changed: binding.EDIT_FIELD_EVENT_CHANGED,
    replacing: binding.EDIT_FIELD_EVENT_REPLACING,
    selectionChanged: binding.EDIT_FIELD_EVENT_SELECTION_CHANGED,
    focusChanged: binding.EDIT_FIELD_EVENT_FOCUS_CHANGED,
    action: binding.EDIT_FIELD_EVENT_ACTION
  }

  _init() {
    return binding.editFieldInit()
  }

  _eventMask(mask) {
    binding.editFieldEventMask(this._tag, mask)
  }

  set hint(value) {
    binding.editFieldHint(this._tag, value)
  }

  get inputType() {
    return binding.editFieldInputType(this._tag)
  }

  set inputType(value) {
    binding.editFieldInputType(this._tag, value)
  }

  get imeOptions() {
    return binding.editFieldImeOptions(this._tag)
  }

  set imeOptions(value) {
    binding.editFieldImeOptions(this._tag, value)
  }

  get selection() {
    return binding.editFieldSelection(this._tag)
  }

  set selection({ start = 0, end = start }) {
    binding.editFieldSelection(this._tag, start, end)
  }

  requestFocus() {
    binding.editFieldFocus(this._tag, true)

    return this
  }

  clearFocus() {
    binding.editFieldFocus(this._tag, false)

    return this
  }
}

// An input type is a class in the low four bits with flags and a variation
// above it, so the class is masked out rather than tested as a flag: text,
// number and phone are 1, 2 and 3 and share bits with each other.
exports.INPUT_TYPE = {
  MASK_CLASS: 0x0000000f,
  CLASS_TEXT: 0x00000001,
  CLASS_NUMBER: 0x00000002,
  CLASS_PHONE: 0x00000003,
  NUMBER_FLAG_DECIMAL: 0x00002000,
  TEXT_FLAG_CAP_SENTENCES: 0x00004000,
  TEXT_FLAG_CAP_WORDS: 0x00002000,
  TEXT_FLAG_CAP_CHARACTERS: 0x00001000,
  TEXT_FLAG_NO_SUGGESTIONS: 0x00080000,
  TEXT_FLAG_MULTI_LINE: 0x00020000,
  TEXT_VARIATION_PASSWORD: 0x00000080,
  TEXT_VARIATION_EMAIL_ADDRESS: 0x00000020,
  TEXT_VARIATION_URI: 0x00000010
}

exports.IME_OPTIONS = {
  ACTION_UNSPECIFIED: 0x00000000,
  ACTION_DONE: 0x00000006,
  ACTION_GO: 0x00000002,
  ACTION_NEXT: 0x00000005,
  ACTION_SEARCH: 0x00000003,
  ACTION_SEND: 0x00000004
}

expose(exports)
