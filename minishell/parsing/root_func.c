/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:09:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/08 02:35:22 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*pour la verification des pipe error ****/
void	pipe_errors(t_token *token)
{
	if (token->next == NULL || token->prev == NULL)
	{
		ft_putstr_fd("ERROR : PIPE IN FRONT OR IN THE END\n", 2);// WA JAWAHIR BADLI HADI B ERROR S7I7
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
	else if (token->next->e_type == TOKEN_PIPE)
	{
		ft_putstr_fd("ERROR : DOUBLE PIPE\n", 2); // WA JAWAHIR BADLI HADI B ERROR S7I7
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/*pour la veriication des error de redurection*/
void	redirection_errors(t_token *token)
{
	if (token->next->e_type != TOKEN_WORD)
	{
		ft_putstr_fd("ERROR : REDIRECTION ERROR\n", 2); // WA JAWAHIR BADLI HADI B ERROR S7I7
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/*****pour la verification des errors pour les simple mot*/
void	word_error(t_token *token)
{
	char	*d;
	char	*s;

	d = ft_strchr(token->value, 'd');
	s = ft_strchr(token->value, 's');
	if (s && s == ft_strrchr(token->value, 's'))
	{
		ft_putstr_fd("ERROR : UNCLOSED SINGLE QUOTE \n", 2); // WA JAWAHIR BADLI HADI B ERROR S7I7
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
	if (d && d == ft_strrchr(token->value, 'd'))
	{
		ft_putstr_fd("ERROR : UNCLOSED DOUBLE QUOTE \n", 2); // WA JAWAHIR BADLI HADI B ERROR S7I7
		g_codes.g_exit_code = 258;
		g_codes.g_error_code = 1;
	}
}

/******la onction racine de tout les autre fonction des error*/
void	error_management(t_data *content)
{
	t_token	*temp;

	temp = content->tokens;
	while (temp)
	{
		if (temp->e_type == TOKEN_PIPE)
			pipe_errors(temp);
		else if (temp->e_type != TOKEN_WORD)
			redirection_errors(temp);
		else
			word_error(temp);
		if (g_codes.g_error_code != 0)
			return ;
		temp = temp->next;
	}
}

/*la fonction racine de tout les onction de parsing part :)  */
void	parsing_part(char *str)
{
	t_data	content;

	content.input = ft_strdup(str); // strdup(str)
	content.meta_v = meta_data(str);
	printf("%s\n", content.input);
	printf("%s\n", content.meta_v);
	content.tokens = to_tokeniser(content);
    // while(content.tokens)
    // {
    //     printf("word is %s his meta is %s token is %d\n", content.tokens->word, content.tokens->value, content.tokens->type);
    //     content.tokens = content.tokens->next;
    // }
	error_management(&content);
	if (g_codes.g_error_code != 0)
		return ;
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
	lex = init_lexer(content.input, content.meta_v); /*initialisation de lexer*/
	token = lexer_get_next_token(lex);
	add_token(&final, token);
	while (token != NULL)
	{
		token = lexer_get_next_token(lex);
		add_token(&final, token);
	}
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
char    **lexer_get_current_char_as_string(char  c)
{
    char    *str;
    
    str = calloc(2, sizeof(char));
    str[0] = c;
    str[1] = '\0';
    return str;
}

/*initialisation de token struct ****/
t_token *init_token(int type, char *value, char *word)
{
    t_token *token;
    
    token = ft_calloc(1, sizeof(t_token));
    if(!token)
        return (NULL);
    token->e_type= type;
    token->value = value;
    token->word = word;
    token->prev = NULL;
    token->next = NULL;
    return token;
}

/*collecter le mot dans un seul token :)*/
t_token *lexer_collect_id(t_lexer   *lexer)
{
    char    *value; 
    char    *word;
    char    *v;
    char    *w;

    value = ft_strdup("");
    word = ft_strdup("");
    while (ft_strchr("bpwr" ,lexer->c) == 0)
    {// this part est repeter dans une fonction
        v = lexer_get_current_char_as_string(lexer->c);
        w = lexer_get_current_char_as_string(lexer->c0);
        value = ft_strjoin(value, v);
        word = ft_strjoin(word, w);
        lexer_advance(lexer);
    }
    return init_token(TOKEN_WORD, value, word);// preparer votre structure 
}

/*goted string :D*/
t_token *lexer_collect_redirection(t_lexer *lexer, int type)
{
    char *value;
    char *word;
    
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
    return init_token(type, value, word);
}

/****le coeur de votre lexer :)*****/
t_token *lexer_get_next_token(t_lexer *lexer)
{
    while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
    {
        if (lexer->c == 'b')
            lexer_skip_whitespace(lexer);
        //pipe token
        if (lexer->c == 'p')
            return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE, 
                lexer_get_current_char_as_string(lexer->c), lexer_get_current_char_as_string(lexer->c0))));
        else if (lexer->c == 'r')
            return (lexer_collect_redirection(lexer, TOKEN_READ));
        else if (lexer->c == 'w')
            return (lexer_collect_redirection(lexer, TOKEN_WRITE));
        /*word :D*/
        else 
            return lexer_collect_id(lexer);
    }
    return (NULL);
}

/*initialisation de lexer*/
t_lexer *init_lexer(char *contents, char *meta_v)
{
    t_lexer *lexer; 
    lexer = ft_calloc(1, sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->contents = meta_v;
    lexer->word = contents;
    lexer->i = 0;
    lexer->c = meta_v[lexer->i];
    lexer->c0 = contents[lexer->i];
    return lexer;
}

void    qouted_str(char *str, unsigned int  *i, char c)
{
    char    n;

    n = 's';
    if (c == '"')
        n = 'd';
    str[*i] = n;
    (*i)++;
    while (str[*i] && str[*i] != c)
    {
        str[*i] = 'q';
        *i += 1;
    }
    if (str[*i] == c)
        str[*i] = n;
    else
        *i -= 1;
}

char    *meta_data(char  *str)
{
    unsigned int i;

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
        else
            str[i] = 'u';
        i++;
    }
    return (str);
}