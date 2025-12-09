CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibs

NAME = philo

OBJ_DIR = objs

UTILS = utils/opt_main.c \
		utils/standard_main.c

OBJS_UTILS = $(UTILS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_UTILS)
	$(CC) $(CFLAGS) main.c $^ -o build/$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

debug: CFLAGS += -g
debug: re

clean:
	@rm -f $(OBJS_UTILS)

fclean: clean
	@rm build/$(NAME)

re: fclean all

.PHONY: all debug clean fclean re
