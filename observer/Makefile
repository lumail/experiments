
all:
	g++ -o observer -std=c++11 main.cc config.cc

clean:
	rm observer || true

indent:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.cc *.h
