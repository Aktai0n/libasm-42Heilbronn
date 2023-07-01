
# -------------------- config -------------------------

NAME := libasm.a

OS := $(shell uname -s)

# assembler config
AS = nasm
ASFLAGS = -wall -iinc

ifeq ($(OS), Darwin) # MacOS
ASFLAGS += -f macho64 -dMACOS=1
else ifeq ($(OS), Linux) # Linux
ASFLAGS += -f elf64 -dLINUX=1
else
$(error Unsupported operating system: $(OS))
endif


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

SRC_BONUS = ft_atoi_base.asm
SDIR_BONUS = bonus

SRC = ft_write.asm \
      ft_read.asm \
      ft_strcmp.asm \
      ft_strcpy.asm \
      ft_strdup.asm \
      ft_strlen.asm \
      $(addprefix $(SDIR_BONUS)/, $(SRC_BONUS))
SDIR = src
SRC_FULL = $(addprefix $(SDIR)/, $(SRC))


IDIR = inc

ODIR = build
OBJ = $(patsubst $(SDIR)/%.asm, $(ODIR)/%.o, $(SRC_FULL))

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

$(ODIR)/%.o: $(SDIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@ -I $(IDIR)