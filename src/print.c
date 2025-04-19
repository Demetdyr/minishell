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
