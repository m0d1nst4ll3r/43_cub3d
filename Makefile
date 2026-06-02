# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2026/06/02 14:27:35 by rapohlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
CFILES				= main.c \
					  free.c \
					  cleanup.c \
					  exit_error.c \
					  parse_map.c \
					  parse_map_color.c \
					  parse_map_elems.c \
					  parse_map_texture.c \
					  parse_map_grid.c \
					  parse_map_fill_grid.c \
					  buffer_map_grid.c \
					  mlx_hooks.c \
					  init.c \
					  render.c
SRCDIR				= src
SRC					= $(addprefix $(SRCDIR)/, $(CFILES))

# Include directories
INCDIR				= inc \
					  libft/inc \
					  mlx

# Build directory
BUILDDIR			= .build

# Object and dependency files
OBJ					= $(SRC:%.c=$(BUILDDIR)/%.o)
DEP					= $(OBJ:.o=.d)

# Output binary
NAME				= cub3d

# Libraries
LIB					= $(LIBFT) \
					  $(MLX)
LINK				= -lXext -lX11 -lm
LIBFT				= libft/libft.a
MLX					= mlx/libmlx_Linux.a
LIBFT_REPO			= https://github.com/m0d1nst4ll3r/43_mylibft
MLX_REPO			= https://github.com/42paris/minilibx-linux

# Compiler settings
CC					= clang
CFLAGS				= -O3 -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I,$(INCDIR))

# Make settings
MAKEFLAGS			+= --no-print-directory
MAKEFLAGS			:= $(MAKEFLAGS) $(if $(filter -j%,$(MAKEFLAGS)),,-j)

# Default rule
all:				$(NAME)

# Link
$(NAME):			$(OBJ) $(LIB)
					$(CC) $^ $(LINK) -o $@

# Build libraries
$(MLX):
					@if [ ! -d mlx ]; then git clone $(MLX_REPO) mlx; fi
					$(MAKE) -C $(@D)

$(LIBFT):
					@if [ ! -d libft ]; then git clone $(LIBFT_REPO) libft; fi
					$(MAKE) -C $(@D)

# Compile source -> object (auto-create directories)
$(BUILDDIR)/%.o:	%.c | $(LIB)
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c -o $@ $<

# Valgrind memory test
valgrind:			$(NAME)
					valgrind -q --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME) $(MAP)

# Cleanup
clean:
					$(MAKE) -C libft clean
					rm -rf $(BUILDDIR)

fclean:
					$(MAKE) -C libft fclean
					$(MAKE) -C mlx clean
					rm -rf $(NAME) $(BUILDDIR)

re:
					$(MAKE) fclean
					$(MAKE) all

# Include dependency files
-include $(DEP)

.PHONY:		all clean fclean re
