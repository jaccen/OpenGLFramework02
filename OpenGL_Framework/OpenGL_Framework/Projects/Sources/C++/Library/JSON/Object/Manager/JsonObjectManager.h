/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Singleton/Singleton.h"
#include "../JsonObject.h"


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
    //! @brief JSON�I�u�W�F�N�g�}�l�[�W���[
    //! @brief JSON�I�u�W�F�N�g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_JsonObjectManager : public Singleton::C_Singleton<C_JsonObjectManager>
    {
        friend C_Singleton<C_JsonObjectManager>;
    public:
        void Entry(const JsonObjectPtr& prLight, const std::string& rId);                       // �o�^����
        void Remove(const std::string& rId);                                                    // ��������
        void AllRemove();                                                                       // �S�Ă�JSON�I�u�W�F�N�g������
        boost::optional<const JsonObjectPtr&> GetJsonObject(const std::string& rId) const;      // JSON�I�u�W�F�N�g���擾
    private:
        /* �O���錾 */
        class C_JsonObjectManagerImpl;

        std::unique_ptr<C_JsonObjectManagerImpl> upImpl_;                                       ///< @brief �������

        C_JsonObjectManager();                                                                  // �R���X�g���N�^
        ~C_JsonObjectManager() override;                                                        // �f�X�g���N�^
    };
}