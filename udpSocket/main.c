#include "client_udp.h"
#include <time.h>

int main()
{

        Test();

        Test_t t;
        Test_t tt;
        Test_t tt1;
        Test_t tt2;
        Test_t tt3;
        Test_t t1;
        Test_t t2;
        Test_t t3;
        Test_t t4;
        Test_t t5;


/////// for I2C: ///////////
        //test 0: 
        t.id = 12; 
        t.per = 4;
        t.iter = 3;

        //test 0: 
        tt.id = 150; 
        tt.per = 4;
        tt.iter = 1;

        //test 0: 
        tt1.id = 160; 
        tt1.per = 4;
        tt1.iter = 2;

        //test 0: 
        tt2.id = 170; 
        tt2.per = 4;
        tt2.iter = 4;


        //test 1:
        t1.id = 105;
        t1.per = 4;
        t1.iter = 4;

        //test 2:
        t2.id = 106;
        t2.per = 4;
        t2.iter = 5;


        //test 3:
        t3.id = 107;
        t3.per = 4;
        t3.iter = 6;


        //test 4:
        t4.id = 108;
        t4.per = 4;
        t4.iter = 7;
       
       //test 5:
        t5.id = 109;
        t5.per = 4;
        t5.iter = 1;


        ///////////// for UART://///

//         //test 0: 
//         t.id = 12; 
//         t.per = 2;
//         t.iter = 3;

//         //test 0: 
//         tt.id = 150; 
//         tt.per = 2;
//         tt.iter = 1;

//         //test 0: 
//         tt1.id = 160; 
//         tt1.per = 2;
//         tt1.iter = 2;

//         //test 0: 
//         tt2.id = 170; 
//         tt2.per = 2;
//         tt2.iter = 4;


//         //test 1:
//         t1.id = 105;
//         t1.per = 1;
//         t1.iter = 4;

//         //test 2:
//         t2.id = 106;
//         t2.per = 4;
//         t2.iter = 5;


//         //test 3:
//         t3.id = 107;
//         t3.per = 8;
//         t3.iter = 6;


//         //test 4:
//         t4.id = 108;
//         t4.per = 16;
//         t4.iter = 7;
       
//        //test 5:
//         t5.id = 109;
//         t5.per = 16;
//         t5.iter = 1;
        
//         /************************************* Code *****************************************************/

//         //send the msg to stm32
        //  fill_buf(tt);  //check uart 
        //  fill_buf(t);
        //  fill_buf(tt1);
        //  fill_buf(tt2);
        //  fill_buf(t1);
        //  fill_buf(t2);
        //  fill_buf(t3);
        //  fill_buf(t4);
        //  fill_buf(t5);

//         // //fill_buf(t1); //check timer  - get request time out
//         // fill_buf(t2); //check spi - get request time out
//         // fill_buf(t3); //check i2c
//         //fill_buf(t4); //check adc
//         //fill_buf(t5); //check adc

        return EQUAL_ZERO;
}




        