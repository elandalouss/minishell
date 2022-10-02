/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:08:35 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/02 02:24:21 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_and_close(char *str)
{
	int	fd;

	fd = open(str, O_CREAT, 0644);
	close(fd);
}

int	check_access_utils(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens->e_type == TOKEN_READ || tokens->e_type == TOKEN_DREAD)
	{
		i = access(tokens->next->word, F_OK);
		if (i == -1)
		{
			ft_print_error("minishell: ",
				tokens->next->old_word, ": No such file or directory");
			return (-2);
		}
		else
			i = access(tokens->next->word, R_OK);
	}
	else if (tokens->e_type == TOKEN_WRITE || tokens->e_type == TOKEN_DWRITE)
	{
		if (access(tokens->next->word, F_OK) == -1)
			open_and_close(tokens->next->word);
		i = access(tokens->next->word, W_OK);
	}
	return (i);
}

int	check_access(t_token *tokens)
{
	int	i;

	if (tokens->next->e_type == TOKEN_RDIR_AMBIGU)
	{
		ft_print_error("minishell: ",
			tokens->next->old_word, ": ambiguous redirect");
		return (-1);
	}
	i = check_access_utils(tokens);
	if (i == -2)
		return (-1);
	if (i == -1)
		ft_print_error("minishell: ",
			tokens->next->old_word, ": Permission denied");
	return (i);
}

/*pour ajuter une variable a av de la commande*/
char	**my_args(char **av, char *to_add)
{
	unsigned int	len;
	char			**new;
	int				i;

	len = 0;
	if (av)
		len = env_len(av);
	len++;
	new = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (av && av[i])
	{
		new[i] = av[i];
		i++;
	}
	new[i++] = ft_strdup(to_add);
	new[i] = NULL;
	free(av);
	return (new);
}
