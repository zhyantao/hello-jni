package org.example;

public class HelloJNI {

    public native UserData createUser(String name, double balance, String[] weekday);

    public native String printUserData(UserData user);

}
