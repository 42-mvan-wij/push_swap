#include "libft.h"
#include <stdio.h>
void	print_stacks(t_list *stack_a, t_list *stack_b) {
	while (stack_a != NULL) {
		printf("|%li\t|", (long)stack_a->content);
		if (stack_b != NULL) {
			printf("%li\t|\n", (long)stack_b->content);
			stack_b = stack_b->next;
		}
		else
			printf("\t|\n");
		stack_a = stack_a->next;
	}
	while (stack_b != NULL) {
		printf("|\t|%li\t|\n", (long)stack_b->content);
		stack_b = stack_b->next;
	}
}
