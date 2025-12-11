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

  protected void
  onDestroy() {
    teardown();
    super.onDestroy();
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
