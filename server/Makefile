##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra
CPPFLAGS	=	-iquote ./include

SRC			=	./src/main.c						\
				./src/server.c 						\
				./src/initialize_server.c           \
				./src/run_server.c                  \
				./src/insert_client_in_struct.c     \
				./src/close_client_socket.c         \

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
