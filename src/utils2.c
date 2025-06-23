#include "../inc/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, bool flag_free)
{
	char	*buf;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	buf = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		buf[j++] = s1[i++];
	i = 0;
	while (s2[i])
		buf[j++] = s2[i++];
	buf[j] = '\0';
	if (flag_free)
		free((void *)s1);
	return (buf);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
