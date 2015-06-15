
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
 
vector<pair<int,int> >vec[110];
 
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    vec[3].push_back(make_pair(2,-1));
	vec[3].push_back(make_pair(5,2));
	vec[3].push_back(make_pair(3,-3));
 
	vec[4].push_back(make_pair(6,-1));
	vec[4].push_back(make_pair(3,6));
	vec[4].push_back(make_pair(0,3));
	vec[4].push_back(make_pair(7,0));
 
	vec[5].push_back(make_pair(8,-1));
	vec[5].push_back(make_pair(3,8));
	vec[5].push_back(make_pair(6,3));
	vec[5].push_back(make_pair(0,6));
	vec[5].push_back(make_pair(9,0));
 
	vec[6].push_back(make_pair(10,-1));
	vec[6].push_back(make_pair(7,10));
	vec[6].push_back(make_pair(2,7));
	vec[6].push_back(make_pair(6,2));
	vec[6].push_back(make_pair(0,6));
	vec[6].push_back(make_pair(11,0));
 
	vec[7].push_back(make_pair(12,-1));
	vec[7].push_back(make_pair(5,12));
	vec[7].push_back(make_pair(8,5));
	vec[7].push_back(make_pair(3,8));
	vec[7].push_back(make_pair(9,3));
	vec[7].push_back(make_pair(0,9));
	vec[7].push_back(make_pair(13,0));
 
	for(int i = 8;i <= 100;i++){
		vec[i].push_back(make_pair(2*i-2,-1));
		vec[i].push_back(make_pair(3,2*i-2));
		for(int j = 0;j < i-4;j++)
			vec[i].push_back(make_pair(vec[i-4][j].first+4,vec[i-4][j].second+4));
		vec[i].push_back(make_pair(0,2*i-5));
		vec[i].push_back(make_pair(2*i-1,0));
	}
	int n;
	bool first = true;
	while(scanf("%d",&n) == 1){
		if(first)first = false;
		else printf("\n");
		for(int i = 0;i < n;i++)
			printf("%d to %d\n",vec[n][i].first,vec[n][i].second);
	}
    return 0;
}
