/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_calc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:41:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/07 16:57:34 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	count_bits(int n, int b, int v)
{
	int	pow;
	int	count;
	int	bit;
	int	i;
	int	vs;

	pow = 1;
	i = 0;
	count = 0;
	vs = 0;
	while (n / pow != 0)
	{
		bit = n / pow % b;
		if (bit == v)
			vs++;
		else if (bit > v)
			count += pow;
		if (bit != 0)
			count += pow / b * i * bit + vs * (n % pow) + vs;
		if (bit != 0)
			vs = 0;
		pow *= b;
		i++;
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
	int	b;
	int	bb;
	int	bv;
	int	v;

	bv = count_ops(len, 2);
	bb = 2;
	b = 3;
	while (b < 100)
	{
		v = count_ops(len, b);
		if (v < bv)
		{
			bv = v;
			bb = b;
		}
		b++;
	}
	return (bb);
}
