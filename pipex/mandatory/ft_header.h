/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:50:06 by tjo               #+#    #+#             */
/*   Updated: 2022/11/13 18:25:26 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

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

/* ft_main.c */
void	error_handling(t_st *str);

/* ft_piping.c */
void	piping(t_st *str, int argc, char **argv);

#endif