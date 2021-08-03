/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 14:59:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 15:13:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "indeces.h"

#include "TMP.h"
void	sort(t_list **stack_a, t_list **stack_b);
int	main(int argc, char *argv[])
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		nums;

	stack_a = ps_init_stack(argc - 1, &(argv[1]));
	stack_b = NULL;
	ps_transform_to_sorted_indeces(&stack_a);
	nums = ft_lstsize(stack_a);
	sort(&stack_a, &stack_b);
	print_stacks(stack_a, stack_b);
}
