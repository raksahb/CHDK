# 0x3242 Found @ 0xfff40040
PLATFORMID=12866

#override OPT_EXMEM_MALLOC=1
#override OPT_CHDK_IN_EXMEM=1

PLATFORMOS=dryos
PLATFORMOSVER=50

# start of firmware
ROMBASEADDR=0xFF000000

MAXRAMADDR = 0x07ffffff

EXMEM_HEAP_SKIP=0x679800	#(0x48000000-0x47986800) from sub_FF074D0C = size of video buffers in EXMEM area
EXMEM_BUFFER_SIZE=0x100000	# Amount of EXMEM memory to allocate for CHDK; 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB

# Set up size variables for AgentRAM
override OPT_ARAM_MALLOC=1

ARAM_HEAP_START=0x3ce000  # Found @ 0xff18c9a8
ARAM_HEAP_SIZE=0x22000   # Found @ 0xff18c96c

# points to the start of the memory pool used by the firmware
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x78867E0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x1716E8		# original non-exmem value D20
endif

# Found @ 0xffff39f0
NEED_ENCODED_DISKBOOT=8

# Found @ 0xffff39e0
KEYSYS=d4c
