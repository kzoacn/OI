#include <cstdio>

#include <algorithm>

#include <cstring>

  

using namespace std ;

  

const int maxv = 35000000 ;

const int maxn = 101000 ;

const int maxV = 1500000 ;

  

struct SORT {

    int a[ maxn << 1 ] , b[ maxn << 1 ] , n , m ;

    SORT(  ) {

        n = m = 0 ;

    }

    inline void add( int x ) {

        a[ ++ n ] = x ;

    }

    inline void solve(  ) {

        sort( a + 1 , a + n + 1 ) ; m = 0 ;

        for ( int i = 0 ; i ++ < n ; ) {

            if ( i == 1 || a[ i ] != a[ i - 1 ] ) b[ ++ m ] = a[ i ] ;

        }

    }

    inline int getpos( int x ) {

        if ( x == b[ 1 ] ) return 1 ;

        if ( x == b[ m ] ) return m ;

        int l = 1 , r = m , mid ;

        while ( r - l > 1 ) {

            mid = ( l + r ) >> 1 ;

            if ( b[ mid ] == x ) return mid ;

            if ( x < b[ mid ] ) r = mid ; else l = mid ;

        }

    }

} Px , Py ;

  

struct node {

    node *lc , *rc ;

    int sum ;

} sgt[ maxv ] ;

  

node *pt ;

  

inline void Init_sgt(  ) {

    pt = sgt ;

}

  

void change( int x , int y , int l , int r , node* &t ) {

    if ( ! t ) {

        t = pt ++ ; 

        t -> lc = t -> rc = NULL , t -> sum = 0 ;

    }

    t -> sum += y ;

    if ( l == r ) return ;

    int mid = ( l + r ) >> 1 ;

    if ( x <= mid ) change( x , y , l , mid , t -> lc ) ; else

    change( x , y , mid + 1 , r , t -> rc ) ;

}

  

int query( int l , int r , int _l , int _r , node *t ) {

    if ( ! t ) return 0 ;

    if ( l == _l && r == _r ) return t -> sum ;

    int mid = ( _l + _r ) >> 1 ;

    if ( r <= mid )  return query( l , r , _l , mid , t -> lc ) ;

    if ( l > mid ) return query( l , r , mid + 1 , _r , t -> rc ) ;

    return query( l , mid , _l , mid , t -> lc ) + query( mid + 1 , r , mid + 1 , _r , t -> rc ) ;

}

  

struct Node {

    Node *lc , *rc ;

    node *t ; 

} Sgt[ maxV ] ;

  

Node *Root , *Pt ;

  

inline void Init_Sgt(  ) {

    Root = NULL , Pt = Sgt ;

}

  

void Change( int px , int py , int v , int l , int r , Node* &t ) {

    if ( ! t ) {

        t = Pt ++ ;

        t -> lc = t -> rc = NULL , t -> t = NULL ;

    }

    change( py , v , 1 , Py.m , t -> t ) ;

    if ( l == r ) return ;

    int mid = ( l + r ) >> 1 ;

    if ( px <= mid ) Change( px , py , v , l , mid , t -> lc ) ; else

    Change( px , py , v , mid + 1 , r , t -> rc ) ;

}

  

int Query( int lx , int rx , int ly , int ry , int _l , int _r , Node *t ) {

    if ( ! t ) return 0 ;

    if ( lx == _l && rx == _r ) return query( ly , ry , 1 , Py.m , t -> t ) ;

    int mid = ( _l + _r ) >> 1 ;

    if ( rx <= mid ) return Query( lx , rx , ly , ry , _l , mid , t -> lc ) ;

    if ( lx > mid ) return Query( lx , rx , ly , ry , mid + 1 , _r , t -> rc ) ;

    return Query( lx , mid , ly , ry , _l , mid , t -> lc ) + Query( mid + 1 , rx , ly , ry , mid + 1 , _r , t -> rc ) ;

}

  

struct seg {

    int lx , rx , ly , ry , z , t , x ;

    inline void oper( int _lx , int _rx , int _ly , int _ry , int _z , int _t , int _x ) {

        lx = _lx , rx = _rx , ly = _ly , ry = _ry , z = _z , t = _t , x = _x ;

    }

    bool operator < ( const seg &S ) const {

        return z < S.z ;

    }

} s[ maxn << 1 ] ;

  

int n , q , a[ maxn ][ 5 ] , sta[ maxn ] , tp = 0 , ans[ maxn ] ;

  

struct point {

    int x , y , z , v ;

    inline void oper( int _x , int _y , int _z , int _v ) {

        x = _x , y = _y , z = _z , v = _v ;

    }

