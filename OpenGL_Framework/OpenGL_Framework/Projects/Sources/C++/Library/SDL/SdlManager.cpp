/* �w�b�_�t�@�C�� */
#include "SdlManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include <SDL.h>


//-------------------------------------------------------------
//!
//! @brief SDL
//! @brief SDL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace SDL
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SdlManager::C_SdlManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SdlManager::~C_SdlManager()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SdlManager::Initialize()
    {
        const int32_t ERROR_VALUE = -1;

        // SDL�̏���������
        if (::SDL_Init(SDL_INIT_EVERYTHING) == ERROR_VALUE)
        {
            PrintLog("[ C_SdlManager::Initialize ] : SDL�̏������Ɏ��s���܂����B\n");
            PrintLog("                  �G���[���e : %s\n", ::SDL_GetError());

            return false;
        }
        
        finalizeFlag_ = false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SdlManager::Finalize()
    {
        ::SDL_Quit();
        finalizeFlag_ = true;
    }
}