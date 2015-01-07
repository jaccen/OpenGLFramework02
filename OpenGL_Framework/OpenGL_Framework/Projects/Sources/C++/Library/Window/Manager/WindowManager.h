/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../Window//BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief �E�B���h�E
//! @brief �E�B���h�E�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Window
{
    /* �ʖ� */
    using WindowPtr = std::shared_ptr<C_BaseWindow>;                                                            // WindowPtr�^


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pMAIN_WINDOW = "MainWindow";                                                          ///< @brief ���C���E�B���h�E
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �E�B���h�E�}�l�[�W���[
    //! @brief �E�B���h�E���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_WindowManager : public Singleton::C_Singleton<C_WindowManager>
    {
        friend C_Singleton<C_WindowManager>;                                                                    // �V���O���g���N���X���t�����h��
    public:
        C_WindowManager();                                                                                      // �R���X�g���N�^
        ~C_WindowManager() override;                                                                            // �f�X�g���N�^
        void Entry(const WindowPtr& prWindow,                                                                   // �o�^����
                   const std::string& rId = ID::s_pMAIN_WINDOW);
        void Remove(const std::string& rId = ID::s_pMAIN_WINDOW);                                               // ��������
        void AllRemove();                                                                                       // �S�ẴE�B���h�E������
        boost::optional<const WindowPtr&> GetWindow(const std::string& rId = ID::s_pMAIN_WINDOW) const;         // �E�B���h�E���擾
    private:
        /* �O���錾 */
        class C_WindowManagerImpl;

        std::unique_ptr<C_WindowManagerImpl> upImpl_;                                                           ///< @brief �������
    };
}