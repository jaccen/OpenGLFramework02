/* ��d�C���N���[�h�h�~ */
#pragma once


/* �}�N����` */
#define STRICT                                                          // <Windows.h> ���Ō����Ȍ^�`�F�b�N���s����悤�ɂ���}�N��
#define WIN32_LEAN_AND_MEAN                                             // <Windows.h> ���ŗ]�v�ȃw�b�_�t�@�C����ǂݍ��܂Ȃ�����}�N��


/* C++�֘A�̃w�b�_�t�@�C�� */
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <cassert>


/* OpenGL�֘A�̃w�b�_�t�@�C�� */
#include <GL/glew.h>                                                    // OpenGL�֘A�̃w�b�_���ň�ԍŏ��ǂݍ��ޕK�v����
#include <GL/glu.h>


/* SDL�֘A�̃w�b�_�t�@�C�� */
#include <SDL_opengl.h>                                                 // OpenGL�̗��p�ɍŒ���K�v�ȃw�b�_�t�@�C����ǂݍ���


/* Boost�֘A�̃w�b�_�t�@�C�� */
#include <boost/optional/optional.hpp>


/* Bullet�֘A�̃w�b�_�t�@�C�� */
#include <btBulletCollisionCommon.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>


/* ����̃w�b�_�t�@�C�� */
#include "../../Library/Memory/Manager/MemoryManager.h"