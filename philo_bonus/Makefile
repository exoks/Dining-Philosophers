# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 15:12:02 by oezzaou           #+#    #+#              #
#    Updated: 2023/05/20 20:34:07 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
##################################
#            COMPILER            #
##################################
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror 
NAME		:= philo_bonus
PTHREAD_LIB := pthread

##################################
#              SRCS              #
##################################
INCDIR		:= includes/
SRCDIR 		:= srcs
OBJDIR 		:= obj
STEMS 		:=	philo_bonus \
				philo_init_bonus \
				philo_actions_bonus \
				philo_init2_bonus \
				philo_utils_bonus\
				philo_clear_bonus
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
	@echo "" | awk 'BEGIN{a=0; printf("$(GREEN)["); while(a < 50){printf("$(RED)%c$(NOCLR)", "#"); system("sleep 0.01");a++}}{print "$(GREEN)]$(NOCLR)\n\n  |==> $(GREEN)Done Cleaing$(NOCLR).\n"}'

fclean: clean
	@rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean re
