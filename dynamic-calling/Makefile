#
# Compile the sample
#
sample: sample.cc
	g++ -o sample sample.cc  -Wall -Werror $(shell pkg-config --cflags lua5.2) $(shell pkg-config --libs lua5.2)


#
# Cleanup
#
clean:
	rm sample || true
