DIRS = lib
ROOT = .

include Make.defines.linux

*: $@

%:	%.cpp
	$(CC) $(CFLAGS) $@.cpp -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	find ./ -not -name "." -not -name "*.cpp" -not -name "Makefile" \
		-not -name "Make.*" -not -type d -not -name "*.h" \
		| grep -v .git | grep -v *.md | grep -v .vs* \
		| xargs rm -rf
