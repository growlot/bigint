#! /bin/sh

### Call of libtoolize is needed when compiling a shared library.
### autoheader will generate config.h.in
autoheader \
&& aclocal \
&& libtoolize \
&& automake --add-missing \
&& autoconf
