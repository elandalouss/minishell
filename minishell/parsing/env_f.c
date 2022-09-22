/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:04:18 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 08:30:43 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

unsigned int	env_len(char **env)
{
	int i;
	
	i = 0;
	while (env[i])
		i++;
	return	(i);
}

/*****cette fonction utiliser pour *******/
void    my_env(char **env, char *to_add)
{
    int				i;
	unsigned int	len;
	
	len = env_len(env);
	if (to_add)
		len++;
	g_codes.g_env = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while(env[i])
	{
		g_codes.g_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (to_add)
		g_codes.g_env[i++] = ft_strdup(to_add);
	g_codes.g_env[i] = NULL;
}

t_token	*remove_list(t_token *to_remove, t_token *head)
{
	t_token	*next;
	t_token	*prev;
	
	if (!to_remove)
		return (head);
	next = to_remove->next;
	prev = to_remove->prev;
	if (next)
		to_remove->next->prev = prev;
	if (prev)
		to_remove->prev->next = next;
	else
		head = next;
	free(to_remove->old_word);
	free(to_remove->value);
	free(to_remove->word);
	free(to_remove);
	return (head);
}
