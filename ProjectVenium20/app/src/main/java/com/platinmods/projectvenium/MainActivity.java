/*TODO: The library in the stored png file for sideload use represents the first part of the file.
        Currently, the lib is to be placed in the normal lib spot based off the code below, as it has
            not been changed to load from assets. This should be ported to JNI as well.
*/

package com.platinmods.projectvenium;
public class MainActivity {
    public native void I(android.content.Context context);
    public MainActivity(android.content.Context context) {
        String apkLibDir = context.getApplicationInfo().nativeLibraryDir;
        String libraryPath = apkLibDir + "/" + System.mapLibraryName("Platinmods");
        System.load(libraryPath);
        I(context);
    }
}