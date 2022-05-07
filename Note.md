# C++ Primer 笔记

## Getting started

使用流进行输入和输出：

```cpp
#include <iostream>

int main(){
    int a;
    std::cin>>a;
	std::cout<<"Hello, world!"<<std::endl;
}
```

代码的第一行表示我们引入了 i/o 流的库。第五行和第六行表示我们使用了 `std` 命名空间当中的 `cin` 和 `cout` 对象、以及 `endl` 对象。

接下来就是类的概念。

- name?
- where defined?
- what operations?

```cpp
int a = 0;
int a = {0};// list initialization
int a{0};// list initialization
int a(0);
```

若我们使用 list 初始化，则必须使用相同类型的初始值。

带有 `extern` 关键字的声明不会初始化变量。

引用类型：

```cpp
int refVal = 2;
int &refVal3 = refVal;
```

表示我们创造一个引用类型。注意我们使用引用的时候，如果对象是 `const` 关键字，那么引用对象也应该声明为 `const`。如果我们引用了一个非 `const` 量并且把这个引用声明成 `const`，则我们绑定的值并非是我们想要的那个值。对于指针我们也是如此。

constant expressions 表示在编译的时候就已经知道的 `const` 值。在新的标准下我们可以使用 `constexpr` 关键词去表示其是 constant expression。

`typedef` 语句可以声明一到两种别名。在 c++11 中我们可以使用如下的语句作为声明：

```cpp
using SI = Sales_item // SI is a synonym for Sales_item
```

在 c++11 中我们可以使用 `auto` 关键词来使得我们的变量根据右侧初始值自动决定类型。`auto` 会忽略顶层的 `const` 声明，但是不会忽略底层的 `const` 声明，比如说我们创造了 `const` 对象的一个指针，则我们就会得到一个 `const` 的指针对象。

c++11 中，我们可以使用 `decltype` 关键字声明一个由函数返回值类型决定类型的变量：

```c++
decltype(f()) sum = x;
```

注意如果我们使用 `decltype((var));` 则括号里面会被视做一个引用对象。接下来我们定义自己的结构体类型：

```c++
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue =0.0;
};
```

### 撰写自己的头文件

我们需要使用 preprocessor：

```c++
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue =0.0;
};
#endif
```

如果我们需要使用命名空间中的对象，但是不想多打字，就可以使用 `using` 声明，如：

```cpp
#include <iostream>
// using declaration; when we use the name cin, we get the one fromthe namespace std
using std::cin;
int main()
{
	int i;
	cin >> i; // ok: cin is a synonym for std::cin
	cout << i; // error: no using declaration; we must use the full name
	std::cout << i; // ok: explicitly use cout from namepsace std
	return 0;
}
```

### string Type

```cpp
string s1; // default initialization; s1 is the empty string
string s2 = s1; // s2 is a copy of s1
string s3 = "hiya"; // s3 is a copy of the string literal
string s4(10, ’c’); // s4 is cccccccccc
```

读取未知个数的字符串

```cpp
int main(){
	string word;
	while (cin>>word)
		cout << word << endl;
	return 0
}
```

使用 `getline` 可以读取整个一行输入，忽略空格：

```cpp
int main()
{
string line;
// read input a line at a time until end-of-file
while (getline(cin, line))
cout << line << endl;
return 0;
}
```

注意 `string` 包中的 `size()` 方法返回值是一个 unsigned 变量！！这很差劲。另外，字符串字面量是不能直接相加的，这是由于字面量不是 `std::string` 量。

在 c++11 标准中，我们可以使用类 for-range 的方式进行历遍字符串：

```cpp
for (auto c : str)
	cout << c << endl;
```

如果我们需要更改值，我们可以使用 for-range 语句进行创造引用，然后更改，如：（如果我们使用索引，实际上就生成了一个引用）

```cpp
for (auto &c : str)
	c = toupper(c);
```

### vector Type

如果我们需要使用 `vector` 容器，我们就需要如下的声明：

```cpp
#include <vector>
using std::vector;

vector<int> ivec;
vector<Sales_item> Sales_vec;
vector<vector<string>> file;
```

有的编译器可能需要我们在声明向量的向量容器的时候使用 `vector<vector<int> >`（注意空格）。初始化的时候我们只可以使用 list 初始化方法，类似地我们也可以使用 `vector<int>v1(10,20)` 进行复制操作。

接下来介绍对于 vector 的操作：

使用 `push_back()` 方法能够添加元素。我们使用 `::size_type` 对象的时候前面的值应该是 `vector<int>`。类似地，我们也有 `empty()` 或 `size()` 语法。

#### 初识迭代器

```cpp
string s("some string");
if (s.begin() != s.end()) { // make sure s is not empty
	auto it = s.begin(); // it denotes the first character in s
	*it = toupper(*it); // make that character uppercase
}
```

使用 \* 操作符可以获取迭代器对应的元素，使用自加和自减操作符能够使得迭代器进行更新。我们可以声明一个迭代其如下：

```cpp
vector<int>::iterator it;
string::iterator it2;
vector<int>::const_iterator it3;
```

迭代器可以加减 `	int` 量，同时也可以相减：两个迭代器相减类似于指标的运算，得到的也是一个迭代器。

### Arrays Type

我们可以使用 `array` 去初始化一个向量：

```cpp
int int_arr[] = {0,1,2,3,4,5};
vector<int> ivec(begin(int_arr), end(int_arr));
```

要做现代的 c++ 程序员！不要使用数组和指针，要用迭代器和 `vector`，例如：

```cpp
size_t cnt = 0;
for (auto &row : ia)
	for (auto &col : row){
		col = cnt;
		++cnt;//用 ++x 而不是 x++
	}
```

### 类型转换

使用 cast 转换类型。 cast 有如下的形式：

```
cast-name<type> (expr);
```

其中 `type` 表示目标类型，`expr` 为源值，`cast-name` 有以下几种：`static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`。

`static_cast` 用来把小的计算类型转化为更大的计算类型。`const_cast` 用来把 `const` 属性去除。`reinterpret_cast` 用来做重新解释的转化。

使用 cast 而不是 类c 的转化方式！
