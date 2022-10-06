/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:20:27 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 12:23:10 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	{
		v = lexer_get_current_char_as_string(lexer->c);
		w = lexer_get_current_char_as_string(lexer->c0);
		value = ft_extrajoin(value, v, FREE_ALL);
		word = ft_extrajoin(word, w, FREE_ALL);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_WORD, value, word));
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
