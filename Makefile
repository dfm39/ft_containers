#						 #
#--- GLOBAL VARIABLES ---#
#						 #

NAME		=	containers

CC				=	c++
DIFF			=	diff -y
MKDIR			=	mkdir -p
SOURCES_DIR		=	./test_files/
HEADER_DIR		=	./includes/
FT_OBJECTS_DIR	=	./objs_ft/
STD_OBJECTS_DIR	=	./objs_std/
RESULTS_DIR		=	./results/
LEAKS			=

IFLAGS		=	-I $(HEADER_DIR)
CFLAGS		=	-Wall -Wextra -Werror -pedantic -std=c++98 $(IFLAGS)
STDFLAG		=	-D STL=1

FT			=	ft_
STD			=	std_

# UNCOMMENT FOR LEAKS CHECK ON MAC
# OS = $(shell uname)
# ifeq ($(OS), Darwin)
# 	LEAKS +=  leaks --atExit -- 
# endif

#------Colors--------
BLACK	=	"\033[1;30m"
RED		=	"\033[1;31m"
BGREEN	=	"\033[1;32m"
GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
PURPLE	=	"\033[1;35m"
CYAN	=	"\033[1;36m"
SCYAN	=	"\033[0;36m"
WHITE	=	"\033[1;37m"
EOC		=	"\033[0;0m"
#====================

#						 #
#--- VECTOR VARIABLES ---#
#						 #

VEC_FILE	=	\
				vector_test

VEC_RESULTS_DIR			=	$(RESULTS_DIR)vector/
FT_VEC_TIME_RESULTS		=	$(VEC_RESULTS_DIR)ft_vec_time.txt
STD_VEC_TIME_RESULTS	=	$(VEC_RESULTS_DIR)std_vec_time.txt
FT_VEC_RESULTS			=	$(VEC_RESULTS_DIR)ft_vec_out.txt
STD_VEC_RESULTS			=	$(VEC_RESULTS_DIR)std_vec_out.txt

#------Paths---------
VEC_SOURCES		=	$(addprefix $(SOURCES_DIR),$(addsuffix .cpp,$(VEC_FILE)))
FT_VEC_OBJECTS	=	$(addprefix $(FT_OBJECTS_DIR),$(addsuffix .o,$(VEC_FILE)))
STD_VEC_OBJECTS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .o,$(VEC_FILE)))
#====================

#						#
#--- STACK VARIABLES ---#
#						#

STCK_FILE	=	\
				stack_test

STCK_RESULTS_DIR		=	$(RESULTS_DIR)stack/
FT_STCK_TIME_RESULTS	=	$(STCK_RESULTS_DIR)ft_stack_time.txt
STD_STCK_TIME_RESULTS	=	$(STCK_RESULTS_DIR)std_stack_time.txt
FT_STCK_RESULTS			=	$(STCK_RESULTS_DIR)ft_stack_out.txt
STD_STCK_RESULTS		=	$(STCK_RESULTS_DIR)std_stack_out.txt

#------Paths---------
STCK_SOURCES		=	$(addprefix $(SOURCES_DIR),$(addsuffix .cpp,$(STCK_FILE)))
FT_STCK_OBJECTS		=	$(addprefix $(FT_OBJECTS_DIR),$(addsuffix .o,$(STCK_FILE)))
STD_STCK_OBJECTS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .o,$(STCK_FILE)))
#====================

#					  #
#--- MAP VARIABLES ---#
#					  #

MAP_FILE	=	\
				map_test

MAP_RESULTS_DIR			=	$(RESULTS_DIR)map/
FT_MAP_TIME_RESULTS		=	$(MAP_RESULTS_DIR)ft_map_time.txt
STD_MAP_TIME_RESULTS	=	$(MAP_RESULTS_DIR)std_map_time.txt
FT_MAP_RESULTS			=	$(MAP_RESULTS_DIR)ft_map_out.txt
STD_MAP_RESULTS			=	$(MAP_RESULTS_DIR)std_map_out.txt

#------Paths---------
MAP_SOURCES		=	$(addprefix $(SOURCES_DIR),$(addsuffix .cpp,$(MAP_FILE)))
FT_MAP_OBJECTS	=	$(addprefix $(FT_OBJECTS_DIR),$(addsuffix .o,$(MAP_FILE)))
STD_MAP_OBJECTS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .o,$(MAP_FILE)))
#====================

