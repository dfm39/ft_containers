#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <iostream>
# include <sys/time.h>
# include <fstream>

#ifndef STL
# define STL 0
#endif

#if STL
	#define NAMESPACE std
#else
	#define NAMESPACE ft
#endif

#define std_vec typename std::vector<T>

void	write_time(std::fstream &tstream, const time_t duration)
{
	if (STL)
		tstream << "STD - ";
	else
		tstream << "FT - ";
	tstream << "TIME: " << duration << " ms" <<"\n";
}

template <typename T>
void	write_std_vec(std_vec vec, std::fstream &ostream)
{
	ostream << "return vec:" "\n\n";
	ostream << "SIZE = " << vec.size() << "\n";

	ostream << "CONTENT =";
	for (std_vec::iterator it = vec.begin(); it != vec.end(); it++)
	{
		ostream << " " << *it;
	}
	ostream << "\n\n";
}

void	write_fname(std::string name,std::fstream &tstream, std::fstream &ostream)
{
	if (STL)
		tstream << std::setw(10) << std::setfill('-') << " STD " <<	\
			name << " " << std::setw(8) << std::setfill('-') << '\n';
	else
		tstream << std::setw(10) << std::setfill('-') << " FT " <<	\
			name << " " << std::setw(8) << std::setfill('-') << '\n';
	ostream << "<< " << name << " >>" << '\n';
}

void	create_file(std::fstream &stream, std::string dir, std::string prefix, std::string suffix)
{
	std::string filename = dir;
	filename += prefix;
	filename += suffix;
	filename += ".txt";
	stream.open(filename.c_str(), std::fstream::out | std::fstream::trunc);
}

time_t	time_ms(timeval start)
{
	struct timeval	time_is;
	time_t			time = 0;

	gettimeofday(&time_is, NULL);
	time = (time_is.tv_sec - start.tv_sec) * 1000 + (time_is.tv_usec - start.tv_usec) / 1000;
	return time;
}

#endif