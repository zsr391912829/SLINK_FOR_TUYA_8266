#include "tuya_smart_api.h"
#include "slink_lib.h"



void slink_link_set_SmartLink_mode(char link_mode)
{
	tuya_set_wf_cfg(link_mode);

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


char slink_flash_init()
{
	tuya_psm_register_module("C pan","flash_dir");
}
 
 char slink_flash_write_param(char *v_name,char *v_data)
 {


 }

 
 char slink_flash_read_param(char *v_name,char *v_data)
 {

 }



