# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgengo <jgengo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/06 10:39:10 by jgengo            #+#    #+#              #
#    Updated: 2020/02/20 17:02:25 by motoure          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_atoi.c ft_nbrlen_u.c ft_memsub.c ft_nbrlen.c ft_printf.c ft_putnbr.c ft_putnbr_base.c ft_putptr.c ft_putstr.c ft_putnbr_base_u.c ft_realloc.c ft_strdup.c ft_strlen.c ft_strrev.c ft_putchar_str.c ft_isprint.c is_hidden.c ft_ptrlen.c write_const.c get_next_arg.c print_struct.c arg_putptr.c arg_putchar.c arg_putunsigned.c arg_puthexa.c arg_putstr.c arg_putnbr.c hidden_strlen.c hidden_of.c ft_str.c print_value_u.c print_value_d.c write_width.c write_precision.c fill_struct.c fill_width_type.c fill_width.c is_arg.c fill_width.c fill_precision.c get_width.c contain_num.c reset_struct.c c_str.c is_arg.c ft_putchar.c is_num.c\

OBJ = $(subst .c,.o,$(SRC))

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
