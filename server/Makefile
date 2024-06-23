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
TTFLAGS 	= 	--coverage -lcriterion
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
				./src/memory/free_program.c 							\
				./src/memory/free_game.c 								\
				./src/game/refill_map_time_unit.c						\
				./src/game/initialize_game.c 							\
				./src/game/initialize_teams.c 							\
				./src/game/initialize_resources.c 						\
				./src/game/player_connection.c 							\
				./src/game/check_players_food.c 						\
				./src/game/win_condition.c								\
				./src/arguments/init_arg_struct.c 						\
				./src/arguments/nb_clients_flag.c 						\
				./src/arguments/frequency_flag.c  						\
				./src/arguments/team_name_flag.c 						\
				./src/arguments/port_flag.c  							\
				./src/arguments/width_flag.c  							\
				./src/arguments/height_flag.c  							\
				./src/arguments/immortal_flag.c 						\
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
				./src/command/command_ia/incantation/elevation.c 		\
				./src/command/command_ia/incantation/incantation.c 		\
				./src/command/command_ia/broadcast/broadcast.c 			\
				./src/command/command_ia/broadcast/calculate_all_dir.c	\
				./src/command/command_ia/broadcast/get_straight_line.c	\
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
				./src/command/command_gui/pbc.c							\
				./src/command/command_gui/seg.c							\
				./src/command/command_gui/smg.c							\
				./src/command/command_gui/pic.c							\
				./src/command/command_gui/pie.c							\
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
				./src/lib/print_tile_resources.c 						\
				./src/lib/get_tile_index.c								\
				./src/lib/calculate_time_unit.c							\
				./src/lib/has_backslash.c

