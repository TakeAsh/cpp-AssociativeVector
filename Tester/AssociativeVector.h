/**
	@file AssociativeVector.h
*/

#pragma once

#include <vector>
#include <algorithm>

namespace TakeAsh {

/**
	Binary Searchable Vector
*/
template<
	typename KEY,
	typename VALUE
>
class AssociativeVector {
public:
	struct Pair :
		public std::pair<KEY, VALUE>
	{
		Pair(
			const KEY& Key,
			const VALUE& Value = VALUE()
		):
			std::pair<KEY, VALUE>(Key, Value)
		{}

		Pair(
			const std::pair<KEY, VALUE>& other
		):
			std::pair<KEY, VALUE>(other)
		{}

		/**
			Move constructor
		*/
		Pair(
			Pair&& other
		):
			std::pair<KEY, VALUE>()
		{
			*this = std::move(other);
		}

		/**
			Move assignment operator
		*/
		Pair& operator=(
			Pair&& other
		){
			if ( this != &other ){
				*this = std::move(other);
			}
			return *this;
		}

		/**
			Assignment operator overload<br>
			for constructing from const array
		*/
		Pair& operator=(
			const Pair& other
		){
			if ( this != &other ){
				*this = Pair(other);
			}
			return *this;
		}

		/**
			Assignment operator overload from std::pair<br>
			for make_pair macro
		*/
		Pair& operator=(
			const std::pair<KEY, VALUE>& other
		){
			*(std::pair<KEY, VALUE>*)this = other;
			return *this;
		}

		/**
			Less operator overload
		*/
		bool operator<(const Pair& other) const {
			return first < other.first;
		}
	};

	typedef KEY key_type;
	typedef VALUE mapped_type;

	typedef std::vector<Pair> InnerVector;
	typedef typename InnerVector::value_type value_type;

	typedef typename InnerVector::iterator iterator;
	typedef typename InnerVector::const_iterator const_iterator;
	typedef typename InnerVector::reverse_iterator reverse_iterator;
	typedef typename InnerVector::const_reverse_iterator const_reverse_iterator;
	typedef typename InnerVector::size_type size_type;

	AssociativeVector(void):
		_list()
	{
	}

	template <class InputIterator>
	AssociativeVector(InputIterator First, InputIterator Last):
		_list(First, Last)
	{
		std::sort(_list.begin(), _list.end());
	}
	
	template<size_t SIZE>
	AssociativeVector(const Pair (&array)[SIZE]):
		_list(array, array + SIZE)
	{
		std::sort(_list.begin(), _list.end());
	}
		
	/**
		Array subscript operator overload
	*/
	Pair& operator[](size_t Pos){
		return _list[Pos];
	}

	/**
		Find a UNIT value bonded to the key.(const version)
		@retval	!=NULL	found
		@retval	==NULL	not found
	*/
	const VALUE* operator[](const KEY Key) const {
		auto itr = lower_bound(_list.begin(), _list.end(), Pair(Key));
		return itr != _list.end()
			? &itr->second
			: NULL;
	}

	/**
		Find a UNIT value bonded to the key.(non const version)
		@retval	!=NULL	found
		@retval	==NULL	not found
	*/
	VALUE* operator[](const KEY Key){
		auto itr = lower_bound(_list.begin(), _list.end(), Pair(Key));
		return itr != _list.end()
			? &itr->second
			: NULL;
	}

	/**
		Adds an element to the end of the vector.
	*/
	void insert(const Pair& Val){
		_list.push_back(Val);
		std::sort(_list.begin(), _list.end());
	}

	/**
		Adds an element to the end of the vector.
	*/
	void insert(Pair&& Val){
		_list.push_back(Val);
		std::sort(_list.begin(), _list.end());
	}

	void erase(iterator Pos){
		_list.erase(Pos);
	}

	void clear(void){
		_list.clear();
	}

	iterator begin(void){ return _list.begin(); }
	const_iterator begin(void) const { return _list.begin(); }
	iterator end(void){ return _list.end(); }
	const_iterator end(void) const { return _list.end(); }
	reverse_iterator rbegin(void){ return _list.rbegin(); }
	const_reverse_iterator rbegin(void) const { return _list.rbegin(); }
	reverse_iterator rend(void){ return _list.rend(); }
	const_reverse_iterator rend(void) const { return _list.rend(); }

	bool empty(void) const { return _list.empty(); }
	size_type size(void) const { return _list.size(); }

private:
	InnerVector _list;
};

}

// EOF
