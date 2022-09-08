/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:06:29 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/07 04:39:31 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef struct s_global
{
    int g_error_code;
    int g_exit_code;
}   t_global;


/******* lexer data********/
typedef struct s_lexer
{
    char            c;
    unsigned int    i;
    char           *contents;
    char           *word;
    char           c0;
}   t_lexer;

/*****  token data :)*****/
typedef struct s_token
{
    enum
    {
        TOKEN_WORD,
        TOKEN_READ,
        TOKEN_DREAD,
        TOKEN_WRITE,
        TOKEN_DWRITE,
        TOKEN_PIPE,
    } type;
    char    *value;// in meta
    char    *word;// original
    struct s_token *prev;
    struct s_token *next;
}   t_token;

/****** ma valise :)*******/
typedef struct s_data
{
    char *input;
    char *meta_v;
    t_token *tokens;
}   t_data;

t_global    g_codes;

t_token *lexer_get_next_token(t_lexer *lexer);
void    lexer_skip_whitespace(t_lexer *lexer);
void    parsing_part(char *str);
void    qouted_str(char *str, unsigned int  *i, char c);
char    *meta_data(char  *str);
t_token *to_tokeniser(t_data content);
t_lexer *init_lexer(char *contents, char *meta_v);
void    error_management(t_data *content);


#endif