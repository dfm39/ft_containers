#include "test_utils.hpp"
#include <sys/time.h>

#ifndef STL
# define STL 0
#endif

#if STL
	#include <vector>
	#define NAMESPACE std
	#define prefix "std_"
#else
	#include "../vector.hpp"
	#define NAMESPACE ft
	#define prefix "ft_"
#endif

#define dir "./results/vector/"
#define T1 int
#define T2 std::string
#define vector_t typename NAMESPACE::vector<T>
#define vector_int NAMESPACE::vector<T1>
#define vector_str NAMESPACE::vector<T2>

static size_t iter;

template <typename T>
void	write_vec(vector_t vec, std::fstream &ostream)
{
	ostream << "----- vec" << iter++ << " -----" << "\n\n";
	ostream << "SIZE = " << vec.size() << "\n";

	ostream << "CONTENT =";
	for (vector_t::iterator it = vec.begin(); it != vec.end(); it++)
	{
		ostream << " " << *it;
	}
	ostream << "\n\n";
}

int	main()
{
	timeval	start;
	time_t	duration = 0;
	std::fstream	tstream, ostream;
	create_file(tstream, dir, prefix, "vec_time");
	create_file(ostream, dir, prefix, "vec_out");

	/*_________________________*/
	/*--- CONSTRUCTOR TESTS ---*/
	/*-------------------------*/
	{
		write_fname("CONSTRUCTOR", tstream, ostream);
		/* PERFORMANCE TEST */
		gettimeofday(&start, NULL);
		vector_int vec0(1000000);
		vector_int vec1(1000000, 12);
		vector_int vec2(vec1);
		vector_int vec3(vec2.begin(), vec2.end());

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec0;
		vector_int vec1(100, 96);
		vector_int vec2(vec1);
		vector_int vec3(vec2.begin(), vec2.end());

		write_vec(vec0, ostream);
		write_vec(vec1, ostream);
		write_vec(vec2, ostream);
		write_vec(vec3, ostream);
	}
	/*________________________*/
	/*--- ASSIGNMENT TESTS ---*/
	/*------------------------*/
	{
		write_fname("ASSIGNMENT", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec4;
		vector_int vec5(1000000, 96);
		vector_int vec6(1000000);
		gettimeofday(&start, NULL);
		vec6 = vec4;
		vec4 = vec5;
		vec5 = vec6;
		vec4 = vec6;
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec4;
		vector_int vec5(72, 1896);
		vector_int vec6(99);
		vector_int vec7;

		vec4.push_back(vec4.empty());
		vec4.push_back(vec4.size());
		vec4.push_back(vec5.size());
		vec4.push_back(vec6.size());

		vec6 = vec4;
		vec4 = vec5;
		vec5 = vec7;
		vec7 = vec4;

		write_vec(vec4, ostream);
		write_vec(vec5, ostream);
		write_vec(vec6, ostream);
		write_vec(vec7, ostream);
	}
	/*____________________*/
	/*--- ASSIGN TESTS ---*/
	/*--------------------*/
	{
		write_fname("ASSIGN", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec8;
		vector_int vec9;
		vector_int vec10(100000, 32);
		vector_int vec11;

		for (size_t i = 0; i < 1234578; i++)
			vec9.push_back(i * 3/2);
		gettimeofday(&start, NULL);
		vec11.assign(424242, 21);
		vec11.assign(vec8.begin(), vec8.end());
		vec11.assign(vec10.begin() + 11, vec10.end() - 99);
		vec11.assign(0, 0);
		vec11.assign(vec11.begin(), vec11.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec8;
		vector_int vec9;
		vector_int vec10(132, 32);
		vector_int vec11;

		for (size_t i = 0; i < 123; i++)
			vec9.push_back(i * 3/2);
		vec11.assign(42, 21);
		vec8.assign(vec10.begin() + 11, vec10.end() - 99);
		vec10.assign(vec9.begin(), vec9.end());
		vec9.assign(0, 0);

		write_vec(vec8, ostream);
		write_vec(vec9, ostream);
		write_vec(vec10, ostream);
		write_vec(vec11, ostream);
	}
	/*_________________________________________________*/
	/*--- AT, [] OVERLOAD, DATA, BACK & FRONT TESTS ---*/
	/*-------------------------------------------------*/
	{
		write_fname("AT, [] OVERLOAD, DATA, BACK & FRONT", \
			tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int tmp1;
		vector_int vec12;
		vector_int vec13;

		for (size_t i = 0; i < 12343; i++)
			tmp1.push_back(i * 3/2);
		gettimeofday(&start, NULL);
		vec12.push_back(tmp1.at(666));
		vec12.push_back(tmp1.at(0));
		vec12.push_back(tmp1.at(1896));
		vec12.push_back(tmp1.at(9696));
		vec13.push_back(tmp1[666]);
		vec13.push_back(tmp1[0]);
		vec13.push_back(tmp1[1896]);
		vec13.push_back(tmp1[9696]);
		vec13.push_back(*tmp1.data());
		vec13.push_back(tmp1.front());
		vec13.push_back(tmp1.back());

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int tmp1;
		vector_int vec12;
		vector_int vec13;
		
		for (size_t i = 0; i < 42; i++)
			tmp1.push_back(i * 3/2);
		vec13.push_back(tmp1.at(14));
		vec12.push_back(tmp1.at(0));
		vec12.push_back(tmp1.at(21));
		vec12.push_back(tmp1.at(24));
		write_vec(vec12, ostream);
		try
		{
			tmp1.at(42);
		}
		catch(const std::out_of_range & e)
		{
			ostream << "EXCEPTION: OUT OF RANGE" << "\n\n";
		}
		vec13.push_back(tmp1[14]);
		vec13.push_back(tmp1[0]);
		vec13.push_back(tmp1[21]);
		vec13.push_back(tmp1[24]);
		vec13.push_back(*tmp1.data());
		vec13.push_back(tmp1.front());
		vec13.push_back(tmp1.back());

		write_vec(vec13, ostream);
	}
	{
		write_fname("ITERATORS", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */
		vector_int vec14;
		vector_int tmp1;
		vector_int tmp2;
		tmp2.push_back(4221);
		tmp2.push_back(12);
		tmp2.push_back(-96);
		tmp2.push_back(1337);
		tmp2.push_back(0);

		vector_int::iterator				it;
		vector_int::const_iterator			cit;
		vector_int::reverse_iterator		rev;
		vector_int::const_reverse_iterator	crev;
		gettimeofday(&start, NULL);
		vec14.push_back((tmp1.begin() == tmp1.end()));
		for (it = tmp2.begin(); it != tmp2.end(); it++)
			vec14.push_back(*it);
		vec14.push_back((it == tmp2.end()));
		vec14.push_back(*(--it));

		for (cit = tmp2.begin(); cit != tmp2.end(); cit++)
			vec14.push_back(*cit);
		vec14.push_back((cit == tmp2.end()));
		vec14.push_back(*(--cit));

		vec14.push_back((tmp1.rbegin() == tmp1.rend()));
		for (rev = tmp2.rbegin(); rev != tmp2.rend(); rev++)
			vec14.push_back(*rev);
		vec14.push_back((rev == tmp2.rend()));
		vec14.push_back(*(--rev));

		for (crev = tmp2.rbegin(); crev != tmp2.rend(); crev++)
			vec14.push_back(*crev);
		vec14.push_back((crev == tmp2.rend()));
		vec14.push_back(*(--crev));
		duration = time_ms(start);
		write_vec(vec14, ostream);
		write_time(tstream, duration);
	}
	/*_____________________________________________________*/
	/*--- SIZE, EMPTY MAX_SIZE, CAPACITY, RESERVE TESTS ---*/
	/*-----------------------------------------------------*/
	{
		write_fname("SIZE, EMPTY, MAX_SIZE, CAPACITY, RESERVE", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */
		vector_int vec15;
		vector_int tmp1;
		vector_int tmp2(321);

		gettimeofday(&start, NULL);
		vec15.push_back(tmp1.size());
		vec15.push_back(tmp2.size());
		vec15.push_back(tmp1.empty());
		vec15.push_back(tmp2.empty());
		vec15.push_back(tmp1.max_size());
		vec15.push_back(tmp2.max_size());
		vec15.push_back(tmp1.capacity());
		vec15.push_back(tmp2.capacity());
		tmp1.reserve(96);
		vec15.push_back(tmp1.size());
		vec15.push_back(tmp1.capacity());
		tmp2.reserve(1);
		vec15.push_back(tmp2.size());
		vec15.push_back(tmp2.capacity());
		tmp2.reserve(323);
		vec15.push_back(tmp2.size());
		vec15.push_back(tmp2.capacity());

		duration = time_ms(start);
		write_vec(vec15, ostream);
		write_time(tstream, duration);
	}
	{
		write_fname("CLEAR", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */
		vector_int vec16;
		vector_int tmp1;
		vector_int tmp2;

		for (size_t i = 0; i < 3210123; i++)
			tmp2.push_back(i * 5 / 2);
		vec16.push_back(tmp1.size());
		vec16.push_back(tmp1.capacity());
		vec16.push_back(tmp2.size());
		vec16.push_back(tmp2.capacity());
		gettimeofday(&start, NULL);
		tmp1.clear();
		tmp2.clear();
		duration = time_ms(start);
		vec16.push_back(tmp1.size());
		vec16.push_back(tmp1.capacity());
		vec16.push_back(tmp2.size());
		vec16.push_back(tmp2.capacity());
		
		write_time(tstream, duration);
		write_vec(vec16, ostream);
	}
	/*___________________________________*/
	/*--- INSERT SINGLE ELEMENT TESTS ---*/
	/*-----------------------------------*/
	{
		write_fname("INSERT SINGLE ELEMENT", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec17;
		vector_str vec18;

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 1000; i++)
		{
			vec17.insert(vec17.begin(), i);
			vec18.insert(vec18.end(), "TEST");
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec17;
		vector_str vec18;
		vector_int::iterator int_it;
		vector_str::iterator str_it;

		for (size_t i = 0; i < 21; i++)
		{
			vec17.insert(vec17.begin(), (i * 3 / 2));
			vec18.insert(vec18.begin(), "FUN");
		}
		vec17.insert(vec17.end(), 9696);
		vec18.insert(vec18.begin(), "INSERTED");

		int_it = vec17.insert(vec17.end() - 8, 12345);
		str_it = vec18.insert(vec18.begin() + 4, "HELLO");
		
		vec17.insert(vec17.begin(), *int_it);
		vec18.insert(vec18.begin(), *str_it);

		write_vec(vec17, ostream);
		write_vec(vec18, ostream);
	}
	/*_________________________*/
	/*--- INSERT FILL TESTS ---*/
	/*-------------------------*/
	{
		write_fname("INSERT FILL", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec19;
		vector_str vec20;

		gettimeofday(&start, NULL);
		vec19.insert(vec19.begin(), 1234567, 1896);
		vec20.insert(vec20.end(), 1765432, "TIK TOK");
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec19;
		vector_str vec20;

		vec19.insert(vec19.begin(), 12, 96);
		vec20.insert(vec20.begin(), 10, "TOK");
		vec19.insert(vec19.begin() + 7, 6, 1896);
		vec20.insert(vec20.begin() + 2, 5, "TIKI");

		write_vec(vec19, ostream);
		write_vec(vec20, ostream);
	}
	/*__________________________*/
	/*--- INSERT RANGE TESTS ---*/
	/*--------------------------*/
	{
		write_fname("INSERT RANGE", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int tmp1;
		vector_str tmp2;
		vector_int vec21;
		vector_str vec22;

		for (size_t i = 0; i < 100000; i++)
		{
			tmp1.push_back(i);
			tmp2.push_back("RANGE");
		}
		gettimeofday(&start, NULL);
		vec21.insert(vec21.begin(), tmp1.begin(), tmp1.end());
		vec21.insert(vec21.begin(), tmp1.begin() + 20, tmp1.end() - 20);
		vec22.insert(vec22.end(), tmp2.begin(), tmp2.end());
		vec22.insert(vec22.end(), tmp2.begin() + 96, tmp2.end() - 96);
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int tmp1;
		vector_str tmp2;
		vector_int vec21;
		vector_str vec22;

		for (size_t i = 0; i < 17; i++)
		{
			tmp1.push_back(i * 5);
			tmp2.push_back("INSERT");
		}
		tmp2.push_back("LAST");
		tmp1.push_back(9966);
		vec21.insert(vec21.begin(), tmp1.begin() + 1, tmp1.end() - 2);
		vec21.insert(vec21.begin(), tmp1.begin(), tmp1.begin());
		vec21.insert(vec21.end(), tmp1.end() - 1, tmp1.end() - 1);
		vec22.insert(vec22.begin(), tmp2.begin() + 1, tmp2.end() - 2);
		vec22.insert(vec22.begin(), tmp2.begin(), tmp2.begin());
		vec22.insert(vec22.end(), tmp2.end() - 1, tmp2.end() - 1);
		write_vec(vec21, ostream);
		write_vec(vec22, ostream);
	}
	/*__________________________________*/
	/*--- ERASE SINGLE ELEMENT TESTS ---*/
	/*----------------------------------*/
	{
		write_fname("ERASE SINGLE ELEMENT", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec23;
		vector_str vec24;
		for (size_t i = 0; i < 5123; i++)
		{
			vec23.push_back(i);
			vec24.push_back("ERASE ME");
		}
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 5123; i++)
		{
			vec23.erase(vec23.begin());
			vec24.erase(vec24.begin());
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int tmp1;
		vector_str tmp2;
		vector_int vec23;
		vector_str vec24;

		vector_int::iterator int_it;
		vector_str::iterator str_it;

		for (size_t i = 0; i < 21; i++)
		{
			tmp1.push_back(i);
			tmp2.push_back("ERASE TEST");
		}

		vec23.push_back(tmp1.size());
		vec23.push_back(tmp2.size());

		for (size_t i = 0; i < 21; i++)
		{
			tmp1.erase(tmp1.begin());
			tmp2.erase(tmp2.begin());
		}

		vec23.push_back(tmp1.size());
		vec23.push_back(tmp2.size());

		vec23.push_back(21);
		vec24.push_back("ERASE");
		
		vec23.push_back(42);
		vec24.push_back("DONT ERASE");

		int_it = vec23.erase(vec23.end() - 2);
		str_it = vec24.erase(vec24.end() - 2);

		vec23.push_back(*int_it);
		vec24.push_back(*str_it);

		write_vec(vec23, ostream);
		write_vec(vec24, ostream);
	}
	/*_________________________*/
	/*--- ERASE RANGE TESTS ---*/
	/*-------------------------*/
	{
		write_fname("ERASE RANGE", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec25;
		vector_str vec26;

		for (size_t i = 0; i < 923457; i++)
		{
			vec25.push_back(i);
			vec26.push_back("ERASE ME");
		}
		gettimeofday(&start, NULL);
		vec25.erase(vec25.begin(), vec25.end());
		vec26.erase(vec26.begin(), vec26.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int tmp1;
		vector_str tmp2;
		vector_int vec25;
		vector_str vec26;

		vector_int::iterator int_it;
		vector_str::iterator str_it;

		for (size_t i = 0; i < 21; i++)
		{
			tmp1.push_back(i);
			tmp2.push_back("ERASE TEST");
		}

		vec25.push_back(tmp1.size());
		vec25.push_back(tmp2.size());

		tmp1.erase(tmp1.begin(), tmp1.end());
		tmp2.erase(tmp2.begin(), tmp2.end());

		vec25.push_back(tmp1.size());
		vec25.push_back(tmp2.size());

		vec25.push_back(42);
		vec26.push_back("DONT ERASE");

		for (size_t i = 0; i < 21; i++)
		{
			vec25.push_back(i);
			vec26.push_back("ERASE");
		}

		vec25.push_back(42);
		vec26.push_back("DONT ERASE");

		int_it = vec25.erase(vec25.begin() + 5, vec25.end() - 1);
		str_it = vec26.erase(vec26.begin() + 1, vec26.end() - 1);

		vec25.push_back(*int_it);
		vec26.push_back(*str_it);

		write_vec(vec25, ostream);
		write_vec(vec26, ostream);
	}
	/*______________________*/
	/*--- POP BACK TESTS ---*/
	/*----------------------*/
	{
		write_fname("POP BACK", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec27;

		for (size_t i = 0; i < 100000; i++)
			vec27.push_back(i * 3 / 2);
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 100000; i++)
			vec27.pop_back();
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec27;

		for (size_t i = 0; i < 15; i++)
			vec27.push_back(i);
		vec27.pop_back();
		vec27.pop_back();
		vec27.pop_back();
		vec27.insert(vec27.end() - 2, 99);
		vec27.pop_back();
		write_vec(vec27, ostream);
	}
	/*____________________*/
	/*--- RESIZE TESTS ---*/
	/*--------------------*/
	{
		write_fname("RESIZE", tstream, ostream);
		/* PERFORMANCE TEST */

		vector_int vec28;
		vector_int tmp1;


		for (int i = 0; i < 1234; i++) 
			tmp1.push_back(i);
		gettimeofday(&start, NULL);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());
		tmp1.resize(42);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());
		tmp1.resize(2342);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());
		tmp1.resize(0);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());
		tmp1.resize(122335);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());;
		tmp1.resize(1114);
		vec28.push_back(tmp1.size());
		vec28.push_back(tmp1.capacity());
		write_time(tstream, duration);
		write_vec(vec28, ostream);
	}
	// /*__________________*/
	// /*--- SWAP TESTS ---*/
	// /*------------------*/
	{
		write_fname("SWAP", tstream, ostream);
		/* PERFORMANCE TEST */
		vector_int vec29;
		vector_int vec30;

		for (size_t i = 0; i < 31241; i++)
		{ 
			vec29.push_back(i);
			vec30.push_back(-i);
		}
		gettimeofday(&start, NULL);
		vec29.swap(vec30);
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		vector_int vec29;
		vector_int vec30;

		for (size_t i = 0; i < 16; i++)
		{ 
			vec29.push_back(i);
			vec30.push_back(-i);
		}
		vec29.swap(vec30);
		write_vec(vec29, ostream);
		write_vec(vec30, ostream);
	}
	/*__________________________________*/
	/*--- RELATIONAL OPERATORS TESTS ---*/
	/*----------------------------------*/
	{
		write_fname("RELATIONAL OPERATORS", tstream, ostream);

		/* PERFORMANCE & FUNCTIONAL TEST */
		vector_int	vec31;
		vector_int	tmp1;
		vector_int	tmp2;

		for (size_t i = 0; i < 10000; i++)
		{ 
			tmp1.push_back(i);
			tmp2.push_back(i);
		}

		gettimeofday(&start, NULL);
		vec31.push_back(tmp1 == tmp2);
		vec31.push_back(tmp1 != tmp2);
		vec31.push_back(tmp1 < tmp2);
		vec31.push_back(tmp1 <= tmp2);
		vec31.push_back(tmp1 > tmp2);
		vec31.push_back(tmp1 >= tmp2);
		tmp1.push_back(1);
		vec31.push_back(tmp1 == tmp2);
		vec31.push_back(tmp1 != tmp2);
		vec31.push_back(tmp1 < tmp2);
		vec31.push_back(tmp1 <= tmp2);
		vec31.push_back(tmp1 > tmp2);
		vec31.push_back(tmp1 >= tmp2);
		tmp2.push_back(1);
		vec31.push_back(tmp1 == tmp2);
		vec31.push_back(tmp1 != tmp2);
		vec31.push_back(tmp1 < tmp2);
		vec31.push_back(tmp1 <= tmp2);
		vec31.push_back(tmp1 > tmp2);
		vec31.push_back(tmp1 >= tmp2);
		tmp1.push_back(5);
		vec31.push_back(tmp1 == tmp2);
		vec31.push_back(tmp1 != tmp2);
		vec31.push_back(tmp1 < tmp2);
		vec31.push_back(tmp1 <= tmp2);
		vec31.push_back(tmp1 > tmp2);
		vec31.push_back(tmp1 >= tmp2);
		tmp2.erase(tmp1.end() - 2);
		vec31.push_back(tmp1 == tmp2);
		vec31.push_back(tmp1 != tmp2);
		vec31.push_back(tmp1 < tmp2);
		vec31.push_back(tmp1 <= tmp2);
		vec31.push_back(tmp1 > tmp2);
		vec31.push_back(tmp1 >= tmp2);
		duration = time_ms(start);
		
		write_time(tstream, duration);
		write_vec(vec31, ostream);
	}
	return 0;
}