#					  #
#--- SET VARIABLES ---#
#					  #

SET_FILE	=	\
				set_test

SET_RESULTS_DIR			=	$(RESULTS_DIR)set/
FT_SET_TIME_RESULTS		=	$(SET_RESULTS_DIR)ft_set_time.txt
STD_SET_TIME_RESULTS	=	$(SET_RESULTS_DIR)std_set_time.txt
FT_SET_RESULTS			=	$(SET_RESULTS_DIR)ft_set_out.txt
STD_SET_RESULTS			=	$(SET_RESULTS_DIR)std_set_out.txt

#------Paths---------
SET_SOURCES		=	$(addprefix $(SOURCES_DIR),$(addsuffix .cpp,$(SET_FILE)))
FT_SET_OBJECTS	=	$(addprefix $(FT_OBJECTS_DIR),$(addsuffix .o,$(SET_FILE)))
STD_SET_OBJECTS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .o,$(SET_FILE)))
#====================

#						  #
#--- SUBJECT VARIABLES ---#
#						  #

SUB_FILE	=	\
				subject_test

#------Paths---------
SUB_SOURCES		=	$(addprefix $(SOURCES_DIR),$(addsuffix .cpp,$(SUB_FILE)))
FT_SUB_OBJECTS	=	$(addprefix $(FT_OBJECTS_DIR),$(addsuffix .o,$(SUB_FILE)))
STD_SUB_OBJECTS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .o,$(SUB_FILE)))
STD_UB_DEPS	=	$(addprefix $(STD_OBJECTS_DIR),$(addsuffix .d,$(SUB_FILE)))
#====================

#					 #
#--- GLOBAL RULES ---#
#					 #

$(NAME):
	@echo $(RED)"\n --- WELCOME! ---\n"; \
	echo $(BGREEN)' COMMANDS:\n '$(YELLOW)'"make container_type"'$(BGREEN)'\t--> \tRUNS "container_type" \
	TESTS - RECOMMENDED FOR CLEARER ARRANGEMENT'; \
	echo $(YELLOW)' "make subject"'$(BGREEN)'\t\t--> \tRUNS TEST FROM 42 PROJECT PAGE';\
	echo $(YELLOW)' "make all"'$(BGREEN)'\t\t--> \tRUNS ALL TESTS IN SEQUENCE\n';\
	echo $(EOC)' Results are saved in \t"./tests/container_type"\n' $(EOC)

$(FT_OBJECTS_DIR)%.o : $(SOURCES_DIR)%.cpp
	@$(MKDIR) $(FT_OBJECTS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(STD_OBJECTS_DIR)%.o : $(SOURCES_DIR)%.cpp
	@$(MKDIR) $(STD_OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(STDFLAG) -c $< -o $@

all:
	@make vector
	@make stack
	@make map
	@make set
	@make subject

clean:
	@rm -rf $(FT_OBJECTS_DIR)
	@rm -rf $(STD_OBJECTS_DIR)
	@echo $(YELLOW) "OBJECT FILES CLEANED" $(EOC)

fclean:	clean
	@rm -f $(FT)*
	@rm -f $(STD)*
	@rm -rf $(RESULTS_DIR)
	@echo $(RED)" TESTS & RESULTS DELETED" $(EOC)

re:			fclean all

#				    #
#--- VECTOR TEST ---#
#				    #

ft_vector: $(FT_VEC_OBJECTS)
	@$(CC) $(CFLAGS) $(VEC_SOURCES) -o $@ && $(LEAKS) ./$@


std_vector: $(STD_VEC_OBJECTS)
	@$(CC) $(CFLAGS) $(STDFLAG) $(VEC_SOURCES) -o $@ && $(LEAKS) ./$@

vector:
	@$(MKDIR) $(RESULTS_DIR)
	@$(MKDIR) $(VEC_RESULTS_DIR)

	@echo $(PURPLE) "\n////// VECTOR ///////\n " $(EOC)
	@echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC)

	@make ft_vector
	@make std_vector

	@echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC)
	@$(DIFF) $(FT_VEC_TIME_RESULTS) $(STD_VEC_TIME_RESULTS);	\
																\
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC);			\
	$(DIFF) $(FT_VEC_RESULTS) $(STD_VEC_RESULTS) &&				\
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)



