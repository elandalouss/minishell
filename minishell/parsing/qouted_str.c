/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouted_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:12:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/17 16:46:22 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	to_expand_utils(char dq_flag, char *word)
{
	if (word && word[0] == '\0' && dq_flag == 0)
	{
		free (word);
		word = NULL;
	}
}

/*ici je fais mon expand :D*/
char	*to_expand(char *str, int *i, char dq_flag)
{
	char	*word;
	char	*c;

	word = ft_strdup("");
	(*i)++;
	while (str[(*i)] && (str[(*i)] == '_' || ft_isalnum(str[(*i)])))
	{
		c = ft_strdup(" ");
		c[0] = str[(*i)];
		word = ft_extrajoin(word, c, FREE_ALL);
		(*i)++;
	}
	(*i)--;
	word = check_word_in_env(word);
	if (dq_flag != 0)
	{
		if (word == NULL)
			word = ft_strdup("");
		return (word);
	}
	to_expand_utils(dq_flag, word);
	return (word);
}

/****chercher si charset exist dans s1*****/
int	ft_charset_chr(char	*s1, char	*charset)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(charset, s1[i]))
			return (i);
		i++;
	}
	return (-1);
}


/****remplire la structe word avec la nouveau mot expander*****/
char	change_flag(char dq_flag, char value)
{
	dq_flag = !dq_flag;
	if (value == 's')
		dq_flag = -2;
	return (dq_flag);
}

void	expander(t_token	*t)
{
	int		i;
	char	*c;
	char	*m;
	char	*m_helper;
	char	dq_flag;

	i = 0;
	t->old_word = ft_strdup(t->word);

	free (t->word);
	dq_flag = 0;
	t->word = NULL;
	m_helper = NULL;
	while (t->value[i])
	{
		c = NULL;
		m = NULL;
		if (t->value[i] == 'x')
		{
			c = to_expand(t->old_word, &i, dq_flag);
			if (dq_flag != 0)
				m = ft_strdup("");
			if (c)
			{
				free (m);
				m = ft_strdup(c);
				ft_memset(m, t->value[i], ft_strlen(m));
			}
		}
		else if (t->value[i] != 'd' && t->value[i] != 's')
		{
			c = ft_strdup(" ");
			c[0] = t->old_word[i];
			//if (dq_flag == -2)
			t->value[i] = 'Q' * (dq_flag == -2) + t->value[i] * (dq_flag != -2);
			m = ft_strdup(" ");
			m[0] = t->value[i];
		}
		else if (t->value[i] == 'd' || t->value[i] == 's')
			dq_flag = change_flag(dq_flag, t->value[i]);
		else
		{
			i++;
			continue ;
		}
		t->word = ft_extrajoin(t->word, c, FREE_ALL);
		m_helper = ft_extrajoin(m_helper, m, FREE_ALL);
		i++;
	}
	free (t->value);
	t->value = m_helper;
}

/*removinq qoutes and expand and detection de ambiguest redirection*/
void	removing_qoutes_and_expand(t_token	*tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (ft_strchr(tokens->value, 'x'))
			expander(tokens);
		else
		{
			expander(tokens);
			free(tokens->old_word);
			if (tokens->word == NULL)
				tokens->word = ft_strdup("");
			tokens->old_word = ft_strdup(tokens->word);
			
		}
		if (tokens->word == NULL || (ft_charset_chr(tokens->word, " \t\n") >= 0
				&& tokens->value[ft_charset_chr(tokens->word, " \t\n")] == 'u'))
			tokens->e_type = TOKEN_RDIR_AMBIGU;
		tokens = tokens->next;
	}
}
