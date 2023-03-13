#ifndef UTILS_H
# define UTILS_H

namespace ft
{
	template <class InputIt1, class InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while(first1 != last1)
		{
			if (*first1++ != *first2++)
				return false;
		}
		return true;
	}
	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		while(first1 != last1)
		{
			if (!p(*first1++, *first2++))
				return false;
		}
		return true;
	}
	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while(first1 != last1 && first2 != last2)
		{
			if(*first1 < *first2)
				return true;
			if(*first2++ < *first1++)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	template <class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		while(first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2++, *first1++))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <bool B, class T = void>
	struct	enable_if
	{};

	template <class T>
	struct	enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant
	{
		static const	T value 								= v;
		typedef			T										value_type;
		typedef			integral_constant<value_type, value>	type;
		operator		value_type()
		{
			return this->value;
		}
	};

	typedef	integral_constant<bool, true> true_type;
	typedef	integral_constant<bool, false> false_type;

	template <class T> struct is_integral : public false_type {};

	template <>		struct is_integral<bool> : public true_type {};
	template <>		struct is_integral<char> : public true_type {};
	template <>		struct is_integral<signed char> : public true_type {};
	template <>		struct is_integral<short int> : public true_type {};
	template <>		struct is_integral<int> : public true_type {};
	template <>		struct is_integral<long int> : public true_type {};
	template <>		struct is_integral<unsigned char> : public true_type {};
	template <>		struct is_integral<unsigned short int> : public true_type {};
	template <>		struct is_integral<unsigned int> : public true_type {};
	template <>		struct is_integral<unsigned long int> : public true_type {};
	template <>		struct is_integral<const bool> : public true_type {};
	template <>		struct is_integral<const char> : public true_type {};
	template <>		struct is_integral<const signed char> : public true_type {};
	template <>		struct is_integral<const short int> : public true_type {};
	template <>		struct is_integral<const int> : public true_type {};
	template <>		struct is_integral<const long int> : public true_type {};
	template <>		struct is_integral<const unsigned char> : public true_type {};
	template <>		struct is_integral<const unsigned short int> : public true_type {};
	template <>		struct is_integral<const unsigned int> : public true_type {};
	template <>		struct is_integral<const unsigned long int> : public true_type {};
	template <>		struct is_integral<volatile bool> : public true_type {};
	template <>		struct is_integral<volatile char> : public true_type {};
	template <>		struct is_integral<volatile signed char> : public true_type {};
	template <>		struct is_integral<volatile short int> : public true_type {};
	template <>		struct is_integral<volatile int> : public true_type {};
	template <>		struct is_integral<volatile long int> : public true_type {};
	template <>		struct is_integral<volatile unsigned char> : public true_type {};
	template <>		struct is_integral<volatile unsigned short int> : public true_type {};
	template <>		struct is_integral<volatile unsigned int> : public true_type {};
	template <>		struct is_integral<volatile unsigned long int> : public true_type {};
	template <>		struct is_integral<const volatile bool> : public true_type {};
	template <>		struct is_integral<const volatile char> : public true_type {};
	template <>		struct is_integral<const volatile signed char> : public true_type {};
	template <>		struct is_integral<const volatile short int> : public true_type {};
	template <>		struct is_integral<const volatile int> : public true_type {};
	template <>		struct is_integral<const volatile long int> : public true_type {};
	template <>		struct is_integral<const volatile unsigned char> : public true_type {};
	template <>		struct is_integral<const volatile unsigned short int> : public true_type {};
	template <>		struct is_integral<const volatile unsigned int> : public true_type {};
	template <>		struct is_integral<const volatile unsigned long int> : public true_type {};

	/* C++ 11 TYPES */
	// template <>		struct is_integral<wchar_t> : public true_type {};
	// template <>		struct is_integral<char16_t> : public true_type {};		//c++11 Std
	// template <>		struct is_integral<char32_t> : public true_type {};		//c++11 Std
	// template <>		struct is_integral<long long int> : public true_type {};
	// template <>		struct is_integral<unsigned long long int> : public true_type {};
	// template <>		struct is_integral<const long long int> : public true_type {};
	// template <>		struct is_integral<const unsigned long long int> : public true_type {};
	// template <>		struct is_integral<volatile long long int> : public true_type {};
	// template <>		struct is_integral<const volatile long long int> : public true_type {};

	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;

		pair() : first(), second() {}

		pair (const first_type & a, const second_type & b) : first(a), second(b)
		{}

		template <class X, class Y>
		pair(const pair<X, Y>& other) : first(other.first), second(other.second)
		{}

		pair &	operator=(const pair & pr)
		{
		this->~pair();
		new (this) pair(pr.first, pr.second);
		return *this;
		}
	};

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return pair<T1,T2>(x,y);
	}

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
		
	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return !(lhs == rhs);
	}
		
	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}
		
	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return !(rhs < lhs);
	}
		
	template <class T1, class T2>
	bool operator>(const pair < T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return rhs < lhs;
	}
		
	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
