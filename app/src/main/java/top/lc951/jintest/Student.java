package top.lc951.jintest;

/**
 * Created by lichong on 2017/8/10.
 *
 * @ Email lichongmac@163.com
 */

public class Student {
    private int age ;
    private String name ;
    //构造函数，什么都不做
    public Student(){ }

    public Student(int age ,String name){
        this.age = age ;
        this.name = name ;
    }

    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }
    public String getName() {
        return name;
    }
    public void setName(String name){
        this.name = name;
    }

    public String toString(){
        return "name --- >" + name + "  age --->" + age ;
    }
}
