/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_calc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:41:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/23 19:21:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solve.h"

int	count_ops(int len, int base)
{
	int	bit_value;
	int	count;

	count = 0;
	bit_value = 0;
	while (bit_value < base - 1)
	{
		count += count_bits(len - 1, base, bit_value) * (bit_value + 2);
		bit_value++;
	}
	count += count_bits(len - 1, base, bit_value) * bit_value;
	return (count);
}

int	best_base(int len)
{
	int	base;
	int	best_base;
	int	best_value;
	int	value;

	best_value = count_ops(len, 2);
	best_base = 2;
	base = 3;
	while (base < 100)
	{
		value = count_ops(len, base);
		if (value < best_value)
		{
			best_value = value;
			best_base = base;
		}
		base++;
	}
	return (best_base);
}
