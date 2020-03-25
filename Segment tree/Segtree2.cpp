// segtree para contar quantidade de numeros pares/impar numa query alem do update

#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back

lli v [100001] ;
lli vimpar [100001] ;
lli vpar [100001] ;
lli seg_tree [500005] ;
lli seg_tree2 [500005] ;

lli query (lli i , lli l , lli r , lli ql , lli qr) // query par
{
    if(l >= ql && r <= qr) 
    {
        return seg_tree [i] ;
    }

    if(l > qr || r < ql) 
    {
        return 0 ; 
    }

    lli mid = (l + r) / 2 ;

    return query (2 * i , l , mid , ql , qr) + query ((2 * i) + 1 , mid + 1 , r , ql , qr) ;
}
lli query2 (lli i , lli l , lli r , lli ql , lli qr) // query impar
{
    if(l >= ql && r <= qr) 
    {
        return seg_tree2 [i] ;
    }

    if(l > qr || r < ql) 
    {
        return 0 ; 
    }

    lli mid = (l + r) / 2 ;

    return query2 (2 * i , l , mid , ql , qr) + query2 ((2 * i) + 1 , mid + 1 , r , ql , qr) ;
}
void build (lli l , lli r , lli i) // bulid par
{
    if(l == r) 
    { 
        seg_tree[i] = vpar[l] ;
        return;
    }

    lli mid = (l + r) / 2 ;

    build (l , mid , 2 * i) ; 
    build (mid + 1 , r , (2 * i) + 1) ; 

    seg_tree[i] = seg_tree[2 * i] + seg_tree[(2 * i ) + 1] ; 
}
void build2 (lli l , lli r , lli i) // bulid impar
{
    if(l == r) 
    { 
        seg_tree2[i] = vimpar[l] ;
        return;
    }

    lli mid = (l + r) / 2 ;

    build2 (l , mid , 2 * i) ; 
    build2 (mid + 1 , r , (2 * i) + 1) ; 

    seg_tree2[i] = seg_tree2[2 * i] + seg_tree2[(2 * i ) + 1] ; 
}
void update (lli i , lli l , lli r , lli pos , lli x) // update par
{
    if(l == r) 
    {
        seg_tree[i] = x ;
    }
    else 
    {
        lli mid = (l + r) / 2 ;

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
void update2 (lli i , lli l , lli r , lli pos , lli x) // update impar
{
    if(l == r) 
    {
        seg_tree2[i] = x ;
    }
    else 
    {
        lli mid = (l + r) / 2 ;

	    if(pos <= mid) 
        {
            update2 (2 * i , l , mid , pos , x) ;
        }
	    else 
        {
            update2 ((2 * i) + 1 , mid + 1 , r , pos , x) ;
        }

	    seg_tree2[i] = seg_tree2[2 * i] + seg_tree2[(2 * i) + 1] ;
    }
}
int main() 
{
    lli n , ql , qr , aux , m , ans , type ;

    cin >> n ;

    for (lli i = 0 ; i < n ; i++) 
    {
        cin >> v[i];

        if (v[i] % 2 == 0) 
        {
            vpar[i] = 1 ;
            vimpar[i] = 0 ; 
        }
        else
        {
            vpar[i] = 0 ;
            vimpar[i] = 1 ; 
        }     
    }

    build (0 , n - 1 , 1) ;
    build2 (0 , n - 1 , 1) ;
    
    cin >> m ;

    for (lli i = 0 ; i < m ; i++)
    {
        cin >> type >> ql >> qr ;

        if (type == 0) // update 
        {
            ql--;
            
            if (qr % 2 == 0)
            {
                update(1 , 0 , n - 1 , ql , 1) ;
                update2(1 , 0 , n - 1 , ql , 0) ;
            }
            else
            {
                update(1 , 0 , n - 1 , ql , 0) ;
                update2(1 , 0 , n - 1 , ql , 1) ;
            }
        }
        if (type == 1) // par
        {
            ql--;
            qr-- ;

            cout << query (1 , 0 , n - 1 , ql , qr) << endl ;
        }
        else if (type == 2) // impar
        {
            ql--;
            qr-- ;

            cout << query2 (1 , 0 , n - 1 , ql , qr) << endl ;
        }
    }

    return 0;
}
