NM = ft_nm

OTOOL = ft_otool

CC = gcc

FLAGS = -Werror -Wextra -Wall

SRC_NM_DIR = srcnm

SRC_OTOOL_DIR = srcotool

OBJ_NM_DIR = objnm

OBJ_OTOOL_DIR = objotool

PATH_NM_INCLUDES = includes/nm/

PATH_OTOOL_INCLUDES = includes/otool/

SRC_NM = main.c error_handling.c open_file.c map_file.c \
		handle_64.c symbol_64.c handle.c symbol.c list_create.c display.c \
		display_64.c list_create_64.c handle_fat.c swap.c list_len.c sort.c \
		sort_64.c display_arch.c env.c display_name.c compare.c \
		options_handling.c compare_64.c nope.c check_mmaped_data.c \
		check_mmaped_data_64.c free.c ft_putendl.c ft_putstr_fd.c ft_strjoin.c \
		ft_strcmp.c ft_toupper.c ft_tolower.c ft_strlen.c ft_putstr.c \
		ft_putchar.c ft_strchr.c ft_strcat.c ft_strcpy.c ft_strnew.c ft_bzero.c

SRC_OTOOL = main.c error_handling.c open_file.c map_file.c \
		handle_64.c section_64.c handle.c section.c list_create.c display.c \
		display_64.c list_create_64.c handle_fat.c swap.c \
		display_arch.c env.c display_name.c nope.c free.c print_data.c \
		check_mmaped_data.c check_mmaped_data_64.c ft_putendl.c ft_putstr.c \
		ft_putstr_fd.c ft_strcmp.c ft_strjoin.c ft_putchar.c ft_strlen.c \
		ft_strcat.c ft_strcpy.c ft_strnew.c ft_bzero.c

OBJ_NM = $(SRC_NM:%.c=objnm/%.o)

OBJ_OTOOL = $(SRC_OTOOL:%.c=objotool/%.o)

all: obj $(NM) $(OTOOL)

$(NM): $(OBJ_NM)
	$(CC) -o $@ $(OBJ_NM)

$(OBJ_NM_DIR)/%.o: $(SRC_NM_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_NM_INCLUDES)

$(OTOOL): $(OBJ_OTOOL)
	$(CC) -o $@ $(OBJ_OTOOL)

$(OBJ_OTOOL_DIR)/%.o: $(SRC_OTOOL_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(PATH_OTOOL_INCLUDES)

obj:
	mkdir -p $(OBJ_NM_DIR) $(OBJ_OTOOL_DIR)

clean:
		/bin/rm -f $(OBJ_NM) $(OBJ_OTOOL)

fclean: clean
		/bin/rm -f $(NM) $(OTOOL)

re: clean fclean all
