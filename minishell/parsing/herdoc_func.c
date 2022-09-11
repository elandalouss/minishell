/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:52:20 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/10 16:36:12 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*******ici je calcule le nombre des chevrons << pour le heredoc*/
unsigned int check_number(t_token *tokens)
{
	t_token			*temp;
	unsigned int	i;

	i = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->e_type == TOKEN_DREAD)
			i++;
		temp = temp->next;
	}
	return (i);
}

/*ici je prepare le nom de fichier de heredoc :)*/
char	*get_file_name(void)
{
	char	*file;
	static int	i;
	char	*c;

	file = ft_strdup("/tmp/here_doc....."); 
	file[13] = i / 10 + '0';
	file[14] = i % 10 + '0';
	c = ttyname(0);
	file[15] = c[9];
	file[16] = c[10];
	file[17] = c[11];
//	free(c);
	i++;
	return (file);
}

/*ici je remplire le fichier de heredoc :)*/
void	remplissage_doc(int flag, int fd, char *limiter)
{
	char	*str;
	
	str = readline(">");
	while (str && ft_strncmp(str, limiter, ft_strlen(limiter) + 1))
	{
		if (flag && ft_strchr(str, '$'))
			;//expend(str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline(">");
	}
}

/*****ici j'ouvre le fichier et je pass au remplissage ******/
void	preparation_docv(int expand_flag, char	*limiter)
{
	char		*file;
	int			fd;

	file = get_file_name();
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		printf("minishell: faild to open here_doc tmp file\n"); //WA JAWAHIR DIRIH F STDERR B WRITE
		exit (1);
	}
	remplissage_doc(expand_flag, fd, limiter);
	close (fd);
	// making_file_name(name);
}

/*ici je verifier si les variable a expender au niveau de heredoc*/
char	check_expand(char *name, char *meta, t_token *token)
{
	int 	i;
	char	*c;
	int		j;
	
	if (ft_strchr(meta, 's') != 0 || ft_strchr(meta, 'd') != 0)
	{
		c = ft_calloc(ft_strlen(name) + 1 , sizeof(char));
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
		// printf("%s  ||   %s\n", c, token->word);
		return (0);	
	}
	return (1); // expand
}

/**c'est la fonction  qui lance tout les heredoc ******/
void	open_herdoc(t_token *token)
{
	t_token *temp;
	char	expand_flag;

	temp = token;
	while (temp)
	{
		if (temp->e_type == TOKEN_DREAD)
		{
			expand_flag = check_expand(temp->next->word, temp->next->value, temp->next);
			printf("%i\n%s\n", expand_flag, temp->next->word);
			preparation_docv(expand_flag, temp->next->word);
		}
		temp = temp->next;
	}
}

/*cette fonction verifier les error avans de lancer le heredoc*/
void	here_docs(t_token *tokens)
{
	unsigned int holder;

	holder = check_number(tokens);
	if (holder > 16)
	{
		printf("minishell : maximum here-document count exceeded\n"); //WA JAWAHIR KHEDMO B FT_PUTSTR_FD BASH TKETBI F 2
		//g_codes.g_error_code = 2; // no need :)
		//g_codes.g_exit_code = 2;
		exit(1);
	}
	else if (holder == 0)
		return ;
	// mtn tu dois demarer les heredoc
	open_herdoc(tokens);
	exit(0);
}

/*ces la fonction racine de heredocs ou je cree un nouveau process***/
void	heredoc_racine(t_token	*tokens)
{
	pid_t 	id;
	int		status;
	
	id = fork();
	if(id == 0)
		here_docs(tokens);
	else
	{
		waitpid(id, &status, 0);
		//printf("%d\n", status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				exit(2);
		}
		else if (WIFSIGNALED(status))
		{
			;//hnaya blan heredoc m3a signal
		}
	}
}