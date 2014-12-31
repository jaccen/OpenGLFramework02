/* �w�b�_�t�@�C�� */
#include "GlslObjectManager.h"
#include <unordered_map>


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
        //-------------------------------------------------------------
        //!
        //! @brief GLSL�I�u�W�F�N�g�}�l�[�W���[�C���v�������g
        //! @brief GLSL�I�u�W�F�N�g�}�l�[�W���[�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_GlslObjectManager::C_GlslObjectManagerImpl
        {
        public:
            C_GlslObjectManagerImpl();                                                              // �R���X�g���N�^
            ~C_GlslObjectManagerImpl();                                                             // �f�X�g���N�^
            void Entry(const GlslObjectPtr& prGlslObject, const std::string& rId);                  // �o�^����
            void Remove(const std::string& rId);                                                    // ��������
            void AllRemove();                                                                       // �S�Ă�GLSL�I�u�W�F�N�g������
            boost::optional<const GlslObjectPtr&> GetGlslObject(const std::string& rId) const;      // GLSL�I�u�W�F�N�g���擾
        private:
            std::unordered_map<std::string, GlslObjectPtr> prGlslObjects_;                          ///< @brief GLSL�I�u�W�F�N�g
        };


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_GlslObjectManager::C_GlslObjectManagerImpl::C_GlslObjectManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_GlslObjectManager::C_GlslObjectManagerImpl::~C_GlslObjectManagerImpl()
        {
            if (prGlslObjects_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g�̓o�^���s��
         *  @param  GLSL�I�u�W�F�N�g
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::Entry(const GlslObjectPtr& prGlslObject, const std::string& rId)
        {
            // GLSL�I�u�W�F�N�g�����ɓo�^����Ă���ꍇ
            if (prGlslObjects_.find(rId) != prGlslObjects_.end())
            {
                std::cout << "[ C_GlslObjectManagerImpl::Entry ] : GLSL�I�u�W�F�N�g�����ɓo�^����Ă��܂��B" << std::endl;
                std::cout << "                                ID : " << rId << std::endl;

                return;
            }

            prGlslObjects_.emplace(rId, prGlslObject);
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::Remove(const std::string& rId)
        {
            // GLSL�I�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ
            if (prGlslObjects_.find(rId) == prGlslObjects_.end())
            {
                std::cout << "[ C_GlslObjectManagerImpl::Remove ] : GLSL�I�u�W�F�N�g��o�^���Ă��܂���B" << std::endl;
                std::cout << "                                 ID : " << rId << std::endl;

                return;
            }

            prGlslObjects_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�ẴV�F�[�_�[�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::AllRemove()
        {
            prGlslObjects_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g���擾����
         *  @param  ID
         *  @return �o�^����Ă����ꍇ    �FGLSL�I�u�W�F�N�g
         *  @return �o�^����ĂȂ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const GlslObjectPtr&> C_GlslObjectManager::C_GlslObjectManagerImpl::GetGlslObject(const std::string& rId) const
        {
            auto iterator = prGlslObjects_.find(rId);
            if (iterator == prGlslObjects_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}