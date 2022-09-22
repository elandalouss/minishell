/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:09:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 08:32:42 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	redirection(t_token *tokens)
// {
// 	int	in_filefd;
// 	int	out_filefd;

// 	while (tokens)
// 	{
// 		if (tokens->e_type >= TOKEN_READ)
// 		{
// 			if (tokens->next->e_type == TOKEN_RDIR_AMBIGU)
// 				;
// 		}
// 		tokens = tokens->next;
// 	}
// }

int	number_of_pipes(t_token *tokens)
{
	t_token	*temp;
	int		i;
	
	temp = tokens;
	i = 0;
	while (temp)
	{
		if (temp->e_type == TOKEN_PIPE)
			i++;		
		temp = temp->next;	
	}
	return (i);
}

t_cmd	*list_init(t_token *tokens)
{
	int	i;
	t_cmd	*head;
	t_cmd	*temp;

	head = NULL;
	i = number_of_pipes(tokens);
	i++;
	while (i > 0)
	{
		temp = ft_calloc(1, sizeof(t_cmd));
		temp->index = i - 1;
		temp->flag = TO_EXECUT;
		temp->prev = NULL;
		temp->next = head;
		temp->out_file_fd = -2;
		temp->in_file_fd = -2;
		if (temp->next == NULL)//
			temp->out_file_fd = 1;//
		head = temp;
		i--;
	}
	head->in_file_fd = 0;//
	return (head);
}

// t_token	*part(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->e_type == TOKEN_PIPE)
// 			return (tokens);
// 		tokens = tokens->next;
// 	}
// 	return (tokens);
// }

// t_cmd	*remplissage_fd(t_token **tokens, t_token *temp, t_cmd *cmds)
// {
// 	*tokens = temp;
// 	while (*tokens)
// 	{
// 		if ((*tokens)->e_type =>)
// 		*tokens = (*tokens)->prev;
// 	}
// }

// void	remplire_fd(t_cmd	*cmds, t_token **tokens)
// {
// 	t_token	*temp;
// 	int		i;
	
// 	temp = *tokens;
// 	i = 0;
// 	while(temp)
// 	{
// 		if (temp->e_type == TOKEN_READ || temp->e_type == TOKEN_DREAD)
// 		{
// 			i = access(temp->next->word, F_OK);
// 			if (i != -1)			
// 				i = access(temp->next->word, R_OK);
// 		}
// 		else if (temp->e_type == TOKEN_WRITE || temp->e_type == TOKEN_DWRITE)
// 			i = access(temp->next->word, W_OK);
// 		if (i == -1)
// 		{
// 			cmds->flag = NOT_EXEC;
// 			break;
// 		}
// 		temp = temp->next;
// 	}
// }

// //fuck u;

int		check_access(t_token	*tokens)
{
	int i;

	i = 0;
	if (tokens->next->e_type == TOKEN_RDIR_AMBIGU)
	{
		printf("minishell: %s: ambiguous redirect\n", tokens->next->old_word);
		return (-1);
	}
	if (tokens->e_type == TOKEN_READ || tokens->e_type == TOKEN_DREAD)
	{
		i = access(tokens->next->word, F_OK);
		if (i != -1)			
			i = access(tokens->next->word, R_OK);
	}
	else if (tokens->e_type == TOKEN_WRITE || tokens->e_type == TOKEN_DWRITE)
		i = access(tokens->next->word, W_OK);
	// ambigu red :D
	return (i);
}

