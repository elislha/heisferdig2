#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/order.h"
#include "driver/states.h"


    
int main(){
    elevio_init();


    initial_array();
    set_to_BASE();
    update_current_floor();

    State current_state= BASE;


 while(1){
        
        order_update(); 
        update_current_floor();
        current_floor_light();
        


        switch(current_state){ 
            {
            case BASE :
            {
                current_state= BASE_execute(); 
                
                break;
            }

            case MOVE:
            {
                current_state=MOVE_execute();
                
                break;
            }
            
            case REACHED:
            {
                current_state=REACHED_execute();
                
                break;
            }

            case STOP:
            {
                current_state=STOP_execute();
                break;
            }
        }
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);


     };
     

    return 0;
 }
 
