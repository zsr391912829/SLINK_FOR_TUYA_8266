#include "device.h"
#include "tuya_smart_api.h"
#include "slink_lib.h"

const char* SLINK_PRODUCT_KEY  = {"lXz2geQWhCrjx68o"};        // 此处填写 涂鸦 给的产品 ID 号


void Init_Slink()
{
    ///   if you see ***  , this fun is very imoportant for our program ! 
    ///   if you see *    , this fun will be unuseful for you ,you can del .
 
	//1. Set Wifi Smart_link mode                 ***
	slink_link_set_SmartLink_mode(0);             // 0 : SmartLink  1:Ap mode  2:AirKiss


	//2. Set Reset Key  (复位进入配网状态)                *
	slink_resestkey_init(3000,0);                 // 3000 : Long Press 3000ms ,GPIO_0 to Reset Wifi and Start SmartLink

/*

    //3. Set Wifi Led   (设置WIFI状态指示灯)             *
    slink_wifiLed_init(16);                      // GPIO_16  will be wifi led ;   


	//4. Set WIFI EVENT                           ***
    if(0 == slink_link_register_tuya_recv_cb(char * str, int rec_len)){    //

         SLINK_LOG("reg tuya recv handler OK !")

	}
	*/

	 


	//5. DIY WIFI LAN Enable (UDP局域网)             *


    //6. Init GPIO                                *


	//7. Init SystemThread                        ***

	
	//8. Init SystemRam                           ***


	//9. Init  SystemFlash                        ***
	slink_flash_init();

	//10.Init User                                 *

	//11.Init SystemFile                           *

	//12.Init XXXXXX                               //  you can add your init code at here ! 

	
}



VOID slink_tuya_fisrst_register_cb(SMART_CMD_E cmd,cJSON *root)
{  
//    PR_DEBUG("cmd:%d",cmd);
    cJSON *nxt = root->child; 
    UCHAR dp_id = 0;
    while(nxt) {
        dp_id = atoi(nxt->string);
		deal_dps_handle(dp_id,nxt);
        nxt = nxt->next; 
        SystemSleep(50);
    }
}


void slink_main(int slink_arg,void *slink_cmd)
{
    /*    Slink important code , don't del (1) (2)  */
	SLINK_LOG_SYS_LOG
		SLINK_LOG("product register ok !\n");

    
    //1.Register Product Info     [* For tuya*]
        /*
    OPERATE_RET op_ret;

	if(0 !=  tuya_device_init(SLINK_PRODUCT_KEY,slink_tuya_fisrst_register_cb,USER_SW_VER){

            SLINK_LOG("product register ok !\n");
	}
	else{
        	SLINK_LOG("prod \n");
	}
*/
	
    //2.Init SDK
    Init_Slink();


	//3.you can add your Init code at here ......
	
}








