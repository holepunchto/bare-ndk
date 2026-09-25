package to.holepunch.bare.ndk;

import android.content.Context;
import android.graphics.Rect;
import android.widget.CompoundButton;
import android.widget.Switch;

// The widget's own name is taken, so the subclass is named for what it
// reports. Android tells a listener that the check changed and tells a
// subclass nothing, so the view is its own listener rather than an object a
// caller would have to hold.
public final class Toggle extends Switch implements CompoundButton.OnCheckedChangeListener {
  public static final int EVENT_CHECKED = 1;
  public static final int EVENT_FOCUS_CHANGED = 2;

  private int events;

  public
  Toggle(Context context) {
    super(context);

    setOnCheckedChangeListener(this);
  }

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onChecked();

  private native void
  onFocus(boolean focused);

  @Override
  public void
  onCheckedChanged(CompoundButton button, boolean checked) {
    if ((events & EVENT_CHECKED) != 0) onChecked();
  }

  @Override
  protected void
  onFocusChanged(boolean focused, int direction, Rect previous) {
    super.onFocusChanged(focused, direction, previous);

    if ((events & EVENT_FOCUS_CHANGED) != 0) onFocus(focused);
  }
}
