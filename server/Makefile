##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

CC			=	gcc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -lm
CPPFLAGS	=	-iquote ./include -iquote ./include/command/ 	\
				-iquote ./include/game/
FLAGS_DEBUG = 	-g

SRC			=	./src/main.c											\
				./src/server.c 											\
				./src/initialize_server.c           					\
				./src/run_server.c                  					\
				./src/insert_client_in_struct.c     					\
				./src/get_user_input.c									\
				./src/connect_graphical_client.c 						\
				./src/insert_command_in_queue.c 						\
				./src/check_command_queue.c 							\
				./src/close_client_socket.c         					\
				./src/player_connection.c 								\
				./src/check_players_food.c 								\
				./src/memory/free_program.c 							\
				./src/memory/free_game.c 								\
				./src/game/refill_map_time_unit.c						\
				./src/game/initialize_game.c 							\
				./src/game/initialize_teams.c 							\
				./src/game/initialize_resources.c 						\
				./src/game/print_game_informations.c 					\
				./src/arguments/init_arg_struct.c 						\
				./src/arguments/nb_clients_flag.c 						\
				./src/arguments/frequency_flag.c  						\
				./src/arguments/team_name_flag.c 						\
				./src/arguments/port_flag.c  							\
				./src/arguments/width_flag.c  							\
				./src/arguments/height_flag.c  							\
				./src/command/common/exit.c								\
				./src/command/command_ia/inventory.c 					\
				./src/command/command_ia/take_object.c					\
				./src/command/command_ia/set_object.c 					\
				./src/command/command_ia/move_forward.c 				\
				./src/command/command_ia/move_player.c 					\
				./src/command/command_ia/turn_left.c 					\
				./src/command/command_ia/turn_right.c 					\
				./src/command/command_ia/connect_nbr.c 					\
				./src/command/command_ia/fork_player.c 					\
				./src/command/command_ia/eject_from_tile.c 				\
				./src/command/command_ia/broadcast.c		 			\
				./src/command/command_ia/incantation.c 					\
				./src/command/command_ia/look/look.c		 			\
				./src/command/command_ia/look/get_on_land.c 			\
				./src/command/command_ia/commands_function_pointer.c	\
				./src/command/command_gui/msz.c							\
				./src/command/command_gui/mct.c							\
				./src/command/command_gui/bct.c							\
				./src/command/command_gui/pnw.c				 			\
				./src/command/command_gui/tna.c 						\
				./src/command/command_gui/plv.c 						\
				./src/command/command_gui/ppo.c 						\
				./src/command/command_gui/pin.c 						\
				./src/command/command_gui/pfk.c 		 				\
				./src/command/command_gui/pdr.c 		 				\
				./src/command/command_gui/pgt.c 		 				\
				./src/command/command_gui/pdi.c 		 				\
				./src/command/command_gui/enw.c							\
				./src/command/command_gui/ebo.c							\
				./src/command/command_gui/edi.c							\
				./src/command/command_gui/sgt.c							\
				./src/command/command_gui/sst.c							\
				./src/command/command_gui/pex.c							\
				./src/command/command_gui/commands_function_pointer.c	\
				./src/lib/is_positive_number.c 							\
				./src/lib/array_functions.c 							\
				./src/lib/word_array.c									\
				./src/lib/get_next_id.c 								\
				./src/lib/get_graphical_client.c 						\
				./src/lib/get_link.c									\
				./src/lib/get_player_direction.c 						\
				./src/lib/get_random_team_egg.c 						\
				./src/lib/count_team_slots.c							\
				./src/lib/is_on_same_tile.c 							\
				./src/lib/is_command_queue_full.c						\
				./src/lib/time_is_up.c									\
				./src/lib/get_resources.c								\
				./src/lib/set_resources.c								\
				./src/lib/is_a_resource.c								\
				./src/lib/get_tile_index.c								\
				./src/lib/calculate_time_unit.c

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
