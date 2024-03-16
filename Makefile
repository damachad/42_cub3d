# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 15:25:24 by damachad          #+#    #+#              #
#    Updated: 2024/03/16 18:10:12 by arepsa           ###   ########.fr        #
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
OBJ_DIR		= objs
MAP_DIR		= maps/valid/

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

NAME 		= cub3D
LIBFT		= libft/libft.a
MLX			= mlx/libmlx.a
FILES 		= main init clean draw_line textures raycasting \
			utils movement debug_print minimap \
			parser/parser parser/parse_color parser/parse_texture parser/parse_map \
			parser/check_map
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ ARGUMENTS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

MAP			= colors.cub

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "[$(GREEN)$(SBLINK)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "[$(GREEN)objs directory created$(RESET)]"

$(MLX):
	@make $(MK_FLAG) -sC mlx
	@echo "[$(GREEN)libmlx.a created$(RESET)]"


$(LIBFT):
	@make $(MK_FLAG) -C ./libft

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BNS_DIR)
	@make $(MK_FLAG) -C ./libft clean
	@make $(MK_FLAG) -C ./mlx clean
	@echo "[$(RED)objs removed$(RESET)]"

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) $(LIBFT)
	@echo "[$(RED)executables removed$(RESET)]"

re: fclean all

test: $(NAME)
	@./$(NAME) "$(MAP_DIR)/$(MAP)"

gdb: $(NAME)
	@gdb --args ./$(NAME) "$(MAP_DIR)/$(MAP)"

.PHONY: all clean fclean re test
