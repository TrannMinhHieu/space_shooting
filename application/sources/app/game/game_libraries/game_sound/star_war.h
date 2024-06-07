// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------
#ifndef __STAR_WAR_H__

#include "pitches.h"
#include "buzzer.h"

int melody[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,

  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6,
  NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
  NOTE_C6
};

int durations[] = {
  8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,

  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 16,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 8, 8, 8, 8,

  8, 16, 2, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 4, 8, 4, 8, 4, 8,
  1
};

static const Tone_TypeDef star_war[] = {
    {NOTE_AS4, 8}, {NOTE_AS4, 8}, {NOTE_AS4, 8},
    {NOTE_F5, 2}, {NOTE_C6, 2},
    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F6, 2}, {NOTE_C6, 4},
    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F6, 2}, {NOTE_C6, 4},
    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_AS5, 8}, {NOTE_G5, 2}, {NOTE_C5, 8}, {NOTE_C5, 8}, {NOTE_C5, 8},
    {NOTE_F5, 2}, {NOTE_C6, 2},
    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F6, 2}, {NOTE_C6, 4},

    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F6, 2}, {NOTE_C6, 4},
    {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_AS5, 8}, {NOTE_G5, 2}, {NOTE_C5, 8}, {NOTE_C5, 16},
    {NOTE_D5, 4}, {NOTE_D5, 8}, {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F5, 8},
    {NOTE_F5, 8}, {NOTE_G5, 8}, {NOTE_A5, 8}, {NOTE_G5, 4}, {NOTE_D5, 8}, {NOTE_E5, 4}, {NOTE_C5, 8}, {NOTE_C5, 16},
    {NOTE_D5, 4}, {NOTE_D5, 8}, {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F5, 8},
    
    {NOTE_C6, 8}, {NOTE_G5, 16}, {NOTE_G5, 2}, {REST, 8}, {NOTE_C5, 8},
    {NOTE_D5, 4}, {NOTE_D5, 8}, {NOTE_AS5, 8}, {NOTE_A5, 8}, {NOTE_G5, 8}, {NOTE_F5, 8},
    {NOTE_F5, 8}, {NOTE_G5, 8}, {NOTE_A5, 8}, {NOTE_G5, 4}, {NOTE_D5, 8}, {NOTE_E5, 4}, {NOTE_C6, 8}, {NOTE_C6, 16},
    {NOTE_F6, 4}, {NOTE_DS6, 8}, {NOTE_CS6, 4}, {NOTE_C6, 8}, {NOTE_AS5, 4}, {NOTE_GS5, 8}, {NOTE_G5, 4}, {NOTE_F5, 8},
    {NOTE_C6, 1}
};
#endif // __STAR_WAR_H__