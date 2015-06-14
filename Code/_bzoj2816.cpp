#include <cstdio>

#include <algorithm>

#include <cstring>

#include <set>

 

using namespace std ;

 

#define REP( i , l , r ) for ( int i = l ; i <= r ; ++ i )

#define rep( i , x ) for ( int i = 0 ; i ++ < x ; )

 

const int maxn = 10100 , maxc = 11 ;

 

struct link_cut_tree {

     

    #define C( t ) ( t == L( F( t ) ) )

     

    #define L( t ) left[ t ]

    #define R( t ) right[ t ]

    #define M( t ) Max[ t ]

    #define T( t ) Tag[ t ]

    #define F( t ) father[ t ]

    #define P( t ) parent[ splay_root( t ) ]

    #define G( t ) F( F( t ) )

    #define V( t ) value[ t ]

     

    int left[ maxn ] , right[ maxn ] , Max[ maxn ] , parent[ maxn ] , father[ maxn ] , value[ maxn ] ;

    bool Tag[ maxn ] ;

     

    link_cut_tree(  ) {

        memset( left , 0 , sizeof( left ) ) ;

        memset( right , 0 , sizeof( right ) ) ;

        memset( right , 0 , sizeof( right ) ) ;

        memset( parent , 0 , sizeof( parent ) ) ;

        memset( father , 0 , sizeof( father ) ) ;

        memset( Max , 0 , sizeof( Max ) ) ;

        memset( Tag , false , sizeof( Tag ) ) ;

    }

     

    inline void pushdown( int t ) {

        if ( T( t ) && t ) {

            swap( L( t ) , R( t ) ) ;

            T( L( t ) ) ^= true , T( R( t ) ) ^= true , T( t ) = false ;

        }

    }

     

    inline void update( int t ) {

        M( t ) = max( max( M( L( t ) ) , M( R( t ) ) ) , V( t ) ) ;

    }

     

    inline void zag( int t ) {

        pushdown( t ) ; pushdown( R( t ) ) ;

        int k = R( t ) , u = F( t ) ; bool flag = C( t ) ;

        update( F( R( t ) = L( k ) ) = t ) ;

        update( F( L( k ) = t ) = k ) ;

        if ( F( k ) = u ) if ( flag ) L( u ) = k ; else R( u ) = k ;

    }

     

    inline void zig( int t ) {

        pushdown( t ) ; pushdown( L( t ) ) ;

        int k = L( t ) , u = F( t ) ; bool flag = C( t ) ;

        update( F( L( t ) = R( k ) ) = t ) ;

        update( F( R( k ) = t ) = k ) ;

        if ( F( k ) = u ) if ( flag ) L( u ) = k ; else R( u ) = k ;

    }

     

    inline void splay( int t ) {

        while ( F( t ) ) {

            pushdown( G( t ) ) ; pushdown( F( t ) ) ; pushdown( t ) ;

            if ( ! G( t ) ) if ( C( t ) ) zig( F( t ) ) ; else zag( F( t ) ) ; else {

                if ( C( t ) ) {

                    if ( C( F( t ) ) ) zig( G( t ) ) ; zig( F( t ) ) ;

                } else {

                    if ( ! C( F( t ) ) ) zag( G( t ) ) ; zag( F( t ) ) ;

                }

            }

        }

    }

     

    inline int splay_root( int t ) {

        splay( t ) ;

        for ( pushdown( t ) ; L( t ) ; pushdown( t = L( t ) ) ) ;

        return t ;

    }

     

    inline int Access( int t ) {

        int v = 0 ;

        do {

            splay( t ) ; pushdown( t ) ;

            F( R( t ) ) = 0 ; P( R( t ) ) = t ;

            update( F( R( t ) = v ) = t ) ;

            v = t ; t = P( t ) ;

        } while ( t ) ;

        return v ;

    }

     

    inline void Join( int v , int u ) {

        P( v ) = u ;

    }

     

    inline void cut( int v ) {

        Access( v ) ; splay( v ) ; pushdown( v ) ;

        F( L( v ) ) = 0 ; L( v ) = 0 ; update( v ) ; P( v ) = 0 ;

    }

     

