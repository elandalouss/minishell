/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelandal <aelandal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:35:14 by aelandal          #+#    #+#             */
/*   Updated: 2022/09/30 14:18:31 by aelandal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_size(t_cmd	*data)
{
	t_cmd	*tmp;
	int		i;

	tmp = data;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_2d(char **arr_2d, int ind)
{
	while (ind >= 0)
	{
		free(arr_2d[ind]);
		ind--;
	}
	free(arr_2d);
}

int	ft_strchr_int(const char *s, int c)
{
	int		i;
	char	*cc;

	i = 0;
	cc = (char *)s;
	while (cc[i] != '\0')
	{
		if (cc[i] == (char)c)
			return (1);
		i++;
	}
	if (cc[i] == c)
		return (1);
	return (-1);
}

void	printt_error(char *str1, char *str2, char *str3, int error_code)
{
	ft_putstr_fd((char *)str1, 2);
	write (2, ": ", 2);
	ft_putstr_fd((char *)str2, 2);
	write (2, ": ", 2);
	ft_putendl_fd((char *)str3, 2);
	exit(error_code);
}
