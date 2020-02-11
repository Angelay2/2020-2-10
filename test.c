#include <stdio.h>
#include <stdlib.h>

// 内存对齐
// 结构体的对齐规则:
// 第一个成员在结构体变量偏移量为0的地址处  不需要对齐 
// 每个成员都要对齐到起始偏移量能整除自身对齐数(自身大小) 0可以整除任何正数
// 其他成员变量对齐到某个数字(对齐数)的整数倍的地址处
// 是否对齐由 1.起始偏移量, 2.自身大小(不可调)决定
// 起始偏移量不能往小了调,调到最小的能整除自身大小的值
// 第一个元素不需要对齐 但有对齐数 是他自己大小
// 每个元素都有对齐数 但结构体总大小是最大的那个对齐数的整数倍

// 对齐数:编译器默认的一个对齐数与该成员自身大小的较小值 VS默认为8
// 结构体总大小为最大对齐数(每个成员变量都有一个对齐数)的整数倍
// 如果嵌套了结构体的情况, 嵌套的结构体对齐到自己的最大对齐数的整数倍处,
// 结构体的整体大小就是所有就是所有最大对齐数(含嵌套结构体的对齐数)的整数

// #pragma pack(数字)  // 设置默认对齐数 最终的对齐数是设置值和自身大小之间的较小值 
// 若对齐数为1 也就意味着 不要对齐数 全都为1 必须为1,2,4,8
// #pragma pack() 里面没有数字表示默认对齐 
struct S1{
	char a;
	int b;// a,b没挨着 中间隔了3个字节  本来起始偏移量为1 b的对齐数为4 最后调整为4 因为4是能整除4的最小整数
	char c;
};// 12
struct S2{
	char c1;
	char c2;
	int i;
};// 8
struct S3{
	double d;// 8
	char c;
	int i;
};// 16
struct S4{
	char c1;// 1
	struct S3 s3;// 3 + 16 = 20
	double d;// 28
};// 32/8
struct S5{
	short* p;// 4
	char a[3];// 4+3 = 7
	struct S3* x;//7+1/4 +4=12
	struct S3 s3;// 12+4/8 +16 =32
	double x;// 32+8 = 40
	char* b[3];// 40/4 +12 = 52
	char d;// 52+1 = 53
};// 53+3 /8  => 56
int main(){
	struct S1 obj;
	printf("%p\n", &obj);
	printf("%p\n", &obj.a);// 地址相同
	
	printf("%d\n", sizeof(struct S1));
	printf("%d\n", sizeof(struct S2));
	printf("%d\n", sizeof(struct S3));
	printf("%d\n", sizeof(struct S4));
	printf("%d\n", sizeof(struct S5));

	system("pause");
	return 0;
}