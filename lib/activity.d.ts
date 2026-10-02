import { Wrapper } from 'bare-jni-registry'
import NDKObject = require('./object')
import NDKResources = require('./resources')

/** The activity the runtime started, as an `android.app.Activity`. */
interface NDKActivity extends NDKObject {
  readonly resources: NDKResources

  /** The colour the theme gives an attribute, by its ID from `android.R.attr`. */
  themeColor(attribute: number): number

  /** Show `view` as the whole content of the activity. */
  contentView(view: Wrapper): this
}

declare class NDKActivity {
  protected constructor()
}

/** The one activity of the app. It already exists, so it is not constructed. */
declare const activity: NDKActivity

export = activity
