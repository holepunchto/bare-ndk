package to.holepunch.bare.ndk;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

// `AlertDialog` cannot be changed once it is built and has exactly three button
// slots, so the whole dialog is described at once and the slot that was pressed
// is reported back.
public final class Dialog implements DialogInterface.OnClickListener, DialogInterface.OnCancelListener {
  public static final int DISMISSED = 0;

  private final AlertDialog dialog;

  private boolean answered;

  public
  Dialog(Context context, String title, String message, String positive, String negative, String neutral) {
    AlertDialog.Builder builder = new AlertDialog.Builder(context);

    builder.setTitle(title);

    if (message != null) builder.setMessage(message);

    if (positive != null) builder.setPositiveButton(positive, this);
    if (negative != null) builder.setNegativeButton(negative, this);
    if (neutral != null) builder.setNeutralButton(neutral, this);

    builder.setOnCancelListener(this);

    dialog = builder.create();
  }

  public void
  show() {
    dialog.show();
  }

  private native void
  onResponse(int which);

  // A dialog can be cancelled as its button is pressed, and only the first of
  // the two is reported.
  private void
  answer(int which) {
    if (answered) return;

    answered = true;

    onResponse(which);
  }

  @Override
  public void
  onClick(DialogInterface dialog, int which) {
    answer(which);
  }

  @Override
  public void
  onCancel(DialogInterface dialog) {
    answer(DISMISSED);
  }
}
