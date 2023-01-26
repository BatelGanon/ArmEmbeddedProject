#ifndef CLIENT_UDP_H
#define CLIENT_UDP_H

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//megic number
#define BUF_SIZE 60
#define IP_ADDRESS "192.168.1.2" // The ip adress of the remote side - the server
#define FLAG_ZERO 0 
#define EQUAL_ZERO 0
#define PORT 7 // Port of the server
#define LEN 30 // The length of 
#define SLEEP_TIME 3 
#define ERROR -1 // Error code
#define CHAR_S3XDIZE 6
#define PACKET_SIZE 256
#define TRUE 1
#define FALSE 0
#define PERIPERALS_COUNT 5
#define MAX_MSG_LEN 10
#define EQUAL_ONE 1
#define TEST_COUNT 20
#define MIN_ITERATION 1
#define MAX_ITERATION 30
#define TIMER 1
#define UART 2
#define SPI 4
#define I2C 8
#define ADC 16
#define EQUAL_TOW 2
#define MAX_ID 10000
#define MIN_ID 1

// This struct store all the values of the test we will send
typedef struct Test
{       
        uint32_t id;   
        uint8_t per;
        uint8_t iter;
        uint8_t size; 
        char* msg;
        uint8_t result;
} Test_t;   


// Function declarations

// Void function get a test structure and loads the values into a buffer
// so this buffer will be send as a packet
// then make a call to the function send_msg();
void fill_buf(Test_t t);

// Void function, does not accept values,
// creates a socket and initializes it with an ip address and port,
// sends the packet to the designated address and port
// then get an answer and print it to the screen accordingly
int send_msg();


// A function that does not accept values and returns an int,
// used for manual tests, allows the user to enter the data himself according to the required limitations,
// if the user exceeds the limits, the program will return 0 and end the run,
// at the end of the program, the function fill_buf() will be called with the test structure with the values entered by the user
int MenualTest();

// function asks the user what type of test they would like to perform and passes to the
// appropriate function
int Test();

// Fanction for auto test, fill the packet with msg from msg array
// and send to fill_buff to build the packet 
void AutoTest();

#endif