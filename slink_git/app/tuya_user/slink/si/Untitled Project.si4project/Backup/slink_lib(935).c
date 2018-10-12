#include "tuya_smart_api.h"
#include "slink_lib.h"



void slink_link_set_SmartLink_mode(char link_mode)
{
	tuya_set_wf_cfg(link_mode);

}



