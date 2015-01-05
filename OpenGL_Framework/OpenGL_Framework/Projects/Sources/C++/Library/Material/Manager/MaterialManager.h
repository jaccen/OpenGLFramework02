/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../Material/Material.h"


//-------------------------------------------------------------
//!
//! @brief �}�e���A��
//! @brief �}�e���A���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief �}�e���A���}�l�[�W���[
    //! @brief �}�e���A�����Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_MaterialManager : public Singleton::C_Singleton<C_MaterialManager>
    {
        friend C_Singleton<C_MaterialManager>;
    public:
        void Entry(const MaterialPtr& prMaterial, const std::string& rId);                  // �o�^����
        void Remove(const std::string& rId);                                                // ��������
        void AllRemove();                                                                   // �S�Ẵ}�e���A��������
        boost::optional<const MaterialPtr&> GetMaterial(const std::string& rId) const;      // �}�e���A�����擾
    private:
        /* �O���錾 */
        class C_MaterialManagerImpl;

        std::unique_ptr<C_MaterialManagerImpl> upImpl_;                                     ///< @brief �������

        C_MaterialManager();                                                                // �R���X�g���N�^
        ~C_MaterialManager() override;                                                      // �f�X�g���N�^
    };
}