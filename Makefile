NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -O2 -fsanitize=address
LIBFT = libft/libft.a
LIBFT_PATH = ./libft
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft
MLX_PATH = ./mlx
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lbsd -lXext -lX11 -lm
SDL_PATH = ./sound
SDL_FLAGS = -L$(SDL_PATH)/SDL2/build/.libs -L$(SDL_PATH)/SDL2_mixer/build/.libs -lSDL2 -lSDL2_mixer -I./$(SDL_PATH)/SDL2/include -I./$(SDL_PATH)/SDL2_mixer/include
LDFLAGS = $(LIBFT_FLAGS) $(MLX_FLAGS)
INCLUDES = -I./includes -I$(LIBFT_PATH)/includes
RM = rm -rf
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m
CMD_TO_EXPORT = export LD_LIBRARY_PATH=$(pwd)/sound/SDL2/build/.libs:$(pwd)/sound/SDL2_mixer/build/.libs:$LD_LIBRARY_PATH

SRCS =	srcs/mandatory/main.c\
		srcs/mandatory/init.c\
		srcs/mandatory/debug/print.c\
		srcs/mandatory/free/free_game.c\
		srcs/mandatory/free/free_texture.c\
		srcs/mandatory/free/free_map.c\
		srcs/mandatory/game/character.c\
		srcs/mandatory/game/colors.c\
		srcs/mandatory/game/controls.c\
		srcs/mandatory/game/controls_utils.c\
		srcs/mandatory/game/image.c\
		srcs/mandatory/game/minimap.c\
		srcs/mandatory/game/mlx_functions.c\
		srcs/mandatory/game/mouse_cam.c\
		srcs/mandatory/game/moves.c\
		srcs/mandatory/game/raycasting_utils.c\
		srcs/mandatory/game/raycasting.c\
		srcs/mandatory/parsing/check_arg.c\
		srcs/mandatory/parsing/check_texture.c\
		srcs/mandatory/parsing/check_map.c\
		srcs/mandatory/parsing/check_walls.c\
		srcs/mandatory/parsing/parsing_utils.c\

SRCS_BONUS =	srcs/bonus/main.c\
				srcs/bonus/init.c\
				srcs/bonus/debug/print.c\
				srcs/bonus/free/free_game.c\
				srcs/bonus/free/free_texture.c\
				srcs/bonus/free/free_map.c\
				srcs/bonus/game/animation_utils.c\
				srcs/bonus/game/animation.c\
				srcs/bonus/game/character.c\
				srcs/bonus/game/colors.c\
				srcs/bonus/game/controls.c\
				srcs/bonus/game/doors.c\
				srcs/bonus/game/enemy.c\
				srcs/bonus/game/floor_ceil_raycast.c\
				srcs/bonus/game/image.c\
				srcs/bonus/game/launcher.c\
				srcs/bonus/game/minimap.c\
				srcs/bonus/game/mlx_functions.c\
				srcs/bonus/game/mouse_cam.c\
				srcs/bonus/game/moves.c\
				srcs/bonus/game/raycasting_utils.c\
				srcs/bonus/game/raycasting.c\
				srcs/bonus/game/render_enemy.c\
				srcs/bonus/game/sound.c\
				srcs/bonus/game/tab_images.c\
				srcs/bonus/game/transparency.c\
				srcs/bonus/game/utils.c\
				srcs/bonus/game/weapon.c\
				srcs/bonus/parsing/check_arg.c\
				srcs/bonus/parsing/check_texture.c\
				srcs/bonus/parsing/check_map.c\
				srcs/bonus/parsing/check_walls.c\
				srcs/bonus/parsing/parsing_utils.c\

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

TARGET = $(NAME)
ifeq ($(MAKECMDGOALS), bonus)
	TARGET = $(NAME_BONUS)
endif

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LDFLAGS) $(SDL_FLAGS) $(INCLUDES)
	@echo "\033[1A\033[2K\033[1A"
	@echo "│$(GREEN) Compilation of $(NAME_BONUS) completed ✓ $(NC)      │"
	@echo "└──────────────────────────────────────────────┘"
	@$(RM) errors.tmp

.c.o:
	@if [ "$(TARGET)" = "$(NAME)" ] && [ ! -f .mandatory ]; then \
		echo "$(NC)┌─────$(NAME)────────────────────────────────────┐"; \
		echo "│$(BLUE) Compiling $(NAME) in progress... ⌛$(NC)	       │"; \
		echo "\033[s└──────────────────────────────────────────────┘"; \
		touch .mandatory; \
	elif [ "$(TARGET)" = "$(NAME_BONUS)" ] && [ ! -f .bonus ]; then \
		echo "$(NC)┌─────$(NAME_BONUS)──────────────────────────────┐"; \
		echo "│$(BLUE) Compiling $(NAME_BONUS) in progress... ⌛$(NC)      │"; \
		echo "\033[s└──────────────────────────────────────────────┘"; \
		touch .bonus; \
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

bonus: $(NAME_BONUS)
	@$(RM) .bonus

mlx:
	@git clone https://github.com/42Paris/minilibx-linux mlx
	@cd mlx && make -s
	@echo "$(NC)┌─────mlx──────────────────────────────────────┐"
	@echo "│$(GREEN) Compilation of mlx completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"

sdl:
	@cd sound && git clone https://github.com/FizzyClap/sdl.git
	@cd sound && cd sdl && mv * ../ && rm -rf ../sdl

clean:
	@echo "$(NC)┌─────clean $(NAME)──────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) objects in progress... ⌛$(NC)     │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(OBJS) .mandatory $(OBJS_BONUS) .bonus
	@echo "│$(GREEN) Cleaning of $(NAME) objects completed ✓ $(NC)       │"
	@echo "└──────────────────────────────────────────────┘"

fclean: clean
	@echo "$(NC)┌─────fclean $(NAME)─────────────────────────────┐"
	@echo "│$(BLUE) Cleaning $(NAME) in progress... ⌛$(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@sleep 0.8
	@echo "\033[1A\033[2K\033[1A"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "│$(GREEN) Cleaning of $(NAME) completed ✓ $(NC)	       │"
	@echo "└──────────────────────────────────────────────┘"
	@make -s -C $(LIBFT_PATH) fclean

re: fclean all

rebonus: fclean bonus

norme:
	@echo "$(BLUE)Checking norminette in progress... ⌛"
	@if norminette srcs includes libft > norme.tmp;\
	then echo "$(GREEN)Norminette check passed successfully ✓";\
	else echo "$(RED)Norminette check failed.$(NC)";\
	cat norme.tmp | grep "Error";\
	fi
	@$(RM) norme.tmp

.PHONY: all bonus mlx sdl clean fclean re rebonus norme
