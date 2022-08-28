CC := gcc
PP := g++

PP_SRC_FILES := $(wildcard *.cpp)
PP_HEADER_FILES := $(wildcard *.h)



PP_FLAGS := -lusb-1.0

OUT_FILE := hs_usb_driver

exe: ${PP_SRC_FILES} ${PP_HEADER_FILES}
	${PP} ${PP_SRC_FILES} -o ${OUT_FILE} ${PP_FLAGS}

run: exe
	sudo ./${OUT_FILE}

clean:
	rm ${OUT_FILE}

