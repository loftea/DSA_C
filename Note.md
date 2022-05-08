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

`typedef` 语句可以声明一到两种别名。在 C++11 中我们可以使用如下的语句作为声明：

```cpp
using SI = Sales_item // SI is a synonym for Sales_item
```

在 C++11 中我们可以使用 `auto` 关键词来使得我们的变量根据右侧初始值自动决定类型。`auto` 会忽略顶层的 `const` 声明，但是不会忽略底层的 `const` 声明，比如说我们创造了 `const` 对象的一个指针，则我们就会得到一个 `const` 的指针对象。

C++11 中，我们可以使用 `decltype` 关键字声明一个由函数返回值类型决定类型的变量：

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

我们需要使用预处理：

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
	while (cin >> word)
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

注意 `string` 包中的 `size()` 方法返回值是一个无符号变量 `size_t`！！这很差劲。另外，字符串字面量是不能直接相加的，这是由于字面量不是 `std::string` 量。

在 C++11 标准中，我们可以使用类 for-range 的方式进行历遍字符串：

```cpp
for (auto c : str)
	cout << c << endl;
```

如果我们需要更改值，我们可以使用 for-range 语句进行创造引用，然后更改，如：

（如果我们使用索引，实际上就生成了一个引用）

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

### 初识迭代器

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
vector<int> ivec(begin(int_arr), end(int_arr)); //这个地方是函数得到一个迭代器，而不是
```

要做现代的 C++ 程序员！不要使用数组和指针，要用迭代器和 `vector`，例如：

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

使用 cast 而不是 类C 的转化方式！

##  Go further

### 错误处理

我们通过 try-catch 块来处理错误。相关的语句有：`throw`、`try` 以及 `exception`。

`throw` 用来抛出异常，如：

```cpp
if (item1.isbn()!=item2.isbn()){
	throw runtime_error("Data must refer to same ISBN!");
}
cout << item1+item2 << endl
```

之前我们采取的方法可能会如下：

```cpp
if (item1.isbn()!=item2.isbn()){
	cerr << "Data must refer to same ISBN!" << endl
}
```

另一方面我们考虑如下的异常处理方法：

```cpp
try {
	// something
}catch (runtime_error err){
	//do something
}
```

如果抛出的异常没有被捕捉，则会被 `terminate` 运行时函数捕捉，然后直接退出程序。下面的列表介绍了 `<stdexcept>` 中的异常名字：

|   exception    |       general kind of problem       |
| :------------: | :---------------------------------: |
| runtime_error  |            runtime error            |
|  range_error   |             range error             |
| overflow_error |              overflow               |
|  logic_error   |             logic error             |
|  domain_error  | argument for which no result exists |
| invalid_error  |        inapprociate argument        |
|  length_error  |  attempt to create a larger object  |
|  out_of_range  |            out of range             |

此外，我们还有 `new` 头文件中的 `bad_alloc` 以及 `type_info` 头文件中的 `bad_cast`。

注意我們不能初始化 `exception` 以及上面説到的 `bad_alloc`、`bad_cast` 異常。

### 函數

在調用函數的時候會發生隱性類型轉換。注意區分指針和引用兩者的區別！！下面介紹了怎麽處理命令行參數：

```cpp
int main(int argc, char **argv){
	//something
}
```

其中 argc 表示命令行參數的參數個數（包括程序的名字）。在 C++11 中我們可以使用 `initializer_list` 類型來存儲同一類型的參數。

引用類型的返回值是左值。

重載運算符！只要函數簽名不一樣，就可以使用重名的函數。如果我們結合 `const_cast` 我們可以構造如下有用的實例：（注意函數簽名會忽略 top-level 的 `const` 屬性）

```cpp
const string &shorter (const string &s1, const string &s2){
	return s1.size()<s2.size()?s1:s2;
}

string &shorter (string &s1, string &s2){
    auto &r = shorterString(const_cast<const string&>(s1),
                           const_cast<const string&>(s2));
        return const_cast<string&>(r);
}

