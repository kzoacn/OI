#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	
	int T=0;
	while(1){
		system("A_data > A.in");
		if(system("A <A.in >A.out"))
			break;
		else printf("%d\n",T++);	
			
	}
	return 0;
}
