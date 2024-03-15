#pragma once

typedef enum State
{
    BASE,
    MOVE,
    REACHED,
    STOP
} State;

State BASE_execute();

State MOVE_execute();

State REACHED_execute();

State STOP_execute();

void set_to_BASE();

