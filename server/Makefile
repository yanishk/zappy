##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -lm
CPPFLAGS	=	-iquote ./include
FLAGS_DEBUG = 	-g

SRC			=	./src/main.c							\
				./src/server.c 							\
				./src/initialize_server.c           	\
				./src/run_server.c                  	\
				./src/insert_client_in_struct.c     	\
				./src/call_cmd_function.c				\
				./src/close_client_socket.c         	\
				./src/player_connection.c 				\
				./src/free_program.c 					\
				./src/map/initialize_map.c 				\
				./src/map/initialize_teams.c 			\
				./src/map/initialize_resources.c 		\
				./src/map/print_map_informations.c 		\
				./src/arguments/init_arg_struct.c 		\
				./src/arguments/nb_clients_flag.c 		\
				./src/arguments/frequency_flag.c  		\
				./src/arguments/team_name_flag.c 		\
				./src/arguments/port_flag.c  			\
				./src/arguments/width_flag.c  			\
				./src/arguments/height_flag.c  			\
				./src/command/exit.c					\
				./src/command/inventory.c 				\
				./src/command/take_command.c 			\
				./src/command/set_object.c	 			\
				./src/command/move_forward.c 			\
				./src/command/turn_left.c 				\
				./src/command/turn_right.c 				\
				./src/lib/array_functions.c 			\
				./src/lib/word_array.c					\
				./src/lib/get_player_byid.c

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_server

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
