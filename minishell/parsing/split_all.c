/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:31:03 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 15:34:13 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	num_word(char *av)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (av[i])
	{
		if (av[i] != ' ' && av[i] != '\t' && av[i] != '\n')
		{
			n++;
			while (av[i] && av[i] != ' ' && av[i] != '\t' && av[i] != '\n')
				i++;
		}
		else
			i++;
	}
	return (n);
}

char	**ft_freeall(char **tab, int i)
{
	int	a;

	a = 0;
	while (a <= i)
	{
		free(tab[a]);
		a++;
	}
	free(tab);
	return (NULL);
}

char	**allocationlpl(char **str, char *av, int n)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (i < n && av[j])
	{
		len = 0;
		while (av[j] && av[j] != ' ' && av[j] != '\t' && av[j] != '\n')
		{
			len++;
			j++;
		}
		if (len)
		{
			str[i] = ft_calloc(len + 1, 1);
			if (!str[i])
				return (ft_freeall(str, i));
			i++;
		}
		j++;
	}
	str[i] = NULL;
	return (str);
}

void	ft_remplissage(char **str, char *av, int n)
{
	int	l;
	int	c;
	int	cc;

	l = 0;
	c = 0;
	while (l < n && av[c])
	{
		cc = 0;
		if (av[c] != ' ' && av[c] != '\t' && av[c] != '\n')
		{
			while (av[c] && av[c] != ' ' && av[c] != '\t' && av[c] != '\n')
			{
				str[l][cc] = av[c];
				cc++;
				c++;
			}
			str[l][cc] = '\0';
			l++;
		}
		else
			c++;
	}
}

char	**split_all(char *av)
{
	char	**str;
	int		n;

	if (!av)
		return (NULL);
	n = num_word(av);
	str = ft_calloc(sizeof(char *), n + 1);
	if (!str)
		return (NULL);
	str = allocationlpl(str, av, n);
	if (!str)
		return (NULL);
	ft_remplissage(str, av, n);
	return (str);
}
