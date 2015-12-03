#
#  Basics
#
C=gcc
LINKER=$(CC) -o


CFLAGS+=-Wall -Werror
LDLIBS+=-lmagic

#
# Default targets
#
default: mime

#
#  Cleanup
#
clean:
	rm mime || true

#
#  The main binary
#
mime: mime.c
	${C} -o mime mime.c $(CFLAGS) $(LDLIBS)


indent:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c
