NAME = minishell

SRCS =  main.c \
		parsing/lexer.c \
		parsing/env_f.c \
		parsing/error_manangement.c \
		parsing/free_func.c \
		parsing/herdoc_func.c \

OBJS = $(SRCS:.c=.o)

CC = @cc

CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/readline/ -g #-fsanitize=address

RM = rm -f

all:    $(NAME)

make_libft:
	@make -C libft/ 
	@printf "\n\033[1;33m**** libft Compiled Succesfully ! ****\033[0m\n"

$(NAME):	$(OBJS) make_libft
	@make -C libft clean
	$(CC) $(CFLAGS) -lreadline -L /Users/$(USER)/readline $(OBJS) ./libft/libft.a -o $(NAME)
	@printf "\033[1;33m****Minishell compiled Succesfully ! ****\033[0m\n"
    
clean:
		$(RM) $(OBJS) 
		@make -C libft clean
		@printf "\033[1;36mObject Files Deleted !\033[0m\n"

fclean:    clean
		$(RM) $(NAME)
		@make -C libft fclean
		@printf "\033[1;36mProgram Deleted !\033[0m\n"

re:    fclean all
