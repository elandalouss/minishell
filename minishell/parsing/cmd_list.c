/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:08:35 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/22 15:29:08 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*initialisation de  commande_list */
t_cmd	*list_init(t_token *tokens)
{
	int		i;
	t_cmd	*head;
	t_cmd	*temp;

	head = NULL;
	i = number_of_pipes(tokens);
	i++;
	while (i > 0)
	{
		temp = ft_calloc(1, sizeof(t_cmd));
		temp->index = i - 1;
		temp->flag = TO_EXECUT;
		temp->prev = NULL;
		temp->next = head;
		temp->out_file_fd = -2;
		temp->in_file_fd = -2;
		if (temp->next == NULL)
			temp->out_file_fd = 1;
		head = temp;
		i--;
	}
	head->in_file_fd = 0;
	return (head);
}

/**calculer le nombre de pipe :D**/
int	number_of_pipes(t_token *tokens)
{
	t_token	*temp;
	int		i;

	temp = tokens;
	i = 0;
	while (temp)
	{
		if (temp->e_type == TOKEN_PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

/*ici je remplirre la liste des commande :D*/
void	remplissage_cmds(t_cmd *cmds, t_token *tokens)
{
	t_token		*temp_r;
	t_token		*temp_w;
	char		**tmp;

	while (cmds)
	{
		temp_r = NULL;
		temp_w = NULL;
		while (tokens)
		{
			if (tokens->word == NULL)
			{
				tokens = tokens->next;
				continue ;
			}
			if (tokens->e_type >= TOKEN_READ && tokens->e_type < TOKEN_RDIR_AMBIGU)
			{
				if (check_access(tokens) == -1)
					cmds->flag = NOT_EXEC;
				else
				{
					if (tokens->e_type == TOKEN_DREAD
						|| tokens->e_type == TOKEN_READ)
						temp_r = tokens;
					if (tokens->e_type == TOKEN_DWRITE
						|| tokens->e_type == TOKEN_WRITE)
						temp_w = tokens;
				}
				tokens = tokens->next;
			}
			else if (tokens->e_type == TOKEN_WORD)
				cmds->av = my_args(cmds->av, tokens->word);
			else if (tokens->e_type == TOKEN_RDIR_AMBIGU)
			{
				tmp = split_all(tokens->word);
				while (*tmp)
				{
					cmds->av = my_args(cmds->av, *tmp);
					free(*tmp);
					tmp++;
				}
			}
			else
			{
				tokens = tokens->next;
				break ;
			}
			tokens = tokens->next;
		}
		if (cmds->flag == TO_EXECUT && (temp_r || temp_w))
		{
			open_file(temp_r, temp_w, cmds);
		}
		if (g_codes.g_error_code != 0)
			return ;
		cmds = cmds->next;
	}
}

int	check_access(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens->next->e_type == TOKEN_RDIR_AMBIGU)
	{
		printf("minishell: %s: ambiguous redirect\n", tokens->next->old_word);// you need to print this in standar error
		return (-1);
	}
	if (tokens->e_type == TOKEN_READ || tokens->e_type == TOKEN_DREAD)
	{
		i = access(tokens->next->word, F_OK);
		if (i != -1)
			i = access(tokens->next->word, R_OK);
	}
	else if (tokens->e_type == TOKEN_WRITE || tokens->e_type == TOKEN_DWRITE)
		i = access(tokens->next->word, W_OK);
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
