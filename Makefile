
# -------------------- config -------------------------

NAME = libasm.a

# assembler config
AS = nasm
# -f elf64 for linux, -f macho64 for MacOS
ASFLAGS = -f elf64 -wall

# linker config
LD = ld
# -m elf_i386 = architecture
LDFLAGS = 

# archive (library) config
AR = ar
ARFLAGS = rcs

# compiler config
CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion #-Werror

# utils config
RM = rm -rf
MKDIR = mkdir -p

# -------------------- dependencies ---------------------

SRC = ft_strlen.s
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))

IDIR = inc

ODIR = build
OBJ = $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SRC_FULL))

TEST_DIR = test
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

# -------------------- public rules ---------------------

$(NAME): $(ODIR) $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)


all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

test: all
	$(shell bash $(TEST_DIR)/run.sh)


.PHONY: $(NAME) all clean fclean re bonus

# -------------------- util rules -----------------------

# copy the directory tree from $(SDIR) to $(ODIR)
$(ODIR):
	$(MKDIR) $(patsubst $(SDIR)/%, $(ODIR)/% , $(shell find $(SDIR)/ -type d))

$(ODIR)/%.o: $(SDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@ -I $(IDIR)