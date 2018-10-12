#include "tuya_smart_api.h"
#include "slink_lib.h"


int slink_StrToInt(char* str,int str_len)
{
     int res = 0,i;
	 for(i = 0;i<str_len;i++){

        int temp;
		temp = 0;
        switch(*(str))
        {
			case '0': temp = 0; break;
			case '1': temp = 1; break;
			case '2': temp = 2; break;
			case '3': temp = 3; break;
			case '4': temp = 4; break;
			case '5': temp = 5; break;
			case '6': temp = 6; break;
			case '7': temp = 7; break;
			case '8': temp = 8; break;
			case '9': temp = 9; break;

            default:  temp = 0; break;
		}

        int j;
		for(j = 0;j<(str_len-i-1);j++){

			temp = temp * 10;

		}

        res += temp;
		str++;
	 }

	 return res;
}


void slink_link_set_SmartLink_mode(char link_mode)
{
	tuya_set_wf_cfg(link_mode);

}


void slink_product_iot_init(const char* PK_ID,slink_for_tuya_rec tuya_rec)
{
	int op_ret = tuya_device_init(PK_ID,(SMART_FRAME_CB)tuya_rec,USER_SW_VER);
    if(op_ret != 0) {

	  //  slink_printf_error("Register PK fail\n");
    }

}

char slink_link_send_DPSTR_to_tuya(char * dp_str)
{
    int ret = tuya_obj_dp_trans_report(dp_str);
	if(ret == 0)
	{
       SLINK_LOG("send ok,send len is %d",strlen(dp_str));
	}
	return ret;
}




int Rst_Gpio_ID;

STATIC VOID key_process(INT gpio_no,PUSH_KEY_TYPE_E type,INT cnt)
{

    SLINK_LOG("gpio_no: %d",gpio_no);
    SLINK_LOG("type: %d",type);
    SLINK_LOG("cnt: %d",cnt);

    if( GPIO_ID_PIN(Rst_Gpio_ID) == gpio_no) {
        if(LONG_KEY == type) {
            tuya_dev_reset_factory();
        }else if(SEQ_KEY == type && cnt == 2) {
            ShowSysMemPoolInfo();
        }else if(NORMAL_KEY == type) {
            SLINK_LOG("Rst Key Short Donw !");
        }
    }
}


char slink_resestkey_init(int key_press_time,int GPIO_ID)
{
	tuya_kb_init();

	Rst_Gpio_ID = GPIO_ID;
	tuya_kb_reg_proc(GPIO_ID,key_press_time,key_process);

}

const char* flash_dir_name = "test_psm_zsr_2018";


char slink_flash_init()
{
	tuya_psm_register_module(flash_dir_name,"test_psm_zsr_2018");
	char buf[32] = {0};
	if(0 != slink_flash_read_param("slink_power_on_cnt",buf)){

        char temp_buf[32] = {"0123"};
        slink_flash_write_param("slink_power_on_cnt","0");
		slink_flash_read_param("slink_power_on_cnt",buf);
	}



	int pow_on_cnt = slink_flash_get_PowerOnCnt();
 	pow_on_cnt++;
	SLINK_LOG("power on cnt is %d",pow_on_cnt);
	slink_flash_set_PowerOnCnt(pow_on_cnt);


}
 
 char slink_flash_write_param(char *v_name,char *v_data)
 {
	return tuya_psm_set_single(flash_dir_name,v_name,v_data);
 }

 
 char slink_flash_read_param(char *v_name,char *v_data)
 {
	return tuya_psm_get_single(flash_dir_name,v_name,v_data,32);	
 }

int slink_flash_get_PowerOnCnt()
{
	char buf[32] = {0};

    slink_flash_read_param("slink_power_on_cnt",buf);    
    return slink_StrToInt(buf,strlen(buf));
}

void slink_flash_set_PowerOnCnt(int cnt)
{
	char buf[32] = {0};
	sprintf(buf,"%d",cnt);
    slink_flash_write_param("slink_power_on_cnt",buf);

}


