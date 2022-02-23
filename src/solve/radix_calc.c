/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_calc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:41:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/23 14:32:03 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @param n number (written in base @p b)
 * @param b base to write @p n and @p v in
 * @param v digit value to count
 *
 * @example count_bits(5, 3, 2) = 2:
 * 5b10 = 12b3
 * Counting `2`s in the following sequence gives 2:
 * 12
 * 11
 * 10
 * 02
 * 01
 *
 * @example count_bits(5, 3, 0) = 3:
 * 5b10 = 12b3
 * Counting `0`s in the following sequence gives 3:
 * 12
 * 11
 * 10
 * 02
 * 01
 */
static int	count_bits(int n, int base, int digit)
{
	int	pow;
	int	count;
	int	bit;
	int	digit_i;
	int	digits;

	pow = 1;
	digit_i = 0;
	count = 0;
	digits = 0;
	while (n / pow != 0)
	{
		bit = (n / pow) % base;
		if (bit == digit)
			digits++;
		else if (bit > digit)
			count += pow;
		if (bit != 0)
			count += pow / base * digit_i * bit + digits * (n % pow) + digits;
		if (bit != 0)
			digits = 0;
		pow *= base;
		digit_i++;
	}
	return (count);
}

int	count_ops(int len, int base)
{
	int	v;
	int	count;

	count = 0;
	v = 0;
	while (v < base - 1)
	{
		count += count_bits(len - 1, base, v) * (v + 2);
		v++;
	}
	count += count_bits(len - 1, base, v) * v;
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
