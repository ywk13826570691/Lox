Lox脚本语言？
Lox是一个使用C语言基于yacc/lex开发的简单脚本语言

Lox语言特性
Lox是使用c语言开发，包含基本语言功能。

Lox语言语法
1，变量
Lox变量是不需要提前声明，可以直接使用
Ex:
a = 100
b = "Hello"
***********变量名字不能超过50个字符*************

2,Lox变量类型
2.1 number：
	a = 100
2.2 string:
	str = "hello lox"
2.3 function
	func = print ==> print是函数
2.4 nil
	m = nil
2.5 bool
	true， false
	a = false
	b = true
2.6 table,数组成员可以是任意数据类型
	vec = [1,2,3,4, "hello", print]
	table 不能嵌套定义
	vec = [1,2,3,4, [1,3,4,5]]
	table嵌套定义
	f = [1,2,3]
	vec = [1,2,3, f]

3,Lox运算符号
3.1 “+”
	a = 10 + 100 ==> a = 110
	a = 10 + "hello" ==> a = "hello10"
	a = "hello" + 10 ==> a = "hello10"
	a = "mmm" + "hello" ==> a = "mmmhello"
	a = [1,2,3]
	b = a + 5 ==> b= [1,2,3, 5] , a = [1,2,3]
	c = a + "hello" ==> c = [1,2,3,"hello"] , a = [1,2,3]
	f = [5,6,7]
	g = a + f ==> g = [1,2,3,5,6,7]
3.2 “-”
	a = 100 - 10 ==> a = 90
	str = "helloworld"
	a = str - "hello" ==> a = "world"
	a = [1,2,3,4,"hello"]
	f = a - 1 ==> f = [2,3,4,"hello"]
	f = a - "hello" ==> [1,2,3,4]
	
3.3 “*”
	a = 10 * 100 ==> a = 1000
	a = 2*"hello" ==> a = "hellohello"
	a = [1,2,3, "lox"]
	c = a*2 ==> c = [2,4,6, "loxlox"]
3.4 “/”
	a = 100 / 10  ==> a = 10.0
	a = [2,4,6,7]
	f = a / 2 ==> f = [1,2,3,3.5]
	
3.5 “%”
	a = 10 % 3  ==> a = 1
	
4, Lox逻辑运算
4.1 and
	a and b ==> a和b只要有一个是nil或者false and结果为false，其他都为true
4.2 or
	a or b ==> a和b只要有一个不是nil或false结果就是true
4.3 ==
	a == b ==>a和b相等为true a和b可以是Lox任意数据类型
4.4 ~=
	a ~= b ==>a和b不相等为true a和b可以是Lox任意数据类型
4.5 >=
	a >= b ==>a大于等于b为true a和b可以是Lox任意数据类型
4.5 <=
	a <= b ==>小于等于b为true a和b可以是Lox任意数据类型
4.7 not
	not a ==>a为nil或false结果为true

5, Lox函数
5.1 函数的定义
function func(a,b,c)
	@function block
	return a + b +c
end
5.2函数可以赋值给变量
  f = func
  f(1,2,3)
5.2函数的参数如果是数组则是地址传递，函数是可以改变数组值
	function arr(a)
		a[0] = 100
	end
	f = [1,2,3]
	arr(f)
	print(f[0]) ==> 100
	
6,Lox条件语句
	
	1,
	if a then
		@block
	end
	
	2,
	if a then
		@block
	else
		block
	then
	
	3,
	if a then
		@block
	elseif b then
		@block
	else
		@block
	end

7, Lox循环语句
	1,foreach i in [c,d] @//c起始值， d长度
		@break
		@continue
	end
	
	2,foreach i in [1,10]
		@break
		@continue
		print(i)
	end
	
	3,repeat
		@block
		@break
		@continue
	until a	
	
	4, while a do
		@block
		@break
		@continue
	end
	
8,怎么编译Lox
 8.1 安装yacc/lex
 8.2 make
 8.3 ./lox就是lox解析器
 
 联系:
 ywk13826570691@163.com @vkang

