/* 二重インクルード防止 */
#pragma once


/* マクロ定義 */
#define STRICT                                                          // <Windows.h> 内で厳密な型チェックが行われるようにするマクロ
#define WIN32_LEAN_AND_MEAN                                             // <Windows.h> 内で余計なヘッダファイルを読み込まなくするマクロ


/* C++関連のヘッダファイル */
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <cassert>


/* OpenGL関連のヘッダファイル */
#include <GL/glew.h>                                                    // OpenGL関連のヘッダ内で一番最初読み込む必要あり
#include <GL/glu.h>


/* SDL関連のヘッダファイル */
#include <SDL_opengl.h>                                                 // OpenGLの利用に最低限必要なヘッダファイルを読み込む


/* Boost関連のヘッダファイル */
#include <boost/optional/optional.hpp>


/* Bullet関連のヘッダファイル */
#include <btBulletCollisionCommon.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>


/* 自作のヘッダファイル */
#include "../../Library/Memory/Manager/MemoryManager.h"