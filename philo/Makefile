CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibs

NAME = philo

OBJ_DIR = objects

# ----------------- MAIN ------------------- #

MAIN = main.c
OBJ_MAIN = $(OBJ_DIR)/main.o

# ----------------- UTILS ------------------- #

DIR_UTILS = $(OBJ_DIR)/utils
SRC_UTILS = opt_main.c \
		standard_main.c \
		ft_putstr_fd.c \
		ft_atoi.c

OBJ_UTILS = $(SRC_UTILS:.c=.o)

PATH_OBJ_UTILS = $(patsubst %.c,$(DIR_UTILS)/%.o,$(SRC_UTILS))

# ----------------- RULES ------------------- #
all: $(NAME)

$(NAME): $(PATH_OBJ_UTILS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $^ -o build/$(NAME)

$(OBJ_MAIN): $(MAIN) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/utils/%.o:utils/%.c | $(DIR_UTILS)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_UTILS): $(OBJ_DIR)
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

debug: CFLAGS += -g
debug: re

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm build/$(NAME)

re: fclean all

.PHONY: all debug clean fclean re
