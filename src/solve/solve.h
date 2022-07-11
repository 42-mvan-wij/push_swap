/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solve.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 01:49:29 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/06 14:52:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "libft.h"
# include "operations.h"
# include "utils.h"

int			count_bits(int n, int base, int count_bit_value);
int			best_base(int len);
void		radix_sort(t_data *data, int base);
t_status	brute_force_sort(t_data *ps_data, int max_depth);
t_status	sort_lars(t_data *data);

#endif
