/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/23 19:24:28 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "indeces.h"
#include "solve.h"
#include "operations.h"

void	select_and_run(t_list **stack_a, t_list **stack_b, int size)
{
	if (size <= 5)
		brute_force_sort(stack_a, stack_b, 8);
	else if (size <= 750)
		sort_lars(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b, best_base(size));
}

int	main(int argc, char *argv[])
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = ps_init_stack(argc - 1, &(argv[1]));
	stack_b = NULL;
	if (ps_is_sorted(stack_a, stack_b))
		return (EXIT_SUCCESS);
	ps_transform_to_sorted_indeces(&stack_a);
	select_and_run(&stack_a, &stack_b, ft_lstsize(stack_a));
	ft_lstclear(&stack_a, NULL);
	ft_lstclear(&stack_b, NULL);
	return (EXIT_SUCCESS);
}
