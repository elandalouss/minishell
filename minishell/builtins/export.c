/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:55:32 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/19 04:40:30 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_env(char **tmp_env)
{
	int	i;

	i = 0;
	while (g_codes.g_env[i])
	{
		free(tmp_env[i]);
		tmp_env[i] = ft_strdup(g_codes.g_env[i]);
		i++;
	}
}

void	calloc_protection(char **tmp_env)
{
	if (!tmp_env)
		printt_error("ERROR!", "malloc", "allocation failed", 1);
}

void	export_null(char **tmp_env)
{
	int				i;
	char			*tmp3;
	char			**tmp2;

	tmp_env = ft_calloc(env_len(g_codes.g_env) + 1, sizeof(char *));
	calloc_protection(tmp_env);
	cpy_env(tmp_env);
	cmp_str_env(tmp_env);
	i = 0;
	while (tmp_env[i] != NULL)
	{
		tmp2 = ft_split(tmp_env[i], '=');
		if (ft_strchr_int(tmp_env[i], '=') == 1)
		{
			tmp3 = ft_substr(tmp_env[i], \
				ft_strlen(tmp2[0]) + 1, ft_strlen(tmp_env[i]));
			printf("declare -x %s=\"%s\"\n", tmp2[0], tmp3);
			free(tmp3);
		}
		else
			printf("declare -x %s\n", tmp2[0]);
		i++;
		free_tab(tmp2);
	}
	if(tmp_env)
		free_tab(tmp_env);
}

void	print_export_error(char *str)
{
	printt_error1("./minishell: export", str, "not a valid identifier", 1);
}

void	export(t_cmd	*data)
{
	int				i;
	char			**tmp_env;

	tmp_env = NULL;
	if (g_codes.g_env[0] == NULL)
		return ;
	if (data->av[1] == NULL)
		export_null(tmp_env);
	else if (data->av[1] != NULL)
	{
		i = 1;
		while (data->av[i])
		{
			theres_eq(data->av[i]);
			if (check_export_error(data->av[i]) == -2)
			{
				export_null(tmp_env);
				return ;
			}
			else if (check_export_error(data->av[i]) == -1)
				print_export_error(data->av[i]);
			cmp(data->av[i]);
			i++;
		}
	}
}
