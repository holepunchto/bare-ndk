/** Choose between light and dark mode for the app, as a `MODE_NIGHT` constant. */
export function setApplicationNightMode(mode: number): void

export const MODE_NIGHT: {
  readonly AUTO: number
  readonly CUSTOM: number
  readonly NO: number
  readonly YES: number
}
