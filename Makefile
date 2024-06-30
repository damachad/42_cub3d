# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 15:25:24 by damachad          #+#    #+#              #
#    Updated: 2024/06/30 19:22:36 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COLORS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m
SBLINK 	= \033[5m

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COMMANDS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CC = cc
RM = rm -rf

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FLAGS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

CFLAGS 	= -Wall -Werror -Wextra -g -fsanitize=address
MK_FLAG = --no-print-directory
LFLAGS 	= -L ./libft -lft -L ./mlx -lmlx -lXext -lX11 -lm -lbsd

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ PATHS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

INC			= includes
SRC_DIR		= srcs
SRC_BNS_DIR	= srcs_bonus
OBJ_DIR		= objs
OBJ_BNS_DIR	= objs_bonus
MAP_DIR		= maps/valid/

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

NAME 		= cub3D
NAME_BNS	= cub3D_bonus
LIBFT		= libft/libft.a
MLX			= mlx/libmlx.a
FILES 		= main init clean draw_line textures raycasting \
			utils movement draw_wall raycast_utils move_utils \
			parser/parser parser/parse_color parser/parse_texture parser/parse_map \
			parser/check_map parser/set_map_limits parser/parse_map_utils
FILES_BNS	= $(FILES) minimap_bonus
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
OBJ_BNS 	= $(addprefix $(OBJ_BNS_DIR)/, $(addsuffix .o, $(FILES_BNS)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ ARGUMENTS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

MAP			= subject_map.cub

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "[$(GREEN)$(SBLINK)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_BNS_DIR)/%.o : $(SRC_BNS_DIR)/%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "[$(GREEN)objs directory created$(RESET)]"

$(OBJ_BNS_DIR):
	@mkdir -p $(OBJ_BNS_DIR)
	@echo "[$(GREEN)objs directory created$(RESET)]"

$(MLX):
	@echo "Compiling mlx..."
	@make $(MK_FLAG) -sC mlx > /dev/null 2>&1

$(LIBFT):
	@echo "Compiling libft..."
	@make $(MK_FLAG) -C ./libft > /dev/null

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_BNS_DIR)
	@make $(MK_FLAG) -C ./libft clean > /dev/null
	@make $(MK_FLAG) -C ./mlx clean > /dev/null
	@echo "[$(RED)objs removed$(RESET)]"

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) $(LIBFT)
	@echo "[$(RED)executables removed$(RESET)]"

re: fclean all

bonus: $(NAME_BNS)

$(NAME_BNS): $(OBJ_BNS_DIR) $(OBJ_BNS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LFLAGS) -o $(NAME_BNS) -I $(INC)
	@echo "[$(GREEN)$(SBLINK)$(NAME_BNS) created$(RESET)]"
	
test: $(NAME) $(OBJ)
	@./$(NAME) "$(MAP_DIR)/$(MAP)"

test_bonus: $(NAME_BNS) $(OBJ_BNS)
	@./$(NAME_BNS) "$(MAP_DIR)/$(MAP)"

gdb: $(NAME)
	@gdb --args ./$(NAME) "$(MAP_DIR)/$(MAP)"

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) "$(MAP_DIR)/$(MAP)"

valgrind_bonus: $(NAME_BNS)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME_BNS) "$(MAP_DIR)/$(MAP)"

.PHONY: all clean fclean re test bonus gdb valgrind test_bonus valgrind_bonus
