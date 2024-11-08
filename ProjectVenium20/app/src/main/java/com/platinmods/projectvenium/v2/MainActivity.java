/*TODO: If game is not unity and/or you do not have access to a static activity variable, you will
        have to copy and paste the following to the game's main activity smali to start:
            * Static Library Call
            * 'Init' Native Method Declaration
            * 'Init' Call From This OnCreate to Game's
        This file should not be added.
*/

package com.platinmods.projectvenium.v2;
public class MainActivity extends android.app.Activity {
    static { System.loadLibrary("ProjectVenium"); }
    public native void Init(android.content.Context context);

    @Override protected void onCreate(android.os.Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Init(this);
    }
}