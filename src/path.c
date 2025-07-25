/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduyar <dduyar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:09:36 by dduyar            #+#    #+#             */
/*   Updated: 2025/07/20 12:47:49 by dduyar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

char	*ft_get_exact_path(t_token *token, t_shell *shell)
{
	struct stat	buf;
	char		*str;

	buf = (struct stat){0};
	stat(token->value, &buf);
	if (errno == EACCES)
		return (ft_print_err_exec(token, shell, 106, EACCES), NULL);
	if (S_ISDIR(buf.st_mode))
		return (ft_print_err_exec(token, shell, 126, ERR_ISDIR), NULL);
	if (access(token->value, F_OK))
		return (ft_print_err_exec(token, shell, 127, ERR_NO_FILE), NULL);
	if (access(token->value, X_OK))
		return (ft_print_err_exec(token, shell, 126, ERR_PERMISSION), NULL);
	str = ft_strdup(token->value);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_get_path_str(char **env)
{
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}

static char	*ft_check_path(char *temp, t_token *token, t_shell *shell)
{
	char		*path;
	struct stat	buf;

	path = ft_strjoin(temp, token->value, true);
	if (!path)
		return (NULL);
	if (stat(path, &buf) == -1)
		return (path);
	if (S_ISDIR(buf.st_mode))
		return (free(path), ft_print_err_exec(token, shell, 127, ERR_ISDIR),
			NULL);
	return (path);
}

static char	*ft_get_related_path(t_token *token, t_shell *shell,
	char **path_lst)
{
	char	*path;
	int		i;
	char	*temp;

	i = 0;
	if (*token->value == '\0')
		return (ft_print_err_exec(token, shell, 127, ERR_NO_CMD), NULL);
	while (path_lst[i])
	{
		temp = ft_strjoin(path_lst[i++], "/", false);
		if (!temp)
			return (NULL);
		while (token->type != CMD)
			token = token->next;
		path = ft_check_path(temp, token, shell);
		if (!access(path, F_OK) && !access(path, X_OK))
			return (path);
		free(path);
	}
	return (ft_print_err_exec(token, shell, 127, ERR_NO_CMD), NULL);
}

char	*ft_get_path(t_token *token, t_shell *shell)
{
	char	*path;
	char	**path_lst;
	char	*path_lst_str;

	if (ft_strchr(token->value, '/'))
		return (ft_get_exact_path(token, shell));
	if (!shell->env)
		return (ft_print_err_exec(token, shell, 127, ERR_NO_CMD), NULL);
	path_lst_str = ft_get_path_str(shell->env);
	if (!path_lst_str)
		return (NULL);
	path_lst = ft_split(path_lst_str, ':');
	if (!path_lst)
		return (NULL);
	free(path_lst_str);
	path = ft_get_related_path(token, shell, path_lst);
	ft_free_path(path_lst);
	return (path);
}
