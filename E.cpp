#include<cstdio>
#include<cstring>

int main(){
	char text[10010], crib[10010];
	int a, b, i, j, dif, cont=0;
	scanf("%s %s", text, crib);
	a = strlen(text);
	b = strlen(crib);
	dif = a-b;
	for(i=0; i<=dif; i++){ //Enquanto puder deslocar o crib para comparar com text
		for(j=0; j<b; j++){
			if(text[i+j] == crib[j]){ //Compara o crib da posição j com o texto j deslocado i vezes
				cont++;
				break;
			}
		}
	}
	printf("%d\n", dif-cont+1);
	return 0;
}