/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:04 by tjo               #+#    #+#             */
/*   Updated: 2022/11/12 15:53:26 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

void	error_handling(t_st *str, int type)
{
	ft_fprintf(STDERR_FILENO, "some error occured");
	if (str->heredoc)
		unlink(str->infile);
	if (type == NO_PATH)
		ft_fprintf(STDERR_FILENO, "Cannot find a path.\n");
	else
		strerror(errno);
	ft_fprintf(STDERR_FILENO, ": %d\n", type);
	exit(1);
}

int	prepare_heredoc(t_st *str, char *limiter)
{
	int		fd;
	char	*tmpline;

	str->heredoc = 1;
	str->infile = "./heredoc_tmp";
	fd = open(str->infile, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		return (1);
	tmpline = get_next_line(0);
	if (!tmpline)
		return (1);
	while (ft_strncmp(limiter, tmpline, ft_strlen(tmpline) - 1))
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

	// if (argc < 5)
	// 	return (!ft_printf("invalid arguments\n"));
	str = (t_st){.infile = argv[1], .outfile = argv[argc - 1]};
	if (ft_strncmp(argv[1], "here_doc", -1) == 0)
	{
		if (argc < 6)
			return (!ft_printf("invalid arguments\n"));
		if (prepare_heredoc(&str, argv[2]))
			error_handling(&str, 8);
	}
	piping(&str, argc, argv);
}