#include <jni.h>
#include <string>

#include "android/log.h"

//http://blog.csdn.net/lius1984/article/details/9114451



extern "C" {


JNIEXPORT jint JNICALL
Java_top_lc951_jintest_MainActivity_intFromJNI(JNIEnv *env, jobject instance) {

    // TODO
    return 100;
}



JNIEXPORT jstring JNICALL
Java_top_lc951_jintest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_top_lc951_jintest_MainActivity_print(JNIEnv *env, jobject instance) {

    // TODO
    printf("Java_top_lc951_jintest_MainActivity_print\n");
    __android_log_print(__ANDROID_API_I__,"JNI","This is log");
}

JNIEXPORT jbyte JNICALL
Java_top_lc951_jintest_MainActivity_byteFromJNI(JNIEnv *env, jobject instance, jbyte b) {

    return b;
}
JNIEXPORT jchar JNICALL
Java_top_lc951_jintest_MainActivity_charFromJNI(JNIEnv *env, jobject instance, jchar c) {

    return c;

}

JNIEXPORT jshort JNICALL
Java_top_lc951_jintest_MainActivity_shortFromJNI(JNIEnv *env, jobject instance, jshort s) {

    return s;

}

JNIEXPORT jlong JNICALL
Java_top_lc951_jintest_MainActivity_longFromJNI(JNIEnv *env, jobject instance, jlong l) {

    return l;

}

JNIEXPORT jfloat JNICALL
Java_top_lc951_jintest_MainActivity_floatFromJNI(JNIEnv *env, jobject instance, jfloat f) {

    return f;

}
JNIEXPORT jdouble JNICALL
Java_top_lc951_jintest_MainActivity_doubleFromJNI(JNIEnv *env, jobject instance, jdouble d) {

    return d;

}
JNIEXPORT jstring JNICALL
Java_top_lc951_jintest_MainActivity_StringFromJNI1(JNIEnv *env, jobject instance, jstring s_) {
    const char *s = env->GetStringUTFChars(s_, 0);

    env->ReleaseStringUTFChars(s_, s);

    return env->NewStringUTF(s);
}
JNIEXPORT jclass JNICALL
Java_top_lc951_jintest_MainActivity_classFromJNI(JNIEnv *env, jobject instance, jclass c) {

    return c;

}
/*
 * Class:     com_feixun_jni_HelloJni
 * Method:    getTwoArray
 * Signature: (I)[[I
 */
//通过构造一个数组的数组， 返回 一个二维数组的形式
JNIEXPORT jobjectArray JNICALL
Java_top_lc951_jintest_MainActivity_getTwoArray(JNIEnv *env, jobject instance, jint dimon) {

    jclass intArrayClass = env->FindClass("[I"); //获得一维数组 的类引用，即jintArray类型
    //构造一个指向jintArray类一维数组的对象数组，该对象数组初始大小为dimion
    jobjectArray obejctIntArray  =  env->NewObjectArray(dimon ,intArrayClass , NULL);

    //构建dimion个一维数组，并且将其引用赋值给obejctIntArray对象数组
    for( int i = 0 ; i< dimon  ; i++ )
    {
        //构建jint型一维数组
        jintArray intArray = env->NewIntArray(dimon);

        jint temp[10]  ;  //初始化一个容器，假设 dimion  < 10 ;
        for( int j = 0 ; j < dimon ; j++)
        {
            temp[j] = i + j  ; //赋值
        }

        //设置jit型一维数组的值
        env->SetIntArrayRegion(intArray, 0 , dimon ,temp);
        //给object对象数组赋值，即保持对jint一维数组的引用
        env->SetObjectArrayElement(obejctIntArray , i ,intArray);

        env->DeleteLocalRef(intArray);  //删除局部引用
    }

    return   obejctIntArray; //返回该对象数组

}
//Native层回调Java类方法
JNIEXPORT void JNICALL
Java_top_lc951_jintest_MainActivity_doCallBack(JNIEnv *env, jobject obj) {

    //回调Java中的方法

    jclass cls = env->GetObjectClass(obj);//获得Java类实例
    jmethodID callbackID = env->GetMethodID(cls , "callback" , "(Ljava/lang/String;)V") ;//或得该回调方法句柄

    if(callbackID == NULL)
    {
        __android_log_print(__ANDROID_API_I__,"JNI","getMethodId is failed");
    }

    jstring native_desc = env->NewStringUTF(" I am Native");

    env->CallVoidMethod(obj , callbackID , native_desc); //回调该方法，并且传递参数值
}

JNIEXPORT jobject JNICALL
Java_top_lc951_jintest_MainActivity_nativeGetStudentInfo(JNIEnv *env, jobject instance) {

    //关于包描述符，这儿可以是 top.lc951.jintest 或者是 Ltop.lc951.jintest /Student;
    //   这两种类型 都可以获得class引用
    jclass stucls = env->FindClass("top/lc951/jintest/Student"); //或得Student类引用

    //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID constrocMID = env->GetMethodID(stucls,"<init>","(ILjava/lang/String;)V");

    jstring str = env->NewStringUTF(" come from Native ");

    jobject stu_ojb = env->NewObject(stucls,constrocMID,11,str);  //构造一个对象，调用该类的构造函数，并且传递参数


    return stu_ojb ;

}
//第二个类实例引用代表Student类，即我们传递下来的对象
//在Native层输出Student的信息
JNIEXPORT void JNICALL
Java_top_lc951_jintest_MainActivity_printStuInfoAtNative(JNIEnv *env, jobject instance,
                                                         jobject objstu) {

    jclass stucls = env->GetObjectClass(objstu); //或得Student类引用

    if(stucls == NULL)
    {
        __android_log_print(__ANDROID_API_I__,"JNI","GetObjectClass failed \\n");
    }
    //下面这些函数操作，我们都见过的。O(∩_∩)O~
    jfieldID ageFieldID = env->GetFieldID(stucls,"age","I"); //获得得Student类的属性id
    jfieldID nameFieldID = env->GetFieldID(stucls,"name","Ljava/lang/String;"); // 获得属性ID

    jint age = env->GetIntField(objstu , ageFieldID);  //获得属性值
    jstring name = (jstring)env->GetObjectField(objstu , nameFieldID);//获得属性值

    const char * c_name = env->GetStringUTFChars(name ,NULL);//转换成 char *

    env->ReleaseStringUTFChars(name,c_name); //释放引用

    __android_log_print(__ANDROID_API_I__,"JNI"," at Native age is : # name is ");

}

//获得集合类型的数组
JNIEXPORT jobject JNICALL
Java_top_lc951_jintest_MainActivity_native_1getListStudents(JNIEnv *env, jobject instance) {

    jclass list_cls = env->FindClass("java/util/ArrayList");//获得ArrayList类引用

    if(list_cls == NULL)
    {
        __android_log_print(__ANDROID_API_I__,"JNI","listcls is null \n");
    }
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V"); //获得得构造函数Id

    jobject list_obj = env->NewObject(list_cls , list_costruct); //创建一个Arraylist集合对象
    //或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    jmethodID list_add  = env->GetMethodID(list_cls,"add","(Ljava/lang/Object;)Z");

    jclass stu_cls = env->FindClass("top/lc951/jintest/Student");//获得Student类引用top.lc951.jintest
    //获得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID stu_costruct = env->GetMethodID(stu_cls , "<init>", "(ILjava/lang/String;)V");

    for(int i = 0 ; i < 3 ; i++)
    {
        jstring str = env->NewStringUTF("Native");
        //通过调用该对象的构造函数来new 一个 Student实例
        jobject stu_obj = env->NewObject(list_cls , stu_costruct , 10,str);  //构造一个对象

        env->CallBooleanMethod(list_obj , list_add , stu_obj); //执行Arraylist类实例的add方法，添加一个stu对象
    }

    return list_obj ;

}

}










