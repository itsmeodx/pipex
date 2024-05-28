CC			=	cc -Wall -Wextra -Werror #-g -fsanitize=address
INC			=	-Iheaders -Ift_printf/headers -Ift_printf/Libft/headers \
				-Iget_next_line/headers
HEADER		=	headers/pipex.h
SRCDIR		=	src
OBJDIR		=	obj
GNL_SRCDIR	=	get_next_line/src
GNL_OBJDIR	=	get_next_line/obj
PRINTF		=	ft_printf/libftprintf.a
PRINTF_DIR	=	ft_printf
LIBFT		=	ft_printf/Libft/libft.a
LIBFT_DIR	=	ft_printf/Libft
RED			=	\e[1;31m
GREEN		=	\e[1;32m
YELLOW		=	\e[3;33m
CYAN		=	\e[3;96m
END			=	\e[0m
NAME		=	pipex
NAME_BONUS	=	pipex_bonus
GNL_FILES	=	get_next_line.c get_next_line_utils.c
FILES		=	children.c env.c exec.c exit.c fork.c garbage_collector.c heredoc.c \
				init.c main.c open.c pipex.c
FILES_BONUS	=	children.c env.c exec.c exit.c fork.c garbage_collector.c heredoc.c \
				init.c main_bonus.c open.c pipex.c
GNL_SRC		=	$(addprefix $(GNL_SRCDIR)/, $(GNL_FILES))
SRC			=	$(addprefix $(SRCDIR)/, $(FILES))
SRC_BONUS	=	$(addprefix $(SRCDIR)/, $(FILES_BONUS))
GNL_OBJ		=	$(GNL_SRC:$(GNL_SRCDIR)/%.c=$(GNL_OBJDIR)/%.o)
OBJ			=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJ_BONUS	=	$(SRC_BONUS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(PRINTF) $(OBJ) $(GNL_OBJ) $(HEADER)
	@$(CC) $(OBJ) $(GNL_OBJ) $(PRINTF) -o $(NAME)
	@echo "$(CYAN)$(NAME) is ready to use$(END)"

$(NAME_BONUS): $(PRINTF) $(OBJ_BONUS) $(GNL_OBJ) $(HEADER)
	@$(CC) $(OBJ_BONUS) $(GNL_OBJ) $(PRINTF) -o $(NAME_BONUS)
	@echo "$(CYAN)$(NAME_BONUS) is ready to use$(END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(YELLOW)Compiling $(notdir $<) to $(notdir $@)...$(END)"
	@mkdir -p $(OBJDIR)
	@$(CC) $(INC) -c $< -o $@ > /dev/null
	@echo "$(GREEN)Done.$(END)"

$(GNL_OBJDIR)/%.o: $(GNL_SRCDIR)/%.c
	@echo "$(YELLOW)Compiling $(notdir $<) to $(notdir $@)...$(END)"
	@mkdir -p $(GNL_OBJDIR)
	@$(CC) $(INC) -c $< -o $@ > /dev/null
	@echo "$(GREEN)Done.$(END)"

$(PRINTF):
	@echo "$(YELLOW)Compiling $(notdir $@)...$(END)"
	@make -C $(LIBFT_DIR) all > /dev/null
	@cp $(LIBFT) $(PRINTF)
	@make -C $(PRINTF_DIR) > /dev/null
	@echo "$(GREEN)Done.$(END)"

clean:
	@make -C $(PRINTF_DIR) clean > /dev/null
	@echo "$(RED)Cleaning $(OBJDIR)...$(END)"
	@rm -rf $(OBJDIR)
	@rm -rf $(GNL_OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning $(notdir $(PRINTF))...$(END)"
	@make -C $(PRINTF_DIR) fclean > /dev/null
	@echo "$(RED)Cleaning $(NAME)...$(END)"
	@rm -f $(NAME)
	@echo "$(RED)Cleaning $(NAME_BONUS)...$(END)"
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean
