#include "device.h"
#include "tuya_smart_api.h"
#include "slink_lib.h"

const char* SLINK_PRODUCT_KEY  = {"3yb8esJJHtk4vKK7"};        // 此处填写 涂鸦 给的产品 ID 号


OPERATE_RET ss_FILE_HTTPC_CB(IN CONST BYTE *data,\
                                    IN CONST UINT len)
{
    SLINK_LOG("upggg ...%d", len);

}

 OPERATE_RET sFILE_PRE_CB(IN CONST UINT file_size)
{
 		SLINK_LOG("upggg ...%d", file_size);

 }


void slink_iot_rec(int mode ,cJSON *param)             		//此处填写  接收到涂鸦数据后的处理
{
    char *rec_temp = cJSON_Print(param);
    SLINK_LOG("tuya cloud_rec : %s\n", rec_temp);
    slink_link_send_DPSTR_to_tuya(rec_temp);
    free(rec_temp);
    switch(mode)
    {
       case 0: SLINK_LOG("msg from lan");    break;    //局域网类型
       case 1: 
       case 2:
	  		   SLINK_LOG("msg from cloud");  break;    //云端类型
       default:SLINK_LOG("msg from unkown"); break;
	}

    //对命令数据进行处理
    
	

}


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

	 
	//Product Init  根据不同的云平台定制IOT接口
	slink_product_iot_init(SLINK_PRODUCT_KEY,slink_iot_rec);


	//5. DIY WIFI LAN Enable (UDP局域网)             *



	//7. Init SystemThread                        ***

	
	//8. Init SystemRam                           ***


	//9. Init  SystemFlash                        ***
	slink_flash_init();


	//11.Init SystemFile                           *

	//12.Init XXXXXX                               //  you can add your init code at here ! 


	httpc_upgd_mcu_cb_reg(ss_FILE_HTTPC_CB,sFILE_PRE_CB);
}




void slink_main(int slink_arg,void *slink_cmd)
{
    //1.Hello Slink
	SLINK_LOG_SYS_LOG

    
    //2.Init SDK
    Init_Slink();
}








