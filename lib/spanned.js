// `Spanned` is an interface, so what it contributes is its flags: what happens
// to a span when text is inserted at either of its ends.
exports.SPAN = {
  INCLUSIVE_EXCLUSIVE: 0x11,
  INCLUSIVE_INCLUSIVE: 0x12,
  EXCLUSIVE_EXCLUSIVE: 0x21,
  EXCLUSIVE_INCLUSIVE: 0x22
}
