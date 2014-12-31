/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"
#include <SDL_ttf.h>


//-------------------------------------------------------------
//!
//! @brief �t�H���g
//! @brief �t�H���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Font
{
    /* �ʖ� */
    using Font = TTF_Font;                                                                                  // Font�^
    using FontPtr = std::shared_ptr<Font>;                                                                  // FontPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �t�H���g�}�l�[�W���[
    //! @brief �t�H���g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_FontManager : public Singleton::C_Singleton<C_FontManager>
    {
        friend C_Singleton<C_FontManager>;                                                                  // �V���O���g���N���X���t�����h��
    public:
        bool Initialize();                                                                                  // ����������
        void Finalize();                                                                                    // �I������
        bool Load(const std::string& rFilePath, int32_t size);                                              // ���[�h����
        void Release(const std::string& rFilePath, int32_t size);                                           // �������
        void AllRelease();                                                                                  // �S�ĉ��
        boost::optional<const FontPtr&> GetFont(const std::string& rFilePath, int32_t size) const;          // �t�H���g���擾
    private:
        /* �O���錾 */
        class C_FontManagerImpl;

        std::unique_ptr<C_FontManagerImpl> upImpl_;                                                         ///< @brief �������

        C_FontManager();                                                                                    // �R���X�g���N�^
        ~C_FontManager() override;                                                                          // �f�X�g���N�^
    };
}
