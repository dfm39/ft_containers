NAME		=	containers

NAME1		=	subject

CC			=	c++

RM			=	rm

CFLAGS		=	-Wall -Wextra -Werror -std=c++98

#------Colors--------
BLACK:="\033[1;30m"
RED:="\033[1;31m"
BGREEN:="\033[1;32m"
GREEN:="\033[0;32m"
YELLOW:="\033[1;33m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
#====================

vector:
	@mkdir -p results; \
	mkdir -p results/vector; \
	echo $(PURPLE) "////// VECTOR ///////\n " $(EOC); \
	$(CC) $(CFLAGS) -g -o $(NAME)_ft_vector ./tests/vector_test.cpp && ./$(NAME)_ft_vector && \
	$(CC) $(CFLAGS) -o $(NAME)_std_vector ./tests/vector_test.cpp -D STL=1 && ./$(NAME)_std_vector ;\
	echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/vector/ft_vec_time.txt ./results/vector/std_vec_time.txt ; \
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/vector/ft_vec_out.txt ./results/vector/std_vec_out.txt && \
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)


subject_ft:
	$(CC) $(CFLAGS) -o $(NAME1)_ft ./tests/subject_test.cpp

subject_std:
	$(CC) $(CFLAGS) -o $(NAME1)_std -D STL=1 ./subject_test.cpp


clean:		
			$(RM) -f $(NAME)*
			$(RM) -f $(NAME1)*
			$(RM) -rf results/

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re vector map stack set
