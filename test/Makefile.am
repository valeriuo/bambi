AM_CPPFLAGS = $(HTSLIB_CPPFLAGS)
AM_LDFLAGS = $(HTSLIB_LDFLAGS)

check_PROGRAMS = t_bclfile t_decode t_filterfile t_posfile t_i2b

t_bclfile_SOURCES = t_bclfile.c
t_bclfile_CFLAGS = -DDATA_DIR=$(abs_srcdir)/data
t_bclfile_LDADD = -lz -ldl -lxml2 -lpthread

t_decode_SOURCES = t_decode.c
t_decode_CFLAGS = -I$(top_srcdir)/src -DDATA_DIR=$(abs_srcdir)/data
t_decode_LDADD = $(HTSLIB_HOME)/lib/libhts.a -lz -ldl -lxml2 -lpthread -llzma -lbz2

t_filterfile_SOURCES = t_filterfile.c
t_filterfile_CFLAGS = -DDATA_DIR=$(abs_srcdir)/data

t_posfile_SOURCES = t_posfile.c
t_posfile_CFLAGS = -DDATA_DIR=$(abs_srcdir)/data

t_i2b_SOURCES = t_i2b.c ../src/posfile.c ../src/bclfile.c ../src/filterfile.c ../src/array.c
t_i2b_CFLAGS = -I$(top_srcdir)/src -I/usr/include/libxml2 -DDATA_DIR=$(abs_srcdir)/data
t_i2b_LDADD = $(HTSLIB_HOME)/lib/libhts.a -lz -ldl -lxml2 -lpthread -llzma -lbz2

EXTRA_DIST = data
