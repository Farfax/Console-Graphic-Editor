#pragma once
#pragma warning(disable:4996)

// Menu Location Settings Default 7 17
#define MENU_COLOR LIGHTGRAY
#define LEGEND_SIZE 17

#define DEFAULT_CURSOR_COLOR LIGHTGRAY

// Function Legend Default 2 1
#define LEGEND_POS Vector2i_t(2,1)

// KeyCode Info Default 55 2
#define KEYCODE_POS Vector2i_t(55,2)

// FileName Info Default 55 4
#define FILE_NAME_POS Vector2i_t(55,4)

// Current Mode Info Default 2 16
#define INFO_MODE_POS Vector2i_t(2,17)

// Cursor PosX Info  Default 2 17
#define CURSOR_INFO_POSX Vector2i_t(2,18)

// Cursor PosY Info  Default 7 17 (Care with PosX, optional: behave PosY-PosX>=5)
#define CURSOR_INFO_POSY Vector2i_t(7,18)

// Undo Status Info Default 2 18
#define UNDO_STATUS_POS Vector2i_t(2,19)

//ImageDimension Location Settings Default 3 20 Care with it. Default_Cursor_Pos MUST BE in Dimension Rectangle
#define DIMENSION_LOCATION_POS Vector2i_t(5,26)

//Cursor Begin Status ACHTUNG, Cursor should be inside ImageDimension (Best Option: Take Image Dimension and add 1) Default 4 21
#define DEFAULT_CURSOR_POS Vector2i_t(6,27)

// Clipboard Past status Position Default 2 19
#define CAN_PAST_POS Vector2i_t(2, 20)

// Clipboard Size status Position Default 2 20
#define CLIPBOARD_SIZE_POS Vector2i_t(2, 21)

//  Clipboard Empty Status Position Default 2 21
#define EMPTY_CLIPBOARD_POS Vector2i_t(2, 22)

// Input Box Pos
#define INPUT_NFO_POS Vector2i_t(10, 48)
#define INPUT_BOX_POS Vector2i_t(32, 48)

// FileMarks On/Off

#define MARKS_IS_ON true

// Own Extension Settings Default 4 .xDD
#define EXTENSION_SIZE 4
#define OWN_EXTENSION ".xDD"

#define XPM_EXT "! XPM2"
#define XPM_COLORS_COUNT " 16 "
#define XPM_CHAR_PER_FILE "1 "


//Keybard KeyCodes

#define A 0x41
#define Z 0x5a
#define FROM_A_TO_Z 0x20
#define ESCAPE 0x1B // Run Fool Run!
#define BACKSPACE 0x8
#define SPACE ' '
#define ENTER 0x0d

//Arrows without ctrl and alt

#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

//Arrows with Ctrl

#define CTRL_UP 0x8d
#define CTRL_DOWN 0x91
#define CTRL_LEFT 0x74
#define CTRL_RIGHT 0x73

// Arrows with Alt

#define ALT_UP 0x98
#define ALT_DOWN 0xa0
#define ALT_LEFT 0x9b
#define ALT_RIGHT 0x9d

//SecureMode

#define SECURE_MODE_ON true	/// If false, Let User Draw on outside Dimension, Caution if False Scrollbars may don't work propely
#define FULL_COLOR_MODE_ON true // If false, Draw Color from colorfull '*'