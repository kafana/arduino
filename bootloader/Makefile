AVRDUDE = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude
AVRDUDEFLAGS = -b 19200 -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -c avrispmkII -p m328p -v
BOOTLOADER = optiboot_atmega328.hex

all: fuses install

fuses:
	${AVRDUDE} ${AVRDUDEFLAGS} -U efuse:w:0x05:m
	${AVRDUDE} ${AVRDUDEFLAGS} -U hfuse:w:0xD6:m
	${AVRDUDE} ${AVRDUDEFLAGS} -U lfuse:w:0xFF:m

install:
	${AVRDUDE} ${AVRDUDEFLAGS} -U flash:w:${BOOTLOADER}:a
	${AVRDUDE} ${AVRDUDEFLAGS} -U lock:w:0x0F:m

read:
	${AVRDUDE} ${AVRDUDEFLAGS}
