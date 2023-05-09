# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dly <dly@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:22:17 by dly               #+#    #+#              #
#    Updated: 2023/01/10 16:45:16 by dly              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                              VARIABLES                                       #
#                                                                              #
################################################################################

SRCS_FILES		= pipex.c  child.c  path.c  get_file.c
SRCS_DIR		= srcs/mandatory/
M_SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
M_OBJS			= $(M_SRCS:.c=.o)

BONUS_FILES		= pipex_bonus.c  child_bonus.c  error_bonus.c  files_bonus.c  \
				  free_bonus.c  get_pipes_bonus.c  here_doc_bonus.c 
B_SRCS_DIR		= srcs/bonus/
B_SRCS			= $(addprefix $(B_SRCS_DIR), $(BONUS_FILES))
B_OBJS			= $(B_SRCS:.c=.o)

LIBFT_FILES		= ft_bzero.c  ft_calloc.c  ft_memset.c  ft_split.c \
				  ft_strncmp.c  ft_strlen.c  ft_join.c
LIBFT_DIR		= libft/
L_SRCS			= $(addprefix $(LIBFT_DIR), $(LIBFT_FILES))
L_OBJS			= $(L_SRCS:.c=.o)

GNL_FILES		= get_next_line.c  get_next_line_utils.c 
GNL_DIR			= gnl/
GNL_SRCS		= $(addprefix $(GNL_DIR), $(GNL_FILES))
GNL_OBJS		= $(GNL_SRCS:.c=.o)

INCLUDE			= -I include/ 
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

RM				= rm -f
AR				= ar rcs

NAME			= pipex 
HEADER			= include/pipex.h
HEADER_B		= include/pipex_bonus.h

################################################################################
#                                                                              #
#                                  RULES                                       #
#                                                                              #
################################################################################

all:			$(NAME)

%.o:			%.c
				@echo "Compiling: $<"
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):		$(L_OBJS) $(M_OBJS) $(HEADER)
				@$(CC) $(M_OBJS) $(L_OBJS) -o $(NAME) 
				@echo "pipex executable ready!"
				
bonus: 			$(L_OBJS) $(GNL_OBJS) $(B_OBJS) $(HEADER_B)
				@$(CC) $(CFLAGS) $(INCLUDE) $(L_OBJS) $(GNL_OBJS) $(B_OBJS) -o $(NAME)
				@echo "bonus executable ready!"
				
clean:
				@$(RM) $(M_OBJS) $(GNL_OBJS) $(L_OBJS) $(B_OBJS)
				@echo "pipex & libft object files cleaned!"

fclean:			clean
				@$(RM) $(NAME) 
				@echo " executable files cleaned!"

re:				fclean $(NAME) 

norm:
				@norminette $(SRCS_FILES) $(LIBFT_FILES) $(HEADER) 

.PHONY:			all clean fclean re bonus
