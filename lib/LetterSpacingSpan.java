package to.holepunch.bare.ndk;

import android.text.TextPaint;
import android.text.style.MetricAffectingSpan;

// Android can only space the characters of a whole view and has no span for a
// run, so this is that span. It tells the paint what a view would tell itself.
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

  // The paint counts in multiples of the text size and the caller counts in
  // pixels, and only the paint knows the size.
  private void
  apply(TextPaint paint) {
    paint.setLetterSpacing(spacing / paint.getTextSize());
  }
}
