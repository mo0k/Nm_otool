# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 09:22:47 by mo0k              #+#    #+#              #
#    Updated: 2018/09/07 11:47:46 by mo0k             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				ft_nm

CFLAGS =			-Wall -Werror -Wextra -g
CC = 				gcc $(CFLAGS)

DIR_LIB	=			../lib
LIBFTPRINTF_PATH =	$(DIR_LIB)/libftprintf
LIBFTPRINTF = 		$(LIBFTPRINTF_PATH)/libftprintf.a
LIBOPENFILE_PATH =	$(DIR_LIB)/libopenfile
LIBOPENFILE = 		$(LIBOPENFILE_PATH)/libopenfile.a

INC_LIB =			-I $(LIBFTPRINTF_PATH)/includes -I $(LIBOPENFILE_PATH)/includes -I $(DIR_LIB)

INC_PATH = 			includes

INCS = 				$(INC_PATH)/nm.h \
					$(INC_PATH)/data.h \
					$(INC_PATH)/common.h \
					$(INC_PATH)/get_opts.h \
					$(INC_PATH)/symbol.h \
					$(INC_PATH)/sort.h \
					$(INC_PATH)/arch32.h \
					$(INC_PATH)/arch64.h \
					$(INC_PATH)/print.h

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
					$(SRCS_COMMON_PATH)/corrupted.c \
					$(SRCS_COMMON_PATH)/get_symbol_sect_nofound.c \
					$(SRCS_COMMON_PATH)/get_info_lc.c \
					$(SRCS_COMMON_PATH)/sort_display_clean.c \
					$(SRCS_COMMON_PATH)/del.c \
					$(SRCS_COMMON_PATH)/get_ref.c \
					$(SRCS_COMMON_PATH)/infos_external.c

SRCS_OPTIONS_PATH =	$(SRCS_PATH)/options
SRCS_OPTIONS = 		$(SRCS_OPTIONS_PATH)/get_opts.c

SRCS_SORT_PATH =	$(SRCS_PATH)/sort
SRCS_SORT = 		$(SRCS_SORT_PATH)/sort.c \
					$(SRCS_SORT_PATH)/get_sortfunc.c \
					$(SRCS_SORT_PATH)/sort_ascii32.c		\
					$(SRCS_SORT_PATH)/sort_ascii64.c

SRCS_PRINT_PATH = 			$(SRCS_PATH)/print
SRCS_PRINT_ARCH64_PATH =	$(SRCS_PRINT_PATH)/arch64
SRCS_PRINT_ARCH64 = 		$(SRCS_PRINT_ARCH64_PATH)/get_printfunc64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_none64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_x64.c \
							$(SRCS_PRINT_ARCH64_PATH)/option_j64.c
SRCS_PRINT_ARCH32_PATH =	$(SRCS_PRINT_PATH)/arch32
SRCS_PRINT_ARCH32 = 		$(SRCS_PRINT_ARCH32_PATH)/get_printfunc32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_none32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_x32.c \
							$(SRCS_PRINT_ARCH32_PATH)/option_j32.c

SRCS_PRINT = 		$(SRCS_PRINT_ARCH64) $(SRCS_PRINT_ARCH32)

ALL_SRCS = 			 $(SRCS_OPTIONS) $(SRCS_32) $(SRCS_64)\
					$(SRCS_COMMON) $(SRCS_SORT) $(SRCS_PRINT) $(SRCS_PATH)/nm.c

OBJS =				$(ALL_SRCS:%.c=%.o)

C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(LIBFTPRINTF) $(LIBOPENFILE) $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBFTPRINTF_PATH) -lftprintf -L $(LIBOPENFILE_PATH) -lopenfile
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

$(LIBOPENFILE):
	@make -C $(LIBOPENFILE_PATH)

$(LIBFTPRINTF):
	@make -C $(LIBFTPRINTF_PATH)

%.o: %.c
	$(CC) -I$(INC_PATH) $(INC_LIB) -c -o $@ $<

clean:
	@make clean -C $(LIBFTPRINTF_PATH)
	@make clean -C $(LIBOPENFILE_PATH)
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFTPRINTF_PATH)
	@make fclean -C $(LIBOPENFILE_PATH)
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)"$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean