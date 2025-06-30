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

char	**ft_str_lst_add(char **lst, char *value)
{
	char	**new_lst;
	int		i;
	int		len;

	if (!lst || !value)
		return (NULL);
	i = 0;
	while (lst[i])
		i++;
	len = i;
	new_lst = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_lst)
		return (NULL);
	i = 0;
	while (lst[i])
	{
		new_lst[i] = lst[i];
		i++;
	}
	new_lst[i++] = value;
	new_lst[i] = NULL;
	free(lst);
	return (new_lst);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		num;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

int	ft_env_size(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		return (0);
	while (shell->env[i])
		i++;
	return (i);
}
