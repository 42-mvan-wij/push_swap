/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:33:52 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/24 17:16:12 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/**
 * Converts @p str to an integer
 * @param str
 * @return
 */
int	ft_atoi(const char *str, bool *had_overflow)
{
	int		offset;
	long	result;
	int		is_neg;

	if (had_overflow != NULL)
		*had_overflow = false;
	offset = 0;
	while (str[offset] != '\0' && ft_isspace(str[offset]))
		offset++;
	result = 0;
	is_neg = (str[offset] == '-');
	if (is_neg || str[offset] == '+')
		offset++;
	while (ft_isdigit(str[offset]))
	{
		result *= 10;
		result -= str[offset] - '0';
		if (had_overflow != NULL && ((is_neg && result != (int)result) \
		|| (!is_neg && (-result) != (int)-result)))
			*had_overflow = true;
		offset++;
	}
	if (is_neg)
		return (result);
	return (-result);
}
