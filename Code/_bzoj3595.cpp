#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXT 310000
#define INF 0x3f3f3f3f
struct group
{
        int first,second,third;
};
group make_group(int a,int b,int c)
{
        group ret;
        ret.first=a;
        ret.second=b;
        ret.third=c;
        return ret;
}
struct SBTree
{
        int L[MAXT],R[MAXT],S[MAXT],id[MAXT],pos[MAXT];
        int root;
        queue<int> Q;
        SBTree()
        {
                int i;
                for (i=1;i<MAXT;i++)Q.push(i);
                root=0;
        }
        void update(int &now)
        {
                S[now]=S[L[now]]+S[R[now]]+1;
        }
        void l_rot(int &now)
        {
                int t=R[now];
                R[now]=L[t];update(now);
                L[t]=now;update(t);
                now=t;
        }
        void r_rot(int &now)
        {
                int t=L[now];
                L[now]=R[t];update(now);
                R[t]=now;update(t);
                now=t;
        }
        void maintain(int &now)
        {
                if (S[L[L[now]]]>S[R[now]])
                {
                        r_rot(now);
                        maintain(L[now]);
                        maintain(R[now]);
                        maintain(now);
                }
                if (S[R[R[now]]]>S[L[now]])
                {
                        l_rot(now);
                        maintain(L[now]);
                        maintain(R[now]);
                        maintain(now);
                }
                if (S[L[R[now]]]>S[L[now]])
                {
                        r_rot(R[now]);
                        l_rot(now);
                        maintain(L[now]);
                        maintain(R[now]);
                        maintain(now);
                }
                if (S[R[L[now]]]>S[R[now]])
                {
                        l_rot(L[now]);
                        r_rot(now);
                        maintain(L[now]);
                        maintain(R[now]);
                        maintain(now);
                }
        }

