#pragma once

#include"DxLib.h"

const int WIDTH = 720;
const int HEIGHT = 480;

//マクロ類
#define SAFE_DELETE( x ) { delete ( x ); ( x ) = 0; }
#define SAFE_DELETE_ARRAY( x ) { delete[] ( x ); ( x ) = 0; }

//デバグとリリースで分岐するもの
