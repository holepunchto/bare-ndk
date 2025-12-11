package to.holepunch.bare;

import android.content.res.AssetManager;
import android.os.Bundle;

public class Activity extends android.app.Activity {
  static {
    System.loadLibrary("bare");
  }

  private native void
  onCreate(AssetManager assetManager);

  @Override
  protected void
  onCreate(Bundle state) {
    onCreate(getAssets());

    super.onCreate(state);
  }
}
