/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:03:19 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/23 17:20:28 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*****ici j'ouvre le fichier et je pass au remplissage ******/
void	preparation_docv(int expand_flag, char	*limiter, int i)
{
	char		*file;
	int			fd;

	file = get_file_name(i);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: faild to open here_doc tmp file\n", 2);
		exit (1);
	}
	remplissage_doc(expand_flag, fd, limiter);
	close (fd);
	free(file);
}

/*ici je verifier si les variable a expender au niveau de heredoc*/
char	check_expand(char *name, char *meta, t_token *token)
{
	int		i;
	char	*c;
	int		j;

	if (ft_strchr(meta, 's') != 0 || ft_strchr(meta, 'd') != 0)
	{
		c = ft_calloc(ft_strlen(name) + 1, sizeof(char));
		i = 0;
		j = 0;
		while (meta[i])
		{
			if (meta[i] != 's' && meta[i] != 'd')
			{
				c[j] = name[i];
				j++;
			}
			i++;
		}
		c[j] = '\0';
		free(token->word);
		token->word = c;
		return (0);
	}
	return (1);
}

/**c'est la fonction  qui lance tout les heredoc ******/
void	open_herdoc(t_token *token)
{
	t_token	*temp;
	char	expand_flag;
	int		i;

	i = 0;
	temp = token;
	while (temp)
	{
		if (temp->e_type == TOKEN_DREAD)
		{
			expand_flag = check_expand
				(temp->next->word, temp->next->value, temp->next);
			preparation_docv(expand_flag, temp->next->word, i);
			i++;
		}
		temp = temp->next;
	}
}

/*cette fonction verifier les error avans de lancer le heredoc*/
void	here_docs(t_token *tokens)
{
	unsigned int	holder;

	holder = check_number(tokens);
	if (holder > 16)
	{
		ft_print_error("minishell : maximum here-document count exceeded", NULL, NULL);
		//printf("minishell : maximum here-document count exceeded\n");
		exit(16);
	}
	open_herdoc(tokens);
	exit(0);
}

/*ces la fonction racine de heredocs ou je cree un nouveau process***/
void	heredoc_racine(t_token	*tokens)
{
	pid_t	id;
	int		status;
	t_token	*temp;
	int		i;

	if (check_number(tokens) == 0)
		return ;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);// to see
		here_docs(tokens);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(id, &status, 0) < 0)
		{
			perror("minishell: waitpid:");
			g_codes.g_error_code = 1;
			g_codes.g_exit_code = 1;
			return ;
		}
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 16)
				exit(2);
			else if (WEXITSTATUS(status) == 1)
			{
				g_codes.g_exit_code = 1;
				g_codes.g_error_code = 1;
				return ;
			}
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
			{
				ft_putstr_fd("\n", 2);
				g_codes.g_error_code = 1;
				g_codes.g_exit_code = 1;
				return ;
			}
			//hnaya blan heredoc m3a signal
		}
		signal(SIGINT, handler);
		temp = tokens;
		i = 0;
		while (temp)
		{
			if (temp->e_type == TOKEN_DREAD)
			{
				free(temp->next->word);
				temp->next->word = get_file_name(i);
				i++;
			}
			temp = temp->next;
		}
	}
}