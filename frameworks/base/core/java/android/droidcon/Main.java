package android.droidcon;

import android.util.Log;

/** @hide */
public class Main {
  public static void main (String[] args) {
      try {
          LibDroidcon.putData("Hello");
          String out = LibDroidcon.getData();
          System.out.println(out);
          LibDroidcon.clear();
      } catch (Exception e) {
          Log.d("droidcon", e.toString());
      }
  }
}
