/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../Light/Light.h"


//-------------------------------------------------------------
//!
//! @brief ���C�g
//! @brief ���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief ���C�g�}�l�[�W���[
    //! @brief ���C�g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_LightManager : public Singleton::C_Singleton<C_LightManager>
    {
        friend C_Singleton<C_LightManager>;
    public:
        void Entry(const LightPtr& prLight, const std::string& rId);                    // �o�^����
        void Remove(const std::string& rId);                                            // ��������
        void AllRemove();                                                               // �S�Ẵ��C�g������
        boost::optional<const LightPtr&> GetLight(const std::string& rId) const;        // ���C�g���擾
    private:
        /* �O���錾 */
        class C_LightManagerImpl;

        std::unique_ptr<C_LightManagerImpl> upImpl_;                                    ///< @brief �������

        C_LightManager();                                                               // �R���X�g���N�^
        ~C_LightManager() override;                                                     // �f�X�g���N�^
    };
}