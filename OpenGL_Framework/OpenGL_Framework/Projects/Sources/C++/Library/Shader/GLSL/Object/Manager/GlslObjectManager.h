/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../../Singleton/Singleton.h"
#include "../GlslObject.h"
#include <boost/optional.hpp>


//-------------------------------------------------------------
//!
//! @brief �V�F�[�_�[
//! @brief �V�F�[�_�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /* �ʖ� */
        using GlslObjectPtr = std::shared_ptr<C_GlslObject>;                                        // GlslObjectPtr�^


        //-------------------------------------------------------------
        //!
        //! @brief GLSL�I�u�W�F�N�g�}�l�[�W���[
        //! @brief GLSL�I�u�W�F�N�g���Ǘ�����N���X
        //!
        //-------------------------------------------------------------
        class C_GlslObjectManager : public Singleton::C_Singleton<C_GlslObjectManager>
        {
            friend C_Singleton<C_GlslObjectManager>;
        public:
            void Entry(const GlslObjectPtr& prGlslObject, const std::string& rId);                  // �o�^����
            void Remove(const std::string& rId);                                                    // ��������
            void AllRemove();                                                                       // �S�Ă�GLSL�I�u�W�F�N�g������
            boost::optional<const GlslObjectPtr&> GetGlslObject(const std::string& rId) const;      // GLSL�I�u�W�F�N�g���擾
        private:
            /* �O���錾 */
            class C_GlslObjectManagerImpl;

            std::unique_ptr<C_GlslObjectManagerImpl> upImpl_;                                       ///< @brief �������

            C_GlslObjectManager();                                                                  // �R���X�g���N�^
            ~C_GlslObjectManager() override;                                                        // �f�X�g���N�^
        };
    }
}
