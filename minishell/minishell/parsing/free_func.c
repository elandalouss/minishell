/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:50:30 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/30 18:28:48 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = *token;
		*token = (*token)->next;
		free(temp->value);
		free(temp->word);
		free(temp->old_word);
		free(temp);
	}
	free(*token);
}

void	ft_free_content(t_data *content)
{
	if (content->input)
		free(content->input);
	if (content->meta_v)
		free(content->meta_v);
}

void	free_dp(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	ft_free_cmds(t_cmd **cmds)
{
	t_cmd	*temp;

	while (*cmds)
	{
		temp = *cmds;
		*cmds = (*cmds)->next;
		if (temp->av)
			free_dp(temp->av);
		free(temp);
	}
	free(*cmds);
}

/*ces la fonction racine de mon lexer :)*/
t_token	*to_tokeniser(t_data content)
{
	t_lexer	*lex;
	t_token	*token;
	t_token	*final;

	final = NULL;
	lex = init_lexer(content.input, content.meta_v);
	token = lexer_get_next_token(lex);
	add_token(&final, token);
	while (token != NULL)
	{
		token = lexer_get_next_token(lex);
		add_token(&final, token);
	}
	free(lex);
	return (final);
}