# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/07 17:00:31 by mvan-wij      #+#    #+#                  #
#    Updated: 2021/09/06 16:43:07 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker
LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
ifdef DEBUG
CFLAGS += -g
endif

LIBS = -L$(dir $(LIBFT)) -lft
HEADERS = libft/libft.h src/push_swap.h
SOURCES = src/exec_ops.c src/rotate.c src/swap_push.c src/utils.c src/TMP.c

ifndef BONUS
# Not Bonus./ch
SOURCES += src/main.c src/solve/radix_sort.c src/indeces.c src/solve/radix_calc.c src/solve/brute_force.c src/solve/bucket_sort.c
HEADERS += src/solve/solve.h
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

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(addprefix -I,$(dir $(HEADERS)))

.PHONY: all clean fclean re debug bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

	#cp $(LIBFT) $(NAME)
	#ar -crs $(NAME) $(OBJECTS)

bonus: $(NAME)
	$(MAKE) BONUS=1

debug:
	$(MAKE) DEBUG=1

$(LIBFT): $(addprefix $(dir $(LIBFT)),$(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
ifdef DEBUG
	$(MAKE) -C $(dir $(LIBFT)) debug bonus
else
	$(MAKE) -C $(dir $(LIBFT)) bonus
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all
