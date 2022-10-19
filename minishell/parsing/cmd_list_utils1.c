/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:29:58 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:57:41 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	function(t_token **tkn, t_cmd **cmds)
{
	int	flag;

	flag = 0;
	if ((*tkn)->e_type == TOKEN_WORD || (*tkn)->e_type == TOKEN_RDAMB)
	{
		expander_and_args(tkn, cmds);
		flag = 1;
	}
	return (flag);
}

void	r_c_u(t_token **tkn, t_cmd **cmds, t_token **t_r, t_token **t_w)
{
	while (*tkn)
	{
		if ((*tkn)->word == NULL)
		{
			(*tkn) = (*tkn)->next;
			continue ;
		}
		if ((*tkn)->e_type >= TOKEN_READ && (*tkn)->e_type < TOKEN_RDAMB)
		{
			if (check_access((*tkn)) == -1)
			{
				change_flag_and_skip_noeuds(cmds, tkn);
				break ;
			}
			else
				take_file_name(tkn, t_r, t_w);
		}
		else if (function(tkn, cmds) != 1)
		{
			(*tkn) = (*tkn)->next;
			break ;
		}
		(*tkn) = (*tkn)->next;
	}
}

/*ici je remplirre la liste des commande :D*/
void	remplissage_cmds(t_cmd *cmds, t_token *tokens)
{
	t_token		*temp_r;
	t_token		*temp_w;

	while (cmds)
	{
		temp_r = NULL;
		temp_w = NULL;
		r_c_u(&tokens, &cmds, &temp_r, &temp_w);
		if (cmds->flag == TO_EXECUT && (temp_r || temp_w))
			open_file(temp_r, temp_w, cmds);
		if (g_codes.g_error_code != 0)
			return ;
		cmds = cmds->next;
	}
}

int check_error_code(t_data *content)
{
	if (g_codes.g_error_code != 0)
	{
		ft_free_list(&(content->tokens));
		ft_free_content(content);
		return (0);
	}
	return (1);
}
