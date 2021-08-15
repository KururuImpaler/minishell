/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:25:37 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:29:51 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSHELL_H
# define LIBSHELL_H

# include "shelldata.h"

t_env		*new_env(t_env *env, char *name, char *data, char *val);
t_env		*free_env(t_env *env, char *name, char *data);
t_env		*get_env(t_env *env, char **envp, int n);
char		*find_env(t_env *env, char *name);
char		**get_env_array(t_env *env, int num);

void		ft_exit(int error);
int			free_all(char *command, int error);

void		start_write(int fd);
int			end_write(int fd);
void		multiline_write(int fd);

char		*ft_subarg(char *s, int j, int n, int m);

char		*get_command(char *command, int i);
void		ft_save_char(char c);
int			test_syntax(char *s, int j);
void		test_syntax_2(t_cmd *cmd);
char		*free_command(char *command, int error);
t_cmd		*free_command_2(char *command, int error);
int			free_args(t_list_args *args, t_list_args *list);

t_cmd		*free_cmd(t_cmd *cmd);
int			get_file_read(t_list_args *list, int fd);
t_cmd		*new_command(t_cmd *cmd, char **arg, char pipe, int ac);
int			len_arr(char **arr);
t_cmd		*separator(void);

int			run_commands(void);
int			ft_pipe_cmd(t_cmd **cmd, int i, int j);
int			ft_next_cmd(t_cmd **cmd);
int			fd_file(t_cmd *cmd);
int			get_pipe(int ***fd, pid_t **pid, t_cmd *cmd);
int			error_run(t_cmd *cmd);
int			pathcmp1(t_cmd *cmd, char *path);
char		*get_path1(t_cmd *cmd, char *path, int j, int n);

void		zero(void);
int			zero_1(void);
char		*zero_2(void);

void		sigint(int n);
void		sigquit(int n);

char		*ft_error(int n);
int			free_errors_string(void);
int			free_pipe(int	**fd, pid_t *pid);

int			skip_space(char *s, int i);
int			skip_quotes(char c1, char c2, char q, int i);
int			skip_to_space(char *s, int i);

int			parse_command(char *command);
t_list_args	*swipe_list(t_list_args *list, int i);

int			copy_env_in_arg_2(char *s, char *str, int m, int *n);
int			copy_env_in_arg(char *s, char *str, int m, int *n);
int			ft_len_arg_2(char *s, int *i, int true_len);
char		*ft_len_arg(char *s, int len, int *j, char *str);

int			ft_write_error(int error, t_cmd *cmd);

int			free_arr(char **arr);
int			ft_check_cpy(t_list_args *cpy, char ***str, int n);

t_env		*delete_env(t_env *env, char *name);

int			ft_strcmp(const char *s1, const char *s2);
int			check_func(t_env *env, t_cmd *cmd);
void		func_cd(t_cmd *cmd, t_env *env, int ac);
void		check_error(char *ar, int flag);
int			check_flag(t_cmd *cmd, int i);
void		func_pwd(void);
void		func_echo(t_cmd *cmd);
void		func_export(t_cmd *cmd, t_env *env);
void		env_print(t_env *env);
void		func_env(t_env *env, t_cmd *cmd);
void		func_unset(t_env *env, t_cmd *cmd);
void		func_exit(t_cmd *cmd);
char		*finder(char *str, t_env *env);

#endif
