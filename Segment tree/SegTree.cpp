#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back

int v [100000] ;
int seg_tree [400000] ;

void update (int i , int l , int r , int pos , int x) 
{
    if(l == r) 
    {
        seg_tree[i] = x ;
    }
    else 
    {
        int mid = (l + r) / 2 ;

	    if(pos <= mid) 
        {
            update (2 * i , l , mid , pos , x) ;
        }
	    else 
        {
            update ((2 * i) + 1 , mid + 1 , r , pos , x) ;
        }

	    seg_tree[i] = seg_tree[2 * i] + seg_tree[(2 * i) + 1] ;
    }
}
int query (int i , int l , int r , int ql , int qr) 
{
    if(l >= ql && r <= qr) 
    {
        return seg_tree [i] ;
    }

    if(l > qr || r < ql) 
    {
        return 0 ; 
    }

    int mid = (l + r) / 2 ;

    return query (2 * i , l , mid , ql , qr) + query ((2 * i) + 1 , mid + 1 , r , ql , qr) ;
}
void build (int l , int r , int i) 
{
    if(l == r) 
    { 
        seg_tree[i] = v[l];
        return;
    }

    int mid = (l + r) / 2 ;

    build (l , mid , 2 * i) ; 
    build (mid + 1 , r , (2 * i) + 1) ; 

    seg_tree[i] = seg_tree[2 * i] + seg_tree[(2 * i ) + 1] ; 
}
int main() 
{
    int n , ql , qr , aux , m , ans ;
    char type ;

    cin >> n ;

    for(int i = 0 ; i < n ; i++) 
    {
        cin >> v[i];
    }

    build (0 , n - 1 , 1) ;
    
    cin >> m ;

    for(int i = 0 ; i < m ; i++)
    {
        cin >> type ;
        cin >> ql >> qr;

        if (type == 'Q')
        {
            cout << query (1 , 0 , n - 1 , ql , qr) << endl ;
        }
        else if (type == 'U')
        {
            update(1 , 0 , n - 1 , ql , qr) ;
        }
    }

    return 0;
}