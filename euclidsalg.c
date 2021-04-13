/* *****************************************************************************
 * euclidsalg.c
 *
 * A program which can implement Euclid's algorithm for finding the GCD of a
 * pair of numbers and use this to simplify a fraction.
 *
 * Author - w-flowers
 * ***************************************************************************/
#include<stdio.h>

struct fraction {
	long num;
	long den;
};

struct fraction simplify_frac(struct fraction frac);

long gcd(long u, long v);
/*
int main(){
	long u = 0;
	long v = 0;
	while(scanf("%li %li", &u, &v) != EOF){
		struct fraction uv = {u, v};
		struct fraction suv = simplify_frac(uv);
		printf("%li/%li = %li/%li\n", uv.num, uv.den, suv.num, suv.den);
	}
}
*/
struct fraction simplify_frac(struct fraction frac){
	struct fraction simpfrac;
	long d = gcd(frac.num, frac.den);
	simpfrac.num = frac.num/d;
	simpfrac.den = frac.den/d;
	if(simpfrac.num < 0 && simpfrac.den < 0){
		simpfrac.num = 0 - simpfrac.num;
		simpfrac.den = 0 - simpfrac.den;
	}
	return simpfrac;
}

long gcd(long u, long v){
	if(u == v) return u;
	if(u < 0) u = 0-u;
	if(v < 0) v = 0-v;
	if(u == 0 || v == 0) return 0;
	long dmy;
	while(u > 0){
		if(u < v){
			dmy = v;
			v = u;
			u = dmy;
		}
		u = u-v;
	}
	return v;
}
