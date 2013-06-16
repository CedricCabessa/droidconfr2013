package android.droidcon;

/**
 * @hide
 */
public class LibDroidcon {
    public native static void clear();
    public native static String getData() throws DroidconException;
    public native static void putData(String in) throws DroidconException;

    static {
        System.loadLibrary("droidcon_jni");
    }
}
