/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:59:11 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/30 18:00:52 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	printf("ffff\n");
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
		ft_print_error("minishell : maximum here-document count exceeded",
			NULL, NULL);
		exit(16);
	}
	open_herdoc(tokens);
	exit(0);
}
