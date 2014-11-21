#ifndef __KDTREE_HPP__

#include <iostream>

namespace kdtree
{

template <typename T>
class node
{
	protected:
		T value_;
	
		node * left_;
		node * right_;

	public:
	// CONSTRUCTORS
		node ();
		node ( node<T> & , node<T> & );
		node ( T );
		node ( const node<T> & );

	// DESTRUCTOR
		~node ();

	// GETTERS
		inline T       value () const;
		inline node<T> left  () const;
		inline node<T> right () const;

	// SETTERS
		inline void value ( T );
		inline void left  ( node<T> & );
		inline void right ( node<T> & );

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

#include "../src/kdtree.cxx"



}

#endif
