#include<cstdio>
#include<bitset>

#define MAX 1010

using namespace std;

int main(){
    int N, M, L, i, j, v, cont = 0, inter[MAX][MAX];
    scanf("%d %d", &N, &M);
    bitset<MAX> lamps, aux;
    scanf("%d", &L);
    for(i=0; i<L; i++){
        scanf("%d", &v);
        lamps[v] = 1;
    }
    aux = lamps;
    for(i=0; i<N; i++){
        scanf("%d", &v);
        inter[i][0] = v;
        for(j=1; j<=v; j++)
            scanf("%d", &inter[i][j]);
    }
    while(true){
        for(i=0; i<N; i++){
            for(j=1; j<=inter[i][0]; j++)
                lamps.flip(inter[i][j]);
            cont++;
            if(lamps.none()){
                printf("%d\n", cont);
                return 0;
            }
        }
        if(lamps == aux){
            printf("-1\n");
            return 0;
        }
    }
    return 0;
}
