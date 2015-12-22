AVRDUDE = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude
AVRDUDEFLAGS = -b 19200 -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -c avrispmkII -p m2560 -v
BOOTLOADER = stk500boot_v2_mega2560.hex

all: read

fuses:
	${AVRDUDE} ${AVRDUDEFLAGS} -e -U lock:w:0x3F:m -U efuse:w:0xFD:m -U hfuse:w:0xD8:m -U efuse:w:0xFF:m

install: fuses
	${AVRDUDE} ${AVRDUDEFLAGS} -V -U flash:w:${BOOTLOADER}
	${AVRDUDE} ${AVRDUDEFLAGS} -U lock:w:0x0F:m

read:
	${AVRDUDE} ${AVRDUDEFLAGS}
