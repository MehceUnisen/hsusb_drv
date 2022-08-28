#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID		0x04d8
#define PRODUCT_ID		0xe83d

#define TRANSFER_SIZE	10

#define TIMEOUT			200


#define WRITE_ENDPOINT 0x01
#define READ_ENDPOINT 0x82


class UsbHandler {
	private:
		struct libusb_device_handle* device_handle;
		int res;
		unsigned char buffer[TRANSFER_SIZE];
		
	public:
	
		int init_usb();
		int write_data(unsigned char* _buffer);
		int read_data(unsigned char* _read_buffer, int _read_len);
		void remove_usb();
};
