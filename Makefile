NAME = minishell

HEADER_DIR =	includes/

LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a


SDIR =	./srcs/
ODIR =	./objs/

SRCS =	$(SDIR)main.c\
		$(SDIR)parse_pipelines.c\
		$(SDIR)parse_cmd_lines.c\
		$(SDIR)parse_s.c\
		$(SDIR)parse_cmd_args.c\
		$(SDIR)parse_in_red.c\
		$(SDIR)parse_out_red.c\
		$(SDIR)parse_sq.c\
		$(SDIR)parse_dq.c\
		$(SDIR)u_free_list.c\
		$(SDIR)u_free_array_bi.c\
		$(SDIR)initialize.c\
		$(SDIR)expand.c\
		$(SDIR)ff.c\
		$(SDIR)ft_split3.c\
		$(SDIR)fd_handler.c\
		$(SDIR)redirect_handler.c\
		$(SDIR)execute_command.c\
		$(SDIR)update_env_var.c\
		$(SDIR)loc_var.c\
		$(SDIR)create_prompt.c\
		$(SDIR)export_var.c\
		$(SDIR)gets.c\
		$(SDIR)exit_msh.c\
		$(SDIR)fork_process.c\
		$(SDIR)safe_malloc.c\
		$(SDIR)reset_flags.c\
		$(SDIR)bye.c\
		$(SDIR)setup.c\
		$(SDIR)term_caps.c\
		$(SDIR)utilits.c\
		$(SDIR)set_return_status.c


OBJS =	$(patsubst $(SDIR)%.c, $(ODIR)%.o, $(SRCS))

CC = clang
HEADERS = -I./$(HEADER_DIR) -I./$(LIBFT_DIR)
C_FLAGS = -Wall -Werror -Wextra -g
C_SANIT = -fsanitize=address
L_FLAGS = -L ./libft -lft -lncurses


$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(C_FLAGS) $(C_SANIT) $(HEADERS) $(L_FLAGS) -o $@

	echo CONCLUIDO
	#./minishell
	#valgrind --leak-check=full --track-origins=yes ,/minishell


$(ODIR)%.o: $(SDIR)%.c
		mkdir -p $(ODIR)
		$(CC) $(C_FLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	make re -C ./libft

all: minishell

clean:
	make clean -C ./libft
	rm -rf $(ODIR)
	#rm -f $(OBJS)
	#rmdir $(ODIR)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

run:
	./minishell

val:	$(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(C_FLAGS) $(HEADERS) $(L_FLAGS) -o $(NAME)
	echo CONCLUIDO
	#./minishell
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./minishell
