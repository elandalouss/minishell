/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:23:24 by aelandal          #+#    #+#             */
/*   Updated: 2022/10/20 05:34:46 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "../minishell.h"
# include "../parsing/parsing.h"
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_cmd
{
	char			flag;
	int				index;
	int				pipe[2];
	int				in_file_fd;
	int				out_file_fd;
	char			**av;
	char			*cmd_path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_tmp
{
	int		i;
	int		j;
	char	**arr_env;
	char	**arr_av;
	char	*join_av;
	char	*join_env;	
}	t_tmp;

int		lst_size(t_cmd	*data);
void	dup_stdin(t_cmd	*data);
void	dup_stdout(t_cmd	*data);
void	dup_files(t_cmd	*data);
void	reset_std(int	*terminal);
void	free_2d(char **arr_2d, int ind);
int		ft_strchr_int(const char *s, int c);
void	printt_error(char *str1, char *str2, char *str3, int error_code);
void	printt_error1(char *str1, char *str2, char *str3, int error_code);
int		buitin_exeution(t_cmd	*data);
void	ls_next_null(t_cmd *data, int *terminal);
int		cmp_without_equal(const char *s1, const char *s2, size_t n);
pid_t	ls_next_not_null(t_cmd *data, int *terminal);
void	check_stat(t_cmd	*data, char	*path);
int		one_cmd(t_cmd	*data);
pid_t	exec_cmd(t_cmd *data);
void	ft_close_all(t_cmd *data);
int		cmp_env(char *str1, char *str2);
void	cmp_str_env(char **tmp_env);
void	free_my_env(char	*av);
pid_t	exec_cmd_2(t_cmd *data);
void	free_env(char *av);
void	cmp(char	*av);
int		check_builtin_error(char *str);
char	**copy_2d(char **str1, char **str2);
void	init_tmp_struct(t_tmp	*vars, char *av);
int		check_export_error(char *str);
void	get_path_split_join(t_cmd	*data);
int		theres_eq(char *str);
void	ft_wait(pid_t	f_pid);
void	unset(t_cmd *data);
void	echo(t_cmd	*data);
void	cd(t_cmd	*data);
void	env(void);
void	pwd(void);
void	exit_p(t_cmd	*data);
void	export(t_cmd	*data);
void	free_tab(char **arr);

#endif
