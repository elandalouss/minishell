/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:30:15 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/18 00:33:22 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_and_args(t_token **tokens, t_cmd **cmds)
{
	if ((*tokens)->e_type == TOKEN_WORD)
		expander_exit_and_remplissage(tokens, cmds);
	else if ((*tokens)->e_type == TOKEN_RDAMB)
		remplissage_args(cmds, tokens);
}

void	expander_exit_and_remplissage(t_token **tokens, t_cmd **cmds)
{
	if (ft_strchr((*tokens)->word, '$'))
	{
		(*tokens)->word = exit_code_expander((*tokens)->word, \
			(*cmds)->index, (*tokens)->value);
	}
	(*cmds)->av = my_args((*cmds)->av, (*tokens)->word);
}

void	take_file_name(t_token **tkn, t_token **t_r, t_token **t_w)
{
	if ((*tkn)->e_type == TOKEN_DREAD || (*tkn)->e_type == TOKEN_READ)
		*t_r = (*tkn);
	if ((*tkn)->e_type == TOKEN_DWRITE || (*tkn)->e_type == TOKEN_WRITE)
		*t_w = (*tkn);
	if ((*tkn) != NULL)
		(*tkn) = (*tkn)->next;
}

void	remplissage_args(t_cmd **cmds, t_token **tokens)
{
	char		**tmp;

	tmp = split_all((*tokens)->word);
	while (*tmp)
	{
		(*cmds)->av = my_args((*cmds)->av, *tmp);
		free(*tmp);
		tmp++;
	}
}
