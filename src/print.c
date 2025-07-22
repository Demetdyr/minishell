/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:41 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/22 19:11:35 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	fdprint(int fd, const char *s)
{
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

void	fdprintln(int fd, const char *s)
{
	if (fd < 0)
		return ;
	fdprint(fd, s);
	fdprint(fd, "\n");
}

void	errprint(const char *str)
{
	fdprint(STDERR_FILENO, str);
}

void	errprintln(const char *str)
{
	fdprintln(STDERR_FILENO, str);
}

void	fdprintn(int fd, const char *str, size_t n)
{
	if (!str)
		return ;
	write(fd, str, n);
}
