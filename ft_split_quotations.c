/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_split_quotations.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 15:49:39 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/30 15:59:40 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_substrings(char **strings_array, int j)
{
	while (j >= 0)
	{
		free(strings_array[j]);
		j--;
	}
	free(strings_array);
}

static int	word_length(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static int	sentence_length(char const *s, int i)
{
	int	j;

	j = 0;
	while ((s[i] != 39 && s[i] != 34) && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	**split_words_quotations(char **str_array,
		char const *s, char c, int words)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (j < words && s[i])
	{
		while (s[i] == c || ((s[i] == 39 || s[i] == 34) && s[i + 1] == c))
			i++;
		if (s[i] == 39 || s[i] == 34)
			len = sentence_length(s, ++i);
		else
			len = word_length(s, i, c);
		str_array[j] = ft_substr(s, i, len);
		if (!str_array[j])
			return (free_substrings(str_array, j), NULL);
		i += len;
		j++;
	}
	return (str_array);
}

char	**ft_split_quotations(char const *s, char c)
{
	char	**str_array;
	int		words;

	words = ft_word_counter_quotations(s, c);
	str_array = ft_calloc(words + 1, sizeof(char *));
	if (!str_array)
		return (0);
	str_array = split_words_quotations(str_array, s, c, words);
	if (!str_array)
		return (0);
	return (str_array);
}
