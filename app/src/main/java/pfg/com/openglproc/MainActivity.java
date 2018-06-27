package pfg.com.openglproc;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.content.res.AssetManager;
import java.io.InputStream;
import java.io.IOException;
import android.graphics.BitmapFactory;

public class MainActivity extends Activity implements SurfaceHolder.Callback{

    private static final int COLOR_RED = 0;
    private static final int COLOR_GREEN = 1;
    private static final int COLOR_BLUE = 2;

    private native void nativeSetColor(int color);
    private native int nativeSurfaceInit(Object surface, Object bitmap);
    private native void nativeSurfaceFinalize();
    private native int nativeShowBitmap(Object bitmap);

    OpenGLSurfaceView surfaceView;


    static {
        System.loadLibrary("opengl_proc");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        surfaceView = (OpenGLSurfaceView) findViewById(R.id.surface_video);
        SurfaceHolder sh = surfaceView.getHolder();
        sh.addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        AssetManager manager = getAssets();
        InputStream open;
        Bitmap bitmap;
        try {
            open = manager.open("GStreamer_overview_new.png");
            bitmap = BitmapFactory.decodeStream(open);
            nativeSurfaceInit(surfaceHolder.getSurface(), bitmap);
            nativeShowBitmap(bitmap);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            Log.i("OpenGLProc"," exception:"+e.getMessage());
            e.printStackTrace();

        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height) {
        Log.i("OpenGLProc"," surfaceChanged width:"+width+" height:"+height+" format:"+format);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        nativeSurfaceFinalize();
    }

}
