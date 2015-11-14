
colour-string: colour-string.cc
	g++ -ggdb -o colour-string -std=c++11 colour-string.cc -lpcrecpp

clean:
	rm colour-string || true

indent:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.cc *.h
