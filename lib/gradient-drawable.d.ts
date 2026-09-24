import NDKDrawable = require('./drawable')

/** A filled shape with rounded corners and a border, as a `GradientDrawable`. */
interface NDKGradientDrawable extends NDKDrawable {
  setColor(color: number): this

  setCornerRadius(radius: number): this

  /** Set each corner, as eight radii: x and y for the top left, top right, bottom right, bottom left. */
  setCornerRadii(radii: number[]): this

  /** Draw a border. Give `dashWidth` and `dashGap` for a dashed one. */
  setStroke(width: number, color: number, dashWidth?: number, dashGap?: number): this
}

declare class NDKGradientDrawable {
  constructor()
}

export = NDKGradientDrawable
