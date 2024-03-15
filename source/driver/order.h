#pragma once
#include "elevio.h"


int array_orders[N_FLOORS][N_BUTTONS]; //array med etaje X knapp

int current_floor_int; //FUNKER FJELL

void initial_array(); //fyller matrisen med nuller

void update_current_floor(); //skal kjøres i while(1) i main for å kontinuerlig oppdatere current_floor-- FUNKER FJELL

void order_update(); //opddaterer kø; sjekker om knappen trykkes, setter på lyset til request-knappen , oppdater plassen i matrisen

int new_order(); //funksjon som henter opp neste bestilling i matrisen 

void help_delete(ButtonType button); //setter ordre som er ferdig tilbake til 0, skrur av lyset i knappen

void floor_reached(); //skrur av lyset i etasjen og sletter orderene i etasjen fra matrisen 

void delete_all_orders(); //brukes i stop, sletter alle ordre i matrise og slukker lyset i knappene

void current_floor_light(); //setter lyset på etasje indikatoren-FUNKER
















   