package android.droidcon;

import android.os.RemoteException;

public class DroidconManager {
    IDroidconManager mService;

    /**
     * @hide
     */
    public DroidconManager(IDroidconManager service) {
        mService = service;
    }

    /**
     * Remove every data in the droidcon device.
     */
    public void clear() {
        try {
            mService.clear();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    /**
     * Fetch data from the droidcon device.
     * @return data as a String.
     */
    public String getData() {
        try {
            return mService.getData();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * Feed droidcon device with data.
     * @param data the data as String
     */
    public void putData(String data) {
        try {
            mService.putData(data);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
