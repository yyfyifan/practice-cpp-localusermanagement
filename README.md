# README

* Video链接： https://www.youtube.com/watch?v=I_aWPGCaaFA&loop=0

这是一个C++的基于terminal的练习项目，允许用户选择注册或者登录，并且讲注册好的用户信息保存在文件中。

* 基本use case
    1. 显示提示菜单，让用户选择 注册 or 登录
    2. 如果用户选择注册，则提示输入账号密码，并且把结果存储到文件
    3. 如果用户选择登录，则提示输入账号密码，然后检测是否登陆成功


* 可选功能
    * [x] 改写成OOP方式
    * [x] 查看所有已注册用户
    * [x] 删除用户
    * 用户输入密码时显示*     
    * [x] 对用户密码进行加密存储
    

## 知识记录

1. `while(!cin)` 或者 `while(cin >> x)` 或者 `while(cin)`
    * 这几种写法都是基于istream来判断自身的true或者false。 `istream`这个类重载了`operator!`, 效果和调用`cin.fail()`一样，即如果自身出现了错误则返回true，否则返回false
    * 当读取失败的时候，fstream会把内部的failbit给设置起来，之后判断`!cin`就会返回true代表读取失败。
    * 调用`cin.clear()`会清除这个failbit状态

2. 清除istream缓冲区的内容
    ```cpp
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ```
3. `[[ noreturn ]]` 是一个C++ attribute，用来声明一个函数没有返回值。
    > [参考文档](https://en.cppreference.com/w/cpp/language/attributes/noreturn)

4. 文件操作教程
    > [参考文档](https://www.learncpp.com/cpp-tutorial/basic-file-io/)
    1. ifstream 和 ofstream是否需要调用close：这两个对象都会在销毁的时候自动关闭，但是为了避免系统意外crash
       造成缓存没有处理的情况，最好在使用完毕后自动调用close方法
    2. 输出流缓存：C++的输出流在很多时候都是有buffer的，主要是为了性能考虑。可以主动flush的方法有：
        1. 调用`ostream::flush()`方法
        2. 将`std::flush` 输出给output stream
        3. 将`std::endl` 输出给output stream
        4. 调用`ostream::close()`方法
    3. 文件模式：使用ios file stream的时候有下面的模式参数可以传递
       
       | Ios file mode | Meaning |
       | ----- | ----- |
       | app | Opens the file in append mode |
       |  ate | Seeks to the end of the file before reading/writing |
       | binary | Opens the file in binary mode (instead of text mode) |
       | in | Opens the file in read mode (**default for ifstream**) | 
       | out | Opens the file in write mode (**default for ofstream**) |
       | trunc | Erases the file if it already exists |
    
        例如
        ```cpp
        // 使用append模式打开
        std::ofstream outf{ "Sample.dat", std::ios::app };
        ```
    4. 列出目录中所有文件： C++ 17引入了`std::filesystem`，可以通过如下代码处理 
        ```cpp
        #include <filesystem>
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            std::cout << entry.path() << "\n";
        }
        ```
    5. 关于其他filename的相关操作
        > [参考链接](https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path)
       ```cpp
       string filename = "C:\\MyDirectory\\MyFile.bat";

       std::cout << fs::path(filename).filename() << '\n'   // MyFile.bat
        << fs::path(filename).stem() << '\n'                // MyFile
        << fs::path("/foo/bar.txt").filename() << '\n'      // bar.txt
        << fs::path("/foo/bar.txt").stem() << '\n'          // bar
        << fs::path("/foo/.bar").filename() << '\n'         // .
        << fs::path("/foo/bar/").filename() << '\n'         // .
        << fs::path("/foo/.").filename() << '\n'            // ..
        << fs::path("/foo/..").filename() << '\n'           // .
        << fs::path(".").filename() << '\n'                 // .
        << fs::path("..").filename() << '\n'                // ..
        << fs::path("/").filename() << '\n';                // /
       ```
       
5. 引入静态库 .a 文件和相关头文件的方法
    > [参考链接](https://www.jianshu.com/p/37fbe3dd202b)
    ```cmake
    include_directories(${CMAKE_SOURCE_DIR}/inc)
    link_directories(${CMAKE_SOURCE_DIR}/lib)
    
    add_executable(foo ${FOO_SRCS})
    target_link_libraries(foo bar)
    ```
   
6. 使用hashlib++对字符串进行加密
    [官方网站](http://hashlib2plus.sourceforge.net/index.html)