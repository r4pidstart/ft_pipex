/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_piping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:45:46 by tjo               #+#    #+#             */
/*   Updated: 2022/11/09 04:21:16 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

extern char	**environ;

char	*find_path(t_st *str, char *cmd)
{
	int		idx;
	char	**paths;
	char	*tmp[3];

	idx = 0;
	while (ft_strncmp(environ[idx], "PATH=", 5))
		idx++;
	paths = ft_split(environ[idx] + 5, ':');
	idx = 0;
	tmp[2] = 0;
	if (!paths)
		error_handling(str, NO_PATH);
	while (paths[idx])
	{
		tmp[0] = ft_strjoin(paths[idx], "/");
		tmp[1] = ft_strjoin(tmp[0], cmd);
		if (access(tmp[1], X_OK) == 0 && !tmp[2])
			tmp[2] = ft_strdup(tmp[1]);
		free(paths[idx++]);
		free(tmp[0]);
		free(tmp[1]);
	}
	free(paths);
	return (tmp[2]);
}

void	exec(t_st *str, char *cmd)
{
	char	**parsed;

	parsed = ft_split(cmd, ' ');
	if (access(cmd, X_OK) == 0)
		if (execve(parsed[0], &parsed[0], environ) == -1)
			error_handling(str, 0);
	if (execve(find_path(str, parsed[0]), &parsed[0], environ) == -1)
		error_handling(str, 0);
}

void	make_child(t_st *str, char *cmd)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	if (pid == -1 || pipe(fd) == -1 || dup2(STDIN_FILENO, fd[0]) == -1)
		error_handling(str, 0);
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error_handling(str, 0);
		exec(str, cmd);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1 || \
		close(fd[0]) == -1 || close(fd[1]) == -1)
		error_handling(str, 0);
	waitpid(pid, 0, 0);
}

void	piping(t_st *str, int argc, char **argv)
{
	int	idx;

	str->infile_fd = open(str->infile, O_RDONLY);
	str->outfile_fd = open(str->outfile, O_WRONLY | \
		!str->heredoc * O_TRUNC | O_CREAT, 0777);
	if (!str->infile_fd || !str->outfile_fd)
		error_handling(str, 0);
	idx = 2 + str->heredoc;
	if (dup2(str->infile_fd, STDIN_FILENO) == -1)
		error_handling(str, 0);
	while (idx < argc - 2)
		make_child(str, argv[idx++]);
	if (dup2(str->outfile_fd, STDOUT_FILENO) == -1)
		error_handling(str, 0);
	exec(str, argv[idx]);
}