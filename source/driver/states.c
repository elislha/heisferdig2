#include "elevio.h"
#include "order.h"
#include "states.h" 
#include <stdio.h>
#include "timer.h"


State BASE_execute(){
    printf("BASE BASE BASE BASE BASE BASE BASE BASE! \n");


    if(elevio_stopButton()){ 
            return STOP;
        }
    
    if(new_order()==10){ //returnerer til BASE om alt i matrisen er 0(dvs ingen bestillinger)
        return BASE;
    }
    else if(new_order()!=10){
        return MOVE; //(dersom det er ordre, ta deg av ordren i MOVE
    } 
    return BASE;

};

State MOVE_execute(){ 

    int next_floor=new_order();

    if (next_floor<0 || next_floor>3){//sikrer at vi ikke går utenfor definerte etasjer
        printf("INVALID FLOOR!!!");
        return STOP;
    }
  
    while(current_floor_int != next_floor){ 
            order_update();
            current_floor_light();
            update_current_floor(); 

            if(elevio_stopButton()){ 
                return STOP;
            }

            
            if(current_floor_int>next_floor){ //står i en høyere etasje enn den neste orderen
                printf("Heisen går ned \n");
                printf("NEXT_FLOOR ER : %d \n", next_floor);

                elevio_motorDirection(DIRN_DOWN);  
                
            }
            else if(current_floor_int<next_floor){ //står i etasje lavere enn neste ordre
                printf("Heisen går opp \n");
                printf("NEXT_FLOOR ER : %d \n", next_floor);
                elevio_motorDirection(DIRN_UP);
        }
        
    }
    printf("Right floor reached, a new order will begin \n");
    floor_reached();

    return REACHED; 

    };
    



State REACHED_execute(){ 
    printf("REACHED REACHED REACHED REACHED REACHED REACHED REACHED REACHED \n");

    if(elevio_stopButton()){ 
        return STOP;
    }

    elevio_motorDirection(DIRN_STOP);
    start_timer();
    while(!end_timer()){ //så lenge end_timer returerer null
        elevio_motorDirection(DIRN_STOP);
        elevio_doorOpenLamp(1);
        order_update();
    }
    

    int check_obstruction=0;

    while(elevio_obstruction()){ //sjekker om obstruksjonsbryter er høy, åpner døra
        printf("OBSTRUCTION");
        check_obstruction=1;
        elevio_motorDirection(DIRN_STOP);
        elevio_doorOpenLamp(1);
        order_update();   
    }

    start_timer();
    if(check_obstruction==1){ //lukker døren og fortsetter 3sek etter obstruksjon går lav
        while(!end_timer()){
            elevio_motorDirection(DIRN_STOP);
            order_update();
            check_obstruction=0;
        }
        printf("OBSTRUCTION ENDED");
    }
    

    elevio_doorOpenLamp(0);

    return BASE;
   
};

State STOP_execute(){
    
    printf("STOP STOP STOP STOP\n");

    while(elevio_stopButton()){
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        delete_all_orders();

        if(elevio_floorSensor()!=-1){
            elevio_doorOpenLamp(1);
        }
    }
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);

    if(elevio_floorSensor()!=-1){
        start_timer();
        while(!end_timer()){
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
            order_update();
        }

        elevio_doorOpenLamp(0);
        return BASE;  
    }

    
    return BASE;

};

void set_to_BASE(){

    delete_all_orders();

    while(elevio_floorSensor() ==-1){ //fikser start condition
         elevio_motorDirection(DIRN_DOWN);
     }
     elevio_motorDirection(DIRN_STOP);

};