#include <stdio.h>
#include <stdlib.h>

// int foo (int a) { return a%2; }

// int triple (int a) {return 2*a;}
// int triple (float);//n [error: conflicting types for 'triple']

int fooo(int a) { return 2*a; }
float baar(float a, float b) { return a/b;}

int main()
{
	// int a[1][2] = {2,3}; //y
	// int b[1][2] =  {{2},{}}; //n
	// int c[1][2] =  {{2,3,4}}; //n
	// int d[1][2] =  {{2,3}}; //y
	// int e[1][2] =  {{2},{3}}; //n

	// int a[-1]; //n
	// int b[0]; //y
	// int c[0x16]; //y

	// typedef int Float;
	// Float x = 1.6*2;
	// printf("%d, %.2f\n", x, 1.6*2); // 3, 3.2

	// // nada
	// float a;
	// int a;

	// typedef enum {sun, mon, tue, wed, thu, fri, sat} Weekday;
	// char* WeekdayS[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
	// Weekday day;
	// day = (mon+23)%7; // (1+23) % 7 = 24%7 = 24-21=3 = wed
	// printf("%d = %s\n", day, WeekdayS[day]); // wed

	// int i = 3;
	// float f = 2.5;
	// i *= f;
	// printf("nocast %d\n", i); // 7
	// i = 3;
	// i *= (int)f;
	// printf("w/cast %d\n", i); // 6

	// float a[3]={1,2 , 2,3 , 3,5}; // 1.0, 2.0, 3.0
	// int b[3] = {}; // 0.0, 0.0, 0.0

	// int a[2++] = {1.5,2.4,4.5}; //n
	// int b[] = {}; //y

	// int i=3, j=1;
	// // for (i-- ; i>=j ; j++){
		// // printf("i %d, j %d, i*j %d, i*j%%3 %d\n", i, j, i*j, i*j%3);
		// // i = i * j % 3;
	// // }
	// i--;
	// printf("i %d, j %d\n", i, j);
	// while(i>=j){
		// printf("i %d, j %d, i*j %d, i*j%%3 %d\n", i, j, i*j, i*j%3);
		// i = i * j % 3;
		// j++;
	// }
	// printf("i %d, j %d\n", i, j);

	// int arr[2] = {2, 3};
	// if (foo(arr[1])) arr[0]=foo(1);
	// printf("%d, %d\n", arr[0], arr[1]); // 1, 2

	// int i;
	// float f = 1.5;
	// double d = 3.0;
	// i = 3.9;
	// d *= f *= i;
	// printf("d %.2f, f %.2f, i %d\n", d, f, i); // d 13.50, f 4.50, i 3

	// int log = 13;
	// int cnt = 0;
	// while (log > 2)
		// log -= 2, cnt++;
	// printf("log %d, cnt %d\n", log, cnt); // log 1, cnt 6

	// int a[4] = {1, 2, 3, 4}, i = 0;
	// for (i=1 ; i<4 ; i++) {
		// printf("a[i] %d, a[i-1] %d, i %d\n", a[i], a[i-1], i);
		// a[i] %= a[i-1];
	// }
	// which means:
	// // a[i] 2, a[i-1] 1, i 1; a[i] becomes 0 after %
	// // a[i] 3, a[i-1] 0, i 2
	// // Floating point exception

	// float fa[2][2] = {{1.5, 4.7},{7.3, 6.1}};
	// int a[2], i;
	// for (i=0 ; i<2 ; i++) {
		// a[i] = fa[i][0] + fa[i][1];
	// }
	// printf("a0 %d, a1 %d\n", a[0], a[1]);

	// int a = 2, b = 3;
	// a = fooo(baar(a,b));
	// printf("a %d, b %d\n", a, b);

	return 0;
}

