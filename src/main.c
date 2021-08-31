/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/31 16:25:58 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "indeces.h"
#include "solve.h"

#include "TMP.h"
int	main(int argc, char *argv[])
{
	t_list	*stack_a;
	t_list	*stack_b;
	// int		nums;
	// int		base;

	(void)stack_a;
	(void)stack_b;
	stack_a = ps_init_stack(argc - 1, &(argv[1]));
	stack_b = NULL;
	ps_transform_to_sorted_indeces(&stack_a);
	// nums = ft_lstsize(stack_a);
	// base = best_base(nums);
	// radix_sort(&stack_a, &stack_b, base);
	printf("can sort: %i\n", brute_force_sort(&stack_a, &stack_b, 2));
	return (EXIT_SUCCESS);
}