```

如果我們構造局部函數，那麽他會覆蓋其他同名的重載運算符。在函數的簽名檔中我們可以設置默認值，如：

```cpp
int f(int x = 1);
```

使用 `inline` 關鍵詞可以把函數當作宏展開在代碼當中。僅適用於簡單并且常用的函數。使用 `inline` 或 `constexpr` 申明通常放在頭文件當中。

在匹配重載函數的時候，相合的變量類型會被優先匹配，這一條原則在輸入參數個數匹配之前。對於多參數，編譯器會逐步檢查參數看是否能找到一個對於 **所有** 參數都比較好的函數選擇，否則編譯器會返回錯誤，認爲調用是意義不明的。

在調用重載函數的時候可能發生兩種隱性轉換的時候，編譯器會認爲該轉換是意義不明的，如：

```
void f(long x);
void f(float x);
f(3.14);// !!error!!
```

#### 函數的指針！

函數是一等公民！所以我們可以創造指向函數的指針，只要我們聲明函數的簽名就可以了。

### 調試語句

#### Assert 預處理語句

爲了使用 `assert` 語句請 `#include <cassert>`。`assert (expr)` 如果捕獲了一個 `false` 值，則其會抛出一個異常。

#### NDEBUG 變量

我們在命令行的時候使用如下的：

```bash
$ CC -D NDEBUG main.c
```

相當於我們在文件前面加了一個 `#define NDEBUG` 的預處理語句。采取如下的實例：

```cpp
void print(const int ia[], size_t size){
#ifndef NDEBUG
cerr << __func__ << "array size = "<< size << endl;
#endif
/...
}
```

其中我們用到了 `__func__` 表示函數名，另外我們還有類似的：`__line__`、`__time__`、`__date__` 分別表示文件名、列號、時間字符串和日期字符串：

```cpp
if (word.size()<threshold)
	cerr << "Error:" << __file__
    << ": in function" << __func__
    << "at line" << __line__
    << "at" << __time__ << endl
    << "Word read was \"" << word
    << "\": Length too short" << endl
```

## 類！！！

### Get started：設計自己的抽象類

```cpp
struct Sales_data{
std::string isbn() const{return bookNo;}
Sales-data& combine(const Sales_data&);
double avg_price() const;
};
```

其中 `isbn()` 方法的 `const` 關鍵字是爲了修飾 `this` 這個指針的，表示該方法不會改變 `this` 的成員。

在類的外部我們也可以定義方法：

```cpp
double Sales_data::avg_price() const{
	if (units_sold)
		return revenue/units_sold;
	else
		return 0;
}
```

我們可以返回 `*this` 對象：

```cpp
Sales_data& Sales_data::combine(const Sales_deta &rhs){
    unites_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```

我們還可以重載以下的函數：

```cpp
istream &read(istream &is, Sales_data &item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
```

我們通常還需要定義我們的構建函數，構建函數的名字和類名相同。我們還可以考慮使用 `Sales_data()=default;` 表示聲明一個默認的構建函數。

構建函數我們如果要初始化 `const` 對象，就需要使用如下的：

```
ConstRef::ConstRef(int ii):i(ii), ci(ii), ri(i){}
```

這種方法被稱爲 constructor initializer，但是這種方法一定要注意一個問題，參數初始化的順序和類裏面對應變量的順序相同。最好的辦法是在 Initializer 裏面不要互相引用。

編譯器自動生成的構建函數被我們稱爲 `synthesized default constructor`，他會根據類成員是否有自定義的構建函數分別進行初始化。

在使用函數的時候可以發生隱形類型轉化，但是只可以發生一次，同時如果我們使用了 `explict` 關鍵字，這種隱性轉化就不應該發生，示例如下：

```cpp
class Sales_data{
public:
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned n, double p):
		bookNo(s), units_sold(n), revenue(p*n){}
		explicit Sales_data(std::istream&);
};
```



#### Delegating constructor

```cpp
class Sales_data {
public:
// nondelegating constructor initializes members from corresponding arguments
	Sales_data(std::string s, unsigned cnt, double price):
		bookNo(s), units_sold(cnt), revenue(cnt*price) { }
// remaining constructors all delegate to another constructor
	Sales_data(): Sales_data("", 0, 0) {}
	Sales_data(std::string s): Sales_data(s, 0,0) {}
	Sales_data(std::istream &is): Sales_data()
	{ read(is, *this); }
// other members as before
};
```



