/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:26:10 by jchennak          #+#    #+#             */
/*   Updated: 2022/10/18 00:34:23 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (head)
			head->prev = temp;
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

/*ajouter jusyt pour la norme :D*/
char	*exit_code_util(char *new_word, int index)
{
	int	exit_code;

	exit_code = g_codes.g_exit_code;
	if (index != 0)
		exit_code = 0;
	new_word = ft_extrajoin(new_word, ft_itoa(exit_code), FREE_ALL);
	return (new_word);
}

/**expander le exit code :D ********/
char	*exit_code_expander(char *str, int index, char *meta)
{
	int		i;
	char	*new_word;
	char	*c;

	i = 0;
	new_word = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && meta[i] != 'Q')
		{
			new_word = exit_code_util(new_word, index);
			i++;
		}
		else
		{
			c = ft_strdup(" ");
			c[0] = str[i];
			new_word = ft_extrajoin(new_word, c, FREE_ALL);
		}
		i++;
	}
	free(str);
	return (new_word);
}

void	change_flag_and_skip_noeuds(t_cmd **cmds, t_token **tokens)
{
	(*cmds)->flag = NOT_EXEC;
	(*tokens) = skip_noeud((*tokens));
	if ((*tokens) != NULL)
		(*tokens) = (*tokens)->next;
}
