package com.example.rxjavatutorial;

import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import io.reactivex.Observable;
import io.reactivex.Observer;
import io.reactivex.disposables.CompositeDisposable;
import io.reactivex.disposables.Disposable;
import io.reactivex.subjects.PublishSubject;

public class PublishSubjectTest {
    private static final String TAG = "PublishSubjectTest_Tag";
    private PublishSubject<String> publishSubject;
    private Observable observable;
    private Observer<String> observer1;
    private Observer<String> observer2;
    private CompositeDisposable compositeDisposable;
    private Disposable disposable1;
    private Disposable disposable2;
    private List<String> list;

    public PublishSubjectTest() {
        initialize();
    }

    public void test1() {
        // PublishSubject가 onNext() Method를 Call하면 Observer들에게 Data를 Emit한다.
        Log.i(TAG, "test[1] method ======================================");

        publishSubject = PublishSubject.create();

        publishSubject.subscribe(observer1);
        publishSubject.onNext("This is new String");

        publishSubject.subscribe(observer2);
        publishSubject.onNext("And this is the second String emitted");

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);

        compositeDisposable.clear();

        publishSubject.onNext("Emit data after dispose");

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);

        publishSubject = null;
    }

    public void test2() {
        // PublishSubject가 Observable을 subscribe하고 있으면 onNext() Method로 Data를 Observer들에게 Emit할 수 없다.

        Log.i(TAG, "test[2] method ======================================");

        observable = Observable.fromIterable(list);

        publishSubject = PublishSubject.create();
        publishSubject.subscribe(observer1);
        publishSubject.subscribe(observer2);

        observable.subscribe(publishSubject);

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);

        publishSubject.onNext("This is new String");

        compositeDisposable.clear();

        isDisposed("Observer[1]", disposable1);
        isDisposed("Observer[2]", disposable2);
    }

    public void initialize() {
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
                Log.i(TAG, "Observer[1] : " + s);
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
                Log.i(TAG, "Observer[2] : " + s);
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
