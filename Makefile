# Variables declarations

NAME = cub3D

BUILD = unitTests/build

FLAGS = -Wall -Wextra -Werror -g

CC = cc

SRC = check_arguments.c  cub3d.c hooks.c mlx_utils.c error_handling.c readmap.c\
	  utils.c array_utils.c map_validation.c flood_fill.c render_functions.c player_movement.c\
	  raycaster.c texture_functions.c

SRCS = $(addprefix src/, $(SRC))

OBJS = $(SRCS:.c=.o)

RM = rm -rf

INCLUDES = -I./includes

# Change MLX to match OS 

ifeq ($(shell uname), Linux)
LIBS	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz includes/libft/libft.a
MLX_O	= -I/usr/include -O3
MLX_DIR	= mlx_linux
else
LIBS	= -Lmlx -lmlx -framework OpenGL -framework AppKit includes/libft/libft.a
MLX_O	= -Imlx
MLX_DIR	= mlx
endif

MLX = ./$(MLX_DIR)/libmlx.a

LIBFT = ./includes/libft/libft.a

# Compile Rules 

%.o: %.c
			@${CC} -O0 -c ${FLAGS} ${INCLUDES} ${MLX_O} $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLX)	
			$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)
			@echo "cub3d created."

$(MLX):
			make -C ./${MLX_DIR}

$(LIBFT):
			make -C includes/libft

clean:
			@make -C ./includes/libft clean
			@make -C ./$(MLX_DIR) clean
			@${RM} ${NAME}.dSYM $(OBJS)
			@echo "cub3d cleaned."

fclean:		clean
			@make -C ./includes/libft fclean
			@$(RM) $(NAME)
			@$(RM) ./$(BUILD)
			@echo "cub3d all cleaned."

re:			fclean all

map1:		
			make all
			valgrind --suppressions=mlx.supp --leak-check=full --show-leak-kinds=all ./cub3D maps/map1.cub

map2:		
			amke all
			valgrind --suppressions=mlx.supp --leak-check=full --show-leak-kinds=all ./cub3D maps/map2.cub

.PHONY:		all clean fclean re map1 map2
