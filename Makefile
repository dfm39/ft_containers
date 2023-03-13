NAME		=	containers

CC			=	c++

RM			=	rm

CFLAGS		=	-Wall -Wextra -Werror -std=c++98

FT			=	_ft

STD			=	_std

VECTOR		=	_vector

STACK		=	_stack




#------Colors--------
BLACK:="\033[1;30m"
RED:="\033[1;31m"
BGREEN:="\033[1;32m"
GREEN:="\033[0;32m"
YELLOW:="\033[1;33m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
SCYAN:="\033[0;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
#====================

$(NAME):
	@echo $(RED)" --- WELCOME! ---\n"; \
	echo $(BGREEN)' COMMANDS:\n '$(YELLOW)'"make container_type"'$(BGREEN)'\t--> \tTESTS "container_type" RECOMMENDED FOR CLEARER ARRANGEMENT'; \
	echo $(YELLOW)' "make all"'$(BGREEN)'\t\t--> \tRUNS ALL TESTS IN SEQUENCE\n';\
	echo $(EOC)' Results are saved in \t"./tests/container_type"\n' $(EOC)

vector:
	@mkdir -p results; \
	mkdir -p results/vector; \
	echo $(PURPLE) "////// VECTOR ///////\n " $(EOC); \
	echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC); \
	$(CC) $(CFLAGS) -g -o $(NAME)$(FT)$(VECTOR) ./tests/vector_test.cpp && ./$(NAME)$(FT)$(VECTOR) && \
	$(CC) $(CFLAGS) -o $(NAME)$(STD)$(VECTOR) ./tests/vector_test.cpp -D STL=1 && ./$(NAME)$(STD)$(VECTOR) ;\
	echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/vector/ft_vec_time.txt ./results/vector/std_vec_time.txt ; \
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/vector/ft_vec_out.txt ./results/vector/std_vec_out.txt && \
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

stack:
	@mkdir -p results; \
	mkdir -p results/stack; \
	echo $(PURPLE) "////// STACK ///////\n " $(EOC); \
	echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC); \
	$(CC) $(CFLAGS) -o $(NAME)$(FT)$(STACK) ./tests/stack_test.cpp && ./$(NAME)$(FT)$(STACK) && \
	$(CC) $(CFLAGS) -o $(NAME)$(STD)$(STACK) ./tests/stack_test.cpp -D STL=1 && ./$(NAME)$(STD)$(STACK) ; \
	echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/stack/ft_stack_time.txt ./results/stack/std_stack_time.txt ; \
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/stack/ft_stack_out.txt ./results/stack/std_stack_out.txt && \
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

map:
	@mkdir -p results; \
	mkdir -p results/map; \
	echo $(PURPLE) "////// MAP ///////\n " $(EOC); \
	echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC); \
	$(CC) $(CFLAGS) -o $(NAME)$(FT)$(MAP) ./tests/map_test.cpp && ./$(NAME)$(FT)$(MAP) && \
	$(CC) $(CFLAGS) -o $(NAME)$(STD)$(MAP) ./tests/map_test.cpp -D STL=1 && ./$(NAME)$(STD)$(MAP) ; \
	echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/map/ft_map_time.txt ./results/map/std_map_time.txt ; \
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC) ; \
	diff -y ./results/map/ft_map_out.txt ./results/map/std_map_out.txt && \
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

subject_ft:
	$(CC) $(CFLAGS) -o subject_ft ./tests/subject_test.cpp

subject_std:
	$(CC) $(CFLAGS) -o subject_std -D STL=1 ./subject_test.cpp


clean:		
			$(RM) -f $(NAME)*
			$(RM) -f $(NAME1)*
			$(RM) -rf results/

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re vector map stack set
