#include<bits/stdc++.h>
using namespace std;
string S;
string dict[700]={"a","i","am","an","as","at","be","by","do","go","he","if","in","is","it","ll","me","mr","my","no","of","on","or","re","so","to","up","ve","we","ago","all","and","any","are","bar","bat","big","bit","boy","bug","but","can","cat","cup","cut","day","did","dog","don","end","fee","fly","for","fox","fur","get","gnu","god","gpl","had","has","her","him","his","how","iee","iel","its","joy","key","law","let","may","mrs","new","nor","not","now","one","our","out","paw","pay","ran","run","sat","saw","see","set","she","six","tea","the","too","two","use","war","was","way","who","why","yet","you","zoo","adam","also","aren","away","back","bank","bear","beat","beef","been","bell","bill","bird","boar","body","bone","book","bore","both","came","camp","case","code","come","cook","copy","damn","damp","date","dead","deer","deny","dish","does","dull","each","ever","eyes","face","felt","fill","find","fire","fish","five","four","free","from","gain","gave","gets","girl","give","glad","good","hand","hard","have","here","high","hold","hour","hunt","ieee","into","jack","just","keep","kept","kiss","knew","know","lamb","last","lazy","lead","left","lend","life","like","live","long","look","love","made","make","many","mars","mary","meat","meet","mind","mine","moon","moor","more","morn","most","much","must","name","need","nine","once","only","over","paid","pain","papa","pass","past","pays","pink","play","poor","pray","puma","rain","ramp","rope","said","sake","same","seen","shed","show","sing","some","song","stop","such","sure","take","tape","tell","than","that","them","then","they","this","tied","time","tiny","told","tony","took","tree","trip","true","upon","used","user","very","wall","want","wasn","ways","well","went","were","what","when","whom","wife","wild","will","wish","with","wood","work","year","your","about","added","adore","after","again","aleko","along","among","apple","apply","armed","asked","began","being","below","betty","black","blade","bleed","blood","bored","brown","carry","catch","cause","chuck","clock","comes","could","death","doesn","doing","dwelt","eight","every","facts","fetch","field","fifty","first","forty","found","fully","given","gives","going","grant","great","hands","happy","hares","heart","hours","human","jumps","keeps","kinds","known","lamps","large","legal","lines","lived","local","lover","lovin","madam","makes","marks","merry","miles","money","moses","names","never","night","offer","often","other","paint","parts","place","plain","plays","price","prize","prove","pumas","quick","quiet","reach","right","roses","scamp","seven","shall","share","shine","sight","since","sixty","small","sorry","south","speak","stars","start","steel","steps","still","sword","table","taken","teeth","terms","thank","theft","their","there","these","thief","thing","think","those","three","times","today","torch","tower","trade","trail","truly","trust","under","users","vicar","wants","watch","weeks","where","which","while","white","whole","wings","woken","woman","words","works","world","worth","would","yards","years","yours"};
string rot(string S,int d){
	for(int i=0;i<S.length();i++){
		if(isalpha(S[i])){
			S[i]=tolower(S[i]);
			S[i]=((S[i]-'a')+d)%26+'a';
		}
	}return S;
}
string _rot(string S,int d){
	for(int i=0;i<S.length();i++){
		if(isalpha(S[i])){
			if(islower(S[i]))
				S[i]=((S[i]-'a')+d)%26+'a';
			else S[i]=((S[i]-'A')+d)%26+'A';
		}
	}return S;
}
set<string>M;
int calc(string S){
	vector<string>sp;
	int la=0;S=S+' ';
	for(int i=1;i<S.length();i++){
		if(S[i]==' '||S[i]=='.'||S[i]=='!'||S[i]=='?'||S[i]==','||S[i]=='_'){
			if(i-la>=1)
			sp.push_back(S.substr(la,i-la));
			la=i+1;
//			cerr<<sp.back()<<endl;
		}
	}int ans=0;
	for(int i=0;i<sp.size();i++){
//		cerr<<sp[i]<<endl;
		if(M.count(sp[i]))ans++;
	}
	return ans;
}
void sol(){
	getline(cin,S);
//	cerr<<S<<endl;
	int ans=0;string anss=S;
	for(int i=0;i<26;i++){
		int tmp=calc(rot(S,i));
//		cerr<<rot(S,i)<<endl;
		if(tmp>ans){
			ans=tmp;
			anss=_rot(S,i);
		}
	}cout<<anss<<endl;
}
void I(string s){M.insert(s);}
int main(){
//	freopen("bzoj2145.in","r",stdin);
	for(int i=0;dict[i]!="";i++)
		I(dict[i]);
	int T=10;
	while(T--)sol();	
	return 0;
}
