/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../ModelDefine.h"
#include <vector>


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
        /* �O���錾 */
        class C_ModelLoader;


        /* �ʖ� */
        using ModelLoaderPtr = std::shared_ptr<C_ModelLoader>;                                          // ModelLoaderPtr�^


        //-------------------------------------------------------------
        //!
        //! @brief ���f�����[�_�[
        //! @brief ����t�H�[�}�b�g�̃��f���t�@�C���̃��[�h���s���N���X
        //!
        //-------------------------------------------------------------
        class C_ModelLoader
        {
        public:
            C_ModelLoader();                                                                            // �R���X�g���N�^
            virtual ~C_ModelLoader();                                                                   // �f�X�g���N�^
            void LoadModel(const std::string& rModelFilePath);                                          // ���f���̃��[�h����
            void LoadMaterial(const std::string& rMaterialFilePath);                                    // �}�e���A���̃��[�h����
            void LoadAnimation(const std::string& rAnimationFilePath);                                  // �A�j���[�V�����̃��[�h����
            void Release();                                                                             // �������
            uint32_t GetMeshCount() const;                                                              // ���b�V�������擾
            uint32_t GetBoneCount(uint32_t meshIndex) const;                                            // �{�[�������擾
            uint32_t GetMaterialCount() const;                                                          // �}�e���A�������擾
            const S_Mesh& GetMesh(uint32_t index) const;                                                // ���b�V�����擾
            const S_Material& GetMaterial(uint32_t index) const;                                        // �}�e���A�����擾
            uint32_t GetAnimationEndFrame() const;                                                      // �A�j���[�V�����̏I���t���[�������擾
            const Matrix4x4& GetMeshAnimationMatrix(uint32_t frame, uint32_t meshIndex) const;          // ���b�V���̃A�j���[�V�����s����擾
            const Matrix4x4& GetBoneAnimationMatrix(uint32_t frame,                                     // �{�[���̃A�j���[�V�����s����擾
                                                    uint32_t meshIndex,
                                                    uint32_t boneIndex) const;

            static ModelLoaderPtr s_Create();                                                           // ��������
        private:
            std::vector<S_Mesh> meshList_;                                                              ///< @brief ���b�V�����X�g
            std::vector<S_Material> materialList_;                                                      ///< @brief �}�e���A�����X�g
            uint32_t animationEndFrame_ = 0;                                                            ///< @brief �A�j���[�V�����I���t���[����

            void GetModelFromFileData(char* pFileData);                                                 ///< @brief �t�@�C���f�[�^���烂�f�����擾
            void GetMaterialFromFileData(char* pFileData);                                              ///< @brief �t�@�C���f�[�^����}�e���A�����擾
            void GetAnimationFromFileData(char* pFileData);                                             ///< @brief �t�@�C���f�[�^����A�j���[�V�������擾
        };
    }
}