/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:06 by tjo               #+#    #+#             */
/*   Updated: 2022/11/12 18:05:54 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_BONUS_H
# define FT_HEADER_BONUS_H

# include<fcntl.h>
# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<errno.h>
# include"../ft_mylibft/libft.h"

typedef struct s_st
{
	char	*infile;
	char	*outfile;
	int		heredoc;
	int		infile_fd;
	int		outfile_fd;
}t_st;

enum e_type
{
	HEREDOC_IN = 1,
	INOUT_FD = 2,
	DUP_ERR = 3,
	PIPE_ERR = 4,
	FD_CLOSE = 5,
	EXECVE_ERR = 6,
	NO_PATH = 7
};

/* ft_main.c */
void	error_handling(t_st *str, int type);

/* ft_piping.c */
void	piping(t_st *str, int argc, char **argv);

#endif