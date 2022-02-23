# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/07 17:00:31 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/02/23 14:35:02 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PROJECT    = push_swap
NAME       = push_swap
NAME_BONUS = checker
LIBFT      = libft/libft.a

CC	   = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
ifdef DEBUG
CFLAGS += -g
endif

LIBS = -L$(dir $(LIBFT)) -lft
HEADERS = 	libft/libft.h	\
			src/push_swap.h

SOURCES =	src/exec_ops.c	\
			src/rotate.c	\
			src/swap_push.c	\
			src/utils.c		\
			src/TMP.c

ifndef BONUS
# Not Bonus
SOURCES +=	src/main.c							\
			src/solve/radix_sort.c				\
			src/indeces.c						\
			src/solve/radix_calc.c				\
			src/solve/brute_force.c				\
			src/solve/lars.c					\
			src/solve/lars_util/groups.c		\
			src/solve/lars_util/final_sorts.c	\
			src/solve/lars_util/group_data.c	\
			src/solve/lars_util/resolve_group.c

HEADERS +=	src/solve/solve.h	\
			src/solve/lars_util/lars_util.h
CFLAGS  +=
LIBS    +=
else
# Bonus
NAME    = $(NAME_BONUS)
SOURCES += src/checker.c
HEADERS +=
CFLAGS  +=
LIBS    +=
endif

include colours.mk
RULE_SPACING = 6
PROJECT_SPACING = 11

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(addprefix -I,$(dir $(HEADERS)))

.PHONY: all clean fclean re debug bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : $(BLUE_FG)$(NAME)$(RESET_COLOR) created\n" "[$(PROJECT)]" "make"

bonus: $(NAME)
	@$(MAKE) BONUS=1

debug:
	@$(MAKE) DEBUG=1

$(LIBFT): $(addprefix $(dir $(LIBFT)),$(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
ifdef DEBUG
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT)) debug
else
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT))
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "make"
	@printf "$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@$(CLEAR_REST_OF_LINE)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "$@"
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(PROJECT)]" "$@"
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(dir $(LIBFT)) fclean

re: fclean all
