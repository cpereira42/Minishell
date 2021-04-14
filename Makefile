# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 17:32:06 by cpereira          #+#    #+#              #
#    Updated: 2021/04/13 17:45:27 by cpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			mini
NAMEM =			mini2

HEADER_DIR =	./includes/

LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a

SRC_DIR		=	./source
SRC			=	$(SRC_DIR)/get_next_line_utils.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/setup.c \
				$(SRC_DIR)/exports.c \

OBJ_DIR	=		./obj
OBJ = $(subst .c,.o,$(SRC))

INCLUDES 		= -I $(INC_DIR)

CFLAGS = -Wall -Wextra -Werror

LINUX_FLAGS = -L ./$(LIBFT_DIR) -lmy -lreadline -lncurses

MAC_FLAGS = -L ./$(LIBFT_DIR) -lft

all: $(NAME)
	./$(NAME)
$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)


%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@


mini: $(NAMEM)

$(NAMEM): $(OBJ) $(LIBFT)
		clang -I. -L. $(LIBFT) $(OBJ) $(INCLUDES) $(CFLAGS) $(LINUX_FLAGS) -g  -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
		mkdir -p $(OBJ_DIR)
		clang -c $(CFLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

mac: $(NAMEM)

$(NAMEM): $(OBJ) $(LIBFT)
		gcc -I. -L. $(LIBFT) $(OBJ) $(INCLUDES) $(CFLAGS) $(MAC_FLAGS) -ltermcap -fsanitize=address -g -o $(NAMEM)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
		mkdir -p $(OBJ_DIR)
		clang -c $(CFLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PONY: all clean fclean re mac