#				   #
#--- STACK TEST ---#
#				   #

ft_stack: $(FT_STCK_OBJECTS)
	@$(CC) $(CFLAGS) $(STCK_SOURCES) -o $@ && $(LEAKS) ./$@

std_stack: $(STD_STCK_OBJECTS)
	@$(CC) $(CFLAGS) $(STDFLAG) $(STCK_SOURCES) -o $@ && $(LEAKS) ./$@

stack:
	@$(MKDIR) $(RESULTS_DIR)
	@$(MKDIR) $(STCK_RESULTS_DIR)

	@echo $(PURPLE) "\n////// STACK ///////\n " $(EOC)
	@echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC)

	@make ft_stack
	@make std_stack

	@echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC)
	@$(DIFF) $(FT_STCK_TIME_RESULTS) $(STD_STCK_TIME_RESULTS);	\
																\
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC);			\
	$(DIFF) $(FT_STCK_RESULTS) $(STD_STCK_RESULTS) &&			\
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

#				 #
#--- MAP TEST ---#
#				 #

ft_map: $(FT_MAP_OBJECTS)
	@$(CC) $(CFLAGS) $(MAP_SOURCES) -o $@ && $(LEAKS) ./$@

std_map: $(STD_MAP_OBJECTS)
	@$(CC) $(CFLAGS) $(STDFLAG) $(MAP_SOURCES) -o $@ && $(LEAKS) ./$@

map:
	@$(MKDIR) $(RESULTS_DIR)
	@$(MKDIR) $(MAP_RESULTS_DIR)
	
	@echo $(PURPLE) "\n////// MAP ///////\n " $(EOC)
	@echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC)

	@make ft_map
	@make std_map

	@echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC)
	@$(DIFF) $(FT_MAP_TIME_RESULTS) $(STD_MAP_TIME_RESULTS);	\
																\
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC);			\
	$(DIFF) $(FT_MAP_RESULTS) $(STD_MAP_RESULTS) &&				\
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

#				 #
#--- SET TEST ---#
#				 #

ft_set: $(FT_SET_OBJECTS)
	@$(CC) $(CFLAGS) $(SET_SOURCES) -o $@ && $(LEAKS) ./$@

std_set: $(STD_SET_OBJECTS)
	@$(CC) $(CFLAGS) $(STDFLAG) $(SET_SOURCES) -o $@ && $(LEAKS) ./$@

set:
	@$(MKDIR) $(RESULTS_DIR)
	@$(MKDIR) $(SET_RESULTS_DIR)
	
	@echo $(PURPLE) "\n////// SET ///////\n " $(EOC)
	@echo $(YELLOW) "**** RUNNING TESTS, PLEASE WAIT ****\n " $(EOC)

	@make ft_set
	@make std_set

	@echo $(CYAN) "PERFORMANCE COMPARISON VIA DIFF:" $(EOC)
	@$(DIFF) $(FT_SET_TIME_RESULTS) $(STD_SET_TIME_RESULTS);	\
																\
	echo $(CYAN) "OUTPUT COMPARISON VIA DIFF:" $(EOC);			\
	$(DIFF) $(FT_SET_RESULTS) $(STD_SET_RESULTS) &&				\
	echo $(BGREEN) "NO DIFFERENCE IN STD AND FT FOUND" $(EOC)

ft_subject: $(FT_SUB_OBJECTS)
	@echo $(CYAN) "COMPILING PROGRAM '$@'" $(EOC)
	@$(CC) $(CFLAGS) $(SUB_SOURCES) -o $@

std_subject: $(STD_SUB_OBJECTS)
	@echo $(CYAN) "COMPILING PROGRAM '$@'" $(EOC)
	@$(CC) $(CFLAGS) $(STDFLAG)  $(SUB_SOURCES) -o $@

subject:
	@echo $(PURPLE) "\n////// 42 TEST ///////\n" $(EOC)
	@make ft_subject
	@make std_subject
	@echo $(PURPLE) "TO TEST, EXECUTE PROGRAMS WITH SEED AS ARG" $(EOC)

.PHONY: all clean fclean re vector map stack set subject
