package org.example;

public class App {

    static {
        // 引入 C++ 动态库并运行
        System.loadLibrary("HelloJNI");
    }

    public static void main( String[] args ) {

        HelloJNI helloJNI = new HelloJNI();

        // 设置用户信息
        UserData user = helloJNI.createUser("张三", 100, new String[]{"Sun", "Mon", "Tue"});

        // 打印用户信息
        String str = helloJNI.printUserData(user);
        System.out.println("Print By Java\t" + str);
    }

}
