#include<stdio.h>

int main(){
	int n, v, res = 0;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &v);
		res+=(v!=1);
	}
	printf("%d\n", res);
	return 0;
}