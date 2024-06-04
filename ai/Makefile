##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CXX			=	g++
RM			=	rm -f

CXXFLAGS	=	-Wall -Wextra -Werror -lasio
CPPFLAGS	=	-iquote ./include

SRC			=	./src/Main.cpp			\
				./src/Network.cpp		\
				./src/TeamAi.cpp		\
				./src/Ressources.cpp	\

OBJ			=	$(SRC:.cpp=.o)

NAME		=	zappy_ai

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