    inline void Link( int v , int u ) {

        Access( v ) ; splay( v ) ; T( v ) ^= true ;

        Join( v , u ) ;

    }

     

    inline void Cut( int v , int u ) {

        Access( v ) ; int lca = Access( u ) ;

        if ( lca == v ) cut( u ) ; else cut( v ) ;

    }

     

    inline int Query( int v , int u ) {

        Access( v ) ; int lca = Access( u ) ;

        if ( lca == v ) {

            splay( v ) ; pushdown( v ) ;

            return max( V( v ) , M( R( v ) ) ) ;

        } else {

            splay( v ) ; splay( lca ) ; pushdown( lca ) ;

            return max( max( V( lca ) , M( R( lca ) ) ) , M( v ) ) ;

        }

    }

     

    inline void change( int v , int w ) {

        splay( v ) ;

        V( v ) = w ; update( v ) ;

    }

     

    inline int get_root( int v ) {

        Access( v ) ;

        return splay_root( v ) ;

    }

     

} lct[ maxc ] , L ;

 

int n , m , C , k ;

 

struct edge {

    int s , t , w ;

    edge( int _s , int _t , int _w ) : s( min( _s , _t ) ) , t( max( _s , _t ) ) , w( _w ) {

    }

    bool operator < ( const edge &x ) const {

        return s < x.s || ( s == x.s && t < x.t ) ;

    }

    bool operator == ( const edge &x ) const {

        return s == x.s && t == x.t ;

    }

    bool operator > ( const edge &x ) const {

        return s > x.s || ( s == x.s && t > x.t ) ;

    }

} ;

set < edge > bst ;

 

int D[ maxc ][ maxn ] ;

 

int main(  ) {

    memset( D , 0 , sizeof( D ) ) ;

    scanf( "%d%d%d%d" , &n , &m , &C , &k ) ;

    int val ;

    rep( i , n ) {

        scanf( "%d" , &val ) ;

        REP( j , 0 , ( C - 1 ) ) {

            lct[ j ].Max[ i ] = lct[ j ].value[ i ] = val ;

        }

    }

    while ( m -- ) {

        int s , t , w ; scanf( "%d%d%d" , &s , &t , &w ) ;

        lct[ w ].Link( s , t ) , bst.insert( edge( s , t , w ) ) ;

        D[ w ][ s ] ++ , D[ w ][ t ] ++ ;

    }

    int K = 0 ;

    while ( k -- ) {

        int a , b , c , d ; scanf( "%d" , &a ) ;

        if ( ! a ) {

            scanf( "%d%d" , &b , &c ) ;

            REP( j , 0 , ( C - 1 ) ) lct[ j ].change( b , c ) ;

        } else if ( a == 1 ) {

            scanf( "%d%d%d" , &b , &c , &d ) ;

            set < edge > :: iterator p = bst.find( edge( b , c , d ) ) ;

            if ( p == bst.end(  ) ) {

                printf( "No such edge.\n" ) ; continue ;

            }

            if ( p -> w == d ) {

                printf( "Success.\n" ) ; continue ;

            }

            if ( D[ d ][ b ] > 1 || D[ d ][ c ] > 1 ) {

                printf( "Error 1.\n" ) ; continue ;

            }

            if ( lct[ d ].get_root( b ) == lct[ d ].get_root( c ) ) {

                printf( "Error 2.\n" ) ; continue ;

            }

            printf( "Success.\n" ) ;

            lct[ p -> w ].Cut( b , c ) ; lct[ d ].Link( b , c ) ;

            D[ p -> w ][ b ] -- , D[ p -> w ][ c ] -- , D[ d ][ b ] ++ , D[ d ][ c ] ++ ;

            bst.erase( p ) ; bst.insert( edge( b , c , d ) ) ;

        } else {

            scanf( "%d%d%d" , &b , &c , &d ) ;

            if ( lct[ b ].get_root( c ) != lct[ b ].get_root( d ) ) {

                printf( "-1\n" ) ; continue ;

            }

            printf( "%d\n" , lct[ b ].Query( c , d ) ) ;

        }

    }

    return 0 ;

}
