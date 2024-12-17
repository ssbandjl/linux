#include <stdio.h>
#include <stdlib.h>
/*
 * min()/max() macros that also do
 * strict type-checking.. See the
 * "unnecessary" pointer comparison.
 */
//比较两个数，如果x>y，输出y,否则输出x
#define min(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);		\
	_x < _y ? _x : _y; })
//比较两个数，如果x>y，输出x,否则输出y 
#define max(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);		\
	_x > _y ? _x : _y; })
//比较三个数的大小 ,输出最小的一项 
#define min3(x,y,z) ({   \
	typeof(x)  _min1 = (x) ; \
	typeof(y)  _min2 = (y) ; \
	typeof(z)  _min3 = (z) ; \
	(void) (&_min1 == &_min2) ; \
	(void) (&_min1 == &_min3) ; \
	_min1 < _min2 ? (_min1 < min3 ? _min1 : _min3) ; \
		(_min2 < _min3 ? _min2 : _min3) ;} )
//比较三个数的大小 ,输出最大的一项 
#define max3(x,y,z) ({   \
	typeof(x)  _max1 = (x) ; \
	typeof(y)  _max2 = (y) ; \
	typeof(z)  _max3 = (z) ; \
	(void) (&_max1 == &_max2) ; \
	(void) (&_max1 == &_max3) ; \
	_max1 > _max2 ? (_max1 > max3 ? _max1 : _max3) ; \
		(_max2 > _max3 ? _max2 : _max3) ;} )
//输出绝对值 
#define abs(x) ({				\
		int __x = (x);			\
		(__x < 0) ? -__x : __x;		\
	})
//交换两个数
#define swap(a,b)  \
	do{typeof(a) __tmp = (a); (a) = (b) ; b = (__tmp) ;}while(0)
int main(void)
{
	int ret = 0 ;
	ret = max(1,2);
	printf("%d\n",ret);
	printf("%d\n",abs(-100));
	int a = 2 ; 
	int b = 3 ; 
	swap(a,b);
	printf("%d %d\n",a,b);
	
	return 0 ;
}
