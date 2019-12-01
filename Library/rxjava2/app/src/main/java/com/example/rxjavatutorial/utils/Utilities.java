package com.example.rxjavatutorial.utils;

import android.util.Log;

import io.reactivex.disposables.Disposable;

public class Utilities {
    public static boolean isDisposed(String tag, String observable, Disposable disposable) {
        if (disposable.isDisposed()) {
            Log.i(tag, observable + "is disposed");
            return true;
        }
        else {
            Log.i(tag, observable + "is not disposed");
            return false;
        }
    }
}
