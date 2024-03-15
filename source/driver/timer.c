#include "timer.h"




void start_timer(){
    start=time(NULL);
};

int end_timer(){
    end=start + 3;
    if(time(NULL)>=end){ //hvis en returneres har tiden gått ut, hvis null skal vi fortsatt telle
        return 1;
    }
    else{
        return 0;
    }

};