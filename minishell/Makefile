NAME = minishell

SRCS =  main.c \
		parsing/parsing.c \
		parsing/env_f.c \
		parsing/error_manangement.c \
		parsing/free_func.c \
		parsing/herdoc_func.c \
		parsing/qouted_str.c \
		parsing/qouted_str1.c \
		parsing/tokeniser.c \
		parsing/tokeniser_1.c \
		parsing/heredoc_1.c \
		parsing/heredoc_1_utils.c \
		parsing/heredoc_2.c \
		parsing/meta_data.c \
		parsing/split_all.c \
		parsing/cmd_list.c \
		parsing/cmd_list_utils.c \
		parsing/cmd_list_utils1.c \
		parsing/cmd_list_utils2.c \
		execution/execution.c \
		execution/exec_utils.c \
		execution/dup_wait_functions.c \
		execution/cmd_staff.c \
		execution/utils.c \
		builtins/echo.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \


OBJS = $(SRCS:.c=.o)

CC = @cc

CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/readline/include  -g -fsanitize=address


RM = rm -f

all:    $(NAME)

make_libft:
	@make -C libft/ 
	@printf "\n\033[1;33m**** libft Compiled Succesfully ! ****\033[0m\n"

$(NAME):	$(OBJS) make_libft
	@make -C libft clean
	$(CC) $(CFLAGS) -lreadline -L /Users/$(USER)/readline/lib $(OBJS) ./libft/libft.a -o $(NAME)
#	$(CC) $(CFLAGS) -lreadline -L /Users/$(USER)/goinfre/.brew/opt/readline/lib $(OBJS) ./libft/libft.a -o $(NAME) # -L /Users/$(USER)/goinfre/.brew/opt/readline/include 
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