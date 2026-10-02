import { Wrapper } from 'bare-jni-registry'

export interface Measurement {
  width: number
  height: number
  lines: number
}

/**
 * Measure `text` as a text view would show it, wrapped at `width` pixels, which defaults to
 * `Infinity`. `style.size` is in pixels, and 0 means the default size. Results are cached.
 */
export function measure(
  text: string,
  style?: { family?: string | null; size?: number },
  width?: number
): Measurement

/**
 * Measure styled text from an `NDKSpannableStringBuilder`, wrapped at `width` pixels. A
 * `lineHeight` of 0, the default, uses the height of the font.
 */
export function measureSpanned(text: Wrapper, width?: number, lineHeight?: number): Measurement
