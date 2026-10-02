import NDKBitmap = require('./bitmap')

/** Load an image file, or return `null` if it is missing or is not an image. */
export function decodeFile(path: string): NDKBitmap | null
