/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:17:55 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/15 19:41:27 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Compares @p n bytes of memory at @p p1 and @p p2
 * @param p1
 * @param p2
 * @param n
 * @return 0 if equal, *@p p1 - *@p p2 where a difference has been found
 */
int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	size_t				i;
	const unsigned char	*s1 = p1;
	const unsigned char	*s2 = p2;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
