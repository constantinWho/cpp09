NAME = btc

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
FILES = main BitcoinExchange
OBJ = $(FILES:=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
