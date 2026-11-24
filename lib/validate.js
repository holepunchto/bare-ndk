// Strings are handed on to Java and native code as C strings, where a NUL would
// cut them short and give them a different meaning.
exports.validateNoNullBytes = function validateNoNullBytes(value, name) {
  if (typeof value === 'string' && value.includes('\0')) {
    throw new TypeError(`The "${name}" argument must not contain null bytes`)
  }
}
