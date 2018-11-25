CC := gcc
CFLAGS := -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi
CWARNS := -Wno-int-to-pointer-cast -Wno-unused-variable -Wno-pointer-to-int-cast
LDFLAGS := -L$(SDKSTAGE)/opt/vc/lib/ -lbrcmGLESv2 -lbrcmEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt -lm -lilclient -Lsrc/libs/ilclient -lvgfont -Lsrc/libs/vgfont -L$(SDKSTAGE)/src/libs/vgfont -lfreetype -lz
INCLUDE := -I$(SDKSTAGE)/opt/vc/include/ -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux -I./ -I$(SDKSTAGE)/src/libs/ilclient -I$(SDKSTAGE)/src/libs/vgfont

output.bin:
	#$(CC) -o bin/output.bin -Wl,--whole-archive $(OBJS) $(LDFLAGS) -Wl,--no-whole-archive -rdynamic
	$(CC) glue.c $(CFLAGS) $(CWARNS) $(INCLUDE) $(LDFLAGS) -DMAX_HEAP_SPACE=16777215 -DMAX_FRAMES=8388607

build-all:
	sh scripts/build_all.sh

run:
	bin/output.bin

.PHONY: build-all run
