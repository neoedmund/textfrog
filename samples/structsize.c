/*
cp t1.c /opt/lab/lab3/textfrog/samples/structsize.c
gcc -o t1.run t1.c && ./t1.run
*/
# include <stdio.h>
union Job {
	float salary , a , b , c ;
	int workerNo ;
} j ;
struct S0 {
	long v2 ;
	char v1 ;
} ;
struct S1 {
	char v1 ;
	struct S0 s0 ;
	char x1 ;
	//	union Job j2 ; //4
	//	char j3,p1 ; //1
	//---
	//	int j4 ; //4
	//	char v5,k1,k2,k3; //1
} s1 ;
int main ( ) {
	float f1 = 45.6 ;
	j . workerNo = 100 ;
	j . salary = 12.3 ;
	j . a = 23.4 ;
	//	j . s2 = 23.4 ;
	//	j . s3 = & f1;
	printf ( "sizeof = %d, size2=%d\n" , sizeof ( j ) , sizeof ( s1 ) ) ;
	printf ( "Salary = %.1f\n" , j . salary ) ;
	printf ( "Number of workers = %d" , j . workerNo ) ;
	return 0 ;
}
