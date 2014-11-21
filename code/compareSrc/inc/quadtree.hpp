#ifndef __QUADTREE_HPP__

#include <iostream>

namespace quadtree
{

template <typename T>
class node
{
	protected:
		T value_;
	
		node * child1_;
		node * child2_;
		node * child3_;
		node * child4_;

	public:
	// CONSTRUCTORS
		node ();
		node ( node<T> & , node<T> & , node<T> & , node<T> & );
		node ( T );
		node ( const node<T> & );

	// DESTRUCTOR
		~node ();

	// GETTERS
		inline T       value  () const;
		inline node<T> child1 () const;
		inline node<T> child2 () const;
		inline node<T> child3 () const;
		inline node<T> child4 () const;

	// SETTERS
		inline void value  ( T );
		inline void child1 ( node<T> & );
		inline void child2 ( node<T> & );
		inline void child3 ( node<T> & );
		inline void child4 ( node<T> & );

	// OPERATORS
		T &             operator () ();
		T &             operator () () const;
		node<T> &       operator [] ( int );
		const node<T> & operator [] ( int ) const;
		node<T> &       operator =  ( const node<T> & );

	// METHODES

	// EXCEPTIONS
		class e_bornes {
			public:
			e_bornes () {
				std::cerr << "\033[1;31m ERROR : not Hénaff children \033[0m" << std::endl;
			}
		};
		class e_iterations {
			public:
			e_iterations () {
				std::cerr << "\033[1;31m ERROR : too many iterations \033[0m" << std::endl;
			}
		};

};

//template <typename T>
//std::ostream operator << ( std::ostream & , const node<T> & );

//template <typename T>
//node<T> build( space<T> );

#include "../src/quadtree.cxx"



}

#endif
