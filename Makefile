# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 18:12:06 by cbaillat          #+#    #+#              #
#    Updated: 2018/03/02 11:47:57 by briviere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in

CC		= gcc
# CFLAGS	= -Wall -Wextra -Werror
# CFLAGS	= -Wall -Wextra -fsanitize=address
CFLAGS	= -Wall -Wextra -Og -g3

# sources
VPATH	+= ./srcs:./srcs/parsing:./srcs/algorithm
VPATH	+= ./srcs/move_ants:./srcs/utilities
SRCS	=	lem_in.c \
			error_manager.c
SRCS	+=	algorithm.c \
			bfs.c \
			dfs.c \
			edmonds-karp.c \
			flow_control.c
SRCS	+=	check_map.c \
			get_ants.c \
			get_rooms.c \
			parse_room.c \
			parse_tube.c \
			parsing.c
SRCS	+=	mv_ants.c
SRCS	+=	map_utilities.c \
			path_utilities.c \
			print_map.c \
			string_utilities.c \
			room_utilities.c \
			way_utilities.c

# object files
OBJ_DIR		:=	./obj
OBJECTS		+= $(patsubst %,$(OBJ_DIR)/%,$(SRCS:.c=.o))
# objects dependencies
DEPS		= $(OBJECTS:.o:.d)
DEPS_FLAGS	= -MMD -MP

# includes
INC_DIR	:=	./includes
INC_DIR	+=	./libft/includes
IFLAGS	+= $(foreach d, $(INC_DIR), -I$d)

# libraries
LIB_DIR		:= ./libft
LIBS		:= ft
LIB_FLAGS	:= -L$(LIB_DIR) -l$(LIBS)

# echo output colours
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m
ORANGE	= \033[1;38m
NC		= \033[0m

.PHONY: all clean fclean re

all:
	@make -C $(LIB_DIR)/
	@make $(NAME)

$(NAME): $(OBJECTS)
	@echo "[Building ${RED}lem_in${NC}]"
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:%.c
	@echo "[Building ${RED}lem_in${NC} object: $@]"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(DEPS_FLAGS) $(IFLAGS) -o $@ -c $<

clean:
	@make clean -C $(LIB_DIR)/
	@echo "[Cleaning ${RED}lem_in${NC} objects]"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)/
	@echo "[Cleaning ${RED}lem_in${NC} binary]"
	@rm -rf $(NAME)

re: fclean all

order:
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++++++++++++///+++++++++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++++++++++++++++/:.   .-/++++++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++++++++++++/:-           -:/++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++/:.        .        .:/+++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++//-.        -:///:-        .-:/+++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++/:-        .://+++++++//-.        .:/++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++//:.        -:/+++++++++++++++/:.        .-//++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++/:-            .-//+++++++++++++++++//-.        -:/+++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++//:.        .-.        -:/+++++++++++++++++//:.        .://+++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++/:-.        -:/+++/:-        -:/++++++++++++++++++/:-.        -:/++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++/:.        .-//+++++++++/:-.       .:/++++++++++++++++++//:.        .://++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++//-.        .:/++++++++++++++++//-        .-//++++++++++++++++++/:-        .-:/+++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++/-        .-:/++++++++++++++++++//-.            -:/++++++++++++++++++//-.        -/+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:      .:/+++++++++++++++++++/:-        .-.        .://++++++++++++++++++/:.      -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    ./++++++++++++++++++//:.        -:/+++/:-        .-//++++++++++++++++++/-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -++++++++++++++++/:-        .-//+++++++++//-.        -://+++++++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -++++++++++++//:.        -:/+++++++++++++++++/:-        .://++++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++:        .-//+++++++++++++++++++++++//-.        :+++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++.     .:/+++++++++++++++++++++++++++++++/:.     ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++.    :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++.    :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++.    :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++.    :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/    ./++++++++++-    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/    ./+++++++++/.    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/    ./+++++/:-       -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/    ./++/-.          -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/     :-        ..    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     :+++++++++++++++++++++++++++++++++++++/            -:/+:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     .:/+++++++++++++++++++++++++++++++++/:.        .-//++++:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++        .-//+++++++++++++++++++++++++//-.        -://+++++++:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++            -:/+++++++++++++++++++/:.        .-//+++++++++++:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     -.        .:/++++++++++++//-.        .://++++++++++++++:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:    -+++++++++++     /+/:-.        -:/+++++/:-         -:/++++++++++++++++++:    -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++:     -:/++++++++     /++++//:.        .:/-.        .-//++++++++++++++++++/:-     -+++++++++\033[0m"
	@echo "\033[38;5;202m++++++++/        .://++++     /++++++++/:-               .:/++++++++++++++++++//:.        :+++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++//-.       .-:/+     /+++++++++++//-.       .-:/++++++++++++++++++//-.       .-:/++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++/:.        .     /+++++++++++++++/:. .://++++++++++++++++++/:-        .://+++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++/:-.          /++++++++++++++++++/++++++++++++++++++//:.        -:/+++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++//:.        -:/+++++++++++++++++++++++++++++++/:-        .-//++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++/:-        .://+++++++++++++++++++++++//:.        -:/++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++//-.       .-:/+++++++++++++++++//-.       .-:/+++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++/:.        .://+++++++++//:-        .:/+++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++++/:-        .-//+++//-.        -:/++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++++++++/:.        -:-        .-/++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++++/:-             -:/+++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++++++++/-.     .-/+++++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m+++++++++++++++++++++++++++++++++++++++++++++++/:-:/++++++++++++++++++++++++++++++++++++++++++++++++\033[0m"
	@echo "\033[38;5;202m++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\033[0m"

# include all dependicy files
-include $(DEPS)
