DATE = 2016-01-23
VERSION = 9.22
RXVTNAME = urxvt
SHELL = /bin/sh
prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
man1dir = ${prefix}/share/man/man1
man1ext = 1
man3dir = ${prefix}/share/man/man3
man3ext = 3
PODOPTS = quotes => q<"> , center => q<RXVT-UNICODE>, release => q<$(VERSION)>
CXX = g++
PERL = perl
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = /usr/bin/install -c -m 755
INSTALL_DATA = /usr/bin/install -c -m 644
CXXFLAGS = -g -O3 -fno-rtti -fvisibility-inlines-hidden -fno-threadsafe-statics -fno-enforce-eh-specs -w
CPPFLAGS =    -I/usr/include/freetype2
LDFLAGS = 
DEFS = -DHAVE_CONFIG_H
LIBS =  -lsupc++ -lm
XINC =   
XLIB = -lfontconfig -lfreetype -lXft -lXrender -lX11 -lXmu -lXt -lX11  -lX11   
COMPILE = $(CXX) -I.. -I$(srcdir) -I. -I$(srcdir)/../libev -I$(srcdir)/../libptytty/src $(DEFS) $(CPPFLAGS) $(CXXFLAGS) $(XINC)
LINK = gcc $(LDFLAGS)
EXEEXT = 
PERLFLAGS =  -D_REENTRANT -D_GNU_SOURCE -DDEBIAN -fwrapv -fno-strict-aliasing -pipe -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64  -I/usr/lib/x86_64-linux-gnu/perl/5.22/CORE 
PERLLIB = -Wl,-E  -fstack-protector-strong -L/usr/local/lib  -L/usr/lib/x86_64-linux-gnu/perl/5.22/CORE -lperl -ldl -lm -lpthread -lc -lcrypt

srcdir = .


first_rule: all
dummy:

COMMON = command.o rxvtfont.o init.o main.o misc.o screen.o xdefaults.o \
	encoding.o rxvttoolkit.o rxvtutil.o keyboard.o \
	ev_cpp.o fdpass_wrapper.o ptytty_wrapper.o rxvtperl.o

COMMON_DAEMON = rxvtdaemon.o

RXVT_BINNAME=$(DESTDIR)$(bindir)/$(RXVTNAME)$(EXEEXT)
RXVTC_BINNAME=$(DESTDIR)$(bindir)/$(RXVTNAME)c$(EXEEXT)
RXVTD_BINNAME=$(DESTDIR)$(bindir)/$(RXVTNAME)d$(EXEEXT)

#
# Distribution variables
#

.SUFFIXES:	.C .c .o

#-------------------------------------------------------------------------
# inference rules
.C.o:
	$(COMPILE) -c $<

#-------------------------------------------------------------------------

all: allbin

rxvt: rxvt.o $(COMMON)
	$(LINK) -o $@ rxvt.o $(COMMON) $(LIBS) $(XLIB) $(PERLLIB)

rxvtd: rxvtd.o $(COMMON) $(COMMON_DAEMON)
	$(LINK) -o $@ rxvtd.o $(COMMON) $(COMMON_DAEMON) $(LIBS) $(XLIB) $(PERLLIB)

rxvtc: rxvtc.o $(COMMON_DAEMON) fdpass_wrapper.o
	$(LINK) -o $@ rxvtc.o $(COMMON_DAEMON) fdpass_wrapper.o $(LIBS)

#-------------------------------------------------------------------------

#EXUBERANT_OPTS = -I NOTHROW -I THROW

tags: *.[Ch]
	ctags $(EXUBERANT_OPTS) *.[Ch]

TAGS: *.[Ch]
	etags $(EXUBERANT_OPTS) *.[Ch]

allbin: rxvt rxvtd rxvtc

alldoc:

clean:
	rm -f rxvt rxvtc rxvtd perlxsi.c rxvtperl.C manlst mantmp
	rm -f *.o

distclean: clean
	rm -f Makefile

realclean: distclean
	rm -f tags TAGS

cleandir: realclean

