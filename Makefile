SRC = main.c src/exit.c src/parsing.c src/pipex.c src/tokenize_args.c src/helpers.c src/helpers2.c src/ft_split.c \
src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c
SRC_BNS = main_bonus.c src/exit.c src/parsing.c src/pipex.c src/here_doc_bonus.c \
src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c src/tokenize_args.c \
src/helpers.c src/helpers2.c src/ft_split.c
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)
BONUS = .bonus
MANDATORY = .mandatory
CC = cc #-fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror
NAME = pipex

all: $(NAME)

$(NAME): $(MANDATORY) $(OBJ)
	@rm -f $(NAME) $(BONUS)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(MANDATORY) :
	@touch $(MANDATORY)

$(BONUS): $(OBJ_BNS)
	@rm -f $(NAME) $(MANDATORY)
	@touch $(BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BNS) -o $(NAME)

bonus: $(BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BNS) $(MANDATORY) $(BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

