/* �w�b�_�t�@�C�� */
#include "FontManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include "../Common/CommonHelper.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �t�H���g
//! @brief �t�H���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Font
{
    //-------------------------------------------------------------
    //!
    //! @brief �t�H���g�}�l�[�W���[�C���v�������g
    //! @brief �t�H���g�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_FontManager::C_FontManagerImpl
    {
    public:
        C_FontManagerImpl();                                                                        // �R���X�g���N�^
        ~C_FontManagerImpl();                                                                       // �f�X�g���N�^
        void Finalize();                                                                            // �I������
        bool Load(const std::string& rFilePath, int32_t size);                                      // ���[�h����
        void Release(const std::string& rFilePath, int32_t size);                                   // �������
        void AllRelease();                                                                          // �S�ĉ��
        boost::optional<const FontPtr&> GetFont(const std::string& rFilePath, int32_t size);        // �t�H���g���擾
        void SetFinalizeFlag(bool finalizeFlag);                                                    // �I���������s���������f����t���O��ݒ�
    private:
        std::unordered_map<std::string, FontPtr> pFonts_;                                           ///< @brief �t�H���g
        bool finalizeFlag_ = false;                                                                 ///< @brief �I���������s���������f����t���O
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FontManager::C_FontManagerImpl::C_FontManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FontManager::C_FontManagerImpl::~C_FontManagerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::Finalize()
    {
        // �t�H���g��S�ĉ��
        AllRelease();

        // �t�H���g�̏I������
        ::TTF_Quit();
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
    bool C_FontManager::C_FontManagerImpl::Load(const std::string& rFilePath, int32_t size)
    {
        // ID
        const std::string ID = rFilePath + std::to_string(size);

        // ���Ƀ��[�h���Ă���ꍇ
        if (pFonts_.find(ID) != pFonts_.end())
        {
            std::cout << "[ C_FontManagerImpl::Load ] : ���ɓ����t�H���g�����[�h���Ă��܂��B" << std::endl;
            std::cout << "               �t�@�C���p�X : " << rFilePath << std::endl;

            return true;
        }

        // �t�H���g�����[�h
        FontPtr pTempFont(::TTF_OpenFont(Common::C_CommonHelper::s_ConvertShiftJisToUtf8(rFilePath).c_str(), size),
                          [](Font* pFont){ ::TTF_CloseFont(pFont); });

        if (!pTempFont)
        {
            PrintLog("[ C_FontManagerImpl::TextureCreate ] : �t�H���g�̃��[�h�Ɏ��s���܂����B\n");
            PrintLog("                        �t�@�C���p�X : %s\n", rFilePath.c_str());
            PrintLog("                          �G���[���e : %s\n", TTF_GetError());

            return false;
        }

        // ���[�h�����t�H���g��ێ�����
        pFonts_.emplace(ID, pTempFont);

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
    void C_FontManager::C_FontManagerImpl::Release(const std::string& rFilePath, int32_t size)
    {
        // ID
        const std::string ID = rFilePath + std::to_string(size);

        // �t�H���g�����[�h����Ă��Ȃ��ꍇ
        if (pFonts_.find(ID) == pFonts_.end())
        {
            std::cout << "[ C_FontManager::Release ] : �t�H���g�����[�h����Ă��܂���B" << std::endl;

            return;
        }

        // �v�f���폜
        pFonts_.erase(ID);
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g��S�ĉ������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::AllRelease()
    {
        pFonts_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �t�H���g���擾����
     *  @param  �t�@�C���p�X
     *  @param  �T�C�Y
     *  @return �t�H���g
     *
     ****************************************************************/
    boost::optional<const FontPtr&> C_FontManager::C_FontManagerImpl::GetFont(const std::string& rFilePath, int32_t size)
    {
        const std::string ID = rFilePath + std::to_string(size);

        auto iterator = pFonts_.find(ID);
        if (iterator == pFonts_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s���������f����t���O��ݒ�
     *  @param  �I���������s���������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::SetFinalizeFlag(bool finalizeFlag)
    {
        finalizeFlag_ = finalizeFlag;
    }
}