#include "order.h"
#include "elevio.h"
#include <stdio.h>

//fylle matrisen med null initielt
void initial_array(){
    for(int i=0;i<4; i++){
        for(int j=0; j<3;j++){
            array_orders[i][j]=0;
        }
    }
}


//funksjon som oppdaterer current_floor-variabel. kjøres kontinuerlig i main sin while(1)
void update_current_floor(){
    if(elevio_floorSensor()!=-1){
        //*current_floor_p=elevio_floorSensor(); //peker
        current_floor_int=elevio_floorSensor(); //int
        
    }
    

};


// opddaterer kø; sjekker om knappen trykkes, setter på lyset til request-knappen , oppdater plassen i matrisen, kjøres kontinuerlig i main
void order_update(){
    for( int f=0; f<N_FLOORS; f++){
        for(ButtonType b=BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
            if (elevio_callButton(f,b)==1){
                elevio_buttonLamp(f,b,1);
                array_orders[f][b]=1;
            }
        }

    }
};

//funksjon som henter opp neste bestilling i matrisen 
int new_order(){
    for (int f=N_FLOORS-1; f>=0;f--){
        for(ButtonType b=BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
            if(array_orders[f][b]==1 ){ //sjekker hvilke kanpper som er høye, og som har en bestilling, returnerer hvilke etasje som har bestilling
                return f;
            }

        }

    }
    return 10; 

};



//setter ordre som er ferdig tilbake til 0, skrur av lyset i knappene, brukes ikke
void help_delete(ButtonType button){

    array_orders[current_floor_int][button]=0;
    elevio_buttonLamp(current_floor_int,button,0);

};


void delete_all_orders(){ //brukes i stop, sletter alle ordre i matrise og slukker lyset i knappene

    for(ButtonType b=BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
        for(int f=0; f<4; f++){
            if(array_orders[f][b]==1){
                array_orders[f][b]=0;
                elevio_buttonLamp(f,b,0);
            }
        }
    }
};


void floor_reached(){ //skrur av lyset i etasjen og sletter orderene i etasjen fra matrisen 
    for (ButtonType b=BUTTON_HALL_UP; b<=BUTTON_CAB; b++){
        array_orders[current_floor_int][b]=0;
        elevio_buttonLamp(current_floor_int,b,0);
    }

};





//setter etasjelys- FUNKER SOM EN KULE
void current_floor_light(){
    if(elevio_floorSensor()==0){
        elevio_floorIndicator(0);
    }
    if(elevio_floorSensor()==1){
        elevio_floorIndicator(1);
    }
    if(elevio_floorSensor()==2){
        elevio_floorIndicator(2);
    }
    if(elevio_floorSensor()==3){
        elevio_floorIndicator(3);
    }
};

 

    
