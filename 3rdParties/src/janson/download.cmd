

set JANSSON_SRC=2.13
if not exist %JANSSON_SRC% (
	echo downloading Jansson
	mkdir %JANSSON_SRC%
	git clone --branch %JANSSON_SRC% https://github.com/akheron/jansson.git ./%JANSSON_SRC%
)