install-perl:
	$(INSTALL) -d $(DESTDIR)$(libdir)
	$(INSTALL) -d $(DESTDIR)$(libdir)/urxvt
	$(INSTALL) -d $(DESTDIR)$(libdir)/urxvt/perl
	$(INSTALL) -d $(DESTDIR)$(man1dir)
	$(INSTALL) -d $(DESTDIR)$(man3dir)
	$(INSTALL_DATA) $(srcdir)/urxvt.pm $(DESTDIR)$(libdir)/urxvt/urxvt.pm
	for ext in $(srcdir)/perl/*; do \
	   test -f "$$ext" || continue; \
	   base=`basename "$$ext"`; \
	   $(INSTALL_DATA) "$$ext" $(DESTDIR)$(libdir)/urxvt/perl/; \
	   < "$$ext" \
	   $(PERL) -MPod::Man -e '(new Pod::Man name => "'urxvt-$$base'", $(PODOPTS))->parse_from_file' \
	   > mantmp; \
	   test -s mantmp && $(INSTALL_DATA) mantmp $(DESTDIR)$(man1dir)/$(RXVTNAME)-$$base.$(man1ext); \
	   < "$$ext" $(PERL) -ne '<>, (print <> . "\n"), exit if /^=head1/' >&3; \
	done 3>manlst
	cat $(srcdir)/../doc/extensions.pod.top manlst $(srcdir)/../doc/extensions.pod.bot | \
	$(PERL) -MPod::Man -e '(new Pod::Man name => "$(RXVTNAME)-extensions", $(PODOPTS))->parse_from_file' \
	> mantmp
	$(INSTALL_DATA) mantmp $(DESTDIR)$(man1dir)/$(RXVTNAME)-extensions.$(man1ext)
	< $(srcdir)/urxvt.pm \
	$(PERL) -MPod::Man -e '(new Pod::Man name => "$(RXVTNAME)perl", section => 3, $(PODOPTS))->parse_from_file' \
	> mantmp
	$(INSTALL_DATA) mantmp $(DESTDIR)$(man3dir)/$(RXVTNAME)perl.$(man3ext)

install-bin: allbin
	$(INSTALL) -d $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) rxvt  $(RXVT_BINNAME)
	$(INSTALL_PROGRAM) rxvtc $(RXVTC_BINNAME)
	$(INSTALL_PROGRAM) rxvtd $(RXVTD_BINNAME)

install: install-bin install-perl

perlxsi.c: Makefile
	$(PERL) -MExtUtils::Embed -e xsinit -- -std urxvt

rxvtperl.C: rxvtperl.xs iom_perl.h iom_perl.xs typemap typemap.iom
	PERL="$(PERL)" $(PERL) /usr/share/perl/5.22/ExtUtils/xsubpp -C++ -typemap /usr/share/perl/5.22/ExtUtils/typemap -typemap 'typemap.iom' -typemap 'typemap' -prototypes $(srcdir)/rxvtperl.xs >$@

rxvtperl.o: rxvtperl.C perlxsi.c
	$(COMPILE) $(PERLFLAGS) -DLIBDIR="\"$(libdir)/urxvt\"" -c $<

depend:
	makedepend -f Makefile.in -I. -I.. -I../libptytty/src -I../libev -Y *.C *.xs >/dev/null 2>&1

# DO NOT DELETE: nice dependency list follows

command.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
command.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h
command.o: rxvttoolkit.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
command.o: callback.h ../libptytty/src/libptytty.h
command.o: rxvtperl.h hookinc.h rsinc.h optinc.h version.h command.h
command.o: keyboard.h
encoding.o: ../config.h encoding.h rxvtutil.h ../libptytty/src/ecb.h
encoding.o: ../libptytty/src/estl.h emman.h table/iso8859_1.h
encoding.o: table/iso8859_15.h table/iso8859_2.h table/iso8859_3.h
encoding.o: table/iso8859_4.h table/iso8859_5.h table/iso8859_6.h
encoding.o: table/iso8859_7.h table/iso8859_8.h table/iso8859_9.h
encoding.o: table/iso8859_10.h table/iso8859_11.h table/iso8859_13.h
encoding.o: table/iso8859_14.h table/iso8859_16.h table/koi8_r.h
encoding.o: table/koi8_u.h table/ksc5601_1987_0.h table/big5.h table/gbk_0.h
encoding.o: table/gb2312_1980_0.h table/cns11643_1992_1.h
encoding.o: table/cns11643_1992_2.h table/cns11643_1992_3.h
encoding.o: table/cns11643_1992_4.h table/cns11643_1992_5.h
encoding.o: table/cns11643_1992_6.h table/cns11643_1992_7.h
encoding.o: table/cns11643_1992_f.h table/big5_ext.h table/big5_plus.h
encoding.o: table/viscii.h table/jis0201_1976_0.h table/jis0208_1990_0.h
encoding.o: table/jis0212_1990_0.h table/jis0213_1.h table/jis0213_2.h
encoding.o: table/compose.h table/category.h
ev_cpp.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h ../libev/ev.c
ev_cpp.o: ../libev/ev_vars.h ../libev/ev_epoll.c ../libev/ev_select.c
fdpass_wrapper.o: ../libptytty/src/fdpass.C ../config.h
fdpass_wrapper.o: ../libptytty/src/libptytty.h
init.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
init.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
init.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
init.o: ../libptytty/src/libptytty.h rxvtperl.h
init.o: hookinc.h rsinc.h optinc.h init.h keyboard.h
keyboard.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
keyboard.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h
keyboard.o: rxvttoolkit.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
keyboard.o: callback.h ../libptytty/src/libptytty.h
keyboard.o: rxvtperl.h hookinc.h rsinc.h optinc.h keyboard.h
main.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
main.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
main.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
main.o: ../libptytty/src/libptytty.h rxvtperl.h
main.o: hookinc.h rsinc.h optinc.h init.h keyboard.h
misc.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
misc.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
misc.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
misc.o: ../libptytty/src/libptytty.h rxvtperl.h
misc.o: hookinc.h rsinc.h optinc.h
ptytty_wrapper.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h
ptytty_wrapper.o: encoding.h rxvtutil.h ../libptytty/src/estl.h emman.h
ptytty_wrapper.o: rxvtfont.h rxvttoolkit.h ev_cpp.h ../libev/ev++.h
ptytty_wrapper.o: ../libev/ev.h callback.h
ptytty_wrapper.o: ../libptytty/src/libptytty.h rxvtperl.h hookinc.h rsinc.h
ptytty_wrapper.o: optinc.h ../libptytty/src/logging.C
ptytty_wrapper.o: ../libptytty/src/ptytty.h ../libptytty/src/ptytty_conf.h
ptytty_wrapper.o: ../libptytty/src/proxy.C ../libptytty/src/ptytty.C
rxvt.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
rxvt.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
rxvt.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
rxvt.o: ../libptytty/src/libptytty.h rxvtperl.h
rxvt.o: hookinc.h rsinc.h optinc.h
rxvtc.o: ../config.h rxvtdaemon.h rxvtutil.h ../libptytty/src/ecb.h
rxvtc.o: ../libptytty/src/estl.h emman.h ../libptytty/src/libptytty.h
rxvtd.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
rxvtd.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
rxvtd.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
rxvtd.o: ../libptytty/src/libptytty.h rxvtperl.h
rxvtd.o: hookinc.h rsinc.h optinc.h rxvtdaemon.h
rxvtdaemon.o: rxvtdaemon.h rxvtutil.h ../libptytty/src/ecb.h
rxvtdaemon.o: ../libptytty/src/estl.h emman.h
rxvtfont.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
rxvtfont.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h
rxvtfont.o: rxvttoolkit.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
rxvtfont.o: callback.h ../libptytty/src/libptytty.h
rxvtfont.o: rxvtperl.h hookinc.h rsinc.h optinc.h table/linedraw.h
rxvtperl.o: ../config.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
rxvtperl.o: rxvt.h feature.h ../libptytty/src/ecb.h encoding.h rxvtutil.h
rxvtperl.o: ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
rxvtperl.o: callback.h ../libptytty/src/libptytty.h
rxvtperl.o: rxvtperl.h hookinc.h rsinc.h optinc.h keyboard.h perlxsi.c
rxvtperl.o: iom_perl.h
rxvttoolkit.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
rxvttoolkit.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h
rxvttoolkit.o: rxvttoolkit.h ev_cpp.h ../config.h ../libev/ev++.h
rxvttoolkit.o: ../libev/ev.h callback.h
rxvttoolkit.o: ../libptytty/src/libptytty.h rxvtperl.h hookinc.h rsinc.h
rxvttoolkit.o: optinc.h
rxvtutil.o: emman.c emman.h ../libptytty/src/ecb.h rxvtutil.h
rxvtutil.o: ../libptytty/src/estl.h
screen.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
screen.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
screen.o: ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h callback.h
screen.o: ../libptytty/src/libptytty.h rxvtperl.h
screen.o: hookinc.h rsinc.h optinc.h
xdefaults.o: ../config.h rxvt.h feature.h ../libptytty/src/ecb.h encoding.h
xdefaults.o: rxvtutil.h ../libptytty/src/estl.h emman.h rxvtfont.h
xdefaults.o: rxvttoolkit.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
xdefaults.o: callback.h ../libptytty/src/libptytty.h
xdefaults.o: rxvtperl.h hookinc.h rsinc.h optinc.h version.h keyboard.h
rxvtperl.o: ../config.h ev_cpp.h ../config.h ../libev/ev++.h ../libev/ev.h
rxvtperl.o: rxvt.h feature.h ../libptytty/src/ecb.h encoding.h rxvtutil.h
rxvtperl.o: ../libptytty/src/estl.h emman.h rxvtfont.h rxvttoolkit.h
rxvtperl.o: callback.h ../libptytty/src/libptytty.h
rxvtperl.o: rxvtperl.h hookinc.h rsinc.h optinc.h keyboard.h perlxsi.c
rxvtperl.o: iom_perl.h
