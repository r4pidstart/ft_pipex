# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2022/10/08 18:53:20 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CFLAGS = -Wall -Wextra -Werror

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft
SRCS = *.c

ifdef BONUS
	NAME = checker
	FOLDER = bonus/
	SRCS = 
else
	FOLDER = mandatory/
endif

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(FOLDER), $(SRCS:.c=.o))
	clang -Wall -Wextra -Werror -g3 -ggdb \
	-o ./$(NAME) \
	$(addprefix $(FOLDER), $(SRCS)) \
	-L$(LIBFT_SRCS) -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@
	
bonus:
	$(MAKE) BONUS=1

clean:
	rm -rf */*.o
	rm -rf *.o
	make clean -C $(LIBFT_SRCS)
	
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_SRCS)

re: fclean all

.PHONY: bonus all clean fclean re