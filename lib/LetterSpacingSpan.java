package to.holepunch.bare.ndk;

import android.text.TextPaint;
import android.text.style.MetricAffectingSpan;

// Android spaces the characters of a whole view and has no span of its own for
// spacing a run inside one, so this is that span: it says the same thing to
// the paint that a view would say to itself, and says it where the run is.
public final class LetterSpacingSpan extends MetricAffectingSpan {
  private final float spacing;

  public
  LetterSpacingSpan(float spacing) {
    this.spacing = spacing;
  }

  @Override
  public void
  updateDrawState(TextPaint paint) {
    apply(paint);
  }

  @Override
  public void
  updateMeasureState(TextPaint paint) {
    apply(paint);
  }

  // The paint counts in multiples of the size it is drawing at, where the
  // caller counts in pixels, and only the paint knows the size.
  private void
  apply(TextPaint paint) {
    paint.setLetterSpacing(spacing / paint.getTextSize());
  }
}
