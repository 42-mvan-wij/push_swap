/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/14 14:18:15 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "indeces.h"
#include "solve.h"

typedef	enum	e_solvers {
	RADIX,
	BRUTE_FORCE,
	LARS
}	t_solvers;

void	sort_lars(t_list **stack_a, t_list **stack_b);
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

	t_solvers	solver = LARS;
	/* radix sort: */
	if (solver == RADIX)
	{
		int nums = ft_lstsize(stack_a);
		int base = best_base(nums);
		radix_sort(&stack_a, &stack_b, base);
	}
	/* lars' sorting alg: */
	else if (solver == LARS)
	{
		sort_lars(&stack_a, &stack_b);
	}
	/* brute force sort: */
	else if (solver == BRUTE_FORCE)
	{
		brute_force_sort(&stack_a, &stack_b, 8);
	}
	ft_lstclear(&stack_a, NULL);
	ft_lstclear(&stack_b, NULL);
	return (EXIT_SUCCESS);
}