SRC_TEST 	=   	./src/lib/calculate_time_unit.c							\
                    ./tests/lib/test_calculate_time_unit.c					\
					./src/lib/get_graphical_client.c						\
                    ./tests/lib/test_get_graphical_client.c					\
					./src/lib/get_next_id.c									\
                    ./tests/lib/test_get_next_id.c							\
					./src/lib/get_random_team_egg.c 						\
					./tests/lib/test_get_random_team_egg.c					\
					./src/lib/get_tile_index.c 								\
					./tests/lib/test_get_tile_index.c						\
					./src/lib/get_player_direction.c 						\
					./tests/lib/test_get_player_direction.c					\
					./src/lib/has_backslash.c 								\
					./tests/lib/test_has_backslash.c						\
					./src/lib/is_a_resource.c 								\
					./tests/lib/test_is_a_resource.c						\
					./src/lib/is_on_same_tile.c 							\
					./tests/lib/test_is_on_same_tile.c						\
					./src/lib/is_positive_number.c 							\
					./tests/lib/test_is_positive_number.c					\
					./src/lib/time_is_up.c 									\
					./tests/lib/test_time_is_up.c							\
					./src/lib/count_team_slots.c							\
					./tests/lib/test_count_team_slots.c 					\
					./src/lib/get_link.c									\
					./tests/lib/test_get_link.c 							\
					./src/lib/array_functions.c 							\
					./tests/lib/test_array_functions.c						\
					./src/lib/word_array.c 									\
					./tests/lib/test_word_array.c							\
					./src/lib/get_resources.c 								\
					./tests/lib/test_get_resources.c						\
					./src/lib/is_command_queue_full.c 						\
					./tests/lib/test_is_command_queue_full.c				\
					./src/arguments/frequency_flag.c						\
					./tests/arguments/test_frequency_flag.c 				\
					./src/arguments/height_flag.c							\
					./tests/arguments/test_height_flag.c 					\
					./src/arguments/width_flag.c							\
					./tests/arguments/test_width_flag.c 					\
					./src/arguments/port_flag.c								\
					./tests/arguments/test_port_flag.c 						\
					./src/arguments/nb_clients_flag.c						\
					./tests/arguments/test_nb_clients_flag.c 				\
					./src/arguments/immortal_flag.c							\
					./tests/arguments/test_immortal_flag.c 					\
					./src/arguments/team_name_flag.c						\
					./tests/arguments/test_team_name_flag.c 				\
					./src/arguments/init_arg_struct.c						\
					./tests/arguments/test_init_arg_struct.c 				\
					./src/command/command_gui/msz.c							\
					./tests/command_gui/test_msz.c							\
					./src/command/command_gui/bct.c							\
					./src/lib/print_tile_resources.c						\
					./tests/command_gui/test_bct.c							\
					./src/command/command_gui/mct.c							\
					./tests/command_gui/test_mct.c							\
					./src/command/command_gui/tna.c							\
					./tests/command_gui/test_tna.c							\
					./src/command/command_gui/pnw.c							\
					./tests/command_gui/test_pnw.c							\
					./src/command/command_gui/ppo.c							\
					./tests/command_gui/test_ppo.c							\
					./src/command/command_gui/plv.c							\
					./tests/command_gui/test_plv.c							\
					./src/command/command_gui/pin.c							\
					./tests/command_gui/test_pin.c							\
					./src/command/command_gui/pex.c							\
					./tests/command_gui/test_pex.c							\
					./src/command/command_gui/pbc.c							\
					./tests/command_gui/test_pbc.c							\
					./src/command/command_gui/pic.c							\
					./src/command/command_ia/incantation/elevation.c		\
					./tests/command_gui/test_pic.c							\
					./src/command/command_gui/pie.c							\
					./tests/command_gui/test_pie.c							\
					./src/command/command_gui/pfk.c 						\
					./tests/command_gui/test_pfk.c							\
					./src/command/command_gui/pdr.c 						\
					./tests/command_gui/test_pdr.c							\
					./src/command/command_gui/pgt.c 						\
					./tests/command_gui/test_pgt.c							\
					./src/command/command_gui/pdi.c 						\
					./tests/command_gui/test_pdi.c							\
					./src/command/command_gui/enw.c 						\
					./tests/command_gui/test_enw.c							\
					./src/command/command_gui/ebo.c 						\
					./tests/command_gui/test_ebo.c							\
					./src/command/command_gui/edi.c 						\
					./tests/command_gui/test_edi.c							\
					./src/command/command_gui/sgt.c 						\
					./tests/command_gui/test_sgt.c							\
					./src/command/command_gui/sst.c 						\
					./tests/command_gui/test_sst.c							\
					./src/command/command_gui/seg.c 						\
					./tests/command_gui/test_seg.c							\
					./src/command/command_gui/smg.c 						\
					./tests/command_gui/test_smg.c							\
					./src/command/command_ia/turn_left.c 					\
					./tests/command_ia/test_turn_left.c						\
					./src/command/command_ia/turn_right.c 					\
					./tests/command_ia/test_turn_right.c					\
					./src/command/command_ia/look/look.c 					\
					./src/command/command_ia/look/get_on_land.c 			\
					./tests/command_ia/test_look.c							\
					./src/command/command_ia/inventory.c 					\
					./tests/command_ia/test_inventory.c						\
					./src/command/command_ia/broadcast/broadcast.c 			\
					./src/command/command_ia/broadcast/calculate_all_dir.c 	\
					./src/command/command_ia/broadcast/get_straight_line.c 	\
					./tests/command_ia/test_broadcast.c 					\
					./src/command/command_ia/connect_nbr.c 					\
					./tests/command_ia/test_connect_nbr.c					\
					./src/command/command_ia/fork_player.c 					\
					./tests/command_ia/test_fork.c							\
					./src/command/command_ia/eject_from_tile.c 				\
					./src/command/command_ia/move_player.c					\
					./src/memory/free_game.c								\
					./tests/command_ia/test_eject.c 						\
					./src/command/command_ia/take_object.c 					\
					./src/lib/set_resources.c								\
					./tests/command_ia/test_take_object.c 					\
					./src/command/command_ia/set_object.c 					\
					./tests/command_ia/test_set_object.c

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_server
NAME_TEST	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

tests_run:
	$(CC) -o $(NAME_TEST) $(SRC_TEST) $(TTFLAGS) $(CFLAGS) $(CPPFLAGS)
	./$(NAME_TEST)

coverage: tests_run
	gcovr --exclude tests/

tests_clean:
		$(RM) $(NAME_TEST)
		$(RM) *.gcno *.gcda

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno *.gcda

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re
