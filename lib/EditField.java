package to.holepunch.bare.ndk;

import android.content.Context;
import android.graphics.Rect;
import android.widget.EditText;

// Android reports text changes to a watcher, and caret and focus changes to a
// subclass, so this view is both.
public final class EditField extends EditText {
  public static final int EVENT_CHANGED = 1;
  public static final int EVENT_REPLACING = 2;
  public static final int EVENT_SELECTION_CHANGED = 4;
  public static final int EVENT_FOCUS_CHANGED = 8;
  public static final int EVENT_ACTION = 16;

  // Checked here, so a view that nobody listens to never calls into native
  // code.
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

  // `TextView` reports an edit both to a subclass and to a watcher, with the
  // same method, so being both would deliver every edit twice. This is the
  // subclass half.
  @Override
  protected void
  onTextChanged(CharSequence text, int start, int before, int count) {
    super.onTextChanged(text, start, before, count);

    if ((events & EVENT_REPLACING) != 0) {
      onReplacing(text.subSequence(start, start + count).toString(), start, start + before);
    }

    if ((events & EVENT_CHANGED) != 0) onChanged();
  }

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

    // Called while the view is still being built, before anything can listen.
    if ((events & EVENT_SELECTION_CHANGED) != 0) onSelection(start, end);
  }

  @Override
  protected void
  onFocusChanged(boolean focused, int direction, Rect previous) {
    super.onFocusChanged(focused, direction, previous);

    if ((events & EVENT_FOCUS_CHANGED) != 0) onFocus(focused);
  }
}
