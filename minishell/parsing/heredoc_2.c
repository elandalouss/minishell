/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:04:28 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/02 02:23:47 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**********join with benefits :P ******/
char	*ft_extrajoin(char *s1, char *s2, char flag)
{
	char	*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		final = ft_strdup(s2);
		extra_free(s1, s2, flag);
		return (final);
	}
	if (!s2)
	{
		final = ft_strdup(s1);
		extra_free(s1, s2, flag);
		return (final);
	}
	final = ft_strjoin(s1, s2);
	extra_free(s1, s2, flag);
	return (final);
}

char	*expand_utile(char *str, int *i, char *flag)
{
	char	*suffix;
	char	*word;

	suffix = ft_strdup(" ");
	(*i)++;
	word = NULL;
	while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[(*i)] == '_'))
	{
		*suffix = str[(*i)];
		word = ft_extrajoin(word, suffix, FREE_FIRST);
		(*i)++;
	}
	free(suffix);
	*flag = 1;
	return (word);
}

char	*expand(char	*str, char c, char flag, char *word)
{
	char	*prefix;
	char	*suffix;
	int		i;

	prefix = NULL;
	suffix = NULL;
	i = position(str, c);
	if (str[i] == '\0')
		return (ft_substr(str, 0, ft_strlen(str) + 1));
	if (i > 0)
		prefix = ft_substr(str, 0, i);
	word = ft_strdup("");
	if (str[i] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		word = expand_utile(str, &i, &flag);
	else
	{
		prefix = ft_extrajoin(prefix, "$", FREE_FIRST);
		suffix = expand(str + (i + 1), '$', 0, NULL);
	}
	if (flag)
		suffix = expand(str + i, '$', 0, NULL);
	word = check_word_in_env(word);
	word = ft_extrajoin(prefix, word, FREE_ALL);
	word = ft_extrajoin(word, suffix, FREE_ALL);
	return (word);
}

/*******ici je calcule le nombre des chevrons << pour le heredoc*/
unsigned int	check_number(t_token *tokens)
{
	t_token			*temp;
	unsigned int	i;

	i = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->e_type == TOKEN_DREAD)
			i++;
		temp = temp->next;
	}
	return (i);
}

/*ici je prepare le nom de fichier de heredoc :)*/
char	*get_file_name(int i)
{
	char	*file;
	char	*c;

	file = ft_strdup("/tmp/here_doc.....");
	file[13] = i / 10 + '0';
	file[14] = i % 10 + '0';
	c = ttyname(0);
	file[15] = c[9];
	file[16] = c[10];
	file[17] = c[11];
	return (file);
}
