/* �w�b�_�t�@�C�� */
#include "FrameBufferMamager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    //-------------------------------------------------------------
    //!
    //! @brief �t���[���o�b�t�@�C���v�������g
    //! @brief �t���[���o�b�t�@�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_FrameBufferManager::C_FrameBufferManagerImpl
    {
    public:
        C_FrameBufferManagerImpl();                                                                         // �R���X�g���N�^
        ~C_FrameBufferManagerImpl();                                                                        // �f�X�g���N�^
        void Entry(const FrameBufferPtr& prUniformBuffer, const std::string& rId);                          // �o�^����
        void Remove(const std::string& rId);                                                                // ��������
        void AllRemove();                                                                                   // �S�Ẵt���[���o�b�t�@������
        boost::optional<const FrameBufferPtr&> GetFrameBuffer(const std::string& rId) const;                // �t���[���o�b�t�@���擾
    private:
        std::unordered_map<std::string, FrameBufferPtr> pFrameBuffers_;                                     ///< @brief �t���[���o�b�t�@
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManagerImpl::C_FrameBufferManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManagerImpl::~C_FrameBufferManagerImpl()
    {
        if (pFrameBuffers_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@�̓o�^���s��
     *  @param  �t���[���o�b�t�@
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId)
    {
        if (pFrameBuffers_.find(rId) != pFrameBuffers_.end())
        {
            std::cout << "[ C_FrameBufferManagerImpl::Entry ] : �t���[���o�b�t�@�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        pFrameBuffers_.emplace(rId, prFrameBuffer);
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::Remove(const std::string& rId)
    {
        // �t���[���o�b�t�@���o�^����Ă��Ȃ��ꍇ
        if (pFrameBuffers_.find(rId) == pFrameBuffers_.end())
        {
            std::cout << "[ C_FrameBufferManagerImpl::Remove ] : �t���[���o�b�t�@��o�^���Ă��܂���B" << std::endl;
            std::cout << "                                  ID : " << rId << std::endl;

            return;
        }

        pFrameBuffers_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵt���[���o�b�t�@�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::AllRemove()
    {
        pFrameBuffers_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@���擾����
     *  @param  ID
     *  @return �o�^����Ă����ꍇ    �F�t���[���o�b�t�@
     *  @return �o�^����ĂȂ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const FrameBufferPtr&> C_FrameBufferManager::C_FrameBufferManagerImpl::GetFrameBuffer(const std::string& rId) const
    {
        auto iterator = pFrameBuffers_.find(rId);
        if (iterator == pFrameBuffers_.end()) return boost::none;

        return (*iterator).second;
    }
}