    bool operator < ( const point &P ) const {

        return z < P.z ;

    }

} p[ maxn ] ;

  

int pn , sn ;

  

void solve( int l , int r ) {

    if ( l == r ) return ;

    int mid = ( l + r ) >> 1 ; pn = sn = 0 ;

    for ( int i = l ; i <= mid ; ++ i ) if ( ! a[ i ][ 0 ] ) {

        p[ ++ pn ].oper( a[ i ][ 1 ] , a[ i ][ 2 ] , a[ i ][ 3 ] , a[ i ][ 4 ] ) ;

    }

    for ( int i = mid + 1 ; i <= r ; ++ i ) if ( a[ i ][ 0 ] ) {

        s[ ++ sn ].oper( a[ i ][ 1 ] , a[ i ][ 1 ] + a[ i ][ 4 ] , a[ i ][ 2 ] , a[ i ][ 2 ] + a[ i ][ 4 ] , a[ i ][ 3 ] - 1 , i , -1 ) ;

        s[ ++ sn ].oper( a[ i ][ 1 ] , a[ i ][ 1 ] + a[ i ][ 4 ] , a[ i ][ 2 ] , a[ i ][ 2 ] + a[ i ][ 4 ] , a[ i ][ 3 ] + a[ i ][ 4 ] , i , 1 ) ;

    }

    sort( p + 1 , p + pn + 1 ) , sort( s + 1 , s + sn + 1 ) ;

    int x = 1 ;

    Init_sgt(  ) , Init_Sgt(  ) ;

    for ( int i = 0 ; i ++ < sn ; ) {

        for ( ; x <= pn && p[ x ].z <= s[ i ].z ; ++ x ) {

            Change( Px.getpos( p[ x ].x ) , Py.getpos( p[ x ].y ) , p[ x ].v , 1 , Px.m , Root ) ;

        }

        ans[ s[ i ].t ] += ( s[ i ].x * Query( Px.getpos( s[ i ].lx ) , Px.getpos( s[ i ].rx ) , Py.getpos( s[ i ].ly ) , Py.getpos( s[ i ].ry ) , 1 , Px.m , Root ) ) ;

    }

    solve( l , mid ) , solve( mid + 1 , r ) ;

}

  

int main(  ) {
	freopen("bzoj3290.in","r",stdin);

    scanf( "%d" , &n ) ;

    for ( int i = 0 ; i ++ < n ; ) {

        scanf( "%d%d%d" , &a[ i ][ 1 ] , &a[ i ][ 2 ] , &a[ i ][ 3 ] ) ;

        a[ i ][ 0 ] = 0 , a[ i ][ 4 ] = 1 ;

    }

    scanf( "%d" , &q ) ;

    char s[ 10 ] ;

    for ( int i = n + 1 ; i <= ( n + q ) ; ++ i ) {

        scanf( "%s" , s ) ;

        if ( s[ 0 ] == 'A' ) {

            a[ i ][ 0 ] = 0 , sta[ ++ tp ] = i ;

            scanf( "%d%d%d" , &a[ i ][ 1 ] , &a[ i ][ 2 ] , &a[ i ][ 3 ] ) ;

            a[ i ][ 4 ] = 1 ;

        } else if ( s[ 0 ] == 'C' ) {

            int now = sta[ tp -- ] ;

            a[ i ][ 0 ] = 0 , a[ i ][ 1 ] = a[ now ][ 1 ] , a[ i ][ 2 ] = a[ now ][ 2 ] , a[ i ][ 3 ] = a[ now ][ 3 ] , a[ i ][ 4 ] = -1 ;

        } else {

            a[ i ][ 0 ] = 1 ;

            scanf( "%d%d%d%d" , &a[ i ][ 1 ] , &a[ i ][ 2 ] , &a[ i ][ 3 ] , &a[ i ][ 4 ] ) ;

        }

    }

    n += q ;

    for ( int i = 0 ; i ++ < n ; ) if ( ! a[ i ][ 0 ] ) {

        Px.add( a[ i ][ 1 ] ) , Py.add( a[ i ][ 2 ] ) ;

    } else {

        Px.add( a[ i ][ 1 ] ) , Px.add( a[ i ][ 1 ] + a[ i ][ 4 ] ) ;

        Py.add( a[ i ][ 2 ] ) , Py.add( a[ i ][ 2 ] + a[ i ][ 4 ] ) ;

    }

    Px.solve(  ) , Py.solve(  ) ;

    memset( ans , 0 , sizeof( ans ) ) ;

    solve( 1 , n ) ;

    for ( int i = 0 ; i ++ < n ; ) if ( a[ i ][ 0 ] ) printf( "%d\n" , ans[ i ] ) ;

    return 0 ;

}
