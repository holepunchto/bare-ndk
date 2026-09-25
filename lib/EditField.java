package to.holepunch.bare.ndk;

import android.content.Context;
import android.graphics.Rect;
import android.widget.EditText;

// Android reports a text change to a watcher and a caret move and a focus
// change to whoever subclasses the view, so both routes are here rather than
// two objects a caller would have to hold.
public final class EditField extends EditText {
  public static final int EVENT_CHANGED = 1;
  public static final int EVENT_REPLACING = 2;
  public static final int EVENT_SELECTION_CHANGED = 4;
  public static final int EVENT_FOCUS_CHANGED = 8;
  public static final int EVENT_ACTION = 16;

  // Checked here rather than in native code, so an unobserved view costs no
  // transition at all.
  private int events;

  public
  EditField(Context context) {
    super(context);
  }

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onChanged();

  private native void
  onReplacing(String text, int start, int end);

  private native void
  onSelection(int start, int end);

  private native void
  onFocus(boolean focused);

  private native void
  onAction();

  // `TextView` tells a subclass what changed and tells a watcher the same
  // thing, and the two methods have the same signature, so being both
  // delivered every edit twice. This is the subclass half.
  @Override
  protected void
  onTextChanged(CharSequence text, int start, int before, int count) {
    super.onTextChanged(text, start, before, count);

    if ((events & EVENT_REPLACING) != 0) {
      onReplacing(text.subSequence(start, start + count).toString(), start, start + before);
    }

    if ((events & EVENT_CHANGED) != 0) onChanged();
  }

  // What the return key of a software keyboard does, which is the one thing
  // watching the text cannot report.
  @Override
  public void
  onEditorAction(int action) {
    super.onEditorAction(action);

    if ((events & EVENT_ACTION) != 0) onAction();
  }

  @Override
  protected void
  onSelectionChanged(int start, int end) {
    super.onSelectionChanged(start, end);

    // Called while the view is still being constructed, before anything can
    // have asked to hear about it.
    if ((events & EVENT_SELECTION_CHANGED) != 0) onSelection(start, end);
  }

  @Override
  protected void
  onFocusChanged(boolean focused, int direction, Rect previous) {
    super.onFocusChanged(focused, direction, previous);

    if ((events & EVENT_FOCUS_CHANGED) != 0) onFocus(focused);
  }
}
