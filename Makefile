parsing_files = parsing.c check_validity.c map_processing.c parse_infos.c check_splited.c \
				parse_infos_utils.c check_validity_utils.c 
libft_files = ft_atoi.c ft_char_1.c ft_char_2.c ft_malloc.c ft_split.c \
			ft_str_1.c ft_str_2.c ft_str_3.c get_color.c get_next_line.c
execution_files = raycasting.c mlx_keys.c move_player.c mlx_init.c textures.c \
				wall_rendering.c wall_rendering_utils.c raycasting_utils1.c \
				raycasting_utils2.c

bonus_files = cursor_bonus.c main_bonus.c minimap_bonus.c

main_files = main.c

parsing_srcs = $(addprefix parsing/,$(parsing_files))
libft_srcs = $(addprefix libft/,$(libft_files))
execution_srcs = $(addprefix execution/,$(execution_files))
bonus_srcs = $(addprefix bonus/,$(bonus_files))
main_srcs = main.c

parsing_objects = $(addprefix object_files/,$(parsing_srcs:.c=.o))
libft_objects = $(addprefix object_files/,$(libft_srcs:.c=.o))
execution_objects = $(addprefix object_files/,$(execution_srcs:.c=.o))
main_object = $(addprefix object_files/main/,$(main_srcs:.c=.o))
bonus_objects = $(addprefix object_files/,$(bonus_srcs:.c=.o))

CFLAGS =  -Wall -Wextra -Werror -g -fsanitize=address
NAME = cub3d
LIBMLX = ../MLX42
HEADERS = -I$(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm -L"/Users/$(USER)/homebrew/Cellar/glfw/3.4/lib/"

all: $(NAME)

$(NAME): $(parsing_objects) $(libft_objects) $(execution_objects) $(main_object)
	@cc $(CFLAGS) $^ $(LIBS) $(HEADERS) -o $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

bonus: $(parsing_objects) $(libft_objects) $(execution_objects) $(bonus_objects)
	@cc $(CFLAGS) $^ $(LIBS) $(HEADERS) -o $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

object_files/bonus/%.o: bonus/%.c cub3d.h cub3d_bonus.h
	@mkdir -p object_files/bonus
	@cc $(CFLAGS) -c $< -I . -o $@ $(HEADERS)

object_files/parsing/%.o: parsing/%.c cub3d.h
	@mkdir -p object_files/parsing
	@cc $(CFLAGS) -c $< -I . -o $@ $(HEADERS)

object_files/libft/%.o: libft/%.c cub3d.h
	@mkdir -p object_files/libft
	@cc $(CFLAGS) -c $< -I . -o $@ $(HEADERS)

object_files/execution/%.o: execution/%.c cub3d.h
	@mkdir -p object_files/execution
	@cc $(CFLAGS) -c $< -I . -o $@ $(HEADERS)

object_files/main/%.o: main.c cub3d.h
	@mkdir -p object_files/main
	@cc $(CFLAGS) -c $< -I . -o $@ $(HEADERS)

clean:
	@rm -rf  object_files

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Cleaning Done"

re: fclean all