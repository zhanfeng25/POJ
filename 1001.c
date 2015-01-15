/*
 * [1001] Exponentiation
 *
 * Description: Problems involving the computation of exact values of very
 * large magnitude and precision are common. For example, the computation
 * of the national debt is a taxing experience for many computer systems. 
 * This problem requires that you write a program to compute the exact value
 * of Rn where R is a real number ( 0.0 < R < 99.999 ) and n is an integer
 * such that 0 < n <= 25.
 * 
 * Input: The input will consist of a set of pairs of values for R and n.
 * The R value will occupy columns 1 through 6, and the n value will be in
 * columns 8 and 9.
 *
 * Output: The output will consist of one line for each line of input giving
 * the exact value of R^n. Leading zeros should be suppressed in the output.
 * Insignificant trailing zeros must not be printed. Don't print the decimal
 * point if the result is an integer.
 *
 * Sample Input:
 * 95.123 12
 * 0.4321 20
 * 5.1234 15
 * 6.7592  9
 * 98.999 10
 * 1.0100 12
 *
 * Sample Output:
 * 548815620517731830194541.899025343415715973535967221869852721
 * .00000005148554641076956121994511276767154838481760200726351203835429763013462401
 * 43992025569.928573701266488041146654993318703707511666295476720493953024
 * 29448126.764121021618164430206909037173276672
 * 90429072743629540498.107596019456651774561044010001
 * 1.126825030131969720661201
 */
#include <stdio.h>	/* scanf, printf */
#include <string.h>	/* memset */

char Rstr[8];	/* Get the real number R as char array */
int num[200], n, k1[200], k2[200], Rcount = 0;

void Change()
{
	int m[200], i, j = 1, q;

	/* truncate the trailing zeros */
	i = 5;
	while (Rstr[i] == '0')
		i--;
	Rcount = i;

	q = Rcount;
	while (Rstr[i] != '.')
		i--;
	Rcount = Rcount - i;

	if (Rcount == 0) {	/* Rstr: only zero after decimal point */
		i = 0;
		while (Rstr[i] != '.') {
			m[i+1] = Rstr[i] - '0';
			i++;
		}
		for (i = q+1; i < 6; i++)
			m[i] = -1;
	} else {	/* Rstr: non-zero value after decimal point */
		/* get rid of decimal point */
		for (i = 0; i < 6; i++) {
			if (Rstr[i] != '.') {
				m[j] = Rstr[i] - '0';
				j++;
			}
		}

		/* replace the prefix and trailing zeros with -1 */
		i = 1;
		while (m[i] == 0) {
			m[i] = -1;
			i++;
		}
		i = 5;
		while (m[i] == 0) {
			m[i] = -1;
			i--;
		}
	}

	/* reverse the real number without decimal point store it into num */
	j = 1;
	for (i = 5; i >= 1; i--)
		if (m[i] != -1) {
			num[j] = m[i];
			j++;
		}
	num[0] = j - 1;
}

/* s = a*b */
void Mult(int a[],int b[],int *s)
{
	int i, j, max, carry, k;
	for (i = 1; i <= b[0]; i++) {
		carry = 0;
		for (j = 1; j <= a[0]; j++) {
			k = s[i+j-1] + b[i]*a[j] + carry;
			s[i+j-1] = k%10;
			carry = k/10;
		}
		if(carry)
			s[i+a[0]] = carry%10;
	}
	max = a[0] + b[0] - 1;
	while (carry) {
		s[++max] = carry%10;
		carry /= 10;
	}
	s[0] = max;
}

void Copy(int a[],int b[])
{
	int i;
	for (i = 0; i < 200; i++)
		a[i]=b[i];
}

void Print(int *s)
{
	int i;
	if (Rcount*n >= s[0]) {
		printf(".");
		for (i = 0; i < Rcount*n-s[0]; i++)
			printf("0");
		for (i = s[0]; i >= 1; i--)
			printf("%d",s[i]);
	} else
		for (i = s[0]; i >= 1; i--) {
			if(i == Rcount*n)
				printf(".");
			printf("%d", s[i]);
		}
	printf("\n");
}

int main(void)
{
	int i;

	while (scanf("%s%d", Rstr, &n) != EOF) {
		memset(num, 0, sizeof(num));
		memset(k1, 0, sizeof(k1));
		memset(k2, 0, sizeof(k2));
		Change();
		Copy(k1, num);
		for (i = 0; i < n-1; i++) {
			memset(k2, 0, sizeof(k2));
			Mult(k1, num, k2);	// k2 = k1*num
			Copy(k1, k2);		// k1 = k2
		}
		if (n > 1)
			Print(k2);
		else
			Print(k1);
	}

	return 0;
}
