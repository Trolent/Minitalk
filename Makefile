# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trolland <trolland@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 16:23:19 by trolland          #+#    #+#              #
#    Updated: 2024/05/15 17:07:56 by trolland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
NAME_SERV = server
NAME_CLI = client

BONUS_NAME = minitalk_bonus
NAME_SERV_BONUS = server_bonus
NAME_CLI_BONUS = client_bonus


SRC := verify_pid.c

LIBFT	= 	libft/libft.a

SRCS := $(addprefix src/, $(SRC))
OBJS := $(patsubst src/%.c, object/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

SERVER_MAIN := src/server/main.c
CLIENT_MAIN := src/client/main.c

SERVER_MAIN_BONUS := src/server_bonus/main.c
CLIENT_MAIN_BONUS := src/client_bonus/main.c

CC := cc

CFLAGS := -Wall -Werror -Wextra -MMD -MP -Iincludes -Ilibft -g

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(NAME_SERV) $(NAME_CLI)

$(NAME_SERV): $(OBJS) object/server/main.o $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) object/server/main.o $(LIBFT) -o $(NAME_SERV)

$(NAME_CLI): $(OBJS) object/client/main.o $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) object/client/main.o $(LIBFT) -o $(NAME_CLI)
	
$(BONUS_NAME): $(NAME_SERV_BONUS) $(NAME_CLI_BONUS)

$(NAME_SERV_BONUS): $(OBJS) object/server_bonus/main.o $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) object/server_bonus/main.o $(LIBFT) -o $(NAME_SERV_BONUS)

$(NAME_CLI_BONUS): $(OBJS) object/client_bonus/main.o $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) object/client_bonus/main.o $(LIBFT) -o $(NAME_CLI_BONUS)

object/%.o: src/%.c
	@if [ ! -d "object" ]; then mkdir object; fi
	@printf "\033[0;32m\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

object/client/main.o: $(CLIENT_MAIN)
	@if [ ! -d "object" ]; then mkdir object; fi
	@if [ ! -d "object/client" ]; then mkdir object/client; fi
	@printf "\033[0;32m\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

object/server/main.o: $(SERVER_MAIN)
	@if [ ! -d "object" ]; then mkdir object; fi
	@if [ ! -d "object/server" ]; then mkdir object/server; fi
	@printf "\033[0;32m\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

object/client_bonus/main.o: $(CLIENT_MAIN_BONUS)
	@if [ ! -d "object" ]; then mkdir object; fi
	@if [ ! -d "object/client_bonus" ]; then mkdir object/client_bonus; fi
	@printf "\033[0;32m\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

object/server_bonus/main.o: $(SERVER_MAIN_BONUS)
	@if [ ! -d "object" ]; then mkdir object; fi
	@if [ ! -d "object/server_bonus" ]; then mkdir object/server_bonus; fi
	@printf "\033[0;32m\tCompiling: $<\033[0m\n";
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@$(MAKE) --no-print-directory clean -C libft
	@echo "Cleaning minitalk's object files..."
	@rm -rf object
	@rm -rf object_bonus

fclean: clean
	@echo "Cleaning libft..."
	@rm -f libft/libft.a
	@echo "Cleaning minitalk..."
	@rm -f $(NAME_SERV) $(NAME_CLI) $(NAME_SERV_BONUS) $(NAME_CLI_BONUS)  

re: fclean all

norm:
	$(MAKE) -C libft norm
	@echo 'Checking header files...'
	@output_header=$$(norminette -R CheckDefine includes/*.h); \
	echo "$$output_header" | awk '/Error/ {print "\033[0;31m" $$0 "\033[0m"}'; \
	echo 'Checking main file...'; \
	output_main=$$(norminette -R CheckForbiddenSourceHeader main/*.c); \
	echo "$$output_main" | awk '/Error/ {print "\033[0;31m" $$0 "\033[0m"}'; \
	echo 'Checking main_bonus file...'; \
	output_main_bonus=$$(norminette -R CheckForbiddenSourceHeader main_bonus/*.c); \
	echo "$$output_main_bonus" | awk '/Error/ {print "\033[0;31m" $$0 "\033[0m"}'; \
	echo 'Checking source files...'; \
	output_source=$$(norminette -R CheckForbiddenSourceHeader src/*.c); \
	echo "$$output_source" | awk '/Error/ {print "\033[0;31m" $$0 "\033[0m"}'; \
	total_errors=$$(echo "$$output_header $$output_source $$output_main \
	$$output_main_bonus" | grep -c 'Error:'); \
	if [ $$total_errors -gt 0 ]; then \
	    echo "\033[0;31m$$total_errors errors found\033[0m"; \
	else \
	    echo "\033[0;32mNo norminette error in Pipex\033[0m"; \
	fi

-include $(DEPS) $(DEPS_BONUS) 

.PHONY: all clean fclean re norm bonus
