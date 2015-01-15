/* �w�b�_�t�@�C�� */
#include "JsonObjectManager.h"
#include <unordered_map>


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON�֘A�̃N���X��֐��Ȃǂɕt���閼�O���
///
//-------------------------------------------------------------
namespace JSON
{
    //-------------------------------------------------------------
    //!
    //! @brief JSON�I�u�W�F�N�g�}�l�[�W���[�C���v�������g
    //! @brief JSON�I�u�W�F�N�g�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_JsonObjectManager::C_JsonObjectManagerImpl
    {
    public:
        C_JsonObjectManagerImpl();                                                                  // �R���X�g���N�^
        ~C_JsonObjectManagerImpl();                                                                 // �f�X�g���N�^
        void Entry(const JsonObjectPtr& prJsonObject, const std::string& rId);                      // �o�^����
        void Remove(const std::string& rId);                                                        // ��������
        void AllRemove();                                                                           // �S�Ă�JSON�I�u�W�F�N�g������
        boost::optional<const JsonObjectPtr&> GetJsonObject(const std::string& rId) const;          // JSON�I�u�W�F�N�g���擾
    private:
        std::unordered_map<std::string, JsonObjectPtr> pJsonObjects_;                                ///< @brief JSON�I�u�W�F�N�g
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManagerImpl::C_JsonObjectManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManagerImpl::~C_JsonObjectManagerImpl()
    {
        if (pJsonObjects_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g�̓o�^���s��
     *  @param  JSON�I�u�W�F�N�g
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::Entry(const JsonObjectPtr& prJsonObject, const std::string& rId)
    {
        // JSON�I�u�W�F�N�g�����ɓo�^����Ă���ꍇ
        if (pJsonObjects_.find(rId) != pJsonObjects_.end())
        {
            std::cout << "[ C_JsonObjectManagerImpl::Entry ] : JSON�I�u�W�F�N�g�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                                ID : " << rId << std::endl;

            return;
        }

        pJsonObjects_.emplace(rId, prJsonObject);
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::Remove(const std::string& rId)
    {
        // JSON�I�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ
        if (pJsonObjects_.find(rId) == pJsonObjects_.end())
        {
            std::cout << "[ C_JsonObjectManagerImpl::Remove ] : JSON�I�u�W�F�N�g��o�^���Ă��܂���B" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        pJsonObjects_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ă�JSON�I�u�W�F�N�g�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::AllRemove()
    {
        pJsonObjects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g���擾����
     *  @param  ID
     *  @return �o�^����Ă����ꍇ    �FJSON�I�u�W�F�N�g
     *  @return �o�^����ĂȂ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const JsonObjectPtr&> C_JsonObjectManager::C_JsonObjectManagerImpl::GetJsonObject(const std::string& rId) const
    {
        auto iterator = pJsonObjects_.find(rId);
        if (iterator == pJsonObjects_.end()) return boost::none;

        return (*iterator).second;
    }
}