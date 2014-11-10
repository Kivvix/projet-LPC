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
	std::cout << b() << std::endl;
	b() = 2;
	std::cout << b() << std::endl;

	d.value( 0 );
	std::cout << d() << std::endl;

	std::cout << c() << std::endl;

	return 0;
}
