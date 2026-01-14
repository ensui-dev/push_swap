# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 15:23:43 by mju-ferr          #+#    #+#              #
#    Updated: 2025/10/24 19:11:41 by mju-ferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(OBJS) $(BONUS_OBJS)
	@touch .bonus
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	@$(RM) .bonus
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	@if [ -f .bonus ]; then \
		$(MAKE) --no-print-directory fclean; \
		$(MAKE) --no-print-directory bonus; \
	else \
		$(MAKE) --no-print-directory fclean; \
		$(MAKE) --no-print-directory all; \
	fi

.PHONY: all clean fclean re bonus