#include <cstdio>
#include <vector>
#include <algorithm>

#define INF 1000000100

using namespace std;

typedef vector<pair<int, int>> vi;
typedef pair<int, int> pii;

typedef unsigned long long ull;

ull inversoes(vi &vet){
	if(vet.size() == 1)
		return 0;
	int i, med=vet.size()/2;
	vi init, end;
	for(i=0; i<med; i++)
		init.push_back(vet[i]);
	for(i=med; i<vet.size(); i++)
		end.push_back(vet[i]);
	int a = 0, b = 0;
	ull inv;

	inv = inversoes(init) + inversoes(end);
	init.push_back(pii(0, INF));
	end.push_back(pii(0, INF));

	for(i=0; i<vet.size(); i++){
		if(init[a].second <= end[b].second){
			vet[i] = init[a++];
		}
		else{
			vet[i] = end[b++];
			inv += (ull)init.size() - a - 1;
		}
	}
	return inv;
}

int comp(pii a, pii b){
	return a.first < b.first;
}

int main(){
	int X, Y, H, V, x, y, i;
	vi hor, ver;
	scanf("%d %d", &X, &Y);
	scanf("%d %d", &H, &V);

	for(i=0; i<H; i++){
		scanf("%d %d", &x, &y);
		hor.push_back(pii(x, y));
	}
	for(i=0; i<V; i++){
		scanf("%d %d", &x, &y);
		ver.push_back(pii(x, y));
	}
	sort(hor.begin(), hor.end(), comp);
	sort(ver.begin(), ver.end(), comp);
	printf("%llu\n", (ull)(H+1)*(V+1) + inversoes(ver) + inversoes(hor));
	return 0;
}