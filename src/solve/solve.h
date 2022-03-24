/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solve.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:49:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/23 19:22:12 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "libft.h"

int		count_bits(int n, int base, int count_bit_value);
int		best_base(int len);
void	radix_sort(t_list **stack_a, t_list **stack_b, int base);
int		brute_force_sort(t_list **stack_a, t_list **stack_b, int max_depth);
void	sort_lars(t_list **stack_a, t_list **stack_b);

#endif
