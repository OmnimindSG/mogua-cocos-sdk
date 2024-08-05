package io.mogua.sdk;

import java.util.HashMap;

public class MoguaCocosOpenCallback implements MoguaCallback {

    native void jniOnData(HashMap<String, Object> data);

    @Override
    public void onData(HashMap<String, Object> data) {
        jniOnData(data);
    }

    native void jniOnError(Exception e);

    @Override
    public void onError(Exception e) {
        jniOnError(e);
    }

}

