#include "../inc/minishell.h"
#include <stdlib.h>

t_token	*ft_token_get_root(t_token *node)
{
	if (!node)
		return (NULL);
	while (node && node->prev)
		node = node->prev;
	return (node);
}
