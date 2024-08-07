/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:06:29 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:56:30 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"
# include "../execution/execution.h"

# define TO_EXECUT	1
# define NOT_EXEC	0

//extrajoin macros
# define FREE_FIRST	1
# define FREE_SECOND	2
# define FREE_ALL	3

typedef struct s_cmd	t_cmd;

/**cette structure pour garder le derniere exit code :)*****/
typedef struct s_global
{
	int		g_error_code;
	int		g_exit_code;
	char	**g_env;
}	t_global;

typedef struct s_xpnd
{
	int		i;
	char	*c;
	char	*m;
	char	*m_helper;
	char	dq_flag;
}	t_xpnd;

t_global				g_codes;

/******* lexer data ********/
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
		TOKEN_RDAMB
	}	e_type;
	char			*value;
	char			*word;
	char			*old_word;
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

/*****PARSING PART******/
//PARSING.C  
void			add_token(t_token **head, t_token *token);
t_cmd			*parsing_part(char *str);
void			qouted_str(char *str, unsigned int *i, char c);
char			*meta_data(char *str);
t_token			*to_tokeniser(t_data content);
void			open_file(t_token *token_r, t_token *token_w, t_cmd *cmd);

/*********TOKENISER :D*******/
//TOKENISER.C  && TOKENISER_1.C
void			lexer_advance(t_lexer *lexer);
t_token			*lexer_get_next_token(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
t_token			*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char			*lexer_get_current_char_as_string(char c);
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
void			ft_print_error(char *s1, char	*s2, char	*s3);
t_token			*skip_noeud(t_token *tokens);

/**free_function***/
//free_func.c
void			ft_free_list(t_token **token);
void			ft_free_content(t_data *content);
void			free_dp(char **av);
void			ft_free_cmds(t_cmd **cmds);

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
char			*expand(char *str, char c, char flag, char *word);
char			*check_word_in_env(char	*word);
void			extra_free(char *s1, char *s2, char flag);
void			herdoc_racine_utils(int i, t_token *temp);

//NEW LIBFT-FUNCTION
char			*ft_extrajoin(char *s1, char *s2, char flag);

/**removing qoutes step :)**/
//qouted_str.c
void			removing_qoutes_and_expand(t_token	*tokens);
char			*to_expand(char *str, int *i, char dq_flag);
int				ft_charset_chr(char	*s1, char	*charset);
void			expander(t_token	*t);
void			expander_utils(t_xpnd	*vars, t_token	*t);
void			expander_utils1(t_xpnd	*vars, t_token	*t);
char			change_flag(char dq_flag, char value);
void			expander_init(t_xpnd	*vars, t_token	*t);

/*remplissage de la liste des commande :D*/
//cmd_list.c
int				number_of_pipes(t_token *tokens);
t_cmd			*list_init(t_token *tokens);
void			remplissage_cmds(t_cmd *cmds, t_token *tokens);
int				check_access(t_token *tokens);
char			**my_args(char **av, char *to_add);
int				function(t_token **tkn, t_cmd **cmds);
void			r_c_u(t_token **tkn, t_cmd **cmds \
	, t_token **t_r, t_token **t_w);
void			remplissage_cmds(t_cmd *cmds, t_token *tokens);
void			expander_and_args(t_token **tokens, t_cmd **cmds);
void			expander_exit_and_remplissage(t_token **tokens, t_cmd **cmds);
void			take_file_name(t_token **tkn, t_token **t_r, t_token **t_w);
void			remplissage_args(t_cmd **cmds, t_token **tokens);
void			change_flag_and_skip_noeuds(t_cmd **cmds, t_token **tokens);
char			*exit_code_expander(char *str, int index, char *meta);

// normale split :D
//split_all.c
int				num_word(char *av);
char			**ft_freeall(char **tab, int i);
char			**allocationlpl(char **str, char *av, int n);
void			ft_remplissage(char **str, char *av, int n);
char			**split_all(char *av);
void			handler(int code);
int				check_error_code(t_data *content);

#endif