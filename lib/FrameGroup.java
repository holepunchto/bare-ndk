package to.holepunch.bare.ndk;

import android.content.Context;
import android.view.MotionEvent;
import android.view.WindowInsets;
import android.view.View;
import android.view.ViewGroup;

// Every frame has already been computed, so this group replays what it was
// given and measures a child to the size it was told rather than asking.
public final class FrameGroup extends ViewGroup {
  public static final int EVENT_SIZE_CHANGED = 1;

  // The actions a `MotionEvent` reports, which is all this group forwards.
  public static final int EVENT_INSETS_CHANGED = 32;

  public static final int EVENT_DOWN = 2;
  public static final int EVENT_MOVE = 4;
  public static final int EVENT_UP = 8;
  public static final int EVENT_CANCEL = 16;

  private static final int EVENT_TOUCH = EVENT_DOWN | EVENT_MOVE | EVENT_UP | EVENT_CANCEL;

  // Checked here rather than in native code, so an unobserved group costs no
  // transition at all.
  private int events;

  public FrameGroup(Context context) {
    super(context);
  }

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onResize(int width, int height);

  private native void
  onTouch(int event, float x, float y, int pointer);

  // Android stops delivering a gesture to a view that let the first event go,
  // so anything listening for any part of one has to claim the press even when
  // it only wants what comes after.
  private native void
  onInsets();

  // The keyboard does not resize the window on every configuration, so what
  // it covers arrives here rather than through a size change.
  @Override
  public WindowInsets
  onApplyWindowInsets(WindowInsets insets) {
    if ((events & EVENT_INSETS_CHANGED) != 0) onInsets();

    return super.onApplyWindowInsets(insets);
  }

  @Override
  public boolean
  onTouchEvent(MotionEvent motion) {
    if ((events & EVENT_TOUCH) == 0) return super.onTouchEvent(motion);

    int action = motion.getActionMasked();
    int event;

    switch (action) {
    case MotionEvent.ACTION_DOWN:
    case MotionEvent.ACTION_POINTER_DOWN:
      event = EVENT_DOWN;
      break;
    case MotionEvent.ACTION_MOVE:
      event = EVENT_MOVE;
      break;
    case MotionEvent.ACTION_UP:
    case MotionEvent.ACTION_POINTER_UP:
      event = EVENT_UP;
      break;
    case MotionEvent.ACTION_CANCEL:
      event = EVENT_CANCEL;
      break;
    default:
      return super.onTouchEvent(motion);
    }

    if ((events & event) == 0) return true;

    // A move carries every pointer at once, where the rest name the one that
    // changed, and every other platform reports one pointer at a time.
    if (event == EVENT_MOVE) {
      for (int i = 0; i < motion.getPointerCount(); i++) {
        onTouch(event, motion.getX(i), motion.getY(i), motion.getPointerId(i));
      }
    } else {
      int i = motion.getActionIndex();

      onTouch(event, motion.getX(i), motion.getY(i), motion.getPointerId(i));
    }

    return true;
  }

  @Override
  protected void
  onSizeChanged(int width, int height, int oldWidth, int oldHeight) {
    super.onSizeChanged(width, height, oldWidth, oldHeight);

    if ((events & EVENT_SIZE_CHANGED) != 0) onResize(width, height);
  }

  public static final class Frame extends ViewGroup.LayoutParams {
    public int x;
    public int y;

    public Frame() {
      super(0, 0);
    }
  }

  public void
  setFrame(View child, int x, int y, int width, int height) {
    Frame frame = (Frame) child.getLayoutParams();

    frame.x = x;
    frame.y = y;
    frame.width = width;
    frame.height = height;

    child.setLayoutParams(frame);
  }

  @Override
  protected ViewGroup.LayoutParams
  generateDefaultLayoutParams() {
    return new Frame();
  }

  @Override
  protected boolean
  checkLayoutParams(ViewGroup.LayoutParams params) {
    return params instanceof Frame;
  }

  @Override
  protected ViewGroup.LayoutParams
  generateLayoutParams(ViewGroup.LayoutParams params) {
    return new Frame();
  }

  // A scroll view measures its child against no bound at all, and a group that
  // knows where it put everything knows what that comes to.
  private static int
  resolve(int spec, int content) {
    return MeasureSpec.getMode(spec) == MeasureSpec.UNSPECIFIED
      ? content
      : MeasureSpec.getSize(spec);
  }

  private static void
  measure(View child, Frame frame) {
    child.measure(
      MeasureSpec.makeMeasureSpec(frame.width, MeasureSpec.EXACTLY),
      MeasureSpec.makeMeasureSpec(frame.height, MeasureSpec.EXACTLY)
    );
  }

  @Override
  protected void
  onMeasure(int widthSpec, int heightSpec) {
    int width = 0;
    int height = 0;

    for (int i = 0; i < getChildCount(); i++) {
      View child = getChildAt(i);

      Frame frame = (Frame) child.getLayoutParams();

      measure(child, frame);

      width = Math.max(width, frame.x + frame.width);
      height = Math.max(height, frame.y + frame.height);
    }

    setMeasuredDimension(resolve(widthSpec, width), resolve(heightSpec, height));
  }

  @Override
  protected void
  onLayout(boolean changed, int left, int top, int right, int bottom) {
    for (int i = 0; i < getChildCount(); i++) {
      View child = getChildAt(i);

      Frame frame = (Frame) child.getLayoutParams();

      if (child.getMeasuredWidth() != frame.width || child.getMeasuredHeight() != frame.height) {
        measure(child, frame);
      }

      child.layout(frame.x, frame.y, frame.x + frame.width, frame.y + frame.height);
    }
  }
}
