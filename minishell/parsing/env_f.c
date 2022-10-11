/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:04:18 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/11 13:27:29 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**** calculer nombre des ligne dans un double pointeur :D***/
unsigned int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*****remplissage des variable d'environement *******/
void	my_env(char **env, char *to_add)
{
	int				i;
	unsigned int	len;

	len = env_len(env);
	if (to_add)
		len++;
	system("leaks minishell");
	//if (g_codes.g_env)
//	free_dp(g_codes.g_env);
	g_codes.g_env = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		g_codes.g_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (to_add)
		g_codes.g_env[i++] = ft_strdup(to_add);
	g_codes.g_env[i] = NULL;
	system("leaks minishell");
}

/******unused function :) seul pour supprimer un noeud*******/
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

/*UTILISER POUR AFFICHER LES MESSAGE EN STANDAR D'ERROR*/
void	ft_print_error(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	write(2, "\n", 1);
}

t_token	*skip_noeud(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->e_type == TOKEN_PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (tokens);
}
