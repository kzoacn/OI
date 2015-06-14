# include<cstdio>
# include<iostream>
# include<algorithm>

using namespace std;

# define MAX 10000000

struct node
{
    int value;
    int wei;
}a[MAX];

int cmp ( const struct node & x, const struct node & y )
{
    return x.value < y.value;
}

int main(void)
{
    int n;
    while ( cin>>n )
    {
        for ( int i = 0;i < n;i++ )
        {
            cin>>a[i].value;
        }
        long long sum = 0;
        for ( int i = 0;i < n;i++ )
        {
            cin>>a[i].wei;
            sum+=a[i].wei;
        }
        long double sum1 = sum/2.0;

        sort(a,a+n,cmp);

        long long max_limit = 0;
        long long min_limit = 0;

        int pos_wei;
        for ( int i = 1;i < n-1;i++ )
        {
            min_limit = min_limit + a[i-1].wei;
            max_limit = sum - min_limit - a[i].wei;

            if ( min_limit < sum1 && (max_limit <= sum1) )
            {
                pos_wei = a[i].value;
                break;
            }

        }
        cout<<pos_wei<<endl;

    }


    return 0;
}
