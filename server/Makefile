##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CC			=	g++
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror
CPPFLAGS	=	-iquote ./include

SRC			=	./src/main.c		\

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_server

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
