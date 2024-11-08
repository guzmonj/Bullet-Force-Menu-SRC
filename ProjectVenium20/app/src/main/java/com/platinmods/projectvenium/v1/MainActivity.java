/*TODO: If game is unity or if you do have access to a static activity variable for the game,
        you can follow this v1 method and make the following AndroidManifest changes to start:
            * change applications main activity to this one
            * add original main activity as 2nd activity, LEANBACK_LAUNCHER intent w/ other metadata
            * add multidexsupport
        You do not need to worry about anything with this file other than that.
*/

package com.platinmods.projectvenium.v1;
public class MainActivity extends android.app.Activity {
    static { System.loadLibrary("ProjectVenium"); }
    public int layer;
    final android.os.Handler handler = new android.os.Handler(android.os.Looper.getMainLooper());

    @Override protected native void onCreate(android.os.Bundle savedInstanceState);

    public void Check() {
        switch (layer) {
            case 0: new java.util.Timer().schedule(new java.util.TimerTask() { @Override public native void run(); }, 1000); break;
            case 1: handler.post(new Runnable() { @Override public native void run(); }); break;
            default: break;
        }
    }
}