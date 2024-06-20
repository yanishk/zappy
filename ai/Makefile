##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CXX			=	g++
RM			=	rm -f

CXXFLAGS	=	-Wall -Wextra -Werror -lasio
CPPFLAGS	=	-pthread -iquote ./include
TTFLAGS		=	-lcriterion --coverage

SRC			=	./src/Main.cpp						\
				./src/Network.cpp					\
				./src/Ressources.cpp				\
				./src/CreateAI.cpp					\
				./src/GetAI.cpp						\
				./src/Run.cpp						\
				./src/AI/Queen.cpp					\
				./src/AI/Searcher.cpp				\
				./src/AI/Searcher/Broadcast.cpp		\
				./src/AI/Searcher/Mouvement.cpp		\
				./src/AI/Searcher/Priority.cpp		\
				./src/AI/Searcher/BackToQueen.cpp	\
				./src/AI/Quentin.cpp				\
				./src/AI/AAi.cpp					\

SRC_TEST	=	./src/Ressources.cpp				\
				./tests/TestsRessources.cpp			\

OBJ			=	$(SRC:.cpp=.o)

NAME		=	zappy_ai
NAME_TEST	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

tests_run: $(SRC_TEST)
	$(CXX) -o $(NAME_TEST) $(SRC_TEST) $(CPPFLAGS) $(TTFLAGS)
	./unit_tests

coverage: tests_run
	gcovr --exclude tests/*

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno *.gcda

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re
