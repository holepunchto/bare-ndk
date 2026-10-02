package to.holepunch.bare.ndk;

import android.content.Context;
import android.widget.HorizontalScrollView;

// Android only tells a subclass that the view scrolled.
public final class HorizontalScrollGroup extends HorizontalScrollView {
  public static final int EVENT_SCROLL_CHANGED = 1;

  // Checked here, so a view that nobody listens to never calls into native
  // code.
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

    if ((events & EVENT_SCROLL_CHANGED) != 0) onScroll(x, y);
  }
}
