/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouted_str1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:14:10 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:07:24 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_utils(t_xpnd	*vars, t_token	*t)
{
	vars->c = to_expand(t->old_word, &vars->i, vars->dq_flag);
	if (vars->dq_flag != 0)
		vars->m = ft_strdup("");
	if (vars->c)
	{
		free (vars->m);
		vars->m = ft_strdup(vars->c);
		ft_memset(vars->m, t->value[vars->i], ft_strlen(vars->m));
	}
}

void	expander_utils1(t_xpnd	*vars, t_token	*t)
{
	vars->c = ft_strdup(" ");
	vars->c[0] = t->old_word[vars->i];
	if (vars->dq_flag == -2)
		t->value[vars->i] = 'Q';
	vars->m = ft_strdup(" ");
	vars->m[0] = t->value[vars->i];
}

void	expander_init(t_xpnd	*vars, t_token	*t)
{
	vars->i = 0;
	t->old_word = ft_strdup(t->word);
	free (t->word);
	vars->dq_flag = 0;
	t->word = NULL;
	vars->m_helper = NULL;
}

void	free_expand(t_token	*t, t_xpnd	*vars)
{
	free (t->value);
	t->value = vars->m_helper;
	free (vars);
}

void	expander(t_token	*t)
{
	t_xpnd	*vars;

	vars = malloc(sizeof(t_xpnd));
	expander_init(vars, t);
	while (t->value[vars->i])
	{
		vars->c = NULL;
		vars->m = NULL;
		if (t->value[vars->i] == 'x')
			expander_utils(vars, t);
		else if (t->value[vars->i] != 'd' && t->value[vars->i] != 's')
			expander_utils1(vars, t);
		else if (t->value[vars->i] == 'd' || t->value[vars->i] == 's')
			vars->dq_flag = change_flag(vars->dq_flag, t->value[vars->i]);
		else
		{
			vars->i++;
			continue ;
		}
		t->word = ft_extrajoin(t->word, vars->c, FREE_ALL);
		vars->m_helper = ft_extrajoin(vars->m_helper, vars->m, FREE_ALL);
		vars->i++;
	}
	free_expand(t, vars);
}
