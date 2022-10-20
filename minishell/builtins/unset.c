/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:04:30 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/20 00:58:59 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

void	re_fill_env(char **tmp, int j)
{
	int	k;

	k = 0;
	while (tmp[k])
	{
		if (k < j)
		{
			free(g_codes.g_env[k]);
			g_codes.g_env[k] = ft_strdup(tmp[k]);
		}
		else if (tmp[k + 1])
		{
			free(g_codes.g_env[k]);
			g_codes.g_env[k] = ft_strdup(tmp[k + 1]);
		}
		k++;
	}
	free_tab(tmp);
}

void	resise(int *ln_env_cnt, t_cmd *data, int j, int i)
{
	char	**tmp;

	if (ft_strncmp(g_codes.g_env[j], data->av[i], \
		ft_strlen(data->av[i])) == 0)
	{
		tmp = ft_calloc((*ln_env_cnt) + 1, sizeof(char *));
		if (!tmp)
			printt_error("ERROR!", "malloc", "allocation failed", 1);
		tmp = copy_2d(tmp, g_codes.g_env);
		free_2d(g_codes.g_env, (*ln_env_cnt));
		(*ln_env_cnt)--;
		g_codes.g_env = ft_calloc((*ln_env_cnt) + 1, sizeof(char *));
		if (!g_codes.g_env)
			printt_error("ERROR!", "malloc", "allocation failed", 1);
		re_fill_env(tmp, j);
	}
}

void	check_error(char *str)
{
	if (check_builtin_error(str) == -1)
		printt_error1("./minishell: unset", str, ": not a valid identifier", 1);
}

int	count_len(char *str)
{
	int	ln_env_cnt;

	ln_env_cnt = 0;
	check_error(str);
	while (g_codes.g_env[ln_env_cnt])
		ln_env_cnt++;
	return (ln_env_cnt);
}

void	unset(t_cmd	*data)
{
	int		ln_env_cnt;
	char	*tmpy;
	int		j;
	int		i;

	i = 1;
	ln_env_cnt = 0;
	if (!data->av[1])
		return ;
	while (data->av[i])
	{
		ln_env_cnt = count_len(data->av[i]);
		tmpy = ft_strdup(data->av[i]);
		free(data->av[i]);
		data->av[i] = ft_strjoin(tmpy, "=");
		free(tmpy);
		j = 0;
		while (j < ln_env_cnt && g_codes.g_env[j])
		{
			resise(&ln_env_cnt, data, j, i);
			j++;
		}
		i++;
	}
}
