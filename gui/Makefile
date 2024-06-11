##
## EPITECH PROJECT, 2024
## all_test_libray
## File description:
## Makefile
##

CXX		=	g++

SRC		=	main.cpp							\
			src/display/DisplayGame.cpp			\
			src/display/ParsesModelConfig.cpp	\
			src/display/Player.cpp				\
			src/display/AllPlayer.cpp			\
			src/client/Client.cpp				\
			src/client/Commands.cpp				\
			src/display/Item.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	zappy_gui

CPPFLAGS	=	-Wall -Wextra -iquote include -iquote src/display

LIBFLAGS	=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:	$(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
