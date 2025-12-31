CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibs -pthread

NAME = philo_bonus

BUILD_DIR = build
TARGET = $(BUILD_DIR)/$(NAME)

# ----------------- MAIN ------------------- #

MAIN = main.c
OBJ_MAIN = $(OBJ_DIR)/main.o

# ----------------- UTILS ------------------- #

DIR_UTILS = $(OBJ_DIR)/utils
SRC_UTILS = ft_atol_positive.c \
			parse_philos.c \
			time_utils.c \
			initialization.c \
			simulation_utils.c \
			watcher.c \
			routine.c

OBJ_UTILS = $(SRC_UTILS:.c=.o)

PATH_OBJ_UTILS = $(patsubst %.c,$(DIR_UTILS)/%.o,$(SRC_UTILS))

# ----------------- RULES ------------------- #
all: $(TARGET)

unit: fclean
	$(CC) $(CFLAGS) -g unit.c -o unit

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

asan_thread: CFLAGS += -g -fsanitize=thread
asan_thread: re

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BUILD_DIR)
	@rm -rf unit

re: fclean all

.PHONY: all debug clean fclean re unit
