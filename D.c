#include<stdio.h>

int main(){
	int n, v, res = 0;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &v);
		res+=(v!=1); //Se for diferente de 1, ele vence nessa simulação
	}
	printf("%d\n", res);
	return 0;
}