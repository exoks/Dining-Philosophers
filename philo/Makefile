# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 15:12:02 by oezzaou           #+#    #+#              #
#    Updated: 2023/05/21 17:13:53 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
##################################
#            COMPILER            #
##################################
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
NAME		:= philo
PTHREAD_LIB := pthread

##################################
#              SRCS              #
##################################
INCDIR		:= includes/
SRCDIR 		:= srcs
OBJDIR 		:= obj
STEMS 		:= philo philo_init philo_actions philo_utils philo_utils2
OBJS 		:= $(addprefix $(OBJDIR)/, $(addsuffix .o, $(STEMS)))
SRCS 		:= $(addprefix $(SRCDIR)/, $(addsuffix .c, $(STEMS)))

##################################
#             COLORS             #
##################################
GREEN 		:= \033[1;32m
RED 		:= \033[1;31m
CYAN 		:= \033[1;36m
NOCLR 		:= \033[1;0m

##################################
#              RULS              #
##################################

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -I $(INCDIR) -o $@
	@printf "\n$(GREEN)%45s$(NOCLR)\n\n" "<<<<<<<<<<<<< $(NAME) >>>>>>>>>>>>>>"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@
	@printf "$(CYAN)Compiling$(NOCLR) : $< %25s\n" "===> $@"

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)
	@echo "" | awk 'BEGIN{a=0; printf("["); while(a < 50){printf("$(GREEN)%c$(NOCLR)", "#"); system("sleep 0.01");a++}}{print "]\n\n  |==> $(GREEN)Done $(RED)Cleaing$(NOCLR).\n"}'

fclean: clean
	@rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean re
