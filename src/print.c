/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:41 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:42 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

void	fdprint(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

void	fdprintln(int fd, const char *s)
{
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