#### 權限

使用 `class` 和 `struct` 的區別在於 `struct` 默認能夠訪問類的所有元素。一般來説，我們使用 `class` 創造類。

使用關鍵字 `friend (class-name) add(...)...` 能夠使得後面的類訪問本類的私有元素。

#### 更多的……

我們考慮需要構造一對相呼應的類 `Screen` 和 `Window_mgr`：

```cpp
class Screen{
public:
	typedef std::string::size_type pos;
private:
	pos cursor = 0;
	pos height =0, width = 0;
	std::string contents;
};
```

如果我們使用：

```cpp
friend class class_name;
```

則該友鄰可以訪問所有的成員。特別地，我們對於不同的友鄰也可以創造不同的重載友鄰函數。

#### 集合類和字面量類

#### 靜態成員

靜態成員不需要有完全的變量類型，例如：

```cpp
class Bar {
public:
// . . .
private:
    static Bar mem1; // ok: static member can have incomplete type
    Bar *mem2; // ok: pointer member can have incomplete type
    Bar mem3; // error: data members must have complete type
};
```

## C++ 的庫

### IO 類

对于 IO 类的对象，我们不能复制或者复制，IO 类的对象是时常变化的，所以对应对象不能是 `const` 类型。IO 类分为三个头文件，分别是 `iostream`、`fstream`、`sstream` 分别表示从（一般的）流当中读写，以及从文件或者字符串当中读写，后两者继承了第一个类。

#### IO 库中的 Condition State

在库当中定义了一个描述读取状态的类，叫做 `strm::iostate`，在其之上定义了四个不同的状态：`badbit`、`failbit`、`eofbit`、`goodbit` 其中前两者表示错误，第一个 `badbit` 表示遇到了不可挽回的错误，而第二个信号表示可以恢复的信号，后两个分表表示 EOF 和正常状态。在流对象上我们还有几个比较重要的方法：

```cpp
#include <iostream>

s.setstate(flages) \\ 设置状态信号
s.clear() \\ 清除所有信号
s.clear(flag) \\ 清除 flag 信号
```

考虑如下的示例：

```cpp
auto old_state = cin.rdstate();
cin.clear();
process_input(cin); // do something
cin.setstate(old_state);
```

#### Buffer

有的时候，信息流会被堵塞，但是我们可以使用一些操作使得 buffer 被清空，有几种情况：程序正常结束、使用了 `endl` 或者其他的操作、buffer 已满即将清空、使用 `unitbuf` 操作清空 buffer。值得注意的是下面的情况：有的流和其他流相互绑定，比如说 `cin` 和 `cout` 绑定，只要我们开始读 `cin` 或者写 `cerr`，则 `cout` 的 buffer 马上就会清空。`unitbuf` 操作如下：

```cpp
cout << unitbuf; // all out will be immediate
cout << nounitbuf;
```

我们使用绑定的例子如下：

```cpp
cin.tie(&cout);// 参数是一个指针

ostream *old_tie = cin.tie(nullptr);
cin.tie(&cerr);
cin.tie(old_tie);
```

使用文件流的方法如下：

```cpp
ifstream in(iflile); // 绑定了文件
ofstream out; // 未绑定文件
out.open(ifile + ".copy"); // 打开文件
in.close();
in.open(ifile + "2"); //打开另外一个文件
```

在我们初始化绑定流的时候我们可以指定打开方式参数：

| Keywords |             Modes              |
| :------: | :----------------------------: |
|    in    |             input              |
|   out    |             output             |
|   app    |  seek to the end before write  |
|   ate    | seek to the end after the open |
|  trunc   |            truncate            |
|  bianry  |             binary             |

示例如下：

```cpp
ofstream app("file2", ofstream::app);
```

模式可以在每次使用 `open()` 的时候不断改变。

## 序列容器！

内置的有如下的序列容器类型：

