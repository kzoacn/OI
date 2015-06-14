#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
vector<int>vec[30];
int ans[30][30];
char str[30];
 
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
	while(scanf("%d",&n) == 1){
		for(int i = 0;i < n;i++){
			vec[i].clear();
			int num;
			scanf("%d",&num);
			while(num--){
				scanf("%s",str);
				int len = strlen(str);
				int tmp = 0;
				for(int j = 0;j < len;j++)
					tmp |= (1<<(str[j]-'a'));
				vec[i].push_back(tmp);
			}
		}
		memset(ans,-1,sizeof(ans));
		for(int j = 0;j < n;j++){
			int s = (1<<j);
			ans[j][j] = 0;
			for(int cnt = 1;cnt < n;cnt++){
				int ns = s;
				for(int i = 0;i < n;i++)
					if(ans[i][j] == -1){
						bool flag = false;
						for(int k = 0;k < vec[i].size();k++)
							if((s&vec[i][k]) == vec[i][k]){
								flag = true;
								break;
							}
						if(flag){
							ns |= (1<<i);
							ans[i][j] = cnt;
						}
					}
				s = ns;
			}
		}
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
				printf("%d%c",ans[i][j],j==n-1?'\n':' ');
	}
    return 0;
}
