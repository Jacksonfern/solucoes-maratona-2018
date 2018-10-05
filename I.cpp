#include<cstdio>
#include<bitset>

#define MAX 1010

using namespace std;

int main(){
    int N, M, L, i, j, v, cont = 0, inter[MAX][MAX];
    scanf("%d %d", &N, &M);
    bitset<MAX> lamps, aux; //Agrupa conjunto de bits. No problema será usado para o estado da lâmpada
    scanf("%d", &L);
    for(i=0; i<L; i++){
        scanf("%d", &v);
        lamps[v] = 1;
    }
    aux = lamps;
    for(i=0; i<N; i++){
        scanf("%d", &v);
        inter[i][0] = v;
        for(j=1; j<=v; j++) //Interruptor i tem a lâmpada inter[i][j]
            scanf("%d", &inter[i][j]);
    }
    while(true){
        for(i=0; i<N; i++){
            for(j=1; j<=inter[i][0]; j++)
                lamps.flip(inter[i][j]); //Inverte o estado da lâmpada
            cont++;
            if(lamps.none()){ //Não existe mais lâmpada acesa
                printf("%d\n", cont);
                return 0;
            }
        }
        if(lamps == aux){ //Voltou para o estado inicial
            printf("-1\n");
            return 0;
        }
    }
    return 0;
}