        void Insert(int &now,int _id,int _pos)
        {
                if (!now)
                {
                        now=Q.front();
                        Q.pop();
                        id[now]=_id;
                        pos[now]=_pos;
                        S[now]=1;
                        L[now]=R[now]=0;
                        return ;
                }
                if (_id<=id[now])
                {
                        Insert(L[now],_id,_pos);
                }else
                {
                        Insert(R[now],_id,_pos);
                }
                update(now);
                maintain(now);
        }
        pair<int,int> Find(int &now,int _id)
        {
                if (!now)return make_pair(-INF,-INF);
                if (id[now]>_id)
                {
                        return Find(L[now],_id);
                }
                if (id[now]==_id)
                {
                        return make_pair(id[now],pos[now]);
                }
                if (id[now]<_id)
                {
                        pair<int,int> ret;
                        if (R[now])
                        {
                                ret=Find(R[now],_id);
                                if (ret.first<id[now])
                                {
                                        ret.first=id[now];
                                        ret.second=pos[now];
                                }
                        }else
                        {
                                ret.first=id[now];
                                ret.second=pos[now];
                        }
                        return ret;
                }
        }
        void Delete(int &now,int _id)
        {
                if (!now)throw "Cannot delete" ;
                if (_id==id[now])
                {
                        if (!R[now]&&!L[now])
                        {
                                now=0;
                                return ;
                        }
                        if (R[now]&&L[now])
                        {
                                r_rot(now);
                                Delete(R[now],_id);
                        }else 
                        if (!R[now])
                        {
                                now=L[now];
                        }else if (!L[now])//???
                        {
                                now=R[now];
                        }
                        update(now);
                        maintain(now);
                        return ;
                }
                if (_id<id[now])
                {
                        Delete(L[now],_id);
                }else
                {
                        Delete(R[now],_id);
                }
                update(now);
                maintain(now);
                return ;
        }
        void Scan(int &now)
        {
                if (!now)return ;
                Scan(L[now]);
                printf("<%d,%d> ",id[now],pos[now]);
                Scan(R[now]);
        }

}SBT;
struct pTreap
{
        int L[MAXT],R[MAXT],K[MAXT],id[MAXT],pos[MAXT],len[MAXT],size[MAXT],S[MAXT];
        int root;
        queue<int> Q;
        pTreap()
        {
                root=0;
                for(int i=1;i<=MAXT;i++)Q.push(i);
        }
        void up(int now)
        {
                if (!now)return;
                S[now]=S[L[now]]+S[R[now]]+1;
                size[now]=size[L[now]]+size[R[now]]+len[now];
        }
        int Merge(int x,int y)//???
        {
                if (!y)return x;
                if (!x)return y;
                if (K[x]<K[y])
                {
                        R[x]=Merge(R[x],y);
                        up(x);
                        return x;
                }else
                {
                        L[y]=Merge(x,L[y]);
                        up(y);
                        return y;
                }
        }
        pair<int,int> Split(int now,int cnt)
        {
                if (!now)return make_pair(0,0);
                if (S[L[now]]+1<=cnt)
                {
                        pair<int,int> p1;
                        p1=Split(R[now],cnt-S[L[now]]-1);
                        L[now]=Merge(L[now],p1.first);
                        return make_pair(now,p1.second);
                }else
                {
                        pair<int,int> p1;
                        p1=Split(L[now],cnt);
                        R[now]=Merge(p1.second,R[now]);
                        return make_pair(p1.first,now);
                }
        }
        int Insert(int now,int rk,int _id,int _len,int _pos)
        {
                pair<int,int> p1;
                p1=Split(now,rk);
                now=Q.front();
                Q.pop();
                K[now]=rand();
                id[now]=_id;
                len[now]=_len;
                pos[now]=_pos;
                S[now]=1;
                up(now);
                return Merge(p1.first,Merge(now,p1.second));
        }
        group Get(int now,int _pos)
        {
                group g1;
                if (!now)return make_group(0,0,0);
                if (_pos==pos[now])
                {
                        int l,r;
                        l=L[now],r=R[now];
                        L[now]=R[now]=0;
                        up(now);
                        return make_group(l,now,r);
                }
                if (_pos<pos[now])
                {
                        g1=Get(L[now],_pos);
                        L[now]=g1.third;
                        g1.third=now;
                        up(now);
                        return g1;
                }
                if (_pos>pos[now])
                {
                        g1=Get(R[now],_pos);
                        R[now]=g1.first;
                        g1.first=now;
                        up(now);
                        return g1;
                }
        }
        int Get_new_node()
        {
                int ret=Q.front();
                Q.pop();
                return ret;
        }
        int Get_id(int now,int _pos)
        {
                if (!now)throw "Error:Cannot find id";
                if (size[L[now]]+1<=_pos&&size[L[now]]+len[now]>=_pos)
                {
                        return id[now]+_pos-size[L[now]]-1;
                }
                if (_pos<=size[L[now]])
                {
                        return Get_id(L[now],_pos);
                }else
                {
                        return Get_id(R[now],_pos-size[L[now]]-len[now]);
                }
        }
        void Scan(int now,char ch=' ')
        {
                if (!now)return ;
                if (now==root&&size[now]!=1000)throw "range error!!";
                Scan(L[now],ch);
                printf("<%d,%d,%d>%c",id[now],len[now],pos[now],ch);
                Scan(R[now],ch);
        }
        void Scan2(int now,char ch=' ')
        {
                if (!now)return ;
                Scan2(L[now]);
                for (int i=0;i<len[now];i++)
                {
                        printf("%d%c",id[now]+i,ch);
                }
                Scan2(R[now]);
        }
}T;
int n,m;
int main()
{
        try{
        int i,x,y;
        int last_ans=0,ans;
        int now_rank,first_rank,last_rank;
        int opt;
        pair<int,int> p1,p2;
        int ptr_h,ptr_t;
        group g1,g2;
        scanf("%d%d",&n,&m);
        T.Scan2(1);
        SBT.Insert(SBT.root,1,1);
        T.root=T.Insert(T.root,0,1,n,1);
        ptr_h=1,ptr_t=n;
        for (i=0;i<m;i++)
        {
        		last_ans=0;
                scanf("%d",&opt);
                switch(opt)
                {
                        case 1://change id
                                scanf("%d%d",&x,&y);
                                x-=last_ans;y-=last_ans;
                                p1=SBT.Find(SBT.root,x);//<id,pos>
                                g1=T.Get(T.root,p1.second);
                                first_rank=T.size[g1.first]+1;
                                now_rank=first_rank+x-p1.first;
                                last_rank=T.size[g1.first]+T.size[g1.second];
                                ans=now_rank;
                                if (now_rank>first_rank)
                                {
                                        g2.first=T.Get_new_node();
                                        T.S[g2.first]=1;
                                        T.K[g2.first]=rand();
                                        T.len[g2.first]=now_rank-first_rank;
                                        T.id[g2.first]=p1.first;
                                        T.pos[g2.first]=p1.second;
                                }else g2.first=0;
                                if (now_rank<last_rank)
                                {
                                        g2.third=T.Get_new_node();
                                        T.S[g2.third]=1;
                                        T.K[g2.third]=rand();
                                        T.len[g2.third]=last_rank-now_rank;
                                        T.id[g2.third]=x+1;
                                        T.pos[g2.third]=p1.second+now_rank-first_rank+1;
                                }else g2.third=0;
                                g2.second=g1.second;
                                T.S[g2.second]=1;
                                T.K[g2.second]=rand();
                                T.len[g2.second]=1;
                                T.id[g2.second]=y;
                                T.pos[g2.second]=p1.second+now_rank-first_rank;
                                T.up(g2.first);
                                T.up(g2.second);
                                T.up(g2.third);
                                g1.second=T.Merge(g2.first,T.Merge(g2.second,g2.third));
                                T.root=T.Merge(g1.first,T.Merge(g1.second,g1.third));


                                if (now_rank==first_rank)SBT.Delete(SBT.root,p1.first);
                                SBT.Insert(SBT.root,y,p1.second+now_rank-first_rank);
                                if (now_rank<last_rank)SBT.Insert(SBT.root,x+1,p1.second+now_rank-first_rank+1);
                                break;
                        case 2://To the first
                                scanf("%d",&x);
                                x-=last_ans;    
                                p1=SBT.Find(SBT.root,x);//<id,pos>
                                g1=T.Get(T.root,p1.second);
                                first_rank=T.size[g1.first]+1;
                                now_rank=first_rank+x-p1.first;
                                last_rank=T.size[g1.first]+T.size[g1.second];
                                ans=now_rank;
                                if (now_rank>first_rank)
                                {
                                        g2.first=T.Get_new_node();
                                        T.S[g2.first]=1;
                                        T.K[g2.first]=rand();
                                        T.len[g2.first]=now_rank-first_rank;
                                        T.id[g2.first]=p1.first;
                                        T.pos[g2.first]=p1.second;
                                }else g2.first=0;
                                if (now_rank<last_rank)
                                {
                                        g2.third=T.Get_new_node();
                                        T.S[g2.third]=1;
                                        T.K[g2.third]=rand();
                                        T.len[g2.third]=last_rank-now_rank;
                                        T.id[g2.third]=x+1;
                                        T.pos[g2.third]=p1.second+now_rank-first_rank+1;
                                }else g2.third=0;
                                g2.second=g1.second;
                                T.S[g2.second]=1;
                                T.K[g2.second]=rand();
                                T.len[g2.second]=1;
                                T.id[g2.second]=x;
                                T.pos[g2.second]=--ptr_h;
                                T.up(g2.first);
                                T.up(g2.second);
                                T.up(g2.third);
                                g1.second=T.Merge(g2.first,g2.third);
                                T.root=T.Merge(g2.second,T.Merge(g1.first,T.Merge(g1.second,g1.third)));
                                if (now_rank==first_rank)SBT.Delete(SBT.root,p1.first);
                                SBT.Insert(SBT.root,x,ptr_h);
                                if (now_rank<last_rank)SBT.Insert(SBT.root,x+1,p1.second+now_rank-first_rank+1);
                                break;
                        case 3://To thre lase
                                scanf("%d",&x);
                                x-=last_ans;    
                                p1=SBT.Find(SBT.root,x);//<id,pos>
                                g1=T.Get(T.root,p1.second);
                                first_rank=T.size[g1.first]+1;
                                now_rank=first_rank+x-p1.first;
                                last_rank=T.size[g1.first]+T.size[g1.second];
                                ans=now_rank;
                                if (now_rank>first_rank)
                                {
                                        g2.first=T.Get_new_node();
                                        T.S[g2.first]=1;
                                        T.K[g2.first]=rand();
                                        T.len[g2.first]=now_rank-first_rank;
                                        T.id[g2.first]=p1.first;
                                        T.pos[g2.first]=p1.second;
                                }else g2.first=0;
                                if (now_rank<last_rank)
                                {
                                        g2.third=T.Get_new_node();
                                        T.S[g2.third]=1;
                                        T.K[g2.third]=rand();
                                        T.len[g2.third]=last_rank-now_rank;
                                        T.id[g2.third]=x+1;
                                        T.pos[g2.third]=p1.second+now_rank-first_rank+1;
                                }else g2.third=0;
                                g2.second=g1.second;
                                T.S[g2.second]=1;
                                T.K[g2.second]=rand();
                                T.len[g2.second]=1;
                                T.id[g2.second]=x;
                                T.pos[g2.second]=++ptr_t;
                                T.up(g2.first);
                                T.up(g2.second);
                                T.up(g2.third);
                                g1.second=T.Merge(g2.first,g2.third);
                                T.root=T.Merge(T.Merge(g1.first,T.Merge(g1.second,g1.third)),g2.second);
                                if (now_rank==first_rank)SBT.Delete(SBT.root,p1.first);
                                SBT.Insert(SBT.root,x,ptr_t);
                                if (now_rank<last_rank)SBT.Insert(SBT.root,x+1,p1.second+now_rank-first_rank+1);
                                break;
                        case 4://Query position
                                scanf("%d",&x);
                                x-=last_ans;
                                ans=T.Get_id(T.root,x);
                                break;
                }
    //            cout<<"Query:"<<"<"<<i<<">"<<opt<<" "<<x;if (opt==1)cout<<" "<<y;cout<<endl;
        //        cout<<"Query_ret:"<<ans<<endl;
                last_ans=ans;
    //            cout<<"SBT<id,pos>:";SBT.Scan(SBT.root);cout<<endl;
    //            cout<<"Treap<id,len,pos>:";T.Scan(T.root);cout<<endl;
    //            cout<<"Seq:";T.Scan2(T.root);cout<<endl;
                printf("%d\n",ans);
        }

        }catch(const char * err)
        {
                cerr<<err<<endl;
        }

}
