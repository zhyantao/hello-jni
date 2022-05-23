package org.example;

import java.util.Arrays;

public class UserData {

    private String name;
    private double balance;

    private String[] weekday;

    public String[] getWeekday() {
        return weekday;
    }

    public void setWeekday(String[] weekday) {
        this.weekday = weekday;
    }

    public String getUserInfo() {
        return "UserData{" +
                "name='" + name + '\'' +
                ", balance=" + balance +
                ", weekday=" + Arrays.toString(weekday) +
                '}';
    }

}
