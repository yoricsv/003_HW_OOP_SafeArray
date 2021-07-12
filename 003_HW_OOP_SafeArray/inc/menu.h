#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <chrono>

#include "safearray.h"

enum PROG_STATE
{
    CREATE_ARRAY,
    AUTO,
    MANUALLY
};
enum ACTION
{
    CHANGE_VALUE = 1,
    SWAP_VALUES,
    PUSH_VALUE_FRONT,
    PUSH_VALUE_AT,
    PUSH_VALUE_INTO,
    PUSH_VALUE_BACK,
    POP_VALUE_FRONT,
    POP_VALUE_AT,
    POP_VALUE_INTO,
    POP_VALUE_BACK,
    GET_SIZE,
    CHECK_EMPTY,
    OUTPUT_FRONT,
    OUTPUT_ITEM,
    OUTPUT_RANGE,
    OUTPUT_ARRAY,
    OUTPUT_BACK,
    WIPE_OUT,
    EXIT = 0
};

int  creation_type ();
void action_type   (SafeArray &obj);

int  set_size      ();

void change_value  (SafeArray &obj);
void swap_items    (SafeArray &obj);

void insert_front  (SafeArray &obj);
void insert_at     (SafeArray &obj);
void insert_into   (SafeArray &obj);
void insert_back   (SafeArray &obj);

void remove_front  (SafeArray &obj);
void remove_at     (SafeArray &obj);
void remove_into   (SafeArray &obj);
void remove_back   (SafeArray &obj);

void get_size      (SafeArray &obj);
void empty_check   (SafeArray &obj);

void display_front (SafeArray &obj);
void display_item  (SafeArray &obj);
void display_range (SafeArray &obj);
void display_all   (SafeArray &obj);
void display_back  (SafeArray &obj);

void erase         (SafeArray &obj);

#endif // MENU_H
