#include "hsusb_driver.h"

int UsbHandler::write_data (unsigned char* _buffer) {

        const int buf_len = sizeof(_buffer); 


        int sent_bytes = 0;
        res = libusb_bulk_transfer(device_handle, WRITE_ENDPOINT, _buffer, TRANSFER_SIZE, &sent_bytes, TIMEOUT);

        if (res < 0) {
                printf("An error occured while sending data : %s\n", libusb_error_name(res));
        } 
        return res;
}

int UsbHandler::read_data(unsigned char* _read_buffer, int _read_len) {
        int read_bytes = 0;

        memset(buffer, 0, TRANSFER_SIZE);

        res = libusb_bulk_transfer(device_handle, READ_ENDPOINT, _read_buffer,TRANSFER_SIZE, &read_bytes, TIMEOUT);

        //memcpy(_read_buffer, &buffer[1], 7);
        buffer[7] = '\0';

        return res;

}

int UsbHandler::init_usb() {

    device_handle = NULL; 
	char value_str[8]; 
    int result;

    result = libusb_init( NULL );
    if ( result < 0 )
    {
        printf( "Error initializing libusb: %s\n", libusb_error_name( result ) );
        exit( -1 );
    }

    libusb_set_option( NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING );

    device_handle = libusb_open_device_with_vid_pid( NULL, VENDOR_ID, PRODUCT_ID );
    if ( !device_handle )
    {
        printf( "Error finding USB device\n" );
        libusb_exit( NULL );
                exit( -2 );
        }

    libusb_set_auto_detach_kernel_driver( device_handle, 1 );

    result = libusb_claim_interface( device_handle, 0 );
    if ( result < 0 )
    {
        printf( "Error claiming interface: %s\n", libusb_error_name( result ) );
        if ( device_handle )
        {
            libusb_close( device_handle );
        }

        libusb_exit( NULL );
        exit( -3 );
    }
	return result;
}


void UsbHandler::remove_usb(){
	
	libusb_release_interface(device_handle, 0);
    libusb_close(device_handle);

}


int main(){
	UsbHandler usbHandler;
	usbHandler.init_usb();
	char* a = (char*)malloc(sizeof(char)* TRANSFER_SIZE - 1);
	memset(a, 0x41, TRANSFER_SIZE - 2);
	a[TRANSFER_SIZE - 2] = '\0';
	//while(1){
	//	usbHandler.write_data(a);
	//}
	unsigned char read_buf[TRANSFER_SIZE];
	while(1){	
	//if(0 == usbHandler.read_data(read_buf, TRANSFER_SIZE - 1)) {
		 usbHandler.read_data(read_buf, TRANSFER_SIZE - 1);
		 printf("%c\n", read_buf[2]);
//		printf("read buf ->%s\n", read_buf);
	////}
	}
	usbHandler.remove_usb();
	return 0;
}
