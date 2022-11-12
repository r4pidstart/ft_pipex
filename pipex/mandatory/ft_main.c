/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:04 by tjo               #+#    #+#             */
/*   Updated: 2022/11/12 18:03:29 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

void	error_handling(t_st *str, int type)
{
	if (str->heredoc)
		unlink(str->infile);
	if (type == HEREDOC_IN)
		ft_fprintf(STDERR_FILENO, "Cannot make here_doc tmp file.\n");
	else if (type == INOUT_FD)
		ft_fprintf(STDERR_FILENO, "Cannot find in/out files.\n");
	else if (type == DUP_ERR)
		ft_fprintf(STDERR_FILENO, "Cannot duplicate the file descriptor.\n");
	else if (type == PIPE_ERR)
		ft_fprintf(STDERR_FILENO, "Cannot make a pipe.\n");
	else if (type == FD_CLOSE)
		ft_fprintf(STDERR_FILENO, "Cannot close the file descriptor.\n");
	else if (type == EXECVE_ERR)
		ft_fprintf(STDERR_FILENO, "Cannot execute the command.\n");
	else if (type == NO_PATH)
		ft_fprintf(STDERR_FILENO, "Cannot find a path.\n");
	if (errno)
		ft_fprintf(STDERR_FILENO, "%s\n", strerror(errno));
	exit(1);
}

int	prepare_heredoc(t_st *str, char *limiter)
{
	int		fd;
	int		lim_l;
	char	*tmpline;

	str->heredoc = 1;
	str->infile = "./heredoc_tmp";
	fd = open(str->infile, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		return (1);
	tmpline = get_next_line(0);
	if (!tmpline)
		return (1);
	lim_l = ft_strlen(limiter);
	while (ft_strncmp(limiter, tmpline, lim_l) || tmpline[lim_l] != '\n')
	{
		ft_fprintf(fd, "%s", tmpline);
		free(tmpline);
		tmpline = get_next_line(0);
		if (!tmpline)
			return (1);
	}
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_st	str;

	if (argc < 5)
		return (!ft_printf("invalid arguments\n"));
	str = (t_st){.infile = argv[1], .outfile = argv[argc - 1]};
	if (ft_strncmp(argv[1], "here_doc", -1) == 0)
	{
		if (argc < 6)
			return (!ft_printf("invalid arguments\n"));
		if (prepare_heredoc(&str, argv[2]))
			error_handling(&str, HEREDOC_IN);
	}
	piping(&str, argc, argv);
}