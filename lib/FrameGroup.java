package to.holepunch.bare.ndk;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;

// Every frame has already been computed, so this group replays what it was
// given and measures a child to the size it was told rather than asking.
public final class FrameGroup extends ViewGroup {
  public static final int EVENT_RESIZE = 1;

  // Checked here rather than in native code, so an unobserved group costs no
  // transition at all.
  private int events;

  public
  FrameGroup(Context context) {
    super(context);
  }

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onResize(int width, int height);

  @Override
  protected void
  onSizeChanged(int width, int height, int oldWidth, int oldHeight) {
    super.onSizeChanged(width, height, oldWidth, oldHeight);

    if ((events & EVENT_RESIZE) != 0) onResize(width, height);
  }

  public static final class Frame extends ViewGroup.LayoutParams {
    public int x;
    public int y;

    public
    Frame() {
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

  @Override
  protected void
  onMeasure(int widthSpec, int heightSpec) {
    for (int i = 0; i < getChildCount(); i++) {
      View child = getChildAt(i);

      Frame frame = (Frame) child.getLayoutParams();

      child.measure(
        MeasureSpec.makeMeasureSpec(frame.width, MeasureSpec.EXACTLY),
        MeasureSpec.makeMeasureSpec(frame.height, MeasureSpec.EXACTLY)
      );
    }

    setMeasuredDimension(MeasureSpec.getSize(widthSpec), MeasureSpec.getSize(heightSpec));
  }

  @Override
  protected void
  onLayout(boolean changed, int left, int top, int right, int bottom) {
    for (int i = 0; i < getChildCount(); i++) {
      View child = getChildAt(i);

      Frame frame = (Frame) child.getLayoutParams();

      child.layout(frame.x, frame.y, frame.x + frame.width, frame.y + frame.height);
    }
  }
}
