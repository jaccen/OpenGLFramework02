/* �w�b�_�t�@�C�� */
#include "FontManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �t�H���g
//! @brief �t�H���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Font
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FontManager::C_FontManager() :

        // �������
        upImpl_(std::make_unique<C_FontManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FontManager::~C_FontManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̏������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_FontManager::Initialize()
    {
        const int32_t FONT_INITIALIZE_ERROR_VALUE = -1;

        if (::TTF_Init() == FONT_INITIALIZE_ERROR_VALUE)
        {
            PrintLog("[ C_FontManager::Initialize ] : �t�H���g�̏����������Ɏ��s���܂����B\n");
            PrintLog("                   �G���[���e : %s\n", TTF_GetError());

            return false;
        }

        // �I�������̃t���O��������
        upImpl_->SetFinalizeFlag(false);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::Finalize()
    {
        upImpl_->Finalize();
        upImpl_->SetFinalizeFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̃��[�h���s��
     *  @param  �t�@�C���p�X
     *  @param  �T�C�Y
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_FontManager::Load(const std::string& rFilePath, int32_t size)
    {
        if (upImpl_->Load(rFilePath, size) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̉�����s��
     *  @param  �t�@�C���p�X
     *  @param  �T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::Release(const std::string& rFilePath, int32_t size)
    {
        upImpl_->Release(rFilePath, size);
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::AllRelease()
    {
        upImpl_->AllRelease();
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g���擾����
     *  @param  �t�@�C���p�X
     *  @param  �T�C�Y
     *  @return �t�H���g
     *
     ****************************************************************/
    boost::optional<const FontPtr&> C_FontManager::GetFont(const std::string& rFilePath, int32_t size) const
    {
        return upImpl_->GetFont(rFilePath, size);
    }
}