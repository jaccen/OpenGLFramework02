/* �w�b�_�t�@�C�� */
#include "PrimitiveBufferManager.h"
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
    //! @brief �v���~�e�B�u�o�b�t�@�C���v�������g
    //! @brief �v���~�e�B�u�o�b�t�@�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl
    {
    public:
        C_PrimitiveBufferManagerImpl();                                                                         // �R���X�g���N�^
        ~C_PrimitiveBufferManagerImpl();                                                                        // �f�X�g���N�^
        void Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId);                        // �o�^����
        void Remove(const std::string& rId);                                                                    // ��������
        void AllRemove();                                                                                       // �S�Ẵv���~�e�B�u�o�b�t�@������
        boost::optional<const PrimitiveBufferPtr&> GetPrimitiveBuffer(const std::string& rId) const;            // �v���~�e�B�u�o�b�t�@���擾
    private:
        std::unordered_map<std::string, PrimitiveBufferPtr> pPrimitiveBuffers_;                                 ///< @brief �v���~�e�B�u�o�b�t�@
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::C_PrimitiveBufferManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::~C_PrimitiveBufferManagerImpl()
    {
        if (pPrimitiveBuffers_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@�̓o�^���s��
     *  @param  �v���~�e�B�u�o�b�t�@
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId)
    {
        // �v���~�e�B�u�o�b�t�@�����ɓo�^����Ă���ꍇ
        if (pPrimitiveBuffers_.find(rId) != pPrimitiveBuffers_.end())
        {
            std::cout << "[ C_PrimitiveBufferManagerImpl::Entry ] : �v���~�e�B�u�o�b�t�@�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                                     ID : " << rId << std::endl;

            return;
        }

        pPrimitiveBuffers_.emplace(rId, prPrimitiveBuffer);
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::Remove(const std::string& rId)
    {
        // �v���~�e�B�u�o�b�t�@���o�^����Ă��Ȃ��ꍇ
        if (pPrimitiveBuffers_.find(rId) == pPrimitiveBuffers_.end())
        {
            std::cout << "[ C_PrimitiveBufferManagerImpl::Remove ] : �v���~�e�B�u�o�b�t�@��o�^���Ă��܂���B" << std::endl;
            std::cout << "                                      ID : " << rId << std::endl;

            return;
        }

        pPrimitiveBuffers_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵv���~�e�B�u�o�b�t�@�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::AllRemove()
    {
        pPrimitiveBuffers_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@���擾����
     *  @param  ID
     *  @return �o�^����Ă����ꍇ    �F�v���~�e�B�u�o�b�t�@
     *  @return �o�^����ĂȂ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const PrimitiveBufferPtr&> C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::GetPrimitiveBuffer(const std::string& rId) const
    {
        auto iterator = pPrimitiveBuffers_.find(rId);
        if (iterator == pPrimitiveBuffers_.end()) return boost::none;

        return (*iterator).second;
    }
}