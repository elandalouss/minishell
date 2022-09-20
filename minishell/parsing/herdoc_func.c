/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:52:20 by jchennak          #+#    #+#             */
/*   Updated: 2022/09/20 00:36:50 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	position(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return i;
}

// unused function :P
int	position_2(char *str, int i)
{
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*check_word_in_env(char	*word)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(word);
	// printf("suuup insid the check %s\n", word);
	while (*word && g_codes.g_env[i])
	{
		// printf("-------%d ===> %c\n", ft_strncmp(g_codes.g_env[i], word, len), g_codes.g_env[i][len]);
		if (ft_strncmp(g_codes.g_env[i], word, len) == 0 && g_codes.g_env[i][len] == '=')// IDK WHY IT'S WORK WITH LEN - 1 
			{
				//printf("hi");
				free(word);
				word = ft_substr(g_codes.g_env[i], len + 1, ft_strlen(g_codes.g_env[i]) - (len - 2));
				return (word);
			}
		i++;
	}
	free (word);
	return (NULL);
}

void	extra_free(char *s1, char *s2, char flag)
{
	if (flag == FREE_FIRST || flag == FREE_ALL)
		free (s1);
	if (flag == FREE_SECOND || flag == FREE_ALL)
		free (s2);
}

char	*ft_extrajoin(char *s1, char *s2, char flag)
{
	char	*final;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		final = ft_strdup(s2);
		extra_free(s1, s2, flag);
		return (final);
	}
	if (!s2)
	{
		final = ft_strdup(s1);
		extra_free(s1, s2, flag);
		return (final);
	}
	final = ft_strjoin(s1, s2);
	extra_free(s1, s2, flag);
	return (final);
}

char	*expand(char	*str, char c, char flag)
{
	char	*prefix;
	char	*suffix;
	char	*word;
	int		i;

	prefix = NULL;
	suffix = NULL;
	i = position(str, c);
	if (str[i] == '\0')
		return (ft_substr(str, 0, ft_strlen(str) + 1));
	if (i > 0)
		prefix = ft_substr(str, 0, i);
	word = ft_strdup("");
	if (str[i] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
	{
		suffix = ft_strdup(" ");
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		{
			*suffix = str[i];
			word = ft_extrajoin(word, suffix, FREE_FIRST);
			i++;
		}
		free(suffix);
		flag = 1;
	}
	else
	{
		prefix = ft_extrajoin(prefix, "$", FREE_FIRST);
		suffix = expand(str + (i + 1), '$', 0);
	}
	if (flag)
		suffix = expand(str + i, '$', 0);
	word = check_word_in_env(word);
	word = ft_extrajoin(prefix, word, FREE_ALL);
	word = ft_extrajoin(word, suffix, FREE_ALL);
	return (word);
}

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
char	*get_file_name(int i)
{
	char	*file;
	char	*c;

	file = ft_strdup("/tmp/here_doc....."); 
	file[13] = i / 10 + '0';
	file[14] = i % 10 + '0';
	c = ttyname(0);
	file[15] = c[9];
	file[16] = c[10];
	file[17] = c[11];
//	free(c);
	//printf("--a--%s\n",file);
	return (file);
}

/*ici je remplire le fichier de heredoc :)*/
void	remplissage_doc(int flag, int fd, char *limiter)
{
	char	*str;
	char	*tmp;

	// system ("leaks minishell");
	str = readline(">");
	while (str && ft_strncmp(str, limiter, ft_strlen(limiter) + 1))
	{
		if (flag && ft_strchr(str, '$'))
		{
			tmp = str;
			str = expand(str, '$', 0);
			free (tmp);
		}
		printf("----%s\n", str);
		ft_putendl_fd(str, fd);
		free(str);
		str = readline(">");
	}
	if (str)
		free(str);
}

/*****ici j'ouvre le fichier et je pass au remplissage ******/
void	preparation_docv(int expand_flag, char	*limiter, int i)
{
	char		*file;
	int			fd;

	file = get_file_name(i);
	// system ("leaks minishell");
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		printf("minishell: faild to open here_doc tmp file\n"); //WA JAWAHIR DIRIH F STDERR B WRITE
		exit (1);
	}
	remplissage_doc(expand_flag, fd, limiter);
	close (fd);
	free(file);
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
	int		i;

	i = 0;
	temp = token;
	while (temp)
	{
		if (temp->e_type == TOKEN_DREAD)
		{
			expand_flag = check_expand(temp->next->word, temp->next->value, temp->next);
			//printf("%i\n%s\n", expand_flag, temp->next->word);
			preparation_docv(expand_flag, temp->next->word, i);
			i++;
		}
		temp = temp->next;
	}
}

/*cette fonction verifier les error avans de lancer le heredoc*/
void	here_docs(t_token *tokens)
{
	unsigned int holder;

	// system ("leaks minishell");
	holder = check_number(tokens);
	if (holder > 16)
	{
		printf("minishell : maximum here-document count exceeded\n"); //WA JAWAHIR KHEDMO B FT_PUTSTR_FD BASH TKETBI F 2
		//g_codes.g_error_code = 2; // no need :)
		//g_codes.g_exit_code = 2;
		exit(16);
	}
	else if (holder == 0)// j'ai deja verifier au debut :D
		return ;
	// mtn tu dois demarer les heredoc
	open_herdoc(tokens);
	exit(0);
}


void	handler(int code)
{
	(void)code;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*ces la fonction racine de heredocs ou je cree un nouveau process***/
void	heredoc_racine(t_token	*tokens)
{
	pid_t 	id;
	int		status;
	t_token	*temp;
	int		i;
	
	if (check_number(tokens) == 0)
		return ;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
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
		while(temp)
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