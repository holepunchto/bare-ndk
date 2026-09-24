package to.holepunch.bare;

import android.content.res.AssetManager;
import android.os.Bundle;

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
    setup(state, getAssets());
    super.onCreate(state);
  }

  // V8 cannot be initialised twice in one process, and disposing it does not
  // make it possible, so the runtime outlives a configuration change and the
  // process ends with anything else.
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
