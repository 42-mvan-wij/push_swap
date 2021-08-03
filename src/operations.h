/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 22:59:12 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/08/03 14:57:48 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "libft.h"

void	ps_exec(char *cmd, t_list **stack_a, t_list **stack_b);
void	ps_exec_print(char *cmd, t_list **stack_a, t_list **stack_b);

void	ps_swap(t_list **stack);
void	ps_push(t_list **to_stack, t_list **from_stack);
void	ps_rotate(t_list **stack);
void	ps_reverse_rotate(t_list **stack);

void	ps_swap2(t_list **stack_a, t_list **stack_b);
void	ps_rotate2(t_list **stack_a, t_list **stack_b);
void	ps_reverse_rotate2(t_list **stack_a, t_list **stack_b);

#endif
