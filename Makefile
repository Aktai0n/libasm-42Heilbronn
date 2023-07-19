
# -------------------- config -------------------------

NAME := libasm.a
TESTER_NAME := tester

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

ifneq ($(VERBOSE),)
CFLAGS += -DTEST_VERBOSE=1
endif

COMPILER := $(shell $(CC) --version)

# detect whether gcc or clang is being used
# because clang prefixes functions with an underscore
ifneq ($(or $(findstring GCC, $(COMPILER)), $(findstring gcc, $(COMPILER))),)
ASFLAGS += -dCOMPILER=gcc
else ifneq ($(or $(findstring clang, $(COMPILER)), $(findstring clang, $(COMPILER))),)
ASFLAGS += -dCOMPILER=clang
else
$(error Unsupported compiler: $(COMPILER))
endif

# utils config
RM = rm -rf
MKDIR = mkdir -p

# -------------------- dependencies ---------------------

SRC_BONUS = ft_atoi_base.asm \
            ft_list_push_front.asm \
            ft_list_remove_if.asm \
            ft_list_size.asm \
            ft_list_sort.asm
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
# TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_SRC = $(shell find $(TEST_DIR) -type f -name "*.c")

# -------------------- public rules ---------------------

$(NAME): $(ODIR) $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)


all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTER_NAME)

re: fclean test

bonus: all

# test: CFLAGS += -DLIBASM_BONUS=1
test: all
	$(CC) $(CFLAGS) -I$(IDIR) $(TEST_SRC) $(OBJ) -o $(TESTER_NAME)


.PHONY: $(NAME) all clean fclean re bonus

# -------------------- util rules -----------------------

# copy the directory tree from $(SDIR) to $(ODIR)
$(ODIR):
	$(MKDIR) $(patsubst $(SDIR)/%, $(ODIR)/% , $(shell find $(SDIR)/ -type d))

$(ODIR)/%.o: $(SDIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@ -I $(IDIR)