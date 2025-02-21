# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 15:12:02 by oezzaou           #+#    #+#              #
#    Updated: 2023/05/21 17:38:18 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#====<[ CC compiler: ]>=========================================================
CC						:= cc
CFLAGS				:= -Wall -Wextra -Werror
RM						:= rm -rf 

#====<[ Colors: ]>==============================================================
GREEN					= \033[1;32m
RED						= \033[1;31m
BLUE					= \033[34m
CYAN					= \033[1;36m
GRAY					= \033[0;90m
PURPLE				= \033[0;35m
YELLOW				= \033[0;93m
BLACK  				= \033[20m
MAGENTA 			= \033[35m
WHITE  				= \033[37m
PINK					= \033[0;38;5;199m
ORANGE 				= \033[38;5;214m
LIGHT_BLACK  	= \033[90m
LIGHT_RED    	= \033[91m
LIGHT_GREEN  	= \033[92m
LIGHT_YELLOW 	= \033[93m
LIGHT_BLUE   	= \033[94m
LIGHT_MAGENTA = \033[95m
LIGHT_CYAN   	= \033[96m
LIGHT_WHITE  	= \033[97m
LIGHT_BLUE		= \033[38;5;45m
RESET					= \033[1;0m

#===<[ Sources: ]>==============================================================
PROJECT				:= Philosophers
NAME					:= philo
PTHREAD_LIB		:= pthread
INCLUDE				:= -Iinclude
SRC_DIR				:= src
OBJ_DIR				:= obj
STEMS					:= philo philo_init philo_actions philo_utils philo_utils2

OBJ						:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(STEMS)))
SRC						:= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(STEMS)))

#====<[ Rules: ]>===============================================================
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@ -l$(PTHREAD_LIB) 
	@echo "${GREEN}[OK]: ${CYAN}$@ ✔️${RESET}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .create_dir
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(GREEN)[OK]${RESET}: ${PINK}Compiling${RESET} %-29s| $@\n" "$<"

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "" | awk '{a=0; while (a < 69)\
		{printf("$(GREEN)█"); system("sleep 0.01"); a++}; printf("\n\n")}'
	@if [ -d $(OBJ_DIR) ]; then\
		${RM} $(OBJ_DIR);\
		printf "${GREEN}[OK]${RESET}: ${ORANGE}Cleaning  %-29s${RESET}| ./%s\n"\
					 "... " "$(PROJECT)/$(OBJ_DIR) ✔️";\
	else\
		printf "${RED}[KO]${RESET}: ${BLUE}Not Found %-29s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(OBJ_DIR) ✖️";\
	fi

fclean: clean
	@if [ -f $(NAME) ]; then\
		${RM} $(NAME);\
		printf "${GREEN}[OK]${RESET}: ${ORANGE}Cleaning  %-29s${RESET}| ./%s\n"\
					 "... " "$(PROJECT)/$(NAME) ✔️";\
	else\
		printf "${RED}[KO]${RESET}: ${BLUE}Not Found %-29s${RESET}| ./%s\n"\
					 "..." "$(PROJECT)/$(NAME) ✖️";\
	fi

re: fclean all 

.create_dir: $(OBJ_DIR) 

.PHONY: all clean fclean re
#===============================================================================
