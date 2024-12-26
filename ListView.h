// ListView.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Resource.h"

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "..\Classes\ArgumentListClass.h"
#include "..\Classes\DroppedFilesClass.h"
#include "..\Classes\FontClass.h"
#include "..\Classes\ListViewWindowClass.h"
#include "..\Classes\MessageClass.h"
#include "..\Classes\MenuClass.h"
#include "..\Classes\StatusBarWindowClass.h"
#include "..\Classes\WindowClass.h"
#include "..\Classes\WindowClassClass.h"

#define MAIN_WINDOW_CLASS_NAME													"Main ListView Window Class"

#define MAIN_WINDOW_CLASS_MENU_NAME												MAKEINTRESOURCE( IDR_MAIN_MENU )

#define MAIN_WINDOW_TEXT														"ListView"

#define ABOUT_MESSAGE_TEXT														"ListView\r\n"						\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"December 2024"
