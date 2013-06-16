package com.android.server;

import android.content.Context;
import android.util.Slog;
import android.droidcon.LibDroidcon;
import android.droidcon.DroidconException;
import android.droidcon.IDroidconManager;

/**
 * @hide
 */
class DroidconService extends IDroidconManager.Stub {
    private static final String TAG = "DroidconService";
    private Context mContext;


    DroidconService(Context context) {
        mContext = context;
    }

    private void enforceAccessPermission() {
        mContext.enforceCallingOrSelfPermission(android.Manifest.permission.DROIDCON_ACCESS,
                                                "DroidconService");
    }

    public void clear() {
        enforceAccessPermission();
        LibDroidcon.clear();
    }

    public String getData() {
        enforceAccessPermission();
        try {
            return LibDroidcon.getData();
        } catch(DroidconException e) {
            Slog.d(TAG, "cannot getdata");
        }
        return null;
    }

    public void putData(String in) {
        enforceAccessPermission();
        try {
            LibDroidcon.putData(in);
        } catch(DroidconException e) {
            Slog.d(TAG, "cannot putdata");
        }
    }
}
