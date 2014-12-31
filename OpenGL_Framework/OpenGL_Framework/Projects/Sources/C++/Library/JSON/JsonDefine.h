/* ��d�C���N���[�h�h�~ */
#pragma once


#include <memory>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <deque>
#include <unordered_map>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <tuple>
#include <memory>
#include <ostream>
#include <iomanip>


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON�֘A�̃N���X��֐��Ȃǂɕt���閼�O���
///
//-------------------------------------------------------------
namespace JSON
{
    /** �f�[�^�̎�� */
    enum class ecDataType
    {
		TYPE_INTEGER,                   ///< @brief ����
		TYPE_REAL,                      ///< @brief ����
		TYPE_BOOLEAN,                   ///< @brief bool�l
		TYPE_STRING,                    ///< @brief ������
		TYPE_ARRAY,                     ///< @brief �z��
		TYPE_OBJECT,                    ///< @brief �I�u�W�F�N�g( �A�z�z�� )
		TYPE_NULL,                      ///< @brief null�l
	};

    //-------------------------------------------------------------
    //!
    //! @brief �f�t�H���g�A���b�N
    //! @brief �f�t�H���g�̃��������蓖�č\����
    //!
    //-------------------------------------------------------------
    struct S_DefaultAlloc
    {
        /*************************************************************//**
         *
         *  @brief  �֐��Ăяo�����Z�q�̃I�[�o�[���[�h
         *  @param  �������̃T�C�Y
         *
         ****************************************************************/
        void* operator()(std::size_t size)
        {
            return Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
        }
    };

    //-------------------------------------------------------------
    //!
    //! @brief �f�t�H���g�t���[
    //! @brief �f�t�H���g�̃���������\����
    //!
    //-------------------------------------------------------------
    struct S_DefaultFree
    {
        /*************************************************************//**
         *
         *  @brief  �֐��Ăяo�����Z�q�̃I�[�o�[���[�h
         *  @param  ������郁�����̃|�C���^
         *
         ****************************************************************/
        void operator()(void* pDeletePointer)
        {
            Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
        }
    };
}