/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../FbxDefine.h"


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
    //! @brief FBX
    //! @brief FBX�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace FBX
    {
        //-------------------------------------------------------------
        //!
        //! @brief FBX���[�_�[
        //! @brief FBX�t�@�C���̃��[�h���s���N���X
        //!
        //-------------------------------------------------------------
        class C_FbxLoader
        {
        public:
            C_FbxLoader();                                                                              // �R���X�g���N�^
            ~C_FbxLoader();                                                                             // �f�X�g���N�^
            void LoadModel(const std::string& rFilePath);                                               // ���f���̃��[�h����
            void LoadAnimation(const std::string& rFilePath, int32_t animationStackNumber = 0);         // �A�j���[�V�����̃��[�h����
            void Release();                                                                             // �������
            uint32_t GetMeshCount() const;                                                              // ���b�V�������擾
            const S_Mesh& GetMesh(uint32_t index) const;                                                // ���b�V�����擾
            uint32_t GetMaterialCount() const;                                                          // �}�e���A�������擾
            int32_t GetMaterialId(const std::string& rName) const;                                      // �}�e���A����ID���擾
            const S_Material& GetMaterial(int32_t id) const;                                            // �}�e���A�����擾
            int64_t GetAnimationStartFrame() const;                                                     // �A�j���[�V�����̊J�n�t���[�������擾
            int64_t GetAnimationEndFrame() const;                                                       // �A�j���[�V�����̏I���t���[�������擾
            void GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const;        // ���b�V���̍s����擾
            void GetBoneMatrix(int64_t frame,                                                           // �{�[���̍s����擾
                               uint32_t meshIndex,
                               Matrix4x4* pBoneMatrixList,
                               int32_t maxBoneMatrixCount) const;
        private:
            /* �O���錾 */
            class C_FbxLoaderImpl;

            std::unique_ptr<C_FbxLoaderImpl> upImpl_;                                                   ///< @brief �������
        };
    }
}