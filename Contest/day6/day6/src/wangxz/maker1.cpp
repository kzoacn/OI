#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){
	srand(time(0));
	freopen("rect.in","w",stdout);
	int n=1000;
	cout<<n<<endl;
	for(int i(1);i<=n;i++){
		for(int j(1);j<=n;j++)
			putchar(rand()&1?'C':'B');
		puts("");
	}
	return 0;
}
