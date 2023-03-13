#include "test_utils.hpp"
#include <sys/time.h>
#include <vector>

#ifndef STL
# define STL 0
#endif

#if STL
	#include <map>
	#define NAMESPACE std
	#define prefix "std_"
#else
	#include "../map.hpp"
	#define NAMESPACE ft
	#define prefix "ft_"
#endif

#define dir "./results/map/"

#define T1 int
#define T2 std::string
#define pair NAMESPACE::pair
#define make_pair NAMESPACE::make_pair
#define map_t typename NAMESPACE::map<T, U>
#define map_ii NAMESPACE::map<T1, T1>
#define map_is NAMESPACE::map<T1, T2>

#define ret_vec_int std::vector<T1>
#define ret_vec_str std::vector<T2>

static size_t iter;

template <typename T, typename U>
void	write_map(map_t map, std::fstream &ostream)
{
	ostream << "----- map" << iter++ << " -----" << "\n\n";
	ostream << "SIZE = " << map.size() << "\n";

	ostream << "KEYS =";
	for (map_t::iterator it = map.begin(); it != map.end(); it++)
	{
		ostream << " " << it->first;
	}
	ostream << "\nCONTENT =";
	for (map_t::iterator it = map.begin(); it != map.end(); it++)
	{
		ostream << " " << it->second;
	}
	ostream << "\n\n";
}

