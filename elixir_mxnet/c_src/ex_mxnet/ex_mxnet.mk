ex_mxnet_NIF_SRC_DIR := $(C_SRC_DIR)/ex_mxnet
ex_mxnet_NIF_SRC     := $(wildcard $(ex_mxnet_NIF_SRC_DIR)/*.c)
ex_mxnet_NIF_OBJ     := $(ex_mxnet_NIF_SRC:.c=.o)
ex_mxnet_NIF         := $(PRIV_DIR)/ex_mxnet_nif.so

ex_mxnet_NIF_CFLAGS ?= -fPIC -Wall -Wextra -O2  -Wno-unused-parameter

ifeq ($(MIX_ENV),prod)
else
  ex_mxnet_NIF_CFLAGS += -DDEBUG -g
endif

ex_mxnet_NIF_LDFLAGS ?= -fPIC -shared

ALL   += ex_mxnet_nif
CLEAN += ex_mxnet_nif_clean
PHONY += ex_mxnet_nif ex_mxnet_nif_clean

ex_mxnet_nif: $(ex_mxnet_NIF)

ex_mxnet_nif_clean:
	$(RM) $(ex_mxnet_NIF)
	$(RM) $(ex_mxnet_NIF_OBJ)

$(ex_mxnet_NIF): $(ex_mxnet_NIF_SRC_DIR)/ex_mxnet.c
	$(CC)  -undefined dynamic_lookup -dynamiclib -c $(ex_mxnet_NIF_CFLAGS) -o $@ $< $(ERL_CFLAGS)
