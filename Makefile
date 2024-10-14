NAME = cub3D
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
LIBFT = libft/libft.a
LIBFT_PATH = ./libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
MLX_PATH = ./mlx
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lbsd -lXext -lX11 -lm
LDFLAGS = $(LIBFT_FLAGS) $(MLX_FLAGS)
INCLUDES = -I./includes -I$(LIBFT_PATH)/includes
RM = rm -rf
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m

SRCS =	srcs/main.c\
		srcs/init.c\
		srcs/parsing/check_arg.c\
		srcs/parsing/check_texture.c\
		srcs/parsing/check_map.c\
		srcs/parsing/check_walls.c\
		srcs/parsing/parsing_utils.c\
		srcs/free/free_game.c\
		srcs/free/free_texture.c\
		srcs/free/free_map.c\
		srcs/debug/print.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp

.c.o:
	@if [ ! -f .mandatory ]; then \
		echo "$(NC)┌─────$(NAME)────────────────────────────────────┐"; \
		echo "│$(BLUE) Compiling $(NAME) in progress... ⌛$(NC)	       │"; \
		echo "\033[s└──────────────────────────────────────────────┘"; \
		touch .mandatory; \
	fi
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES) 2>> errors.tmp || \
	{ \
		echo "\033[u\033[1A\033[2K│$(RED) Compilation of $(NAME) failed X$(NC)                │"; \
		echo "└──────────────────────────────────────────────┘"; \
		sed "s/error:/\x1b[1;31m&\x1b[0m/g" errors.tmp; \
		$(RM) errors.tmp; \
		exit 1; \
	}

all: $(NAME)
	@$(RM) .mandatory

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

mlx:
	@git clone https://github.com/42Paris/minilibx-linux mlx
	@cd mlx && make -s
	@echo "$(NC)┌─────mlx──────────────────────────────────────┐"
	@echo "│$(GREEN) Compilation of mlx completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"

clean:
	@echo "$(NC)┌─────clean $(NAME)──────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC)     │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(OBJS) .mandatory
	@echo "│$(GREEN) Cleaning of $(NAME) objects completed ✓ $(NC)       │"
	@echo "└──────────────────────────────────────────────┘"

fclean: clean
	@echo "$(NC)┌─────fclean $(NAME)─────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) in progress... ⌛$(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(NAME)
	@echo "│$(GREEN) Cleaning of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@make -s -C $(LIBFT_PATH) fclean

re: fclean all

norme:
	@echo "$(BLUE)Checking norminette in progress... ⌛"
	@if norminette srcs includes libft > norme.tmp;\
	then echo "$(GREEN)Norminette check passed successfully ✓";\
	else echo "$(RED)Norminette check failed.$(NC)";\
	cat norme.tmp | grep "Error";\
	fi
	@$(RM) norme.tmp

.PHONY: all mlx clean fclean re norme
