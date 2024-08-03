/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:22:06 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/03 22:55:40 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	words_counts(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		is_word;

	is_word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_word = 0;
		else if (!is_word)
		{
			count++;
			is_word = 1;
		}
		i++;
	}
	return (count);
}

static size_t	next_len(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static char	*next_word(char const **s, char c, t_free **collector)
{
	size_t	i;
	char	*p;
	size_t	next_lens;

	while (**s && **s == c)
		(*s)++;
	next_lens = next_len(*s, c);
	p = ft_malloc(collector, next_lens + 1);
	i = 0;
	while (i < next_lens)
	{
		p[i] = **s;
		i++;
		(*s)++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c, t_free **collector)
{
	size_t	n_words;
	char	**p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	n_words = words_counts(s, c);
	p = ft_malloc(collector, sizeof(char *) * (n_words + 1));
	while (i < n_words)
	{
		*(p + i) = next_word(&s, c, collector);
		if (!p[i])
		{
			while (i > 0)
				ft_free_ptr(collector, p[--i]);
			ft_free_ptr(collector, p);
			return (NULL);
		}
		i++;
	}
	p[i] = NULL;
	return (p);
}
