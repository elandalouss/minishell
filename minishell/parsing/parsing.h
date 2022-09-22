/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:06:29 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 08:30:43 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"


#define	TO_EXECUT	1
#define	NOT_EXEC 	0

typedef	struct	s_cmd
{
	char			flag;//
	int				index;//
	int 			pipe[2];
	int				in_file_fd;//
	int				out_file_fd;//
	char 			**av;//
	char 			*cmd_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

//extrajoin macros
#define FREE_FIRST	1
#define FREE_SECOND	2
#define FREE_ALL	3

/**cette structure pour garder le derniere exit code :)*****/
typedef struct s_global
{
	int		g_error_code;
	int		g_exit_code;
	char	**g_env;
}	t_global;

/******* lexer data********/
typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
	char			*word;
	char			c0;
}	t_lexer;

/*****  token data :)*****/
typedef struct s_token
{
	enum
	{
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_READ,
		TOKEN_DREAD,
		TOKEN_WRITE,
		TOKEN_DWRITE,
		TOKEN_RDIR_AMBIGU
	}	e_type;
	char			*value;// in meta
	char			*word;// original
	char			*old_word;// new word after expanding the original
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/****** ma valise :)*******/
typedef struct s_data
{
	char	*input;
	char	*meta_v;
	t_token	*tokens;
}	t_data;


t_global		g_codes;

/*****LEXER PART******/
//LEXER.C
void 			add_token(t_token **head, t_token *token);
t_token			*lexer_get_next_token(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
t_cmd			*parsing_part(char *str);
void			qouted_str(char *str, unsigned int *i, char c);
char			*meta_data(char *str);
t_token			*to_tokeniser(t_data content);
void			lexer_advance(t_lexer *lexer);
t_token			*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char			*lexer_get_current_char_as_string(char  c);
t_token			*init_token(int type, char *value, char *word);
t_token			*lexer_collect_id(t_lexer	*lexer);
t_token			*lexer_collect_redirection(t_lexer *lexer, int type);
t_lexer			*init_lexer(char *contents, char *meta_v);


/*****ERROR MANANGEMENT PART*************/
//erro_management.c
void			error_management(t_data *content);
void			redirection_errors(t_token *token);
void			pipe_errors(t_token *token);
void			word_error(t_token *token);

/******MY_envirement :D*********/
//env_f.c
void			my_env(char **env, char *to_add);
unsigned int	env_len(char **env);
t_token			*remove_list(t_token *to_remove, t_token *head);

/**free_function***/
//free_func.c
void			ft_free_list(t_token **token);
void			ft_free_content(t_data *content);

/*******HERE_DOC :D*********/
//herdoc_func
int				position(char *str, char c);
unsigned int	check_number(t_token *tokens);
char			*get_file_name(int i);
void			remplissage_doc(int flag, int fd, char *limiter);
void			preparation_docv(int expand_flag, char	*limiter, int i);
char			check_expand(char *name, char *meta, t_token *token);
void			open_herdoc(t_token *token);
void			open_herdoc(t_token *token);
void			here_docs(t_token *tokens);
void			heredoc_racine(t_token	*tokens);
char			*expand(char	*str, char c, char flag);
char			*check_word_in_env(char	*word);
void			handler(int code);


//NEW LIBFT-FUNCTION
char			*ft_extrajoin(char *s1, char *s2, char flag);

/**removing qoutes step :)**/

void	removing_qoutes_and_expand(t_token	*tokens);
// void    qouted_and_expand(t_token *tokens);
// void    remove_qoutes(t_token *tokens);
//char	*remove_qt(char	*meta, char	*word);
//char	*qt(char	*word, int i);
#endif