|     Type     |          what           |
| :----------: | :---------------------: |
|    vector    |         vector          |
|    deque     | deque，支持快速随机访问 |
|     list     |   double linked list    |
| forward_list |   singly linked list    |
|    string    |         string          |

初始化容器需要一个初始化子，如果没有呢就得提供一个。如：

```cpp
vector<noDefault> v1(10,init)//
vector<noDefault> v2(10)//!!error!!
```

`begin` 和 `end` 家族：

```cpp
list<string> a = {"Milton", "Shakespeare", "Austen"};
auto it1 = a.begin(); // list<string>::iterator
auto it2 = a.rbegin(); // list<string>::reverse_iterator
auto it3 = a.cbegin(); // list<string>::const_iterator
auto it4 = a.crbegin();// list<string>::const_reverse_iterator
```

创造容器我们有以下的方法：

```cpp
C c(b,e); // b, e 为迭代器
C seq(n) // seq has n value-initialized element
C seq(n,t) // seq has n elements with value t
```

我们也可以使用内置的 `array` 容器来代替常见的数列。

下面是两个非常有用的方法：

```cpp
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;// !!error!!
names.assign(oldstyle.cbegin(), oldstyle.cend());

list<string> slist1(1);
slist1.assign(10, "Hiya!");

vector<string> svec1(10);
vector<string> svec2(24);
swap(svec1, svec2);
```

对于可以 push_front 的容器，我们使用 `push_front` 方法可以从前面添加。注意：添加 `vector`、`string`、`deque` 中的元素可能会使得迭代器什么的失效。

我们也可以使用 `insert` 方法插入两个迭代器中的全部元素：

```cpp
slist.insert(slist.begin(), slist.begin(), slist.end());
```

该方法的返回值是插入之后新的迭代器。

`emplace` 方法使用可以直接传入初始化子的参数构造一个新的成员实体加入：

```cpp
c.emplace_back("10086",25,16);
```

对于排序容器，我们有 `back` 方法和 `front` 方法返回最后的元素和最前的元素的 **引用**，还有一个 `at(int n)` 方法能够返回对应位置的元素。

`pop_front` 以及 `pop_back` 方法用来 pop 操作，如果我们需要删除某个位置的成员，我们应该使用 `erase` 方法。使用方法如下：

```cpp
c.erase(p);// at position p
c.erase(b, e); // from b to e
c.clear(); // clear
```

`resize` 方法能够合适地修改容器：

```cpp
list<int> ilist(10, 42); // ten ints: each has value 42
ilist.resize(15); // adds five elements of value 0 to the back of ilist
ilist.resize(25, -1); // adds ten elements of value -1 to the back of ilist
ilist.resize(5); // erases 20 elements from the back of ilist
```

### string 的操作

```cpp
string s(cp, n);
string s(s2, pos2);
string s(s2, pos2, len2);

s.insert(s.size(), 5, ’!’); // insert five exclamation points at the end of s
s.erase(s.size() - 5, 5); // erase the last five characters from s
```

我们还有 `find` 方法操作能够查找对应位置（注意返回值是 `string::size_type` 的无符号类型。）使用 `find_first_of(s2)` 方法可以得到在 `s2` 中的某个元素的位置。我们还可以额外添加参数 `pos` 使得从 `pos` 处开始搜索。

`rfind` 方法从右往左开始搜索。

另外还有一些其他的方法，比如用来比较的 `compare` 方法。

|          args          |                        what                         |
| :--------------------: | :-------------------------------------------------: |
|           s2           |                    compare to s2                    |
|      pos1, n1, s2      | compare n1 characters starting as pos1 from s to s2 |
| pos1, n1, s2, pos2, n2 |                         ...                         |
|           cp           |                                                     |
|      pos1, n1, cp      |                                                     |
|    pos1, n1, cp, n2    |                                                     |

### Adoptors

`stack`、`queue`、`priority_queue` 是三个适配器，我们在初始化的时候需要用一个底层的容器来初始化适配器，`stack` 、`queue` 的底层是双向队列，`priority_queue` 的底层是 `vector`。
