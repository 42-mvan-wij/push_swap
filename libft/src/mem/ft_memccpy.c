/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:51:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/15 19:34:51 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies @p src to @p dst until either @p n bytes
 * or a byte with value @p c has been reached
 * @param dst
 * @param src
 * @param c
 * @param n size to copy
 * @return pointer to char after @p c in @p dst
 * or NULL if @p not is not found in @p src
 */
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char	*from = src;
	char		*to;
	size_t		i;

	to = dst;
	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		if ((unsigned char)from[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
