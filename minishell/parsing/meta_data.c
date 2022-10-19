/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:38:56 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 01:21:34 by jchennak         ###   ########.fr       */
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

/*ici je remplire le fichier de heredoc :)*/
void	remplissage_doc(int flag, int fd, char *limiter)
{
	char	*str;
	char	*tmp;

	str = readline(">");
	if (str == NULL)
		return ;
	while (str && ft_strncmp(str, limiter, ft_strlen(limiter) + 1))
	{
		if (flag && ft_strchr(str, '$'))
		{
			tmp = str;
			str = expand(str, '$', 0, NULL);
			free (tmp);
		}
		ft_putendl_fd(str, fd);
		free(str);
		str = readline(">");
		if (str == NULL)
			break ;
	}
	if (str)
		free(str);
}

void	herdoc_racine_utils(int i, t_token *temp)
{
	temp->next->word = get_file_name(i);
	free(temp->next->value);
	temp->next->value = ft_strdup("uuuuuuuuuuuuuuuuuu");
}
