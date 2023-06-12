
# -------------------- config -------------------------

NAME = libasm.a

# assembler config
ASM = nasm
ASM_FLAGS = -f elf32

# linker config
LD = ld
# -m elf_i386 = architecture
LD_FLAGS = -m elf_i386

# archive (library) config
AR = ar
AR_FLAGS = rcs

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

# -------------------- util rules -----------------------

# copy the directory tree from $(SDIR) to $(ODIR)
$(ODIR):
	$(MKDIR) $(patsubst $(SDIR)/%, $(ODIR)/% , $(shell find $(SDIR)/ -type d))

$(ODIR)/%.o: $(SDIR)/%.s
	$(ASM) $(ASM_FLAGS) $< -o $@ -I $(IDIR)

# -------------------- public rules ---------------------

$(NAME): $(ODIR) $(OBJ)
	$(AR) $(AR_FLAGS) $@ $(OBJ)


all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

test: $(NAME) $()


.PHONY: $(NAME) all clean fclean re bonus