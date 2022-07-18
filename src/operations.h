/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 22:59:12 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/07/14 12:14:25 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "libft.h"
# include "error.h"

typedef enum e_cmd
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	NO_REDUCTION,
	NONE,
}	t_cmd;

typedef struct s_data
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*ops;
}	t_data;

t_status	ps_reduce_ops(t_list **ops);
t_status	ps_exec_store(t_cmd cmd, t_data *data);
void		ps_print_ops(t_list *ops);
int			ps_exec(t_cmd cmd, t_list **stack_a, t_list **stack_b);
void		ps_undo(t_cmd cmd, t_list **stack_a, t_list **stack_b);

int			ps_swap(t_list **stack);
int			ps_push(t_list **to_stack, t_list **from_stack);
int			ps_rotate(t_list **stack);
int			ps_reverse_rotate(t_list **stack);

int			ps_swap2(t_list **stack_a, t_list **stack_b);
int			ps_rotate2(t_list **stack_a, t_list **stack_b);
int			ps_reverse_rotate2(t_list **stack_a, t_list **stack_b);

#endif
