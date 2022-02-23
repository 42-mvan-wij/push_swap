/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:46:34 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/15 19:45:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Sets @p len bytes at @p p to @p c
 * @param p
 * @param c
 * @param len
 */
void	*ft_memset(void *p, int c, size_t len)
{
	while (len)
	{
		((unsigned char *)p)[len - 1] = (unsigned char)c;
		len--;
	}
	return (p);
}
