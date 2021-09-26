
#include "libft.h"
#include <stdio.h>
#include "lars_util.h"
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

void	print_group(t_group *group)
{
	int	i = 0;
	printf("size: %i\ntotal_size: %i\nones: ", group->size, group->total_size);
	while (i < group->size)
	{
		printf("[%i] ", group->ones[i]);
		i++;
	}
	printf("\nthrees: ");
	i = 0;
	while (i < group->size)
	{
		printf("[%i, %i, %i] ", group->threes[i].low, group->threes[i].middle, group->threes[i].high);
		i++;
	}
	printf("\n");
}