int	main()
{
	timeval	start;
	time_t	duration = 0;
	std::fstream	tstream, ostream;
	create_file(tstream, dir, prefix, "map_time");
	create_file(ostream, dir, prefix, "map_out");

	/*_________________________*/
	/*--- CONSTRUCTOR TESTS ---*/
	/*-------------------------*/
	{
		write_fname("CONSTRUCTOR", tstream, ostream);
		/* PERFORMANCE TEST */
		map_ii tmp1;

		for (size_t i = 0; i < 40000; i++)
			tmp1.insert(make_pair(i, i));
		gettimeofday(&start, NULL);
		map_ii map0(tmp1.begin(), tmp1.end());
		map_ii map1(map0);
		map_ii map2;

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		map_ii tmp1;
		for (size_t i = 0; i < 12; i++)
			tmp1.insert(make_pair(i, i * 3 / 2));
		gettimeofday(&start, NULL);
		map_ii map0(tmp1.begin(), tmp1.end());
		map_ii map1(map0);
		map_ii map2;

		write_map(map0, ostream);
		write_map(map1, ostream);
		write_map(map2, ostream);
	}
	/*________________________*/
	/*--- ASSIGNMENT TESTS ---*/
	/*------------------------*/
	{
		write_fname("ASSIGNMENT", tstream, ostream);
		/* PERFORMANCE TEST */
		map_ii tmp1;
		map_is tmp2;

		map_ii map3;
		map_is map4;
		map_ii map5;
		map_is map6;

		for (size_t i = 0; i < 40000; i++)
		{
			map3.insert(make_pair(i, i + 1));
			map4.insert(make_pair(i, "TEST"));
		}
		gettimeofday(&start, NULL);
		
		map5 = map3;
		map6 = map4;
		map3 = tmp1;
		map4 = tmp2;

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTONAL TEST */
		map_ii tmp1;
		map_is tmp2;

		map_ii map3;
		map_is map4;
		map_ii map5;
		map_is map6;

		for (size_t i = 0; i < 32; i++)
		{
			map3.insert(make_pair(i + 17, i + 1));
			map4.insert(make_pair(i, "CTOR"));
		}

		map5 = map3;
		map6 = map4;
		map3 = tmp1;
		map4 = tmp2;

		write_map(map3, ostream);
		write_map(map4, ostream);
		write_map(map5, ostream);
		write_map(map6, ostream);
	}
	/*______________________________*/
	/*--- AT & [] OVERLOAD TESTS ---*/
	/*------------------------------*/
	{
		write_fname("AT & [] OVERLOAD", tstream, ostream);
		/* PERFORMANCE TEST */
		map_ii map7;
		map_is map8;

		for (size_t i = 0; i < 20000; i++)
		{
			map7[i] = i + 1;
			map8[i] = "TEST";
		}
		for (size_t i = 0; i < 20000; i++)
		{
			map7.at(i);
			map8.at(i);
			map7[i];
			map8[i];
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii map7;
		map_is map8;

		ret_vec_int ret_int;
		ret_vec_str ret_str;

		for (size_t i = 12; i < 24; i++)
		{
			map7[i] = i * 3;
			map8[i] = "TEST";
		}
		map7[0] = 42;
		map8[8] = "HELLO";
		map8[9] = "WATSON";

		ret_int.push_back(map7[0]);
		ret_int.push_back(map7[14]);
		ret_int.push_back(map7[18]);
		ret_int.push_back(map7[22]);
		ret_str.push_back(map8[8]);
		ret_str.push_back(map8[9]);
		ret_str.push_back(map8[19]);
		ret_str.push_back(map8[23]);

		ret_int.push_back(map7.at(0));
		ret_int.push_back(map7.at(12));
		ret_int.push_back(map7.at(16));
		ret_int.push_back(map7.at(20));
		ret_str.push_back(map8.at(8));
		ret_str.push_back(map8.at(9));
		ret_str.push_back(map8.at(13));
		ret_str.push_back(map8.at(20));
		try
		{
			ret_int.push_back(map7.at(5));
		}
		catch (const std::out_of_range & e)
		{
			ostream << "\nEXCEPTION: OUT OF RANGE" << "\n\n";
		}

		write_map(map7, ostream);
		write_std_vec(ret_int, ostream);
		write_map(map8, ostream);
		write_std_vec(ret_str, ostream);
	}
	/*_______________________*/
	/*--- ITERATOR TESTS ---*/
	/*-----------------------*/
	{
		write_fname("ITERATORS", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		map_ii map9;
		map_ii::iterator it;
		map_ii::const_iterator cit;
		map_ii::reverse_iterator rev;
		map_ii::const_reverse_iterator crev;

		ret_vec_int	ret;

		for (size_t i = 0; i < 7; i++)
			map9.insert(make_pair(i, (i * 3 / 5)));
		gettimeofday(&start, NULL);
		it = map9.begin();
		cit = map9.begin();
		rev = map9.rbegin();
		crev = map9.rbegin();
		ret.push_back(it == cit);
		for(; it != map9.end() && cit != map9.end(); it++, cit++)
		{
			ret.push_back(it->first);
			ret.push_back(it->second);
			ret.push_back(cit->first);
			ret.push_back(cit->second);
		}
		ret.push_back(it == map9.end());
		ret.push_back(cit == map9.end());
		it--, cit--;
		ret.push_back(it == map9.end());
		ret.push_back(cit == map9.end());
		for(; it != map9.begin() && cit != map9.begin(); it--, cit--)
		{
			ret.push_back(it->first);
			ret.push_back(it->second);
			ret.push_back(cit->first);
			ret.push_back(cit->second);
		}
		ret.push_back(it == map9.end());
		ret.push_back(cit == map9.end());

		/* REVERSE */
		ret.push_back(rev == crev);
		for(; rev != map9.rend() && crev != map9.rend(); rev++, crev++)
		{
			ret.push_back(rev->first);
			ret.push_back(rev->second);
			ret.push_back(crev->first);
			ret.push_back(crev->second);
		}
		ret.push_back(rev == map9.rend());
		ret.push_back(crev == map9.rend());
		rev--, crev--;
		ret.push_back(rev == map9.rend());
		ret.push_back(crev == map9.rend());
		for(; rev != map9.rbegin() && crev != map9.rbegin(); rev--, crev--)
		{
			ret.push_back(rev->first);
			ret.push_back(rev->second);
			ret.push_back(crev->first);
			ret.push_back(crev->second);
		}

		duration = time_ms(start);
		write_time(tstream, duration);
		write_map(map9, ostream);
		write_std_vec(ret, ostream);
	}
	/*__________________________*/
	/*--- EMPTY & SIZE TESTS ---*/
	/*--------------------------*/
	{
		write_fname("EMPTY & SIZE", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		map_ii	tmp1;
		map_ii	tmp2;
		ret_vec_int	ret;

		for (size_t i = 0; i < 91543; i++)
			tmp1.insert(make_pair(i, i * 3));
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

		map_ii	map10;
		map_ii	map11;

		ret_vec_int ret;

		for (size_t i = 0; i < 91543; i++)
			map10.insert(make_pair(i, i * 3));
		ret.push_back(map10.empty());
		ret.push_back(map11.empty());
		gettimeofday(&start, NULL);
		map10.clear();
		map11.clear();
		duration = time_ms(start);
		
		ret.push_back(map10.empty());
		ret.push_back(map11.empty());
		write_time(tstream, duration);
		write_map(map10, ostream);
		write_map(map11, ostream);
		write_std_vec(ret, ostream);
	}
	/*___________________________*/
	/*--- SINGLE INSERT TESTS ---*/
	/*---------------------------*/
	{
		write_fname("SINGLE INSERT", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map12;
		map_is	map13;

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			map12.insert(make_pair(i, i * 3));
			map13.insert(make_pair(i, "TEST"));
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		map_ii	map12;
		map_is	map13;

		ret_vec_int ret_int;
		ret_vec_str ret_str;

		pair<map_ii::iterator, bool> tpair1;
		pair<map_is::iterator, bool> tpair2;

		for (size_t i = 0; i < 6; i++)
		{
			map12.insert(make_pair(i + 5, i * 19));
			map13.insert(make_pair(i, "TEST STUFF"));
		}

		tpair1 = map12.insert(make_pair(13, 1896));
		/* PUSHES CONTENT OF KEY 13 TO RET_INT */
		ret_int.push_back(tpair1.first->second);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair1.second);

		tpair2 = map13.insert(make_pair(8, "INSERTED"));
		/* PUSHES CONTENT OF KEY 8 TO RET_STR */
		ret_str.push_back(tpair2.first->second);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair2.second);

		tpair1 = map12.insert(make_pair(13, 1542));
		/* PUSHES CONTENT OF EXISTING KEY 13 TO RET_INT */
		ret_int.push_back(tpair1.first->second);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair1.second);

		tpair2 = map13.insert(make_pair(8, "ME NO INSERT"));
		/* PUSHES CONTENT OF EXISTING KEY 8 TO RET_STR */
		ret_str.push_back(tpair2.first->second);
		/* PUSHES BOOL RESULT TO RET_INT */
		ret_int.push_back(tpair2.second);

		write_map(map12, ostream);
		write_map(map13, ostream);
		write_std_vec(ret_int, ostream);
		write_std_vec(ret_str, ostream);
	}
	/*_________________________________________*/
	/*--- SINGLE INSERT WITH POSITION TESTS ---*/
	/*-----------------------------------------*/
	{
		write_fname("SINGLE INSERT WITH POSITION", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map14;
		map_is	map15;

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			map14.insert(map14.begin(), make_pair(i, i * 3));
			map15.insert(map15.begin(), make_pair(i, "TEST"));
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map14;
		map_is	map15;

		ret_vec_int ret_int;
		ret_vec_str ret_str;

		for (size_t i = 0; i < 14; i++)
		{
			map14.insert(map14.begin(), make_pair(i + 21, i * 3));
			map15.insert(map15.begin(), make_pair(i, "HOWDY"));
		}

		ret_int.push_back(map14.insert(map14.begin(), \
			make_pair(96, 1896))->second);

		ret_int.push_back(map14.insert(map14.begin(), \
			make_pair(96, 666666))->second);

		ret_str.push_back(map15.insert(map15.begin(), \
			make_pair(19, "INSERT ME"))->second);

		ret_str.push_back(map15.insert(map15.begin(), \
			make_pair(19, "ME NO INSERT"))->second);

		write_map(map14, ostream);
		write_std_vec(ret_int, ostream);
		write_map(map15, ostream);
		write_std_vec(ret_str, ostream);
	}
	/*__________________________*/
	/*--- RANGE INSERT TESTS ---*/
	/*--------------------------*/
	{
		write_fname("RANGE INSERT", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map16;
		map_is	map17;

		map_ii	tmp1;
		map_is	tmp2;

		for (size_t i = 0; i < 53143; i++)
		{
			tmp1.insert(make_pair(i, i * 3));
			tmp2.insert(make_pair(i, "TEST"));
		}
		gettimeofday(&start, NULL);
		map16.insert(tmp1.begin(), tmp1.end());
		map17.insert(tmp2.begin(), tmp2.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map16;
		map_is	map17;

		map_ii	tmp1;
		map_is	tmp2;

		for (size_t i = 0; i < 14; i++)
		{
			tmp1.insert(make_pair(i * 5, i * 3));
			tmp2.insert(make_pair(i + 23, "INSERTED"));
		}
		map16.insert(tmp1.begin(), tmp1.end());
		map17.insert(tmp2.begin(), tmp2.end());

		write_map(map16, ostream);
		write_map(map17, ostream);
	}
	/*_______________________________*/
	/*--- ERASE ON POSITION TESTS ---*/
	/*-------------------------------*/
	{
		write_fname("ERASE ON POSITION", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map18;
		map_is	map19;

		for (size_t i = 0; i < 53143; i++)
		{
			map18.insert(make_pair(i, i * 3));
			map19.insert(make_pair(i, "ERASE"));
		}
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 53143; i++)
		{
			map18.erase(map18.begin());
			map19.erase(map19.begin());
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		map_ii	map18;
		map_is	map19;

		ret_vec_int	ret;

		for (size_t i = 0; i < 4; i++)
		{
			map18.insert(make_pair(i, i * 3));
			map19.insert(make_pair(i, "ERASE"));
		}
		map18.erase(map18.begin());
		map19.erase(map19.begin());
		ret.push_back(map18.size());
		ret.push_back(map19.size());
		ret.push_back(map18.empty());
		ret.push_back(map19.empty());
		map18.erase(map18.begin());
		map19.erase(map19.begin());
		ret.push_back(map18.size());
		ret.push_back(map19.size());
		ret.push_back(map18.empty());
		ret.push_back(map19.empty());

		write_map(map18, ostream);

		map19.erase(map19.begin());
		ret.push_back(map19.size());
		ret.push_back(map19.empty());
		map19.erase(map19.begin());
		ret.push_back(map19.size());
		ret.push_back(map19.empty());

		write_map(map19, ostream);
		write_std_vec(ret, ostream);

	}
	/*_______________________*/
	/*--- ERASE KEY TESTS ---*/
	/*-----------------------*/
	{
		write_fname("ERASE KEY", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map20;
		map_is	map21;

		for (size_t i = 0; i < 32411; i++)
		{
			map20.insert(make_pair(i, i * 3));
			map21.insert(make_pair(i, "ERASE ME"));
		}
		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 32411; i++)
		{
			map20.erase(i);
			map21.erase(i);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map20;
		map_is	map21;

		ret_vec_int	ret;

		for (size_t i = 0; i < 6; i++)
		{
			map20.insert(make_pair(i, i * 3));
			map21.insert(make_pair(i, "TEST"));
		}

		ret.push_back(map20.erase(16));
		ret.push_back(map21.erase(14));
		ret.push_back(map20.erase(1));
		ret.push_back(map21.erase(4));

		write_map(map20, ostream);
		write_map(map21, ostream);
		write_std_vec(ret, ostream);
	}
	/*_________________________*/
	/*--- ERASE RANGE TESTS ---*/
	/*-------------------------*/
	{
		write_fname("ERASE RANGE", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map22;
		map_is	map23;

		for (size_t i = 0; i < 32411; i++)
		{
			map22.insert(make_pair(i, i * 3));
			map23.insert(make_pair(i, "ERASE ME"));
		}
		gettimeofday(&start, NULL);
		map22.erase(map22.begin(), map22.end());
		map23.erase(map23.begin(), map23.end());
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map22;
		map_is	map23;

		for (size_t i = 0; i < 13; i++)
		{
			map22.insert(make_pair(i, i * 3));
			map23.insert(make_pair(i, "ERASE ME"));
		}
		map22.insert(make_pair(13, 54321));
		map23.insert(make_pair(13, "ERASE ME NOT"));
		map22.erase(map22.begin(), --map22.end());
		map23.erase(map23.begin(), --map23.end());

		write_map(map22, ostream);
		write_map(map23, ostream);
	}
	/*__________________*/
	/*--- SWAP TESTS ---*/
	/*------------------*/
	{
		write_fname("SWAP", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map24;
		map_ii	map25;

		for (size_t i = 0; i < 32411; i++)
		{
			map24.insert(make_pair(i, i * 3));
			map25.insert(make_pair(i + 12, i * 2));
		}
		gettimeofday(&start, NULL);
		map24.swap(map25);
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_is	map24;
		map_is	map25;

		for (size_t i = 0; i < 13; i++)
			map24.insert(make_pair(i, "MAP24"));
		for (size_t i = 0; i < 2; i++)
			map25.insert(make_pair(i + 12, "MAP25"));
		map24.swap(map25);

		write_map(map24, ostream);
		write_map(map25, ostream);
	}
	/*__________________________*/
	/*--- COUNT & FIND TESTS ---*/
	/*--------------------------*/
	{
		write_fname("COUNT & FIND", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map26;

		for (size_t i = 0; i < 12414; i++)
			map26.insert(make_pair(i, i * 3));

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 12414; i++)
		{
			map26.count(i);
			map26.find(i);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map26;

		ret_vec_int	ret;

		bool tmp;

		for (size_t i = 0; i < 12; i++)
			map26.insert(make_pair(i, i * 3));

		tmp = map26.count(1);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(map26.find(1)->second);

		tmp = map26.count(6);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(map26.find(6)->second);

		tmp = map26.count(11);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(map26.find(11)->second);

		tmp = map26.count(12);
		ret.push_back(tmp);
		if (tmp)
			ret.push_back(map26.find(12)->second);

		ret.push_back(map26.find(12) == map26.end());

		write_map(map26, ostream);
		write_std_vec(ret, ostream);
	}
	/*____________________________________________________*/
	/*--- EQUAL RANGE, LOWER BOUND & UPPER BOUND TESTS ---*/
	/*----------------------------------------------------*/
	{
		write_fname("EQUAL RANGE, LOWER BOUND & UPPER BOUND", tstream, ostream);
		/* PERFORMANCE TEST */

		map_ii	map27;

		for (size_t i = 1; i < 12414; i++)
			map27.insert(make_pair(i, i * 3));

		gettimeofday(&start, NULL);
		for (size_t i = 0; i < 12415; i++)
		{
			map27.equal_range(i);
			map27.lower_bound(i);
			map27.upper_bound(i);
		}
		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		map_ii	map27;

		ret_vec_int	ret;

		pair<map_ii::iterator, map_ii::iterator> tpair;

		for (size_t i = 1; i < 7; i++)
			map27.insert(make_pair(i, i * 3));

		map27.insert(make_pair(9, 9999));
		for (size_t i = 1; i < 10; i++)
		{
			tpair = map27.equal_range(i);
			ret.push_back(tpair.first->second);
			if (tpair.second != map27.end())
				ret.push_back(tpair.second->second);
			ret.push_back(map27.lower_bound(i)->second);
			if (map27.upper_bound(i) != map27.end())
				ret.push_back(map27.upper_bound(i)->second);
		}

		write_map(map27, ostream);
		write_std_vec(ret, ostream);
	}
	/*__________________________________*/
	/*--- RELATIONAL OPERATORS TESTS ---*/
	/*----------------------------------*/
	{
		write_fname("RELATIONAL OPERATORS", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */

		map_ii	tmp1;
		map_ii	tmp2;

		ret_vec_int	ret;

		gettimeofday(&start, NULL);
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp1.insert(make_pair(6, 6));
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(make_pair(36, 36));
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(make_pair(6, 6));
		ret.push_back(tmp1 == tmp2);
		ret.push_back(tmp1 != tmp2);
		ret.push_back(tmp1 < tmp2);
		ret.push_back(tmp1 <= tmp2);
		ret.push_back(tmp1 > tmp2);
		ret.push_back(tmp1 >= tmp2);
		tmp2.insert(make_pair(3, 3));
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