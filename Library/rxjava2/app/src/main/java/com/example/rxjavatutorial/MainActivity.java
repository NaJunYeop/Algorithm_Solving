package com.example.rxjavatutorial;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import io.reactivex.Observable;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.CompositeDisposable;
import io.reactivex.disposables.Disposable;
import io.reactivex.functions.Consumer;
import io.reactivex.schedulers.Schedulers;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "RX_TEST";
    private ObservableTest observableTest;
    private PublishSubjectTest publishSubjectTest;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Observable Test !!!
        // observableTest = new ObservableTest();
        // observableTest.test();

        // PublishSubject Test !!!
        publishSubjectTest = new PublishSubjectTest();
        //publishSubjectTest.test1();
        publishSubjectTest.test2();
    }
}
