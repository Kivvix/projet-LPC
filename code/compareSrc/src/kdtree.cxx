/* === CLASS node<T> ================================================ */

/* ------------------------------------------------------------------ *
 * CONSTRUCTORS                                                       *
 * ------------------------------------------------------------------ */

template <typename T>
node<T>::node () :
	value_ ( 0 ) ,
	left_  ( NULL ) ,
	right_ ( NULL )
{
}

template <typename T>
node<T>::node ( node<T> & left , node<T> & right ) :
	value_ ( 0 )
{
	left_  = new node ( left  );
	right_ = new node ( right );
}

template <typename T>
node<T>::node ( T value ) :
	value_ ( value ) ,
	left_  ( NULL  ) ,
	right_ ( NULL  )
{
}

template <typename T>
node<T>::node ( const node<T> & n ) :
	value_ ( n.value_ )
{
	if ( n.left_ ) {
		left_ = new node ( *n.left_ );
	} else {
		left_ = 0;
	}
	if ( n.right_ ) {
		right_ = new node ( *n.right_ );
	} else {
		right_ = 0;
	}
}


/* ------------------------------------------------------------------ *
 * DESTRUCTOR                                                         *
 * ------------------------------------------------------------------ */

template <typename T>
node<T>::~node ()
{
	//std::cout << "kill :" << *this << std::endl;
	delete left_;
	delete right_;
}


/* ------------------------------------------------------------------ *
 * GETTERS                                                            *
 * ------------------------------------------------------------------ */

template <typename T>
inline T       node<T>::value () const { return   value_; }
template <typename T>
inline node<T> node<T>::left  () const { return * left_;  }
template <typename T>
inline node<T> node<T>::right () const { return * right_; }


/* ------------------------------------------------------------------ *
 * SETTERS                                                            *
 * ------------------------------------------------------------------ */

template <typename T>
inline void node<T>::value ( T v )         { value_ = v;  }
template <typename T>
inline void node<T>::left  ( node<T> & l ) { left_  = &l; }
template <typename T>
inline void node<T>::right ( node<T> & r ) { right_ = &r; }


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
		return *left_;
	} else if ( i == 2 ) {
		return *right_;
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
		delete right_; delete left_;
		value_ = n.value_;

		if ( n.left_ ) {
			*left_ = *(n.left_);
		} else {
			left_ = 0;
		}
		if ( n.right_ ) {
			*right_ = *(n.right_);
		} else {
			right_ = 0;
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
