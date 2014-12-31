/* �w�b�_�t�@�C�� */
#include "WindowManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �E�B���h�E
//! @brief �E�B���h�E�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Window
{
    //-------------------------------------------------------------
    //!
    //! @brief �J�����}�l�[�W���[�C���v�������g
    //! @brief �J�����}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_WindowManager::C_WindowManagerImpl
    {
    public:
        C_WindowManagerImpl();                                                              // �R���X�g���N�^
        ~C_WindowManagerImpl();                                                             // �f�X�g���N�^
        void Update();                                                                      // �X�V����
        void Entry(const WindowPtr& prWindow,                                               // �o�^����
                   const std::string& rId);
        void Remove(const std::string& rId);                                                // ��������
        void AllRemove();                                                                   // �S�ẴE�B���h�E������

        /* �Q�b�^�[ */
        boost::optional<const WindowPtr&> GetWindow(const std::string& rId) const;          // �E�B���h�E���擾
    private:
        std::unordered_map<std::string, WindowPtr> pWindows;                                ///< @brief �E�B���h�E
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_WindowManager::C_WindowManagerImpl::C_WindowManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_WindowManager::C_WindowManagerImpl::~C_WindowManagerImpl()
    {
        if (pWindows.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �E�B���h�E
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::Entry(const WindowPtr& prWindow,
                                                     const std::string& rId)
    {
        if (pWindows.find(rId) != pWindows.end())
        {
            std::cout << "[ C_WindowManagerImpl::Entry ] : �E�B���h�E�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                            ID : " << rId << std::endl;

            return;
        }

        pWindows.emplace(rId, prWindow);
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::Remove(const std::string& rId)
    {
        if (pWindows.find(rId) == pWindows.end())
        {
            std::cout << "[ C_WindowManagerImpl::Remove ] : �E�B���h�E��o�^���Ă��܂���B" << std::endl;
            std::cout << "                             ID : " << rId << std::endl;

            return;
        }

        pWindows.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ă̏����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::AllRemove()
    {
        pWindows.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E���擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�E�B���h�E
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const WindowPtr&> C_WindowManager::C_WindowManagerImpl::GetWindow(const std::string& rId) const
    {
        auto iterator = pWindows.find(rId);
        if (iterator == pWindows.end()) return boost::none;

        return (*iterator).second;
    }
}