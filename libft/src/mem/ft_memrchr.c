/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:15:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/15 19:45:26 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Search for last occurrence of @p c in memory at @p ptr with length @p n
 * @param ptr
 * @param c
 * @param n
 * @return NULL if @p c cannot be found
 */
void	*ft_memrchr(const void *ptr, int c, size_t n)
{
	const unsigned char	*mem = ptr;

	while (n > 0)
	{
		n--;
		if (mem[n] == (unsigned char)c)
			return ((void *)ptr + n);
	}
	return (NULL);
}
