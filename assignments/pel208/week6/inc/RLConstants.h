#pragma once

#ifndef __RL_CONSTANTS__
#define __RL_CONSTANTS__

#include <inc\Utils.h>

#define MAX_ITERATIONS								1000

// a probabilidade padrão de transição
#define DEFAULT_TRANSITION_PROBABILITY				0.25f

// as recompensas
#define DEFAULT_ACTION_REWARD						-1.0f
#define DEFAULT_CORNER_REWARD						-5.0f
#define END_STATE_REWARD							ZERO

#define MAX_EPISODES								UINT_MAX - 1
#define MAX_EPISODE_LEN								256

#define MAX_ALPHA									ONE
#define MIN_ALPHA									ZERO
#define DEFAULT_ALPHA								0.5f

#define MAX_EPSILON									ONE
#define MIN_EPSILON									0.000001f
#define DEFAULT_EPSILON								0.0f

#define MAX_GAMMA									ONE
#define MIN_GAMMA									0.000001f
#define DEFAULT_GAMMA								ONE

#define DEFAULT_THETA								0.000001f

#define DEFAULT_GAMMA								ONE

#define DEFAULT_LAMDA								ONE

#endif /* __RL_CONSTANTS__ */
