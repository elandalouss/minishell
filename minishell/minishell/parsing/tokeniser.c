/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:17:26 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 12:24:08 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

/* pour depasser les espace :D*/
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 'b')
		lexer_advance(lexer);
}

/*convertire une lettre a un mot :)*/
char	*lexer_get_current_char_as_string(char c)
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
