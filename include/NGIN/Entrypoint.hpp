#pragma once

#ifdef NGIN_DEFINE_MAIN
// Redefine main to avoid conflicts with SDL
#undef main
#define main NGINMain
#endif