/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:12:12 by afelten           #+#    #+#             */
/*   Updated: 2023/04/11 14:12:17 by afelten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

# include "libft.h"

typedef struct s_io_data
{
	char	*infile;
	char	*outfile;
	char	*heredoc_del;
	int		in_fd;
	int		out_fd;
}	t_io_data;

typedef struct s_command
{
	char				*str;
	char				**args;
	int					pipe_fd[2];
	t_io_data			io_data;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char		*line;
	char		**env;
	char		*old_work_dir;
	char		*work_dir;
	int			status;
	t_token		*tokens;
	t_command	*commands;
}	t_data;

typedef struct s_exp_var
{
	t_data	*data;
	char	**args;
	char	*str;
	int		start;
	int		end;
	int		status;
	int		pos;
}	t_exp_var;

enum	e_token {
	WORD,
	PIPE,
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND,
	END
};

enum	e_quote {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

int			init_data(t_data *data, char **env);

int			lexer(t_data *data);
t_token		*create_token(char *str, int type);
void		add_token(t_token **tokens, t_token *new);
t_token		*get_last_token(t_token **tokens);
int			check_syntax(t_data *data, int end);

char		*ft_strndup(const char *s1, int len);
int			is_space(char c);
int			is_operator(char *line);
int			set_quote_status(int status, char c);

void		error_msg(char *msg, char *token, int quoting);
int			perror_return(t_data *data, char *str);
int			perror_cmd_return(t_data *data, char *str);
int			print_error(int start, char *cmd, char *str);

void		free_tokens(t_token *tokens);
void		free_data(t_data *data);
void		free_str_array(char **strs);
void		exit_shell(t_data *data);

char		*get_var_env(t_data *data, char *var);
int			get_var_size(t_data *data, char *var);

int			replace_var_heredoc(char **str, int heredoc, t_data *data);
char		**expand_var(t_data *data, char *str);
int			ft_strs_len(char **strs);

int			rm_quotes(char **str);
int			get_nbr_quotes(char *str);

int			init_parse_io(t_command *command, t_token **token,
				int input, t_data *data);

void		free_output(t_command *command);
void		free_input(t_command *command);

t_command	*init_command(void);
void		add_command(t_command **commands, t_command *new);

int			parser(t_data *data);
int			parse_input(t_command *command, t_token **token, t_data *data);
int			parse_trunc(t_command *command, t_token **token, t_data *data);
int			parse_append(t_command *command, t_token **token, t_data *data);
int			parse_heredoc(t_command *command, t_token **token, t_data *data);
char		**add_str_arr(char **strs, char *str);
char		**add_strs_to_array(char **strs1, char **strs2);

void		close_pipes(t_command *commands, t_command *cmd);
int			create_pipes(t_command *commands, t_data *data);
int			redirect_io(t_command *command, t_data *data);

int			execution(t_data *data);
int			execute_builtin(t_data *data, t_command *command);
int			execute_env_cmd(t_data *data, t_command *command);
int			execute_local_cmd(t_data *data, t_command *command);
int			is_dir(char *cmd);
char		**get_path(t_data *data);
char		*get_cmd_path(t_data *data, char **path, char *cmd);
int			is_builtin(char *str);

void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

int			free_return(void *p);
int			ft_strs_len(char **strs);
int			is_env_var(char *str);

int			cd_builtin(t_data *data, char **strs);
int			env_builtin(t_data *data, char **strs, int export);
int			echo_builtin(char **strs);
int			pwd_builtin(t_data *data);
int			exit_builtin(t_data *data, char **strs);
int			check_env_var(char *var);
int			env_var_count(char **env);
int			get_env_var_index(char **env, char *var);
int			delete_env_var(t_data *data, int i);
void		free_str(char *str);
int			unset_builtin(t_data *data, char **strs);
int			add_env_var(t_data *data, char *key, char *value);
int			export_builtin(t_data *data, char **args);
char		*get_env_var_value(char **env, char *str);
int			error_cmd(char *command, char *detail, char *error, int nb);

#endif
