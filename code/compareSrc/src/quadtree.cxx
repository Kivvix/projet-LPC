/* === CLASS node<T> ================================================ */

/* ------------------------------------------------------------------ *
 * CONSTRUCTORS                                                       *
 * ------------------------------------------------------------------ */

template <typename T>
node<T>::node () :
	value_  ( 0 ) ,
	child1_ ( NULL ) ,
	child2_ ( NULL ) ,
	child3_ ( NULL ) ,
	child4_ ( NULL )
{
}

template <typename T>
node<T>::node ( node<T> & c1 , node<T> & c2 , node<T> & c3 , node<T> c4 ) :
	value_ ( 0 )
{
	child1_ = new node ( c1 );
	child2_ = new node ( c2 );
	child3_ = new node ( c3 );
	child4_ = new node ( c4 );
}

template <typename T>
node<T>::node ( T value ) :
	value_  ( value ) ,
	child1_ ( NULL  ) ,
	child2_ ( NULL  ) ,
	child3_ ( NULL  ) ,
	child4_ ( NULL  )
{
}

template <typename T>
node<T>::node ( const node<T> & n ) :
	value_ ( n.value_ )
{
	if ( n.child1_ ) {
		child1_ = new node ( *n.child1_ );
	} else {
		child1_ = 0;
	}
	if ( n.child2_ ) {
		child2_ = new node ( *n.child2_ );
	} else {
		child2_ = 0;
	}
	if ( n.child3_ ) {
		child3_ = new node ( *n.child3_ );
	} else {
		child3_ = 0;
	}
	if ( n.child4_ ) {
		child4_ = new node ( *n.child4_ );
	} else {
		child4_ = 0;
	}
}


/* ------------------------------------------------------------------ *
 * DESTRUCTOR                                                         *
 * ------------------------------------------------------------------ */

template <typename T>
node<T>::~node ()
{
	delete child1_;
	delete child2_;
	delete child3_;
	delete child4_;
}


/* ------------------------------------------------------------------ *
 * GETTERS                                                            *
 * ------------------------------------------------------------------ */

template <typename T>
inline T       node<T>::value  () const { return   value_;  }
template <typename T>
inline node<T> node<T>::child1 () const { return * child1_; }
template <typename T>
inline node<T> node<T>::child2 () const { return * child2_; }
template <typename T>
inline node<T> node<T>::child3 () const { return * child3_; }
template <typename T>
inline node<T> node<T>::child4 () const { return * child4_; }


/* ------------------------------------------------------------------ *
 * SETTERS                                                            *
 * ------------------------------------------------------------------ */

template <typename T>
inline void node<T>::value  ( T v )         { value_  = v;  }
template <typename T>
inline void node<T>::child1 ( node<T> & c ) { child1_ = &c; }
template <typename T>
inline void node<T>::child2 ( node<T> & c ) { child2_ = &c; }
template <typename T>
inline void node<T>::child3 ( node<T> & c ) { child3_ = &c; }
template <typename T>
inline void node<T>::child4 ( node<T> & c ) { child4_ = &c; }


/* ------------------------------------------------------------------ *
 * OPERATORS                                                          *
 * ------------------------------------------------------------------ */

template <typename T>
T & node<T>::operator () ()
{
	return value_;
}

template <typename T>
T & node<T>::operator () () const
{
	return value_;
}

template <typename T>
node<T> & node<T>::operator [] ( int i )
{
	if ( i == 1 ) {
		return *child1_;
	} else if ( i == 2 ) {
		return *child2_;
	} else if ( i == 3 ) {
		return *child3_;
	} else if ( i == 4 ) {
		return *child4_;
	} else {
		throw e_bornes();
	}
}

template <typename T>
const node<T> & node<T>::operator [] ( int i ) const
{
	if ( i == 1 ) {
		return *left_;
	} else if ( i == 2 ) {
		return *right_;
	} else {
		throw e_bornes();
	}
}

template <typename T>
node<T> & node<T>::operator = ( const node<T> & n )
{
	if ( &n != this ) {
		delete child1_; delete child2_; delete child3_; delete child4_;
		value_ = n.value_;

		if ( n.child1_ ) {
			*child1_ = *(n.child1_);
		} else {
			child1_ = 0;
		}
		if ( n.child2_ ) {
			*child2_ = *(n.child2_);
		} else {
			child2_= 0;
		}
		if ( n.child3_ ) {
			*child3_ = *(n.child3_);
		} else {
			child3_= 0;
		}
		if ( n.child4_ ) {
			*child4_ = *(n.child4_);
		} else {
			child4_= 0;
		}
	}

	return *this;
}

/* ================================================================== */

/*
template <typename T>
std::ostream operator << ( std::ostream & o , const node<T> & n )
{
	o << n() << " ( " << n[1] << " , " << n[2] << " )" << std::endl;
	return o;
}
*/
