/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/07 15:55:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "indeces.h"
#include "solve.h"
#include "operations.h"

t_status	select_and_run(t_data *data, int size)
{
	if (size <= 5)
		brute_force_sort(data, 8);
	else if (size <= 500)
		sort_lars(data);
	else
		radix_sort(data, best_base(size));
	return (ps_get_error());
}

t_status	routine(t_data *data)
{
	if (ps_is_sorted(data->stack_a, data->stack_b))
		return (OK);
	if (ps_transform_to_sorted_indeces(&data->stack_a) != OK)
		return (ps_get_error());
	if (select_and_run(data, ft_lstsize(data->stack_a)) != OK)
		return (ps_get_error());
	ft_lstreverse(&data->ops);
	ft_putnbr_fd(ft_lstsize(data->ops), 2); // tmp
	ft_putchar_fd('\n', 2); // tmp
	if (ps_reduce_ops(&data->ops) != OK)
		return (ps_get_error());
	ft_putnbr_fd(ft_lstsize(data->ops), 2); // tmp
	ft_putchar_fd('\n', 2); // tmp
	return (OK);
}

void	print_error(void)
{
	static char	*error_text[] = {
	[OK] = "lol, get prankt!",
	[E_MALLOC] = "Error",
	[E_EXPECTED_INT] = "Error",
	[E_DUPLICATE] = "Error",
	[E_GNL] = "Error",
	[E_TOO_DEEP] = "Error",
	};

	ft_putendl_fd(error_text[ps_get_error()], STDERR_FILENO);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.ops = NULL;
	data.stack_b = NULL;
	if (ps_init_stack(argc - 1, &(argv[1]), &data.stack_a) != OK
		|| routine(&data) != OK)
	{
		ft_lstclear(&data.ops, NULL);
		ft_lstclear(&data.stack_a, NULL);
		ft_lstclear(&data.stack_b, NULL);
		print_error();
		return (EXIT_FAILURE);
	}
	ps_print_ops(data.ops);
	ft_lstclear(&data.ops, NULL);
	ft_lstclear(&data.stack_a, NULL);
	ft_lstclear(&data.stack_b, NULL);
	return (EXIT_SUCCESS);
}
