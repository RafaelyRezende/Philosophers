CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibs

NAME = philo

OBJ_DIR = objects
BUILD_DIR = build
TARGET = $(BUILD_DIR)/$(NAME)

# ----------------- MAIN ------------------- #

MAIN = main.c
OBJ_MAIN = $(OBJ_DIR)/main.o

# ----------------- UTILS ------------------- #

DIR_UTILS = $(OBJ_DIR)/utils
SRC_UTILS = ft_putstr_fd.c \
			ft_atol_positive.c \
			parse_philos.c

OBJ_UTILS = $(SRC_UTILS:.c=.o)

PATH_OBJ_UTILS = $(patsubst %.c,$(DIR_UTILS)/%.o,$(SRC_UTILS))

# ----------------- RULES ------------------- #
all: $(TARGET)

$(TARGET): $(OBJ_MAIN) $(PATH_OBJ_UTILS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(OBJ_MAIN): $(MAIN) | $(OBJ_DIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/utils/%.o:utils/%.c | $(DIR_UTILS)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_UTILS): $(OBJ_DIR)
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

debug: CFLAGS += -g
debug: re

asan: CFLAGS += -g -fsanitize=thread
asan: re

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BUILD_DIR)

re: fclean all

.PHONY: all debug clean fclean re
