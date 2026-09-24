package to.holepunch.bare;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.Window;

public final class Activity extends android.app.Activity {
  static {
    System.loadLibrary("bare");
  }

  private native void
  setup(Bundle state, AssetManager assets);

  private native void
  teardown();

  private native void
  suspend();

  private native void
  resume();

  @Override
  protected void
  onCreate(Bundle state) {
    // The tree fills the whole window, so there is no room for a title bar: no
    // inset describes it and nothing can be laid out under it.
    requestWindowFeature(Window.FEATURE_NO_TITLE);

    setup(state, getAssets());
    super.onCreate(state);
  }

  // V8 cannot be initialised twice in one process, so the runtime outlives a
  // configuration change and ends with the process.
  @Override
  protected void
  onDestroy() {
    super.onDestroy();

    if (isChangingConfigurations()) return;

    teardown();

    System.exit(0);
  }

  protected void
  onPause() {
    suspend();
    super.onPause();
  }

  protected void
  onResume() {
    resume();
    super.onResume();
  }
}
