package to.holepunch.bare.ndk;

import android.content.Context;
import android.widget.HorizontalScrollView;

// Android tells whoever subclasses the view that it scrolled, which is the
// same reason the Apple platforms subclass theirs.
public final class HorizontalScrollGroup extends HorizontalScrollView {
  public static final int EVENT_SCROLL = 1;

  // Checked here rather than in native code, so an unobserved view costs no
  // transition at all.
  private int events;

  public
  HorizontalScrollGroup(Context context) {
    super(context);
  }

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onScroll(int x, int y);

  @Override
  protected void
  onScrollChanged(int x, int y, int oldX, int oldY) {
    super.onScrollChanged(x, y, oldX, oldY);

    if ((events & EVENT_SCROLL) != 0) onScroll(x, y);
  }
}
