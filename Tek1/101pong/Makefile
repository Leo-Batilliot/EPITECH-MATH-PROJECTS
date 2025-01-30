##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task 01
##

# FILES
SRC	=	pong.c \

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ =	$(SRC:.c=.o)
FLAGS = -lm
CC = gcc
NAME = 101pong

# PRINT COMPILATION
%.o: %.c
	@echo "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS)
	@echo "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"


# CLEAN OBJECT FILES
clean:
	@echo "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@for file in $(OBJ); do \
		if [ -f "$$file" ]; then \
			echo "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$$file$(RESET)"; \
			rm -f "$$file"; \
		fi; \
	done

# CLEAN EXEC / LIB
fclean:
	@echo "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all
