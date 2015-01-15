/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../ModelLoader.h"
#include "../../../../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        //-------------------------------------------------------------
        //!
        //! @brief ���f�����[�_�[�}�l�[�W���[
        //! @brief ���f�����[�_�[���Ǘ�����N���X
        //!
        //-------------------------------------------------------------
        class C_ModelLoaderManager : public Singleton::C_Singleton<C_ModelLoaderManager>
        {
            friend C_Singleton<C_ModelLoaderManager>;
        public:
            void Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId);                // �o�^����
            void Remove(const std::string& rId);                                                    // ��������
            void AllRemove();                                                                       // �S�Ẵ��f�����[�_�[������
            boost::optional<const ModelLoaderPtr&> GetModelLoader(const std::string& rId) const;    // ���f�����[�_�[���擾
        private:
            /* �O���錾 */
            class C_ModelLoaderManagerImpl;

            std::unique_ptr<C_ModelLoaderManagerImpl> upImpl_;                                      ///< @brief �������

            C_ModelLoaderManager();                                                                 // �R���X�g���N�^
            ~C_ModelLoaderManager() override;                                                       // �f�X�g���N�^
        };
    }
}