t_token	*skip_noeud(t_token *tokens)
{
	while(tokens)
	{
		if (tokens->e_type == TOKEN_PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (tokens);
}

void	open_file(t_token *token_r, t_token *token_w, t_cmd *cmd)
{
	if (token_r)
		cmd->in_file_fd = open(token_r->next->word, O_RDONLY);
	if (token_w && token_w->e_type == TOKEN_WRITE)
		cmd->out_file_fd = open(token_w->next->word, O_WRONLY | O_CREAT | O_TRUNC);
	else if (token_w && token_w->e_type == TOKEN_DWRITE)
		cmd->out_file_fd = open(token_w->next->word, O_WRONLY | O_CREAT | O_APPEND);
	if (cmd->out_file_fd == -1 || cmd->in_file_fd == -1)
	{
		ft_putstr_fd("minishell: faild to open red irection files\n", 2);
		g_codes.g_exit_code = 1;
		g_codes.g_error_code = 1;
	}
}

char	**my_args(char **av, char *to_add)
{
	unsigned int	len;
	char			**new;
	int				i;
	
	printf("%s\n", to_add);
	len = 0;
	if (av)
		len = env_len(av);
	len++;
	new = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (av && av[i])
	{
		new[i] = av[i];
		i++;
	}
	new[i++] = ft_strdup(to_add);
	new[i] = NULL;
	free(av);
	return (new);
}

int	num_word(char *av)
{
	int	i;
	int	n;
	
	i = 0;
	n = 0;
	while (av[i])
	{
		if (av[i] != ' ' && av[i] != '\t' && av[i] != '\n')
		{
			n++;
			while (av[i] && av[i] != ' ' && av[i] != '\t' && av[i] != '\n')
				i++;
		}
		else
			i++;
	}
	return (n);
}

char	**ft_freeall(char **tab, int i)
{
	int	a;

	a = 0;
	while (a <= i)
	{
		free(tab[a]);
		a++;
	}
	free(tab);
	return (NULL);
}

char 	**allocationlpl(char **str, char *av, int n)
{
	int i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (i < n && av[j])
	{
		len = 0;
		while (av[j] && av[j] != ' ' && av[j] != '\t' && av[j] != '\n')
		{
			len++;
			j++;
		}
		if (len)
		{
			str[i] = ft_calloc(len + 1, 1);
			if (!str[i])
				return (ft_freeall(str, i));
			i++;
		}
		j++;
	}
	str[i] = NULL;
	return (str);
}

void	ft_remplissage(char **str, char *av, int	n)
{
	int	l;
	int	c;
	int	cc;

	l = 0;
	c = 0;
	while (l < n && av[c])
	{
		cc = 0;
		if (av[c] != ' ' && av[c] != '\t' && av[c] != '\n')
		{
			while (av[c] && av[c] != ' ' && av[c] != '\t' && av[c] != '\n')
			{
				str[l][cc] = av[c];
				cc++;
				c++;
			}
			str[l][cc] = '\0';
			l++;
		}
		else
			c++;
	}
}

char 	**split_all(char *av)
{
	char	**str;
	int		n;
	
	if (!av)
		return (NULL);
	n = num_word(av);
	str = ft_calloc(sizeof(char *), n + 1);
	if (!str)
		return (NULL);
	str = allocationlpl(str, av, n);
	if (!str)
		return (NULL);
	ft_remplissage(str, av, n);
	return (str);
}


void	remplissage_cmds(t_cmd *cmds, t_token *tokens)
{
	t_token		*temp_r;
	t_token		*temp_w;
	char		**tmp;

	while (cmds)
	{
		// printf("ikhan\n");
		//printf("%p temp word\n", temp);
		//cmds->in_file_fd = 0;
		//cmds->out_file_fd = 1;
		temp_r = NULL;
		temp_w = NULL;
		while (tokens)
		{
			//printf("hello tokens\n");
			if (tokens->word == NULL)
			{
				tokens = tokens->next;
				continue ;
			}
			if (tokens->e_type >= TOKEN_READ && tokens->e_type < TOKEN_RDIR_AMBIGU)
			{
				if (check_access(tokens) == -1)
					cmds->flag = NOT_EXEC; //REGLER TOKENS :)
				else
				{
					if (tokens->e_type == TOKEN_DREAD || tokens->e_type == TOKEN_READ)
						temp_r = tokens;
					if (tokens->e_type == TOKEN_DWRITE || tokens->e_type == TOKEN_WRITE)
						temp_w = tokens;
				}
				tokens = tokens->next;
			}
			else if (tokens->e_type == TOKEN_WORD)
				cmds->av = my_args(cmds->av, tokens->word);//regler av :)
			else if (tokens->e_type == TOKEN_RDIR_AMBIGU)
			{
				tmp = split_all(tokens->word);
				while(*tmp)
				{
					cmds->av = my_args(cmds->av, *tmp);
					free(*tmp);
					tmp++;
				}
			}
			else
			{
				tokens = tokens->next;
				break ;
			}
			tokens = tokens->next;
		}
		if (cmds->flag == TO_EXECUT && (temp_r || temp_w))
		{
			open_file(temp_r, temp_w, cmds);
		}
		if (g_codes.g_error_code != 0)
			return ;
		cmds = cmds->next;
	}
}

/*la fonction racine de tout les fonction de parsing part :)  */
t_cmd	*parsing_part(char *str)
{
	t_data	content;
	t_cmd	*cmds_line;

	
	content.input = ft_strdup(str); // strdup(str)  //allocation par strdup
	content.meta_v = meta_data(str);
	//int i = 0;
	// while(g_codes.g_env[i])
	// {
	// 	printf("%s\n", g_codes.g_env[i]);
	// 	i++;
	// }
	//(void)env;
	// printf("|%s|\n", content.input);
	// printf("|%s|\n", content.meta_v);
	content.tokens = to_tokeniser(content);
	if (content.tokens == NULL)
	{
		ft_free_content(&content);// je penses que tu vas utiliser cette variable apres :)
		g_codes.g_error_code = 1;
		return (NULL);
	}
	error_management(&content);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	// while(content.tokens)
    // {
    //     printf("word is %s his meta is %s token is %d\n", content.tokens->word, content.tokens->value, content.tokens->e_type);
    //     content.tokens = content.tokens->next;
    // }
	heredoc_racine(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	removing_qoutes_and_expand(content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)

	cmds_line = list_init(content.tokens);//function the creat the final linked list
	// while (cmds_line)
	// {
	// 	printf("%d cmd line \n", cmds_line->index);
	// 	cmds_line = cmds_line->next;
	// }
	//fuction that fill the final lked list fds and av9
	remplissage_cmds(cmds_line, content.tokens);
	if (g_codes.g_error_code != 0)
		return (NULL);// i guess u need free list and content :)
	
	t_cmd *temp;
	temp = cmds_line;
	int i = 0;
	while (temp)
	{
		printf("========================\n");
		printf("index is        %d \n", temp->index);
		printf("flag is         %d \n", temp->flag);
		printf("in_file fd is 	%d \n", temp->in_file_fd);
		printf("out_file fd is	%d \n", temp->out_file_fd);
		i = 0;
		printf("av is : \n");
		while (temp->av && temp->av[i])
			printf("|%s|\n", temp->av[i++]);
		printf("========================\n");
		temp = temp->next;
	}
// 	t_token *temp;
// 	temp = content.tokens;
//    while(temp)
//    {
//        printf("word is |%s| \n", temp->word);
//         temp = temp->next;
//    }
// 	temp = content.tokens->next;
//     content.tokens = remove_list(temp, content.tokens);
// 	 printf("==================\n");
// 	temp = content.tokens;
//    while(temp)
//    {
//        printf("word is |%s|       type %d\n", temp->word, temp->e_type);
//         temp = temp->next;
//    }
	//if (g_codes.g_error_code != 0)
	//	return ;	
    // while (content.tokens)
    // {
    //     printf("word is %s his meta is %s token is %d and new_word is  %s\n", content.tokens->word, content.tokens->value, content.tokens->e_type, content.tokens->old_word);
    //     content.tokens = content.tokens->next;
    // }

	ft_free_list(&content.tokens);// tu dois les retourner 
	ft_free_content(&content);// je penses que tu vas utiliser cette variable apres :)
	return (cmds_line);
}


/*cette fonction s'occupe au remplissage des token dans une liste double :)*/
void add_token(t_token **head, t_token *token)
{
	t_token	*tmp;

	if (head)
	{
		if (*head == NULL)
			*head = token;
		else
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = token;
			if (token)
				token->prev = tmp;
		}
	}
}

/*ces la fonction racine de mon lexer :)*/
t_token	*to_tokeniser(t_data content)
{
	t_lexer	*lex;
	t_token	*token;
	t_token	*final;

	final = NULL;
	lex = init_lexer(content.input, content.meta_v); /*initialisation de lexer*/    // je doit free tout ces outil :)
	token = lexer_get_next_token(lex);
	add_token(&final, token);
	while (token != NULL)
	{
		//free(token);
		token = lexer_get_next_token(lex);
		add_token(&final, token);
	}
	free(lex);
	return (final);
}

/*bien sur j'ai besoin d'une fonction pour avancer dans le lexer :)*/
void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
		lexer->c0 = lexer->word[lexer->i];
	}
}

