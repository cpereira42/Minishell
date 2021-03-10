# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 17:32:06 by cpereira          #+#    #+#              #
#    Updated: 2021/03/09 18:19:37 by cpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell
NAMEM =			mini2

HEADER_DIR =	./includes/

LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a

SRC_DIR		=	./source
SRC			=	$(SRC_DIR)/get_next_line_utils.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/main.c \

OBJ_DIR	=		./obj
OBJ = $(subst .c,.o,$(SRC))

INCLUDES 		= -I $(INC_DIR)

CFLAGS = -Wall -Wextra -Werror

LINUX_FLAGS = -L ./$(LIBFT_DIR) -lft

MAC_FLAGS = -L ./$(LIBFT_DIR) -lft \

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		clang -I. -L. $(LIBFT) $(OBJ) $(INCLUDES) $(CFLAGS) $(LINUX_FLAGS) -o  $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
		mkdir -p $(OBJ_DIR)
		clang -c $(CFLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

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
		gcc -I. -L. $(LIBFT) $(OBJ) $(INCLUDES) $(CFLAGS) $(MAC_FLAGS) -o $(NAMEM)

clean:
	make clean -C $(LIBFT_DIR)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME) $(NAME_MAC) ./libmlx.dylib

re: fclean all

.PONY: all clean fclean re mac
