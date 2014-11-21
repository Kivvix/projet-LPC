#include <iostream>

#include "../inc/kdtree.hpp"

int main( int , char ** )
{
	kdtree::node<int> a;
	kdtree::node<int> b(2);
	kdtree::node<int> d(a,b);
	kdtree::node<int> c( d[2] );

	a.value( 1 );
	b = a;

	d.value( 0 );
	d[1]() = 3;
	d[2]() = 4;

	return 0;
}