/*******just pour avancer et retourner mon token :D*****/
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 'b')
		lexer_advance(lexer);
}

/*convertire une lettre a un mot :)*/
char	*lexer_get_current_char_as_string(char  c)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = c;
	return (str);
}

/*initialisation de token struct ****/
t_token	*init_token(int type, char *value, char *word)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	token->word = word;
	token->old_word = NULL;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

/*collecter le mot dans un seul token :)*/
t_token	*lexer_collect_id(t_lexer	*lexer)
{
	char	*value;
	char	*word;
	char	*v;
	char	*w;

	value = ft_strdup("");
	word = ft_strdup("");
	while (ft_strchr("bpwr", lexer->c) == 0)
	{// this part est repeter dans une fonction
		v = lexer_get_current_char_as_string(lexer->c);
		w = lexer_get_current_char_as_string(lexer->c0);
		value = ft_extrajoin(value, v, FREE_ALL);
		word = ft_extrajoin(word, w, FREE_ALL);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_WORD, value, word));// preparer votre structure 
}

/*goted string :D*/
t_token	*lexer_collect_redirection(t_lexer *lexer, int type)
{
	char	*value;
	char	*word;

	value = ft_strdup("..");
	word = ft_strdup("..");
	value[0] = lexer->c;
	word[0] = lexer->c0;
	if (lexer->contents[lexer->i] == lexer->contents[lexer->i + 1])
	{
		lexer_advance(lexer);
		value[1] = lexer->c;
		word[1] = lexer->c0;
		type++;
	}
	else
	{
		value[1] = '\0';
		word[1] = '\0';
	}
	lexer_advance(lexer);
	return (init_token(type, value, word));
}

