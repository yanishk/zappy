##
## EPITECH PROJECT, 2024
## all_test_libray
## File description:
## Makefile
##

CXX		=	g++

SRC		=	main.cpp							\
			src/display/Game.cpp				\
			src/display/ParsesModelConfig.cpp	\
			src/display/player/Player.cpp		\
			src/display/player/AllPlayer.cpp	\
			src/client/Client.cpp				\
			src/client/Commands.cpp				\
			src/display/item/Item.cpp			\
			src/display/item/AllItem.cpp		\
			src/display/egg/Eggs.cpp			\
			src/display/egg/AllEggs.cpp			\
			src/display/island/Island.cpp		\
			src/display/island/AllIsland.cpp	\
			src/display/sky/Sky.cpp				\
			src/display/sea/Sea.cpp				\
			src/display/factory/Factory.cpp		\


OBJ		=	$(SRC:.cpp=.o)

NAME	=	zappy_gui

CPPFLAGS	=	-Wall -Wextra -Werror -iquote include -iquote src/display	\
				-iquote src/display/island -iquote src/display/egg			\
				-iquote src/display/player -iquote src/display/item 		\
				-iquote src/display/sky -iquote src/display/sea 			\
				-iquote src/display/player -iquote src/display/factory		\

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
