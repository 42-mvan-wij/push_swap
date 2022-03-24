/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_calc_core.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:41:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/23 19:20:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	in_own_column_until_all_2s_or_0(int pow)
{
	return (pow);
}

static int	in_right_columns_from_2s_down(int pow, int base, int index,
												int digit)
{
	const int	blocks = digit;
	const int	columns = index;
	const int	count_per_column = pow / base;

	return (count_per_column * columns * blocks);
}

static int	in_block(int width, int n, int pow)
{
	const int	n_to_the_right = n % pow;
	const int	rows_until_all_2s = n_to_the_right + 1;
	const int	height = rows_until_all_2s;

	return (width * height);
}

static void	init_count_bits(int *pow, int *index, int *count, int *width)
{
	*pow = 1;
	*index = 0;
	*count = 0;
	*width = 0;
}

/*	start	own_col	right	block	zero	zero	own_col	right	block
	1002	1002	1002	1002					1002	1002	1--2
	1001	1001	1001	1001					1001	1001	1--1
	1000	100-	100-	100-					100-	100-	1---
	0222	0222	0222	0222					-222	-222	-222
	0221	0221	0221	0221					-221	-221	-221
	0220	0220	0220	0220					-220	-22-	-22-
	0212	0212	0212	0212					-212	-212	-212
	0211	0211	0211	0211					-211	-211	-211
	0210	0210	0210	0210					-210	-21-	-21-
	0202	0202	0202	0202					-202	-2-2	-2-2
	0201	0201	0201	0201					-201	-2-1	-2-1
	0200	0200	0200	0200					-200	-2--	-2--
	0122	0122	0122	0122					-122	-122	-122
	0121	0121	0121	0121					-121	-121	-121
	0120	0120	0120	0120					-120	-12-	-12-
	0112	0112	0112	0112					-112	-112	-112
	0111	0111	0111	0111					-111	-111	-111
	0110	0110	0110	0110					-110	-11-	-11-
	0102	0102	0102	0102					-102	-1-2	-1-2
	0101	0101	0101	0101					-101	-1-1	-1-1
	0100	0100	0100	0100					-100	-1--	-1--
	0022	0022	0022	0022					-022	--22	--22
	0021	0021	0021	0021					-021	--21	--21
	0020	0020	0020	0020					-020	--2-	--2-
	0012	0012	0012	0012					-012	--12	--12
	0011	0011	0011	0011					-011	--11	--11
	0010	0010	0010	0010					-010	--1-	--1-
	0002	0002	0002	0002					-002	---2	---2
	0001	0001	0001	0001					-001	---1	---1
	0000	0000	0000	0000					-000	----	----
*/
int	count_bits(int n, int base, int count_bit_value)
{
	int	pow;
	int	count;
	int	digit;
	int	index;
	int	width;

	init_count_bits(&pow, &index, &count, &width);
	while (n / pow != 0)
	{
		digit = (n / pow) % base;
		if (digit == count_bit_value)
			width++;
		if (digit > count_bit_value)
			count += in_own_column_until_all_2s_or_0(pow);
		if (digit != 0)
		{
			count += in_right_columns_from_2s_down(pow, base, index, digit);
			count += in_block(width, n, pow);
			width = 0;
		}
		pow *= base;
		index++;
	}
	return (count);
}
