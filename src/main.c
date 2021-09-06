/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 18:19:09 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "indeces.h"
#include "solve.h"

typedef	enum	e_solvers {
	RADIX,
	BUCKET,
	BRUTE_FORCE
}	t_solvers;

#include "TMP.h"
int	main(int argc, char *argv[])
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = ps_init_stack(argc - 1, &(argv[1]));
	stack_b = NULL;
	if (ps_is_sorted(stack_a, stack_b))
		return (EXIT_SUCCESS);
	ps_transform_to_sorted_indeces(&stack_a);

	t_solvers	solver = BUCKET;
	/* radix sort: */
	if (solver == RADIX)
	{
		int nums = ft_lstsize(stack_a);
		int base = best_base(nums);
		radix_sort(&stack_a, &stack_b, base);
	}
	/* bucket sort: */
	else if (solver == BUCKET)
	{
		bucket_sort(&stack_a, &stack_b);
	}
	/* brute force sort: */
	else if (solver == BRUTE_FORCE)
	{
		if (brute_force_sort(&stack_a, &stack_b, 8))
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
