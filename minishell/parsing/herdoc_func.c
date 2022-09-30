/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:52:20 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/30 17:35:53 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*ici je cherche la position de $ */
int	position(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

/*je cherch si le mot exist dans l'env*/
char	*check_word_in_env(char	*word)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(word);
	while (*word && g_codes.g_env[i])
	{
		if (ft_strncmp(g_codes.g_env[i], word, len) == 0
			&& g_codes.g_env[i][len] == '=')
		{
			free(word);
			word = ft_substr(g_codes.g_env[i], len + 1,
					ft_strlen(g_codes.g_env[i]) - (len - 2));
			return (word);
		}
		i++;
	}
	free (word);
	return (NULL);
}

void	extra_free(char *s1, char *s2, char flag)
{
	if (flag == FREE_FIRST || flag == FREE_ALL)
		free (s1);
	if (flag == FREE_SECOND || flag == FREE_ALL)
		free (s2);
}
