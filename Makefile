##
## EPITECH PROJECT, 2024
## B-YEP-400-PAR-4-1-zappy-edward.lalande
## File description:
## Makefile
##

RM			=	rm -f

AI_BIN		=	zappy_ai
GUI_BIN		=	zappy_gui
SERVER_BIN	=	zappy_server

all:
	make -C ai
	make -C gui
	make -C server
	mv ./ai/zappy_ai .
	mv ./gui/zappy_gui .
	mv ./server/zappy_server .

zappygui:
	cd gui/; make re; mv ./zappy_gui ../; cd ../

tests_run:
	make tests_run -C ai

coverage:
	make coverage -C ai

clean:
	make clean -C ai
	make clean -C gui
	make clean -C server

fclean:
	make fclean -C ai
	make fclean -C gui
	make fclean -C server
	$(RM) $(AI_BIN)
	$(RM) $(GUI_BIN)
	$(RM) $(SERVER_BIN)

re:
	make re -C ai
	make re -C gui
	make re -C server
	mv ./ai/zappy_ai .
	mv ./gui/zappy_gui .
	mv ./server/zappy_server .

.PHONY: all clean fclean re
