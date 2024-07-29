##
## EPITECH PROJECT, 2024
## B-PDG-300-MAR-3-1-PDGRUSH3-vincent.montero-fontaine
## File description:
## Makefile
##

EXEC = zappy_server

EXEC_AI = zappy_ai

EXEC_UI	= zappy_gui

LIB = -lm

UNIT_TEST =		tests/unit_tests

SRC		=	src/server/server.c 					\
			src/server/my_utils.c 					\
			src/server/str_to_word_array.c 			\
			src/server/arr_func.c 					\
			src/server/read_file.c 					\
			src/server/bind_and_listen.c 			\
			src/server/handle_connexion.c 			\
			src/server/handle_client.c 				\
			src/server/handle_command.c 			\
			src/server/index.c 						\
			src/server/quit.c 						\
			src/server/file.c 						\
			src/server/accept_connect.c 			\
			src/server/msg.c 						\
			src/server/login.c 						\
			src/server/tokenize.c 					\
			src/server/verify_quoted.c 				\
			src/server/print_sd_info.c 				\
			src/server/set_socket.c 				\
			src/server/trim_input.c 				\
			src/server/is_whitespace.c 				\
			src/server/users.c 						\
			src/server/uuid.c 						\
			src/server/process_login.c 				\
			src/server/send_all.c 					\
			src/server/help.c 						\
			src/server/array_to_string.c 			\
			src/server/quotes.c 					\
			src/server/cmd_user.c 					\
			src/server/messages.c 					\
			src/server/create.c 					\
			src/server/arr.c 						\
			src/server/process_arguments.c 			\
			src/server/map.c						\
			src/server/num.c						\
			src/server/queue.c						\
			src/server/parse_cmd.c					\
			src/server/fill_map.c					\
			src/server/assign_team.c				\
			src/server/copy_map.c					\
			src/server/commands/msz.c				\
			src/server/commands/bct.c				\
			src/server/commands/mct.c				\
			src/server/commands/tna.c				\
			src/server/commands/sgt.c				\
			src/server/commands/sst.c				\
			src/server/commands/ppo.c				\
			src/server/commands/plv.c				\
			src/server/commands/pin.c				\
			src/server/commands/utils.c				\
			src/server/commands/broadcast.c			\
			src/server/commands/forward.c 			\
			src/server/commands/smg.c 				\
			src/server/commands/inventory.c 		\
			src/server/commands/take.c				\
			src/server/commands/set.c				\
			src/server/commands/turn.c 				\
			src/server/commands/look.c				\
			src/server/commands/loop_look.c			\
			src/server/commands/eject.c 			\
			src/server/commands/connect_nbr.c		\
			src/server/commands/fork.c 				\
			src/server/commands/debug.c 			\
			src/server/commands/ppa.c 				\
			src/server/commands/epa.c 				\
			src/server/incantation/incantation.c 	\
			src/server/incantation/prerequisites.c 	\
			src/server/inventory/handle_items.c		\
			src/server/inventory/utils.c			\
			src/server/teams/eggs.c 				\
			src/server/teams/eggs_utils.c 			\
			src/server/random.c						\
			src/server/conds.c						\

SRC_AI	=	src/ai/bin/ref_ai_bin

GUI_FLAG = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_GUI	=	src/ui/main.cpp\
			src/ui/operators.cpp\
			src/ui/classes/board/Board.cpp\
			src/ui/classes/camera/Camera.cpp\
			src/ui/classes/cube/Cube.cpp\
			src/ui/classes/models/Model.cpp\
			src/ui/classes/window/Window.cpp\
			src/ui/server/ServerConnection.cpp\
			src/ui/classes/items/R1.cpp\
			src/ui/classes/items/R2.cpp\
			src/ui/classes/items/R3.cpp\
			src/ui/classes/items/R4.cpp\
			src/ui/classes/items/R5.cpp\
			src/ui/classes/items/R6.cpp\
			src/ui/classes/items/R7.cpp\
			src/ui/classes/Case/Case.cpp\
			src/ui/classes/board/Item.cpp 			\
			src/ui/classes/board/Inventory.cpp 		\
			src/ui/classes/board/Team.cpp 			\
			src/ui/classes/board/Player.cpp			\
			src/ui/classes/board/Egg.cpp 			\
			src/ui/classes/board/Incantation.cpp	\
			src/ui/classes/board/Core.cpp 			\
			src/ui/classes/Clock.cpp				\
			src/ui/classes/cmdParsing.cpp 			\
			src/ui/server/connection.cpp			\
			src/ui/classes/menu/MenuCase.cpp\
			src/ui/classes/menu/MenuPlayer.cpp\

GCC_PARAM = -W -Wall -Wextra -g3 -g

LAST_FLAG = -ansi -pedantic -Werror

FLAG_VAL = --tool=memcheck --leak-check=yes --show-reachable=yes

FLAG_VAL2 = --leak-check=full --show-leak-kinds=all -s

GRAY := \033[1;30m
PURPLE := \033[0;34m
BLUE := \033[1;34m
GREEN := \033[1;32m
CYAN := \033[1;36m
RED := \033[1;31m
PINK := \033[1;35m
BROWN := \033[0;33m
YELLOW := \033[1;33m
WHITE := \033[1;37m
NC := \033[0m

all: $(EXEC) $(EXEC_AI) $(EXEC_UI)

$(EXEC_AI):
	@echo -e "$(BLUE)COMPILING AI CLIENT!$(NC)"
	@chmod 777 $(SRC_AI)
	@cp $(SRC_AI) .
	@mv ./ref_ai_bin $(EXEC_AI)
	@echo -e "$(GREEN)COMPILATION IS DONE!$(NC)"

$(EXEC): $(SRC)
	@echo -e "$(BLUE)COMPILING SERVER!$(NC)"
	@gcc $(GCC_PARAM) -o $@ $^ $(LIB)
	@echo -e "$(GREEN)COMPILATION IS DONE!$(NC)"

spe: $(SRC)
	@echo -e "$(RED)All flag ...$(NC)"
	@gcc $(GCC_PARAM) $(LAST_FLAG) -o $(EXEC) $^

clean:
	@echo -e "$(GRAY)Cleaning ...$(NC)"
	@rm -f $(EXEC) $(EXEC_AI) $(EXEC_UI)

fclean: clean
	@find . -type f \( -name "*~" -o \( -name "*#" -a -name "#*" \) \) -delete
	@find . -type f \( -name "#*#" -o -name "*~" \) -delete
	@find . -type f \( -name "*.gcno" -o -name "*.gcda" \) -delete
	@find . -type f \( -name "*.o" -o -name "vgcore.*" \) -delete
	@rm -f coding-style-reports.log

style: fclean
	@echo -e "$(PINK)Coding style$(NC)"
	@coding-style . .
	cat coding-style-reports.log

exec:  $(EXEC)
	clear
	@./$(EXEC)

valgrind: all
	@echo -e "$(CYAN)Valgrind$(NC)"
	@echo -e "$(YELLOW)"
	valgrind $(FLAG_VAL) $(FLAG_VAL2) ./$(EXEC) -p 4242 -x 20 -y 25

re:	fclean all

$(EXEC_UI): $(SRC_GUI)
	@echo -e "$(BLUE)COMPILING USER INTERFACE!$(NC)"
	@g++ $(SRC_GUI) -o $(EXEC_UI) $(GUI_FLAG)
	@echo -e "$(GREEN)COMPILATION IS DONE!$(NC)"

.PHONY: clean fclean spe style valgrind re
