package to.holepunch.bare.ndk;

import android.view.Choreographer;

// Choreographer tells an object about each frame it is posted for, so the
// callback is an object of its own.
public final class FrameCallback implements Choreographer.FrameCallback {
  public static final int EVENT_FRAME = 1;

  private int events;

  public void
  setEvents(int events) {
    this.events = events;
  }

  private native void
  onFrame(long frameTimeNanos);

  @Override
  public void
  doFrame(long frameTimeNanos) {
    if ((events & EVENT_FRAME) != 0) onFrame(frameTimeNanos);
  }
}
