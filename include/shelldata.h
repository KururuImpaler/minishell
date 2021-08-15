/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelldata.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:17:07 by cmalt             #+#    #+#             */
/*   Updated: 2020/10/22 19:34:58 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLDATA_H
# define SHELLDATA_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define FILENOTFOUND 1
# define NOFILEORDIR 4

typedef struct			s_env
{
	char				*name;
	char				*val;
	char				*data;
	struct s_env		*next;
}						t_env;

typedef struct			s_list_args
{
	char				*arg;
	char				pipe;
	int					quotes;
	struct s_list_args	*next;
}						t_list_args;

typedef struct			s_cmd
{
	char				**args;
	char				pipe;
	int					ac;
	char				*file;
	int					fd;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_error
{
	char				*er1;
	char				*er2;
	char				*er3;
}						t_error;

typedef struct			s_pipe
{
	pid_t				*pid;
	int					**fd;
}						t_pipe;

typedef struct			s_shell
{
	t_error				errors;
	int					run;
	t_env				*env;
	int					exit;
	int					num_env;
	char				*ret_val;
	int					error;
	int					pipes;
	int					quotes;
	char				**bin_path;
	char				**envp;
	t_cmd				*commands;
	t_list_args			*args;
	int					num_args;
	char				**arr;
	int					next_cmd;
	int					fd_cmd;
	char				*file_cmd;
	int					signal;
	t_pipe				pid_fd;
	int					syntax_error;
	int					flag;
	int					now_fd[2];
	int					stop_run;
	char				c[2];
}						t_shell;

t_shell					g_shell;

#endif
