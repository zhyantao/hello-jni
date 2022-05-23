# JNI 入门示例

## 开发环境

| IDE | 备注 | 模式|
| --- | --- | --- |
| Intellij IDEA 2022 专业版 | JDK 1.8.0_331 | 32 位 |
| Visual Studio 社区版 | Debug x86 模式 | 32 位 |

## 运行结果

下载本仓库，然后用 IDEA 打开 `java` 文件夹下的项目，运行 `main()` 函数即可。

```bash
Print By C++	UserData{name='张三', balance=100.0, weekday=[Sun, Mon, Tue]}
Print By Java	UserData{name='张三', balance=100.0, weekday=[Sun, Mon, Tue]}
```

## JNI 的使用步骤

1. 用 IDEA 打开 java 项目，在项目中创建一个类 `HelloJNI`（类名可以随意，类内的方法名也随意）；
2. 在 `src/main/java/` 文件夹下打开 cmd（而不是 PowerShell），使用
   `javah -jni -encoding UTF-8 org.example.HelloJNI` 编译生成 `.h` 文件（命令 `javah` 适用于 JDK 1.8 版本）；
3. 用 Visual Studio 打开 cpp 项目（我们的目标是拿到解决方案为我们生成的 `.dll` 文件）；
4. VS 选择 `Debug` - `x86` 模式，在项目上右击，选择 `属性` > `配置属性` > `VC++ 目录` > 编辑 `包含目录` > 添加 `$(JAVA_HOME)\include` 和 `$(JAVA_HOME)\include\win32` 以及第 2 步生成的 `org_example_HelloJNI.h` 所在的文件夹；
5. 将生成的 `org_example_HelloJNI.h` 复制到到 VS 项目中（目标位置随意），在 VS 项目中，右击 `头文件` > `添加` > `现有项` > 选择 `org_example_HelloJNI.h`；
6. 在 `pch.h` 中添加一句宏定义，后面会用到 `#define API_DLL __declspec(dllexport)`；
7. 在 VS 项目的 `HelloJNI.cpp` 中实现 `org_example_HelloJNI.h` 中声明的函数（可以在该实现中调用 C++ 中的代码）；
8. 将 C++ 项目中需要调用的函数前添加关键字 `API_DLL`；
9. 将 VS 项目的 `属性` > `配置属性` > `常规` > `配置类型` 更改为 `动态库(.dll)`；
10. 在 VS 项目上右击，选择 `重新生成`；
11. 将生成的 `HelloJNI.dll` 复制到 IDEA 项目（根目录）下；
12. 在 Java 项目中使用 `System.loadLibrary("HelloJNI");` 引入动态库；
13. 运行 Java 项目的 `main()` 函数，查看结果。

---

项目源代码：https://github.com/zhyantao/hello-jni.git
