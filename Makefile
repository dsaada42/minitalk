NAME1 = minitalk_server
NAME2 = minitalk_client

CC = gcc

DENUG = -g3 -fsanitize=address

CFLAGS = -Wall -Werror -Wextra

SRC1 = ./server/main.c

SRC2 = ./client/main.c

OBJ1 = $(SRC1:.c=.o)

OBJ2 = $(SRC2:.c=.o)

$(NAME1): $(OBJ1)
	cd ./libft && make
	$(CC) $(OBJ1) ./libft/libft.a -o $(NAME1)

$(NAME2): $(OBJ2)
	$(CC) $(OBJ2) ./libft/libft.a -o $(NAME2)

all: $(NAME1) $(NAME2)

clean:
		rm -f *.o
		rm -f ./libft/*.o

fclean: clean
		rm -f $(NAME1)
		rm -f $(NAME2)

re: fclean all

.PHONY: all $(NAME1) $(NAME2) clean fclean re
