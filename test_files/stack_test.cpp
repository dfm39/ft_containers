#include "test_utils.hpp"
#include <sys/time.h>
#include <list>
#include <deque>
#include <vector>

#ifndef STL
# define STL 0
#endif

#if STL
	#include <stack>
	#define NAMESPACE std
	#define prefix "std_"
#else

	#include "stack.hpp"
	#define NAMESPACE ft
	#define prefix "ft_"
#endif


#define dir "./results/stack/"
#define T1 int
#define T2 std::string
#define stack_t typename NAMESPACE::stack<T, Container>
#define stack_int NAMESPACE::stack<T1>
#define stack_str NAMESPACE::stack<T2>

static size_t iter;

template <typename T, class Container>
void	write_stack(stack_t stck, std::fstream &ostream)
{
	ostream << "----- stack" << iter++ << " -----" << "\n\n";
	ostream << "SIZE = " << stck.size() << "\n";

	ostream << "CONTENT =";
	while (stck.size() != 0)
	{
		ostream << " " << stck.top();
		stck.pop();
	}
	ostream << "\n\n";
}

int	main()
{
	timeval	start;
	time_t	duration = 0;
	std::fstream	tstream, ostream;
	create_file(tstream, dir, prefix, "stack_time");
	create_file(ostream, dir, prefix, "stack_out");

	/*_________________________*/
	/*--- CONSTRUCTOR TESTS ---*/
	/*-------------------------*/
	{
		write_fname("CONSTRUCTOR", tstream, ostream);
		/* PERFORMANCE & FUNCTIONAL TEST */
		gettimeofday(&start, NULL);

		stack_int 								stck0;
		NAMESPACE::stack<T1, std::vector<T1> >	tmp1;
		NAMESPACE::stack<T1, std::deque<T1> >	tmp2;
		NAMESPACE::stack<T1, std::list<T1> >	tmp3;

		stck0.push(stck0.size());
		stck0.push(tmp1.size());
		stck0.push(tmp2.size());
		stck0.push(tmp3.size());

		duration = time_ms(start);
		write_time(tstream, duration);
		write_stack(stck0, ostream);
	}
	/*________________________*/
	/*--- ASSIGNMENT TESTS ---*/
	/*------------------------*/
	{
		write_fname("ASSIGNMENT", tstream, ostream);
		/* PERFORMANCE TEST */

		stack_int 								stck1;
		NAMESPACE::stack<T1, std::vector<T1> >	stck2;
		NAMESPACE::stack<T1, std::deque<T1> >	stck3;
		NAMESPACE::stack<T1, std::list<T1> >	stck4;

		stack_int 								tmp1;
		NAMESPACE::stack<T1, std::vector<T1> >	tmp2;
		NAMESPACE::stack<T1, std::deque<T1> >	tmp3;
		NAMESPACE::stack<T1, std::list<T1> >	tmp4;

		for (int i = 0; i < 123512; i++)
		{
			tmp1.push(i);
			tmp2.push(i * 2 / 3);
			tmp3.push(i * (-3));
			tmp4.push(i + 9);
		}
		gettimeofday(&start, NULL);
		stck1 = tmp1;
		stck2 = tmp2;
		stck3 = tmp3;
		stck4 = tmp4;

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */
		stack_int 								stck1;
		NAMESPACE::stack<T1, std::vector<T1> >	stck2;
		NAMESPACE::stack<T1, std::deque<T1> >	stck3;
		NAMESPACE::stack<T1, std::list<T1> >	stck4;
		stack_int 								stck5;

		stack_int 								tmp1;
		NAMESPACE::stack<T1, std::vector<T1> >	tmp2;
		NAMESPACE::stack<T1, std::deque<T1> >	tmp3;
		NAMESPACE::stack<T1, std::list<T1> >	tmp4;
		for (int i = 0; i < 17; i++)
		{
			tmp1.push(i);
			tmp2.push(i * 2 / 3);
			tmp3.push(i * (-3));
			tmp4.push(i + 9);
		}
		stck5.push(tmp1.size());
		stck5.push(tmp1.top());
		stck5.push(tmp2.size());
		stck5.push(tmp2.top());
		stck5.push(tmp3.size());
		stck5.push(tmp3.top());
		stck5.push(tmp4.size());
		stck5.push(tmp4.top());
		stck5.push(stck1.size());
		stck5.push(stck2.size());
		stck5.push(stck3.size());
		stck5.push(stck4.size());
		stck1 = tmp1;
		stck2 = tmp2;
		stck3 = tmp3;
		stck4 = tmp4;
		stck5.push(stck1.size());
		stck5.push(stck1.top());
		stck5.push(stck2.size());
		stck5.push(stck2.top());
		stck5.push(stck3.size());
		stck5.push(stck3.top());
		stck5.push(stck4.size());
		stck5.push(stck4.top());

		write_stack(stck1, ostream);
		write_stack(stck2, ostream);
		write_stack(stck3, ostream);
		write_stack(stck4, ostream);
		write_stack(stck5, ostream);
	}
	/*_________________________________________*/
	/*--- EMPTY, SIZE, TOP, PUSH, POP TESTS ---*/
	/*-----------------------------------------*/
	{
		write_fname("EMPTY, SIZE, TOP, PUSH, POP", tstream, ostream);
		/* PERFORMANCE TEST */

		stack_int 								stck6;
		NAMESPACE::stack<T1, std::vector<T1> >	stck7;
		NAMESPACE::stack<T1, std::deque<T1> >	stck8;
		NAMESPACE::stack<T1, std::list<T1> >	stck9;

		gettimeofday(&start, NULL);

		stck6.empty();
		stck7.empty();
		stck8.empty();
		stck9.empty();
		
		for (int i = 0; i < 123512; i++)
		{
			stck6.empty();
			stck7.empty();
			stck8.empty();
			stck9.empty();
			stck6.size();
			stck7.size();
			stck8.size();
			stck9.size();
			stck6.push(i);
			stck7.push(i * 2 / 3);
			stck8.push(i * (-3));
			stck9.push(i + 9);
		}
		for (int i = 0; i < 123512; i++)
		{
			stck6.pop();
			stck7.pop();
			stck8.pop();
			stck9.pop();
			stck6.top();
			stck7.top();
			stck8.top();
			stck9.top();
			stck6.size();
			stck7.size();
			stck8.size();
			stck9.size();
			stck6.empty();
			stck7.empty();
			stck8.empty();
			stck9.empty();
		}

		duration = time_ms(start);
		write_time(tstream, duration);
	}
	{
		/* FUNCTIONAL TEST */

		stack_int 								stck6;
		NAMESPACE::stack<T1, std::vector<T1> >	stck7;
		NAMESPACE::stack<T1, std::deque<T1> >	stck8;
		NAMESPACE::stack<T1, std::list<T1> >	stck9;
		stack_int 								stck10;

		stck6.empty();
		stck7.empty();
		stck8.empty();
		stck9.empty();
		
		for (int i = 0; i < 16; i++)
		{
			stck10.push(stck6.empty());
			stck10.push(stck7.empty());
			stck10.push(stck8.empty());
			stck10.push(stck9.empty());
			stck10.push(stck6.size());
			stck10.push(stck7.size());
			stck10.push(stck8.size());
			stck10.push(stck9.size());
			stck6.push(i);
			stck7.push(i * 2 / 3);
			stck8.push(i * (-3));
			stck9.push(i + 9);
			stck10.push(stck6.top());
			stck10.push(stck7.top());
			stck10.push(stck8.top());
			stck10.push(stck9.top());
		}
		for (int i = 0; i < 15; i++)
		{
			stck8.pop();
			stck9.pop();
			stck10.push(stck6.top());
			stck10.push(stck7.top());
			stck10.push(stck8.top());
			stck10.push(stck9.top());
			stck10.push(stck6.size());
			stck10.push(stck7.size());
			stck10.push(stck8.size());
			stck10.push(stck9.size());
			stck10.push(stck6.empty());
			stck10.push(stck7.empty());
			stck10.push(stck8.empty());
			stck10.push(stck9.empty());
		}
		stck9.pop();
		stck10.push(stck9.size());
		stck10.push(stck9.empty());

		write_stack(stck6, ostream);
		write_stack(stck7, ostream);
		write_stack(stck8, ostream);
		write_stack(stck9, ostream);
		write_stack(stck10, ostream);
	}
	/*__________________________________*/
	/*--- RELATIONAL OPERATORS TESTS ---*/
	/*----------------------------------*/
	{
		write_fname("RELATIONAL OPERATORS", tstream, ostream);

		/* PERFORMANCE & FUNCTIONAL TEST */
		gettimeofday(&start, NULL);

		stack_int 								stck11;

		stack_int 								tmp1;
		NAMESPACE::stack<T1, std::vector<T1> >	tmp2;
		NAMESPACE::stack<T1, std::deque<T1> >	tmp3;
		NAMESPACE::stack<T1, std::list<T1> >	tmp4;

		stack_int 								ttmp1;
		NAMESPACE::stack<T1, std::vector<T1> >	ttmp2;
		NAMESPACE::stack<T1, std::deque<T1> >	ttmp3;
		NAMESPACE::stack<T1, std::list<T1> >	ttmp4;

		stck11.push(tmp1 == ttmp1);
		stck11.push(tmp1 != ttmp1);
		stck11.push(tmp1 < ttmp1);
		stck11.push(tmp1 <= ttmp1);
		stck11.push(tmp1 > ttmp1);
		stck11.push(tmp1 >= ttmp1);

		stck11.push(tmp2 == ttmp2);
		stck11.push(tmp2 != ttmp2);
		stck11.push(tmp2 < ttmp2);
		stck11.push(tmp2 <= ttmp2);
		stck11.push(tmp2 > ttmp2);
		stck11.push(tmp2 >= ttmp2);

		stck11.push(tmp3 == ttmp3);
		stck11.push(tmp3 != ttmp3);
		stck11.push(tmp3 < ttmp3);
		stck11.push(tmp3 <= ttmp3);
		stck11.push(tmp3 > ttmp3);
		stck11.push(tmp3 >= ttmp3);

		stck11.push(tmp4 == ttmp4);
		stck11.push(tmp4 != ttmp4);
		stck11.push(tmp4 < ttmp4);
		stck11.push(tmp4 <= ttmp4);
		stck11.push(tmp4 > ttmp4);
		stck11.push(tmp4 >= ttmp4);

		tmp1.push(1);
		tmp2.push(1);
		tmp3.push(1);
		tmp4.push(1);

		stck11.push(tmp1 == ttmp1);
		stck11.push(tmp1 != ttmp1);
		stck11.push(tmp1 < ttmp1);
		stck11.push(tmp1 <= ttmp1);
		stck11.push(tmp1 > ttmp1);
		stck11.push(tmp1 >= ttmp1);

		stck11.push(tmp2 == ttmp2);
		stck11.push(tmp2 != ttmp2);
		stck11.push(tmp2 < ttmp2);
		stck11.push(tmp2 <= ttmp2);
		stck11.push(tmp2 > ttmp2);
		stck11.push(tmp2 >= ttmp2);

		stck11.push(tmp3 == ttmp3);
		stck11.push(tmp3 != ttmp3);
		stck11.push(tmp3 < ttmp3);
		stck11.push(tmp3 <= ttmp3);
		stck11.push(tmp3 > ttmp3);
		stck11.push(tmp3 >= ttmp3);

		stck11.push(tmp4 == ttmp4);
		stck11.push(tmp4 != ttmp4);
		stck11.push(tmp4 < ttmp4);
		stck11.push(tmp4 <= ttmp4);
		stck11.push(tmp4 > ttmp4);
		stck11.push(tmp4 >= ttmp4);

		ttmp1.push(1);
		ttmp2.push(1);
		ttmp3.push(1);
		ttmp4.push(1);

		stck11.push(tmp1 == ttmp1);
		stck11.push(tmp1 != ttmp1);
		stck11.push(tmp1 < ttmp1);
		stck11.push(tmp1 <= ttmp1);
		stck11.push(tmp1 > ttmp1);
		stck11.push(tmp1 >= ttmp1);

		stck11.push(tmp2 == ttmp2);
		stck11.push(tmp2 != ttmp2);
		stck11.push(tmp2 < ttmp2);
		stck11.push(tmp2 <= ttmp2);
		stck11.push(tmp2 > ttmp2);
		stck11.push(tmp2 >= ttmp2);

		stck11.push(tmp3 == ttmp3);
		stck11.push(tmp3 != ttmp3);
		stck11.push(tmp3 < ttmp3);
		stck11.push(tmp3 <= ttmp3);
		stck11.push(tmp3 > ttmp3);
		stck11.push(tmp3 >= ttmp3);

		stck11.push(tmp4 == ttmp4);
		stck11.push(tmp4 != ttmp4);
		stck11.push(tmp4 < ttmp4);
		stck11.push(tmp4 <= ttmp4);
		stck11.push(tmp4 > ttmp4);
		stck11.push(tmp4 >= ttmp4);

		tmp1.pop();
		tmp2.pop();
		tmp3.pop();
		tmp4.pop();

		stck11.push(tmp1 == ttmp1);
		stck11.push(tmp1 != ttmp1);
		stck11.push(tmp1 < ttmp1);
		stck11.push(tmp1 <= ttmp1);
		stck11.push(tmp1 > ttmp1);
		stck11.push(tmp1 >= ttmp1);

		stck11.push(tmp2 == ttmp2);
		stck11.push(tmp2 != ttmp2);
		stck11.push(tmp2 < ttmp2);
		stck11.push(tmp2 <= ttmp2);
		stck11.push(tmp2 > ttmp2);
		stck11.push(tmp2 >= ttmp2);

		stck11.push(tmp3 == ttmp3);
		stck11.push(tmp3 != ttmp3);
		stck11.push(tmp3 < ttmp3);
		stck11.push(tmp3 <= ttmp3);
		stck11.push(tmp3 > ttmp3);
		stck11.push(tmp3 >= ttmp3);

		stck11.push(tmp4 == ttmp4);
		stck11.push(tmp4 != ttmp4);
		stck11.push(tmp4 < ttmp4);
		stck11.push(tmp4 <= ttmp4);
		stck11.push(tmp4 > ttmp4);
		stck11.push(tmp4 >= ttmp4);

		duration = time_ms(start);
		write_time(tstream, duration);
		write_stack(stck11, ostream);
	}
	return 0;
}
