/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:38:56 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 15:39:29 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	qouted_str(char *str, unsigned int *i, char c)
{
	char	n;

	n = 's';
	if (c == '"')
		n = 'd';
	str[*i] = n;
	(*i)++;
	while (str[*i] && str[*i] != c)
	{
		if (n == 'd' && str[*i] == '$' && (str[(*i) + 1] == '_'
				|| ft_isalpha(str[(*i) + 1])))
			str[*i] = 'x';
		else
			str[*i] = 'q';
		*i += 1;
	}
	if (str[*i] == c)
		str[*i] = n;
	else
		*i -= 1;
}

char	*meta_data(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			str[i] = 'r';
		else if (str[i] == '>')
			str[i] = 'w';
		else if (str[i] == '|')
			str[i] = 'p';
		else if (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
			str[i] = 'b';
		else if (str[i] == '\"' || str[i] == '\'')
			qouted_str(str, &i, str[i]);
		else if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
			str[i] = 'x';
		else
			str[i] = 'u';
		i++;
	}
	return (str);
}
