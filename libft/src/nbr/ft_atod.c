/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atod.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/11 00:37:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/24 17:04:43 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts @p str to a double
 * @param str
 * @return
 */
double	ft_atod(char *str)
{
	double	int_part;
	double	float_part;
	int		is_neg;

	while (ft_isspace(*str))
		str++;
	int_part = (double)ft_atoi(str, NULL);
	is_neg = (*str == '-');
	if (*str == '+' || is_neg)
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != '.' || !ft_isdigit(str[1]))
		return (int_part);
	str++;
	float_part = (double)ft_atoi(str, NULL);
	while (ft_isdigit(*str))
	{
		str++;
		float_part /= (double)10;
	}
	if (is_neg)
		return (int_part - float_part);
	return (int_part + float_part);
}
