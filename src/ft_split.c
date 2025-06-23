#include "../inc/minishell.h"

static char	**ft_free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static int	ft_total_word_count(const char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			i++;
		}
		else
		{
			count++;
			while (str[i] && str[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static char	*ft_putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (j < word_len)
	{
		word[j] = s[i + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_word(char const *s, char c, char **new_s, int total_word)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	while (word < total_word)
	{
		word_len = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		new_s[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!new_s[word])
			return (ft_free_array(new_s, word));
		ft_putword(new_s[word], s, i - word_len, word_len);
		word++;
	}
	new_s[word] = NULL;
	return (new_s);
}

char	**ft_split(char const *s, char c)
{
	char			**new_s;
	unsigned int	total_word;

	if (!s)
	{
		return (0);
	}
	total_word = ft_total_word_count(s, c);
	new_s = (char **)malloc(sizeof(char *) * (total_word + 1));
	if (!new_s)
	{
		return (0);
	}
	new_s = ft_split_word(s, c, new_s, total_word);
	return (new_s);
}
