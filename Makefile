LIBRARY = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC =	parsing/meta_data.c
		

OBJECT_FILE = $(SRC:%.c=%.o)

$(SO_LONG) : $(SO_LONG_OBJ) make_libft
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -L /usr/local/lib  $(SO_LONG_OBJ) ./libft/libft.a -o $(SO_LONG)
	@printf "\033[1;33m****so_long compiled Succesfully ! ****\033[0m\n"

all : $(LIBRARY) 

make_libft:
	@make -C libft/ 
	@printf "\n\033[1;33m**** libft Compiled Succesfully ! ****\033[0m\n"

clean :
	@rm -rf *.o libft/*.o
	@printf "\033[1;36mObject Files Deleted !\033[0m\n"

fclean : clean
	@rm  -rf $(LIBRARY) libft/libft.a	
	@printf "\033[1;36mProgram Deleted !\033[0m\n"

re : fclean all

$(LIBRARY) : $(OBJECT_FILE) make_libft
	$(CC) $(CFLAGS) -pthread $(OBJECT_FILE) -o $(LIBRARY)
	@printf "\033[1;33m****Minishell compiled Succesfully ! ****\033[0m\n"

