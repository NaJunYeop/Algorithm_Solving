package com.example.rxjavatutorial;

import android.util.Log;

import com.example.rxjavatutorial.utils.Utilities;

import org.reactivestreams.Subscriber;
import org.reactivestreams.Subscription;

import java.util.ArrayList;
import java.util.List;

import io.reactivex.Observable;
import io.reactivex.Observer;
import io.reactivex.disposables.CompositeDisposable;
import io.reactivex.disposables.Disposable;
import io.reactivex.observables.ConnectableObservable;

public class ObservableTest {
    private static final String TAG = "ObservableTest_Tag";

    private CompositeDisposable compositeDisposable;
    private ConnectableObservable<String> connectableObservable;
    private Disposable disposable1;
    private Disposable disposable2;
    private Observable<String> observable;
    private Observer<String> observer1;
    private Observer<String> observer2;
    private List<String> list;

    public ObservableTest() {
        initialize();
    }

    public void test() {
        observable = Observable.fromIterable(list);
        observable.subscribe(observer1);
        observable.subscribe(observer2);

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);

        compositeDisposable.clear();

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);

        observable.subscribe(observer1);
    }

    private void initialize() {
        compositeDisposable = new CompositeDisposable();
        list = new ArrayList<>();

        list.add("list : [1]");
        list.add("list : [2]");
        list.add("list : [3]");

        observer1 = new Observer<String>() {
            @Override
            public void onSubscribe(Disposable d) {
                compositeDisposable.add(disposable1 = d);
            }

            @Override
            public void onNext(String s) {
                Log.i(TAG,"Observer[1] : " + s);
            }

            @Override
            public void onError(Throwable e) {

            }

            @Override
            public void onComplete() {

            }
        };

        observer2 = new Observer<String>() {
            @Override
            public void onSubscribe(Disposable d) {
                compositeDisposable.add(disposable2 = d);
            }

            @Override
            public void onNext(String s) {
                Log.i(TAG,"Observer[2] : " + s);
            }

            @Override
            public void onError(Throwable e) {

            }

            @Override
            public void onComplete() {

            }
        };
    }

    private void isDisposed(String dName, Disposable disposable) {
            if (disposable.isDisposed()) {
            Log.i(TAG, dName + " is disposed");
        }
        else {
            Log.i(TAG, dName + " is not disposed");
        }
    }
}
