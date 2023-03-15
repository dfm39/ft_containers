#include "test_utils.hpp"
#include <sys/time.h>
#include <vector>

#ifndef STL
# define STL 0
#endif

#if STL
	#include <set>
	#define NAMESPACE std
	#define prefix "std_"
#else
	#include "set.hpp"
	#define NAMESPACE ft
	#define prefix "ft_"
#endif

#define dir "./results/set/"

#define T1 int
#define T2 std::string
#define pair NAMESPACE::pair
#define make_pair NAMESPACE::make_pair
#define set_t typename NAMESPACE::set<T>
#define set_int NAMESPACE::set<T1>
#define set_str NAMESPACE::set<T2>

#define ret_vec_int std::vector<T1>
#define ret_vec_str std::vector<T2>

static size_t iter;

template <typename T>
void	write_set(set_t set, std::fstream &ostream)
{
	ostream << "----- set" << iter++ << " -----" << "\n\n";
	ostream << "SIZE = " << set.size() << "\n";

	ostream << "\nCONTENT =";
	for (set_t::iterator it = set.begin(); it != set.end(); it++)
		ostream << " " << *it;
	ostream << "\n\n";
}

int	main()
{
	timeval	start;
	time_t	duration = 0;
	std::fstream	tstream, ostream;
	create_file(tstream, dir, prefix, "set_time");
	create_file(ostream, dir, prefix, "set_out");

	/*_________________________*/
	/*--- CONSTRUCTOR TESTS ---*/
	/*-------------------------*/
	{
		write_fname("CONSTRUCTOR", tstream, ostream);
		/* PERFORMANCE TEST */
		set_int tmp1;

		for (size_t i = 0; i < 40000; i++)
			tmp1.insert(i);
		gettimeofday(&start, NULL);
		set_int set0(tmp1.begin(), tmp1.end());
		set_int set1(set0);
		set_int set2;

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		set_int tmp1;

		for (size_t i = 0; i < 12; i++)
			tmp1.insert(i * 3);
		set_int set0(tmp1.begin(), tmp1.end());
		set_int set1(set0);
		set_int set2;

		write_set(set0, ostream);
		write_set(set1, ostream);
		write_set(set2, ostream);
	}
	/*________________________*/
	/*--- ASSIGNMENT TESTS ---*/
	/*------------------------*/
	{
		write_fname("ASSIGNMENT", tstream, ostream);
		/* PERFORMANCE TEST */
		set_int tmp1;
		set_str tmp2;

		set_int set3;
		set_str set4;
		set_int set5;
		set_str set6;

		for (size_t i = 0; i < 40000; i++)
		{
			set3.insert(i + 1);
			set4.insert("TEST");
		}
		gettimeofday(&start, NULL);
		
		set5 = set3;
		set6 = set4;
		set3 = tmp1;
		set4 = tmp2;

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTONAL TEST */
		set_int tmp1;
		set_str tmp2;

		set_int set3;
		set_str set4;
		set_int set5;
		set_str set6;

		for (size_t i = 0; i < 32; i++)
		{
			set3.insert(i + 1);
			set4.insert("CTOR");
		}

		set5 = set3;
		set6 = set4;
		set3 = tmp1;
		set4 = tmp2;

		write_set(set3, ostream);
		write_set(set4, ostream);
		write_set(set5, ostream);
		write_set(set6, ostream);
	}
	/*_______________________*/
	/*--- ITERATOR TESTS ---*/
	/*-----------------------*/
	{
		write_fname("ITERATORS", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		set_int set7;
		set_int::iterator it;
		set_int::const_iterator cit;
		set_int::reverse_iterator rev;
		set_int::const_reverse_iterator crev;

		ret_vec_int	ret;

		for (size_t i = 0; i < 7; i++)
			set7.insert(i * 3 / 5);
		gettimeofday(&start, NULL);
		it = set7.begin();
		cit = set7.begin();
		rev = set7.rbegin();
		crev = set7.rbegin();
		ret.push_back(it == cit);
		for(; it != set7.end() && cit != set7.end(); it++, cit++)
		{
			ret.push_back(*it);
			ret.push_back(*it);
			ret.push_back(*cit);
			ret.push_back(*cit);
		}
		ret.push_back(it == set7.end());
		ret.push_back(cit == set7.end());
		it--, cit--;
		ret.push_back(it == set7.end());
		ret.push_back(cit == set7.end());
		for(; it != set7.begin() && cit != set7.begin(); it--, cit--)
		{
			ret.push_back(*it);
			ret.push_back(*it);
			ret.push_back(*cit);
			ret.push_back(*cit);
		}
		ret.push_back(it == set7.end());
		ret.push_back(cit == set7.end());
		it++;
		ret.push_back(cit == set7.end());
		cit = it;
		ret.push_back(cit == set7.end());

		/* REVERSE */
		ret.push_back(rev == crev);
		for(; rev != set7.rend() && crev != set7.rend(); rev++, crev++)
		{
			ret.push_back(*rev);
			ret.push_back(*rev);
			ret.push_back(*crev);
			ret.push_back(*crev);
		}
		ret.push_back(rev == set7.rend());
		ret.push_back(crev == set7.rend());
		rev--, crev--;
		ret.push_back(rev == set7.rend());
		ret.push_back(crev == set7.rend());
		for(; rev != set7.rbegin() && crev != set7.rbegin(); rev--, crev--)
		{
			ret.push_back(*rev);
			ret.push_back(*rev);
			ret.push_back(*crev);
			ret.push_back(*crev);
		}
		rev++;
		ret.push_back(cit == set7.end());
		crev = rev;
		ret.push_back(cit == set7.end());
		duration = time_ms(start);
		write_time(tstream, duration);
		write_set(set7, ostream);
		write_std_vec(ret, ostream);
	}
	/*__________________________*/
	/*--- EMPTY & SIZE TESTS ---*/
	/*--------------------------*/
	{
		write_fname("EMPTY & SIZE", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		set_int	tmp1;
		set_int	tmp2;

		ret_vec_int	ret;

		for (size_t i = 0; i < 91543; i++)
			tmp1.insert(i * 3);
		gettimeofday(&start, NULL);
		
		ret.push_back(tmp1.empty());
		ret.push_back(tmp1.size());
		ret.push_back(tmp2.empty());
		ret.push_back(tmp2.size());

		duration = time_ms(start);
		write_time(tstream, duration);
		write_std_vec(ret, ostream);
	}
	/*___________________*/
	/*--- CLEAR TESTS ---*/
	/*-------------------*/

	{
		write_fname("CLEAR", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		set_int	set8;
		set_int	set9;

		ret_vec_int ret;

		for (size_t i = 0; i < 91543; i++)
			set8.insert(i * 3);
		ret.push_back(set8.empty());
		ret.push_back(set9.empty());
		gettimeofday(&start, NULL);
		set8.clear();
		set9.clear();
		duration = time_ms(start);
		
		ret.push_back(set8.empty());
		ret.push_back(set9.empty());
		write_time(tstream, duration);
		write_set(set8, ostream);
		write_set(set9, ostream);
		write_std_vec(ret, ostream);
	}
	/*___________________________*/
	/*--- SINGLE INSERT TESTS ---*/
	/*---------------------------*/
	{
		write_fname("SINGLE INSERT", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set10;
		set_str	set11;

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			set10.insert(i * 3);
			set11.insert("TEST");
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		set_int	set10;
		set_str	set11;

		ret_vec_int ret_int;
		ret_vec_str ret_str;

		pair<set_int::iterator, bool> tpair1;
		pair<set_str::iterator, bool> tpair2;

		for (size_t i = 0; i < 6; i++)
		{
			set10.insert(i * 19);
			set11.insert("TEST STUFF");
		}

		tpair1 = set10.insert(1896);
		/* PUSHES CONTENT OF KEY 13 TO RET_INT */
		ret_int.push_back(*tpair1.first);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair1.second);

		tpair2 = set11.insert("INSERTED");
		/* PUSHES CONTENT OF KEY 8 TO RET_STR */
		ret_str.push_back(*tpair2.first);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair2.second);

		tpair1 = set10.insert(1542);
		/* PUSHES CONTENT OF EXISTING KEY 13 TO RET_INT */
		ret_int.push_back(*tpair1.first);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair1.second);

		tpair2 = set11.insert("ME NO INSERT");
		/* PUSHES CONTENT OF EXISTING KEY 8 TO RET_STR */
		ret_str.push_back(*tpair2.first);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair2.second);

		write_set(set10, ostream);
		write_set(set11, ostream);
		write_std_vec(ret_int, ostream);
		write_std_vec(ret_str, ostream);
	}
	/*_________________________________________*/
	/*--- SINGLE INSERT WITH POSITION TESTS ---*/
	/*-----------------------------------------*/
	{
		write_fname("SINGLE INSERT WITH POSITION", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set12;
		set_str	set13;

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			set12.insert(set12.begin(), i * 3);
			set13.insert(set13.begin(), "TEST");
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set12;
		set_str	set13;

		ret_vec_int ret_int;
		ret_vec_str ret_str;

		for (size_t i = 0; i < 14; i++)
		{
			set12.insert(set12.begin(), i + 21);
			set13.insert(set13.begin(), "HOWDY");
		}

		ret_int.push_back \
			(*set12.insert(set12.begin(), 1896));

		ret_int.push_back \
			(*set12.insert(set12.begin(),  666666));

		ret_str.push_back \
			(*set13.insert(set13.begin(), "INSERT ME"));

		ret_str.push_back \
			(*set13.insert(set13.begin(), "ME NO INSERT"));

		write_set(set12, ostream);
		write_std_vec(ret_int, ostream);
		write_set(set13, ostream);
		write_std_vec(ret_str, ostream);
	}
	/*__________________________*/
	/*--- RANGE INSERT TESTS ---*/
	/*--------------------------*/
	{
		write_fname("RANGE INSERT", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set14;
		set_str	set15;

		set_int	tmp1;
		set_str	tmp2;

		for (size_t i = 0; i < 53143; i++)
		{
			tmp1.insert(i * 3);
			tmp2.insert("TEST");
		}
		gettimeofday(&start, NULL);
		set14.insert(tmp1.begin(), tmp1.end());
		set15.insert(tmp2.begin(), tmp2.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set14;
		set_str	set15;

		set_int	tmp1;
		set_str	tmp2;

		for (size_t i = 0; i < 14; i++)
		{
			tmp1.insert(i * 3);
			tmp2.insert("INSERTED");
		}
		set14.insert(tmp1.begin(), tmp1.end());
		set15.insert(tmp2.begin(), tmp2.end());

		write_set(set14, ostream);
		write_set(set15, ostream);
	}
	/*_______________________________*/
	/*--- ERASE ON POSITION TESTS ---*/
	/*-------------------------------*/
	{
		write_fname("ERASE ON POSITION", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set16;
		set_int	set17;

		for (size_t i = 0; i < 53143; i++)
		{
			set16.insert(i * 3);
			set17.insert(i * 5 + 3);
		}
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			set16.erase(set16.begin());
			set17.erase(set17.begin());
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set16;
		set_int	set17;

		ret_vec_int	ret;

		for (size_t i = 0; i < 4; i++)
		{
			set16.insert(i * 3);
			set17.insert(i * 5 + 3);
		}
		set16.erase(set16.begin());
		set17.erase(set17.begin());
		ret.push_back(set16.size());
		ret.push_back(set17.size());
		ret.push_back(set16.empty());
		ret.push_back(set17.empty());
		set16.erase(set16.begin());
		set17.erase(set17.begin());
		ret.push_back(set16.size());
		ret.push_back(set17.size());
		ret.push_back(set16.empty());
		ret.push_back(set17.empty());

		write_set(set16, ostream);

		set17.erase(set17.begin());
		ret.push_back(set17.size());
		ret.push_back(set17.empty());
		set17.erase(set17.begin());
		ret.push_back(set17.size());
		ret.push_back(set17.empty());

		write_set(set17, ostream);
		write_std_vec(ret, ostream);
	}
	/*_______________________*/
	/*--- ERASE KEY TESTS ---*/
	/*-----------------------*/
	{
		write_fname("ERASE KEY", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set18;
		set_int	set19;

		for (size_t i = 0; i < 32411; i++)
		{
			set18.insert(i * 3);
			set19.insert(i * 5 + 7);
		}
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 32411; i++)
		{
			set18.erase(i * 3);
			set19.erase(i * 5 + 7);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set18;
		set_int	set19;

		ret_vec_int	ret;

		for (size_t i = 0; i < 6; i++)
		{
			set18.insert(i * 2);
			set19.insert(i);
		}

		ret.push_back(set18.erase(16));
		ret.push_back(set19.erase(14));
		ret.push_back(set18.erase(12));
		ret.push_back(set19.erase(4));

		write_set(set18, ostream);
		write_set(set19, ostream);
		write_std_vec(ret, ostream);
	}
	/*_________________________*/
	/*--- ERASE RANGE TESTS ---*/
	/*-------------------------*/
	{
		write_fname("ERASE RANGE", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set20;

		for (size_t i = 0; i < 32411; i++)
			set20.insert(i);
		gettimeofday(&start, NULL);
		set20.erase(set20.begin(), set20.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set20;

		for (size_t i = 0; i < 13; i++)
			set20.insert(i);

		set20.insert(54321);
		set20.erase(set20.begin(), --set20.end());

		write_set(set20, ostream);
	}
	/*__________________*/
	/*--- SWAP TESTS ---*/
	/*------------------*/
	{
		write_fname("SWAP", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set21;
		set_int	set25;

		for (size_t i = 0; i < 32411; i++)
		{
			set21.insert(i);
			set25.insert(i + 12);
		}
		gettimeofday(&start, NULL);
		set21.swap(set25);
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set21;
		set_int	set22;

		for (size_t i = 0; i < 16; i++)
		{
			set21.insert(i);
			set22.insert(-i);
		}
		set21.swap(set22);

		write_set(set21, ostream);
		write_set(set22, ostream);
	}
	/*__________________________*/
	/*--- COUNT & FIND TESTS ---*/
	/*--------------------------*/
	{
		write_fname("COUNT & FIND", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set23;

		for (size_t i = 0; i < 12414; i++)
			set23.insert(i);

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 12414; i++)
		{
			set23.count(i);
			set23.find(i);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set23;

		ret_vec_int	ret;

		bool tmp;

		for (size_t i = 0; i < 12; i++)
			set23.insert(i);

		tmp = set23.count(1);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(*set23.find(1));

		tmp = set23.count(6);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(*set23.find(6));

		tmp = set23.count(11);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(*set23.find(11));

		tmp = set23.count(12);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(*set23.find(12));

		ret.push_back(set23.find(12) == set23.end());

		write_set(set23, ostream);
		write_std_vec(ret, ostream);
	}
	/*____________________________________________________*/
	/*--- EQUAL RANGE, LOWER BOUND & UPPER BOUND TESTS ---*/
	/*----------------------------------------------------*/
	{
		write_fname("EQUAL RANGE, LOWER BOUND & UPPER BOUND", tstream, ostream);
		/* PERFORMANCE TEST */

		set_int	set24;

		for (size_t i = 1; i < 12414; i++)
			set24.insert(i);

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 12415; i++)
		{
			set24.equal_range(i);
			set24.lower_bound(i);
			set24.upper_bound(i);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		set_int	set24;

		ret_vec_int	ret;

		pair<set_int::iterator, set_int::iterator> tpair;

		for (size_t i = 1; i < 7; i++)
			set24.insert(i);

		set24.insert(9999);
		for (size_t i = 1; i < 10; i++)
		{
			tpair = set24.equal_range(i);
			ret.push_back(*tpair.first);
			if (tpair.second != set24.end())
				ret.push_back(*tpair.second);
			ret.push_back(*set24.lower_bound(i));
			if (set24.upper_bound(i) != set24.end())
				ret.push_back(*set24.upper_bound(i));
		}

		write_set(set24, ostream);
		write_std_vec(ret, ostream);
	}
	/*__________________________________*/
	/*--- RELATIONAL OPERATORS TESTS ---*/
	/*----------------------------------*/
	{
		write_fname("RELATIONAL OPERATORS", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		set_int	tmp1;
		set_int	tmp2;

		ret_vec_int	ret;

		gettimeofday(&start, NULL);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp1.insert(6);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(36);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(6);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(3);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		duration = time_ms(start);
		write_time(tstream, duration);

		write_std_vec(ret, ostream);
	}
	return 0;
}
