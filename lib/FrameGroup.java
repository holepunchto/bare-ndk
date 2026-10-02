package to.holepunch.bare.ndk;

import android.content.Context;
import android.content.res.Configuration;
import android.view.MotionEvent;
import android.view.WindowInsets;
import android.view.View;
import android.view.ViewGroup;

// Every frame is already worked out, so this group places each child where it
// was told and measures it at that size.
public final class FrameGroup extends ViewGroup {
  public static final int EVENT_SIZE_CHANGED = 1;

  public static final int EVENT_INSETS_CHANGED = 32;

  public static final int EVENT_CONFIGURATION_CHANGED = 64;

  public static final int EVENT_DOWN = 2;
  public static final int EVENT_MOVE = 4;
  public static final int EVENT_UP = 8;
  public static final int EVENT_CANCEL = 16;

  private static final int EVENT_TOUCH = EVENT_DOWN | EVENT_MOVE | EVENT_UP | EVENT_CANCEL;

  // Checked here, so a group that nobody listens to never calls into native
  // code.
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

  // Android stops sending a gesture to a view that ignored its first event, so
  // a listener for any part of a gesture has to claim the press.
  private native void
  onInsets();

  // The manifest keeps the activity alive when the configuration changes, so
  // this is where switching to dark mode arrives.
  private native void
  onConfiguration();

  @Override
  public void
  onConfigurationChanged(Configuration configuration) {
    super.onConfigurationChanged(configuration);

    if ((events & EVENT_CONFIGURATION_CHANGED) != 0) onConfiguration();
  }

  // The keyboard does not always resize the window, so what it covers arrives
  // here instead of as a size change.
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

    // A move carries every pointer, while the other actions name the one that
    // changed. Every other platform reports one pointer at a time.
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

  // A scroll view measures its child with no limit, so report the size of
  // everything placed.
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
