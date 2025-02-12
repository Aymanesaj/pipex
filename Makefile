SRC = main.c src/exit.c src/parsing.c src/pipex.c
SRC_BNS = main_bonus.c src/exit.c src/parsing.c src/pipex.c src/here_doc_bonus.c \
src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)
BONUS = .bonus
MANDATORY = .mandatory
CC = cc #-fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
LIBFT = LIBFT/libft.a

all: $(NAME)

$(NAME): $(MANDATORY) $(OBJ) $(LIBFT)
	@rm -f $(NAME) $(BONUS)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(MANDATORY) :
	@touch $(MANDATORY)

$(BONUS): $(OBJ_BNS) $(LIBFT)
	@rm -f $(NAME) $(MANDATORY)
	@touch $(BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LIBFT) -o $(NAME)

bonus: $(BONUS)

$(LIBFT):
	@make -C LIBFT

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BNS) $(MANDATORY) $(BONUS)
# @make clean -C LIBFT

fclean: clean
	@rm -f $(NAME)
# @make fclean -C LIBFT

re: fclean all

