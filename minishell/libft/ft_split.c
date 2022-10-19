/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:37:27 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/19 04:52:19 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 
// static char	**ft_freeall(char **tab, int i)
// {
// 	int	a;

// 	a = 0;
// 	while (a <= i)
// 	{
// 		free(tab[a]);
// 		a++;
// 	}
// 	free(tab);
// 	return (NULL);
// }

// static int	ft_nbrmot(char const *s, char a)
// {
// 	int	i;
// 	int	nbrmot;

// 	i = 0;
// 	nbrmot = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != a)
// 		{
// 			nbrmot++;
// 			while (s[i] && s[i] != a)
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (nbrmot);
// }

// static char	**ft_allocationlpl(char **t, char const *s, char a, int n)
// {
// 	int	l;
// 	int	len;
// 	int	c;

// 	l = 0;
// 	c = 0;
// 	while (l < n && s[c])
// 	{
// 		len = 0;
// 		while (s[c] && s[c] != a)
// 		{
// 			len++;
// 			c++;
// 		}
// 		if (len != 0)
// 		{
// 			t[l] = (char *)malloc(sizeof(char) * (len + 1));
// 			if (!t[l])
// 				return (ft_freeall(t, l));
// 			l++;
// 		}
// 		c++;
// 	}
// 	t[n] = 0;
// 	return (t);
// }

// static void	ft_remplissage(char **t, char const *s, char a, int n)
// {
// 	int	l;
// 	int	c;
// 	int	cc;

// 	l = 0;
// 	c = 0;
// 	while (l < n && s[c])
// 	{
// 		cc = 0;
// 		if (s[c] != a)
// 		{
// 			while (s[c] && s[c] != a)
// 			{
// 				t[l][cc] = s[c];
// 				cc++;
// 				c++;
// 			}
// 			t[l][cc] = '\0';
// 			l++;
// 		}
// 		else
// 			c++;
// 	}
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		n;
// 	char	**t;

// 	if (s == NULL)
// 		return (0);
// 	n = ft_nbrmot(s, c);
// 	t = (char **)malloc(sizeof(char *) * (n + 1));
// 	if (!t)
// 		return (0);
// 	t = ft_allocationlpl(t, s, c, n);
// 	if (!t)
// 		return (0);
// 	ft_remplissage(t, s, c, n);
// 	return (t);
// }

static int	find_str(char const *s, char c)
{
	int	i;
	int	nb_str;

	i = 0;
	nb_str = 0;
	if (!s[0])
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_str++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_str++;
	return (nb_str);
}

static void	get_next_str(char **next_str, size_t *next_strlen, char c)
{
	size_t	i;

	*next_str += *next_strlen;
	*next_strlen = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_strlen)++;
		i++;
	}
}

static char	**handle_malloc_err(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_str;
	size_t	next_strlen;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (find_str(s, c) + 1));
	if (!tab)
		return (NULL);
	next_str = (char *)s;
	next_strlen = 0;
	while (++i < find_str(s, c))
	{
		get_next_str(&next_str, &next_strlen, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_strlen + 1));
		if (!tab[i])
			return (handle_malloc_err(tab));
		ft_strlcpy(tab[i], next_str, next_strlen + 1);
	}
	tab[i] = NULL;
	return (tab);
}