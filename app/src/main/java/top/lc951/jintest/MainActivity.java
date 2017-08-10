package top.lc951.jintest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.util.ArrayList;

//http://blog.csdn.net/lius1984/article/details/9114451
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);

    }

    public void getStringFromJni(View view){
        tv.setText(stringFromJNI());
    }
    public void getintFromJni(View view){
        tv.setText(intFromJNI()+"");
    }
    public void printfJava(View view){
        print();
    }
    public void printBase(View view){
        String str="Byte="+byteFromJNI((byte) 1)
                +" char="+charFromJNI('d')
                +" short="+shortFromJNI((short) 2)
                +" long="+longFromJNI(2l)
                +" float="+floatFromJNI(2f)
                +" double="+doubleFromJNI(2)
                +" String="+StringFromJNI1("abc")
                ;

        tv.setText(str);

        getTwoArray(10);

        nativeGetStudentInfo();

        printStuInfoAtNative(new Student(28,"lc951"));

        ArrayList<Student> list=native_getListStudents();
        Log.d("student",list.toString());

        doCallBack();
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int intFromJNI();
    public native byte byteFromJNI(byte b);
    public native char charFromJNI(char c);
    public native short shortFromJNI(short s);
    public native long longFromJNI(long l);
    public native float floatFromJNI(float f);
    public native double doubleFromJNI(double d);
    public native String StringFromJNI1(String s);
    //参数代表几行几列数组 ，形式如：int a[dimon][dimon]
    private native int[][] getTwoArray(int dimon) ;

    //Native层回调的方法实现
    public void callback(String fromNative){
        System.out.println(" I was invoked by native method  ############# " + fromNative);
    };
    public native void doCallBack(); //Native层会调用callback()方法

    public native void print();

    //在Native层返回一个Student对象
    public native Student nativeGetStudentInfo() ;

    //在Native层打印Student的信息
    public native void  printStuInfoAtNative(Student stu);

    //在Native层返回ArrayList集合
    public native ArrayList<Student> native_getListStudents();
}
