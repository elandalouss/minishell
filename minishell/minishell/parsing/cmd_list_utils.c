/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:26:10 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/30 17:29:32 by jchennak         ###   ########.fr       */
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
				{
					cmds->flag = NOT_EXEC;
					tokens = skip_noeud(tokens); // :D happy
					if (tokens != NULL)
						tokens = tokens->next;
					break ;
				//	g_codes.g_exit_code = 1;//
				//	g_codes.g_error_code = 1;//i guess no :)
					//you need to skip to the next pipe
				}
				else
				{
					if (tokens->e_type == TOKEN_DREAD
						|| tokens->e_type == TOKEN_READ)
						temp_r = tokens;
					if (tokens->e_type == TOKEN_DWRITE
						|| tokens->e_type == TOKEN_WRITE)
						temp_w = tokens;
					if (tokens != NULL)
						tokens = tokens->next;
				}
			}
			else if (tokens->e_type == TOKEN_WORD)
			{
				// printf ("word %s , old %s , meta %s\n",tokens->word, tokens->old_word, tokens->value);
				if (ft_strchr(tokens->word, '$'))
					tokens->word = exit_code_expander(tokens->word, cmds->index, tokens->value);
				
				cmds->av = my_args(cmds->av, tokens->word);
			}
			else if (tokens->e_type == TOKEN_RDIR_AMBIGU)
			{
				tmp = split_all(tokens->word);////
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
