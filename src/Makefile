TARGET := wml2xml

SRCS    := serialization/parser.cpp tstring.cpp serialization/tokenizer.cpp config_attribute_value.cpp config.cpp serialization/preprocessor.cpp game_config.cpp color.cpp color_range.cpp log.cpp filesystem_boost.cpp filesystem_common.cpp serialization/unicode.cpp serialization/string_utils.cpp gettext_boost.cpp serialization/binary_or_text.cpp version.cpp font/constants.cpp

#precompiled headers
HEADERS := 
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

CXXFLAGS += -fpic -I.
LDFLAGS += 
.PHONY: all release debug clean distclean 

all: release
release: ${TARGET}
debug: ${TARGET}
info: ${TARGET}
profile: ${TARGET}
hardcore: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS}

${OBJS}: %.o: %.cpp %.dep ${GCH}
	${CXX} ${CXXFLAGS} -o $@ -c $<

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

${GCH}: %.gch: ${HEADERS} 
	${CXX} ${CXXFLAGS} -o $@ -c ${@:.gch=.hpp}

install:
	mkdir -p ${DESTDIR}/${PREFIX}
	cp ${TARGET} ${DESTDIR}/${PREFIX}

uninstall:
	rm ${DESTDIR}/${PREFIX}/${TARGET}

clean:
	rm -f *~ ${DEPS} ${OBJS} ${CUO} ${GCH} ${TARGET} 

distclean: clean