/****le coeur de votre lexer :)*****/
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == 'b')
			lexer_skip_whitespace(lexer);
		else if (lexer->c == 'p')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
						lexer_get_current_char_as_string(lexer->c),
						lexer_get_current_char_as_string(lexer->c0))));
		else if (lexer->c == 'r')
			return (lexer_collect_redirection(lexer, TOKEN_READ));
		else if (lexer->c == 'w')
			return (lexer_collect_redirection(lexer, TOKEN_WRITE));
		else
			return (lexer_collect_id(lexer));
	}
	return (NULL);
}

/*initialisation de lexer*/
t_lexer	*init_lexer(char *contents, char *meta_v)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->contents = meta_v;
	lexer->word = contents;
	lexer->i = 0;
	lexer->c = meta_v[lexer->i];
	lexer->c0 = contents[lexer->i];
	return (lexer);
}

void	qouted_str(char *str, unsigned int  *i, char c)
{
	char	n;

	n = 's';
	if (c == '"')
		n = 'd';
	str[*i] = n;
	(*i)++;
	while (str[*i] && str[*i] != c)
	{
		if (n == 'd' && str[*i] == '$' && (str[(*i) + 1] == '_' || ft_isalpha(str[(*i) + 1])))
			str[*i] = 'x'; 				
		else
			str[*i] = 'q';
		*i += 1;
	}
	if (str[*i] == c)
		str[*i] = n;
	else
		*i -= 1;
}

char	*meta_data(char  *str)
{
	unsigned int	i;

	i = 0;
	/*
	wa jawahir tkayssi matbadlich 
	f string gadi wa7ed jdid okhali lakhor tkhadmi bih menba3d
	*/
	while (str[i])
	{
		if (str[i] == '<')
			str[i] = 'r';
		else if (str[i] == '>')
			str[i] = 'w';
		else if (str[i] == '|')
			str[i] = 'p';
		else if (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
			str[i] = 'b';
		else if (str[i] == '\"' || str[i] == '\'')
			qouted_str(str, &i, str[i]);
		else if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
			str[i] = 'x';
		else
			str[i] = 'u';
		i++;
	}
	return (str);
}
