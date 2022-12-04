#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG_ENGINE(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Constants -----------
#define DEGTORAD 0.01745329251f
#define RADTODEG 1.0f / DEGTORAD
#define HIGH_LIMIT 0.006f          // Keep At/Below 144fps
#define LOW_LIMIT 0.1f            // Keep At/Above 10fps

// Configuration -----------
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 800
#define FULLSCREEN false
#define BORDERLESS false
#define RESIZABLE true
#define FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Deus Ex Machina"
#define GLSL_VERSION "#version 440"