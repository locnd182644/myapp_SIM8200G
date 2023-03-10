/**	@brief define Constants & Prototypes for MQTT Functions.
	@history
		- 2021_07_24: Create.
*/
#ifndef _APP_MQTT_H_
#define _APP_MQTT_H_

#include <EthControl.h>
///////////////////////////////////CONSTANTS///////////////////////////////////

////////////////////////////////////TYPES//////////////////////////////////////

///////////////////////////////////PROTOTYPES//////////////////////////////////////
void mqtt_init(void);
int mqtt_sub(void);
int mqtt_pub(char *buff, int len, char *topic);
#endif
