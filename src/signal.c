/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:55 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/09 18:09:56 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static void	ft_ctrl_d(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\033[K");
	rl_redisplay();
	g_sig = 0;
}

static void	ft_ctrl_c(int sig)
{
	(void)sig;
	if (g_sig == IN_HEREDOC)
	{
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else if (g_sig == IN_CMD)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_sig = AFTER_CMD;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig = 1;
}

static void	ft_termios_config(void)
{
	struct termios	trm;

	if (tcgetattr(STDIN_FILENO, &trm) != 0)
		exit((perror("error"), -1));
	else
	{
		trm.c_cc[VQUIT] = _POSIX_VDISABLE;
		trm.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &trm) != 0)
			exit((perror("error"), -1));
		if (tcgetattr(STDIN_FILENO, &trm) != 0)
			exit((perror("error"), -1));
	}
}

void	ft_check_signal(void)
{
	ft_termios_config();
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_d);
}
