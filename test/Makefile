TAR = ifconfig message
CFLAGS = -g -Wall `pkg-config --libs --cflags libwp0`

all: $(TAR)

$(TAR): % : %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(TAR)
