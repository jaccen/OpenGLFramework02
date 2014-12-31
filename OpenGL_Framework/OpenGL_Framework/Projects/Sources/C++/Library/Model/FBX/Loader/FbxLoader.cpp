/* �w�b�_�t�@�C�� */
#include "FbxLoaderImpl.h"


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
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_FbxLoader::C_FbxLoader() :

            // �������
            upImpl_(std::make_unique<C_FbxLoaderImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_FbxLoader::~C_FbxLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̃��f���̃��[�h�������s��
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::LoadModel(const std::string& rFilePath)
        {
            upImpl_->LoadModel(rFilePath);
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̃A�j���[�V�����̃��[�h�������s��
         *  @param  �t�@�C���p�X
         *  @param  �A�j���[�V�����X�^�b�N�ԍ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::LoadAnimation(const std::string& rFilePath, int32_t animationStackNumber)
        {
            upImpl_->LoadAnimation(rFilePath, animationStackNumber);
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̉���������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::Release()
        {
            upImpl_->Release();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V���̐����擾����
         *  @param  �Ȃ�
         *  @return ���b�V���̐�
         *
         ****************************************************************/
        uint32_t C_FbxLoader::GetMeshCount() const
        {
            return upImpl_->GetMeshCount();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V�����擾����
         *  @param  �C���f�b�N�X
         *  @return ���b�V��
         *
         ****************************************************************/
        const S_Mesh& C_FbxLoader::GetMesh(uint32_t index) const
        {
            return upImpl_->GetMesh(index);
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A���̐����擾����
         *  @param  �Ȃ�
         *  @return �}�e���A���̐�
         *
         ****************************************************************/
        uint32_t C_FbxLoader::GetMaterialCount() const
        {
            return upImpl_->GetMaterialCount();
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A����ID���擾����
         *  @param  �}�e���A����
         *  @return �}�e���A����ID
         *
         ****************************************************************/
        int32_t C_FbxLoader::GetMaterialId(const std::string& rName) const
        {
            return upImpl_->GetMaterialId(rName);
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�����擾����
         *  @param  �}�e���A����ID
         *  @return �}�e���A��
         *
         ****************************************************************/
        const S_Material& C_FbxLoader::GetMaterial(int32_t materialId) const
        {
            return upImpl_->GetMaterial(materialId);
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����̊J�n�t���[�������擾����
         *  @param  �Ȃ�
         *  @return �A�j���[�V�����̊J�n�t���[����
         *
         ****************************************************************/
        int64_t C_FbxLoader::GetAnimationStartFrame() const
        {
            return upImpl_->GetAnimationStartFrame();
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����̏I���t���[�������擾����
         *  @param  �Ȃ�
         *  @return �A�j���[�V�����̏I���t���[����
         *
         ****************************************************************/
        int64_t C_FbxLoader::GetAnimationEndFrame() const
        {
            return upImpl_->GetAnimationEndFrame();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V���̍s����擾����
         *  @param  �t���[����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @param  ���b�V���̍s��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const
        {
            upImpl_->GetMeshMatrix(frame, meshIndex, pMeshMatrix);
        }


        /*************************************************************//**
         *
         *  @brief  �{�[���̍s����擾����
         *  @param  �t���[����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @param  �{�[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::GetBoneMatrix(int64_t frame,
                                        uint32_t meshIndex,
                                        Matrix4x4* pBoneMatrixList,
                                        int32_t maxBoneMatrixCount) const
        {
            upImpl_->GetBoneMatrix(frame, meshIndex, pBoneMatrixList, maxBoneMatrixCount);
        }
    }
}