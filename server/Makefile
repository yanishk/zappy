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

SRC			=	./src/main.c							\
				./src/server.c 							\
				./src/initialize_server.c           	\
				./src/run_server.c                  	\
				./src/insert_client_in_struct.c     	\
				./src/call_cmd_function.c				\
				./src/close_client_socket.c         	\
				./src/arguments/init_arg_struct.c 		\
				./src/arguments/flag_c.c 				\
				./src/arguments/flag_f.c  				\
				./src/arguments/flag_n.c 				\
				./src/arguments/flag_p.c  				\
				./src/arguments/flag_x.c  				\
				./src/arguments/flag_y.c  				\
				./src/command/exit.c					\
				./src/lib/array_functions.c 			\
				./src/lib/word_array.c

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
