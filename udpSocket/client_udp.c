#include "client_udp.h"    


// Global Vars 
struct sockaddr_in dest;                // Holds Destination socket (IP+PORT)
int socket_fd;                          // Holds socket file descriptor
unsigned int ssize;                     // Holds size of dest
struct hostent *hostptr;                // Holds host information
char buf[BUF_SIZE + 1];                 // Used for writing/ Reading from buffer
int retVal = EQUAL_ZERO;                // Holds return Value for recvfrom() / sendto()
char *cRetVal = NULL;                   // Holds return Value for fgets()
char packet[PACKET_SIZE] = {EQUAL_ZERO};      // Holds the data we will send in the packet
Test_t tests[TEST_COUNT] = {EQUAL_ZERO};


// Fanction for auto test, fill the packet with msg from msg array
// and send to fill_buff to build the packet 
void AutoTest() {

        int length = 0;
        uint8_t j = 1;
        char* msg[TEST_COUNT] = {"abcd" , "234566" , "batel" , "@#$%^&(" , "hello84" , "bye!@#" , "ef#$" , "jdc k" , "09@@08" , "++_)!@#$,"
                     "kjdnckjn" , "234566" , "batel" , "msgmsg" , "hello84" , "Test" , "jdksiua" , "h8dehf87" , "jkdcjk" , "87w4rh8,"} ;
        for (size_t i = EQUAL_ZERO; i < TEST_COUNT; i++)
        {
                length = strlen(msg[i]);
                tests[i].id = i + EQUAL_ONE;
                tests[i].iter = 2;
                tests[i].msg = msg[i];
                tests[i].size = strlen(tests[i].msg);
                tests[i].per =  2;
                fill_buf(tests[i]);
                
        }
 }

// function asks the user what type of test they would like to perform and passes to the
// appropriate function
int Test(){

        int choice = FLAG_ZERO; 
        printf("Hello, for automatic test please press 1, for menual test please press 2\n");
        scanf("%d", &choice);
        while(getchar() != '\n'); 
        if (choice == EQUAL_ONE)
        {
                AutoTest();
                return FALSE;
        }
        if (choice == EQUAL_TOW) 
        {
                MenualTest();
                return FALSE; 
        }
        else 
        {
                printf("Invalide value\n");
                return FALSE;
        }
}


//function to manage menual tests, 
// get input from the user and fill the packet
int MenualTest(){
        Test_t t;
        char buff[PACKET_SIZE] = {EQUAL_ZERO};
        printf("Please enter a msg : \n");
        scanf("%s", buff);
        t.size = strlen(buff);

        //check that size of data is between 1 to 255 char
        if (! (t.size >= EQUAL_ONE) && (t.size <= PACKET_SIZE))
        {
                printf("Invalid Data length");
                return FALSE;
        }
        
        printf("Please choose protocol:\n1.TIMER\n2.UART\n4.SPI\n8.I2C\n16.ADC\n");
        scanf("%"SCNu8 , &(t.per));
        if ((t.per != TIMER) && (t.per != UART) && (t.per != SPI) && (t.per != I2C ) && (t.per != ADC))
        {
                printf("Invalid Peripheria");
                return 0;
        }

        printf("Please enter Test ID : \n");
        scanf("%"SCNu32, &(t.id));
         if(! (t.id < MAX_ID && t.size > MIN_ID))
        {
                printf("Invalid ID number");
                return FALSE;
        }


        printf("Please enter Iteration number : \n");
        scanf("%"SCNu8, &(t.iter));
        if(! (t.iter < MAX_ITERATION && t.size > MIN_ITERATION))
        {
                printf("Invalid Iteration number");
                return FALSE;
        }

        t.msg = (char*) buff;
        fill_buf(t);
        return TRUE;

}
        

// function to fill the packet with the data we want to send
void fill_buf(Test_t t) {
        *(uint32_t *)(packet + 0) = t.id;
        *(uint8_t *)(packet + 4) = t.per;
        *(uint8_t *)(packet + 5) = t.iter;
        *(uint8_t *)(packet + 6) = t.size;
        memcpy(packet + 7, t.msg, t.size);

        //send to function send_msg to craete the connection 
        send_msg();
        
}        

// Void function handles the creation of the socket to the remote side, 
// if the connection is established successfully it sends the packet, 
// checks its integrity and receives a reply,
// then prints the result to the screen      
int send_msg(){

        // Initialization 

        // Create socket
        socket_fd = socket(AF_INET, SOCK_DGRAM, FLAG_ZERO); 
        
        // Validate the socket
        if (socket_fd == ERROR)
        {
                perror("Create socket");
                exit(1);
        } 

        // Clearing the struct
        bzero((char *)&dest, sizeof(dest));
        // Setting IPv4           
        dest.sin_family = (short)AF_INET;
        // Setting port             
        dest.sin_port = htons(PORT);      
        // Setting IP address            
        dest.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
        // Get dest size
        ssize = sizeof(dest);                         

        while(TRUE)
        {        
                // Send msg - get packet with data, length, flag, ip address   
                retVal = sendto(socket_fd, packet, 7 + strlen(packet + 7), FLAG_ZERO, (struct sockaddr*) &dest, ssize); 
                
                // Checks if the packet was sent successfully, if not prints an error message 
                if (retVal < EQUAL_ZERO){
                        printf("Fail to send msg");
                        break;
                }  

                // if (strcmp(buf, "exit") == EQUAL_ZERO){
                //         printf("you choose to exit, bye bye");
                //         break;
                // }

                // Get answer from remote side
                retVal = recvfrom(socket_fd, buf, LEN, FLAG_ZERO, (struct sockaddr *)&dest, &ssize); 

                // Checks if the packet was received successfully, if not prints an error message
                if (retVal < EQUAL_ZERO)
                {
                        printf("Fail to get msg");
                        break;
                }

                // Reads the test result and prints the ID and result to the screen accordingly
                if(buf[EQUAL_ZERO] == FALSE) {
                        printf("Test ID: %"SCNu32"\n Result: Fail\n", *(uint32_t*)(buf + EQUAL_ONE));
                }
                else if(buf[EQUAL_ZERO] == TRUE){
                        printf("Test ID: %"SCNu32"\n Result: Sucsses\n", *(uint32_t*)(buf + EQUAL_ONE));
                }

                // Closing socket
                close(socket_fd); 
                printf("Closing client...\n");
                sleep(SLEEP_TIME);
                return FALSE;
        }
        return FALSE ;
}

