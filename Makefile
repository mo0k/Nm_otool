# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 09:22:47 by mo0k              #+#    #+#              #
#    Updated: 2018/04/01 19:32:05 by mo0k             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				nm

CFLAGS =			-Wall -Werror -Wextra -g
CC = 				gcc $(CFLAGS)

LIBPRINT_PATH =		libftprintf
LIB = 				$(LIBPRINT_PATH)/libftprintf.a

INC_PATH = 			includes

INCS = 				$(INC_PATH)/nm.h \
					$(INC_PATH)/data.h \
					$(INC_PATH)/common.h \
					$(INC_PATH)/get_opts.h \
					$(INC_PATH)/symbol.h \
					$(INC_PATH)/sort.h \
					$(INC_PATH)/swap_bits.h \
					$(INC_PATH)/arch32.h \
					$(INC_PATH)/arch64.h \
					$(INC_PATH)/print.h \
					$(INC_PATH)/debug.h


SRCS_PATH = 		sources

SRCS_32_PATH =		$(SRCS_PATH)/arch32
SRCS_32 = 			$(SRCS_32_PATH)/get_symbol.c \
					$(SRCS_32_PATH)/handler_fat.c \
					$(SRCS_32_PATH)/handler_symtab.c \
					$(SRCS_32_PATH)/handler.c

SRCS_64_PATH =		$(SRCS_PATH)/arch64
SRCS_64 = 			$(SRCS_64_PATH)/get_symbol.c \
					$(SRCS_64_PATH)/handler_symtab.c \
					$(SRCS_64_PATH)/handler.c	

SRCS_COMMON_PATH =	$(SRCS_PATH)/common
SRCS_COMMON = 		$(SRCS_COMMON_PATH)/get_dylibname.c \
					$(SRCS_COMMON_PATH)/get_type_stab.c \
					$(SRCS_COMMON_PATH)/swap_bit.c \
					$(SRCS_COMMON_PATH)/corrupted.c \
					$(SRCS_COMMON_PATH)/infos_external.c

SRCS_OPTIONS_PATH =	$(SRCS_PATH)/options
SRCS_OPTIONS = 		$(SRCS_OPTIONS_PATH)/get_opts.c

SRCS_SORT_PATH =	$(SRCS_PATH)/sort
SRCS_SORT = 		$(SRCS_SORT_PATH)/sort.c \
					$(SRCS_SORT_PATH)/get_sortfunc.c \
					$(SRCS_SORT_PATH)/sort_ascii.c

SRCS_PRINT_PATH = 			$(SRCS_PATH)/print
SRCS_PRINT_ARCH64_PATH =	$(SRCS_PRINT_PATH)/arch64
SRCS_PRINT_ARCH64 = 		$(SRCS_PRINT_ARCH64_PATH)/get_printfunc64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_none64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_x64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_j64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_m64.c
SRCS_PRINT_ARCH32_PATH =	$(SRCS_PRINT_PATH)/arch32
SRCS_PRINT_ARCH32 = 		$(SRCS_PRINT_ARCH32_PATH)/get_printfunc32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_none32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_x32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_j32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_m32.c

SRCS_PRINT = 		$(SRCS_PRINT_ARCH64) $(SRCS_PRINT_ARCH32)

ALL_SRCS = 			$(SRCS_PATH)/nm.c $(SRCS_OPTIONS) $(SRCS_32) $(SRCS_64)\
					$(SRCS_COMMON) $(SRCS_SORT) $(SRCS_PRINT)

OBJS =				$(ALL_SRCS:%.c=%.o)

C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(LIB) $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBPRINT_PATH) -lftprintf
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

$(LIB):
	@make -C $(LIBPRINT_PATH)

%.o: %.c
	@$(CC) -I $(INC_PATH) -I $(LIBPRINT_PATH)/includes -c -o $@ $<
	@echo "Linking file" $@

clean:
	@make clean -C $(LIBPRINT_PATH)
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBPRINT_PATH)
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)"$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean