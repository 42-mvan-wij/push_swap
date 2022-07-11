/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   radix_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 15:07:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/11 17:41:59 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operations.h"

static t_status	move_to_b(t_data *data, int digit, int base)
{
	int	i;
	int	val;
	int	len;

	i = 0;
	while (i < base - 1)
	{
		len = ft_lstsize(data->stack_a);
		while (len > 0)
		{
			val = ((long)(data->stack_a)->content / digit) % base;
			if (val == i)
				ps_exec_store(PB, data);
			else
				ps_exec_store(RA, data);
			if (ps_get_error() != OK)
				return (ps_get_error());
			len--;
		}
		i++;
	}
	return (OK);
}

t_status	radix_sort(t_data *data, int base)
{
	int		len;
	int		digit;

	len = ft_lstsize(data->stack_a);
	digit = 1;
	while ((len - 1) / digit != 0)
	{
		if (move_to_b(data, digit, base) != OK)
			return (ps_get_error());
		while (data->stack_b != NULL)
			ps_exec_store(PA, data);
		if (ps_get_error() != OK)
			return (ps_get_error());
		digit *= base;
		len = ft_lstsize(data->stack_a);
	}
	return (OK);
}
