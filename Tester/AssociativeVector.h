/**
	@file AssociativeVector.h
*/

#pragma once

#include <utility>
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
	typedef std::pair<KEY, VALUE> Pair;

	struct PairComp {
		bool operator()(const Pair& lhs, const Pair& rhs) const {
			return lhs.first < rhs.first;
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
	{}

	template <class InputIterator>
	AssociativeVector(InputIterator First, InputIterator Last):
		_list(First, Last)
	{
		std::sort(_list.begin(), _list.end(), PairComp());
	}
	
	template<size_t SIZE>
	AssociativeVector(const Pair (&array)[SIZE]):
		_list(array, array + SIZE)
	{
		std::sort(_list.begin(), _list.end(), PairComp());
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
		auto itr = lower_bound(_list.begin(), _list.end(), Pair(Key, VALUE()), PairComp());
//		auto itr = std::find(_list.begin(), _list.end(), Pair(Key, VALUE()));
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
		auto itr = lower_bound(_list.begin(), _list.end(), Pair(Key, VALUE()), PairComp());
//		auto itr = std::find(_list.begin(), _list.end(), Pair(Key, VALUE()));
		return itr != _list.end()
			? &itr->second
			: NULL;
	}

	/**
		Adds an element to the end of the vector.
	*/
	void insert(const Pair& Val){
//		_list.push_back(Val);
//		std::sort(_list.begin(), _list.end());
		auto itr = lower_bound(_list.begin(), _list.end(), Val, PairComp());
		_list.insert(itr, Val);
	}

	/**
		Adds an element to the end of the vector.
	*/
	void insert(Pair&& Val){
//		_list.push_back(Val);
//		std::sort(_list.begin(), _list.end());
		auto itr = lower_bound(_list.begin(), _list.end(), Val, PairComp());
		_list.insert(itr, Val);
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
