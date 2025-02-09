SRC = src/main.c src/exit.c src/parsing.c
OBJ = $(SRC:.c=.o)
CC = cc #-fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
LIBFT = LIBFT/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@make -C LIBFT

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
