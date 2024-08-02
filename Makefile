parsing_files = parsing.c map_init.c
libft_files = ft_atoi.c ft_char_1.c ft_char_2.c ft_malloc.c ft_split.c ft_str_1.c ft_str_2.c ft_str_3.c get_color.c
execution_files = raycasting.c mlx_hooks.c move_player.c draw_2d.c mlx_init.c wall_rendering.c textures.c
main_files = main.c

parsing_srcs = $(addprefix parsing/,$(parsing_files))
libft_srcs = $(addprefix libft/,$(libft_files))
execution_srcs = $(addprefix execution/,$(execution_files))
main_srcs = main.c

parsing_objects = $(addprefix object_files/,$(parsing_srcs:.c=.o))
libft_objects = $(addprefix object_files/,$(libft_srcs:.c=.o))
execution_objects = $(addprefix object_files/,$(execution_srcs:.c=.o))
main_objects = $(addprefix object_files/main/,$(main_srcs:.c=.o))

# CFLAGS =  -g -fsanitize=address
NAME = cub3d
LIBMLX = ./MLX42
HEADERS = -I$(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm -L"/Users/$(USER)/homebrew/Cellar/glfw/3.4/lib/"

all: $(NAME)

$(NAME): $(parsing_objects) $(libft_objects) $(execution_objects) $(main_objects)
	@cc $(CFLAGS) $^ $(LIBS) $(HEADERS) -o $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Program Created"

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