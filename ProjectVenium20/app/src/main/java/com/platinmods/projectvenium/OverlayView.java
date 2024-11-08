package com.platinmods.projectvenium;
public class OverlayView extends android.view.View {
    @Override public native void onDraw(android.graphics.Canvas canvas);
    @Override public native boolean onTouchEvent(android.view.MotionEvent event);
    public OverlayView(android.content.Context context){super(context);}
}