# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/31 09:06:42 by mo0ky             #+#    #+#              #
#    Updated: 2018/05/09 13:50:38 by mo0k             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libopenfile.a

CC = gcc $(CFLAGS)

INC_PATH = includes

INCS = $(INC_PATH)/open_file.h

SRCS_PATH = sources
SRCS =	$(SRCS_PATH)/open_file.c

OBJS	= $(SRCS:%.c=%.o)
C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	ar rcs $(NAME) $(OBJS)
	libtool -static -o $(NAME) $(OBJS) $(LIB)
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

%.o: %.c
	$(CC) -I $(INC_PATH) -I $(LIB_PATH)/$(INC_PATH) -c -o $@ $<

clean: 
	@/bin/rm -f $(OBJS)

fclean: clean
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)."$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean