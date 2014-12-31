/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief SDL
//! @brief SDL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace SDL
{
    //-------------------------------------------------------------
    //!
    //! @brief SDL�}�l�[�W���[
    //! @brief SDL���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_SdlManager : public Singleton::C_Singleton<C_SdlManager>
    {
        friend C_Singleton<C_SdlManager>;           // �V���O���g���N���X���t�����h��
    public:
        bool Initialize();                          // ����������
        void Finalize();                            // �I������
    private:
        bool finalizeFlag_ = false;                 ///< @brief �I���������s���������f����t���O 

        C_SdlManager();                             // �R���X�g���N�^
        ~C_SdlManager() override;                   // �f�X�g���N�^
    };
}