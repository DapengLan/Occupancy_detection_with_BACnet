#Makefile to build BACnet Gateway Demonstration Application for the Linux Port

# tools - only if you need them.
# Most platforms have this already defined
# CC = gcc

# Executable file name
TARGET = bacgateway

TARGET_BIN = ${TARGET}$(TARGET_EXT)

# put any overloaded or special built src files here,
# so the linker uses these instead of the functions in the library
SRCS = main.c \
	$(BACNET_OBJECT)/gw_device.c \
	$(BACNET_HANDLER)/h_routed_npdu.c \
	$(BACNET_HANDLER)/s_router.c

OBJS = ${SRCS:.c=.o}

DEFINES += -DBAC_ROUTING

CFLAGS  = $(WARNINGS) $(DEBUGGING) $(OPTIMIZATION) $(STANDARDS) $(INCLUDES) $(DEFINES)

all: ${BACNET_LIB_TARGET} Makefile ${TARGET_BIN}

${TARGET_BIN}: ${OBJS} Makefile ${BACNET_LIB_TARGET} 
	${CC} ${PFLAGS} ${OBJS} ${LFLAGS} -o $@
	size $@
	cp $@ ../../bin

lib: ${BACNET_LIB_TARGET}

${BACNET_LIB_TARGET}:
	( cd ${BACNET_LIB_DIR} ; $(MAKE) clean ; $(MAKE) )

.c.o:
	${CC} -c ${CFLAGS} $*.c -o $@

depend:
	rm -f .depend
	${CC} -MM ${CFLAGS} *.c >> .depend

clean:
	rm -f core ${TARGET_BIN} ${OBJS} ${BACNET_LIB_TARGET} $(TARGET).map

include: .depend

