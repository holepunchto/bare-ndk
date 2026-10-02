import NDKClipData = require('./clip-data')

/** Put `clip` on the clipboard. */
export function setPrimaryClip(clip: NDKClipData): void

/** What is on the clipboard, or `null`. */
export function getPrimaryClip(): NDKClipData | null

export function hasPrimaryClip(): boolean

export function clearPrimaryClip(): void
