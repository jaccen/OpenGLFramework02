/* �w�b�_�t�@�C�� */
#include "ModelLoader.h"
#include "../../../Common/CommonHelper.h"
#include <fstream>


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
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoader::C_ModelLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoader::~C_ModelLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���f���̃��[�h�������s��
         *  @param  ���f���t�@�C���̃p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::LoadModel(const std::string& rModelFilePath)
        {
            std::ifstream inFile(rModelFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadModel ] : ���̓t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // �t�@�C���T�C�Y���擾
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // �t�@�C���f�[�^�̃��������m�ۂ��A�t�@�C������f�[�^��S�ēǂݍ���
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // �t�@�C���f�[�^���烂�f�����擾
            GetModelFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A���̃��[�h�������s��
         *  @param  �}�e���A���t�@�C���̃p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::LoadMaterial(const std::string& rMaterialFilePath)
        {
            std::ifstream inFile(rMaterialFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadMaterial ] : ���̓t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // �t�@�C���T�C�Y���擾
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // �t�@�C���f�[�^�̃��������m�ۂ��A�t�@�C������f�[�^��S�ēǂݍ���
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // �}�e���A�����t�@�C���f�[�^����擾
            GetMaterialFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����̃��[�h�������s��
         *  @param  �A�j���[�V�����t�@�C���̃p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::LoadAnimation(const std::string& rAnimationFilePath)
        {
            std::ifstream inFile(rAnimationFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadMaterial ] : ���̓t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // �t�@�C���T�C�Y���擾
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // �t�@�C���f�[�^�̃��������m�ۂ��A�t�@�C������f�[�^��S�ēǂݍ���
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // �A�j���[�V�������t�@�C���f�[�^����擾
            GetAnimationFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  ����������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::Release()
        {
            meshList_.clear();
            materialList_.clear();
            animationEndFrame_ = 0;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V�������擾����
         *  @param  �Ȃ�
         *  @return ���b�V����
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetMeshCount() const
        {
            return meshList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  �{�[�������擾����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @return �{�[����
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetBoneCount(uint32_t meshIndex) const
        {
            return meshList_[meshIndex].bones_.size();
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�������擾����
         *  @param  �Ȃ�
         *  @return �}�e���A����
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetMaterialCount() const
        {
            return materialList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V�����擾����
         *  @param  �C���f�b�N�X
         *  @return ���b�V��
         *
         ****************************************************************/
        const S_Mesh& C_ModelLoader::GetMesh(uint32_t index) const
        {
            assert(index < meshList_.size());
            return meshList_[index];
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�����擾����
         *  @param  �C���f�b�N�X
         *  @return �}�e���A��
         *
         ****************************************************************/
        const S_Material& C_ModelLoader::GetMaterial(uint32_t index) const
        {
            assert(index < materialList_.size());
            return materialList_[index];
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����I���t���[�������擾����
         *  @param  �Ȃ�
         *  @return ���b�V�����X�g
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetAnimationEndFrame() const
        {
            return animationEndFrame_;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V���̃A�j���[�V�����s����擾����
         *  @param  �t���[����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @return ���b�V���̃A�j���[�V�����s��
         *
         ****************************************************************/
        const Matrix4x4& C_ModelLoader::GetMeshAnimationMatrix(uint32_t frame, uint32_t meshIndex) const
        {
            return meshList_[meshIndex].eachFrameAnimationMatrices_[frame];
        }


        /*************************************************************//**
         *
         *  @brief  �{�[���̃A�j���[�V�����s����擾����
         *  @param  �t���[����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @param  �{�[���̃C���f�b�N�X
         *  @return �{�[���̃A�j���[�V�����s��
         *
         ****************************************************************/
        const Matrix4x4& C_ModelLoader::GetBoneAnimationMatrix(uint32_t frame,
                                                               uint32_t meshIndex,
                                                               uint32_t boneIndex) const
        {
            return meshList_[meshIndex].bones_[boneIndex].eachFrameAnimationMatrices_[frame];
        }


        /*************************************************************//**
         *
         *  @brief  �t�@�C���f�[�^���烂�f�����擾����
         *  @param  �t�@�C���f�[�^
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::GetModelFromFileData(char* pFileData)
        {
            // �t�@�C���f�[�^�̐擪����̃I�t�Z�b�g
            size_t fileDataOffset = 0;

            // ���b�V�������擾
            uint32_t* pMeshCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // ���b�V�����X�g�̃��������m��
            meshList_.reserve(*pMeshCount);

            for (size_t i = 0; i < *pMeshCount; ++i)
            {
                S_Mesh mesh;

                // ���O�Ɛe�̖��O�ƃ}�e���A�������擾
                mesh.name_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                mesh.parentName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                mesh.materialName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                // ���_���ƃC���f�b�N�X���ƃ{�[�������擾
                uint32_t* pVertexCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                uint32_t* pIndexCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                uint8_t* pBoneWeightCount = reinterpret_cast<uint8_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint8_t);
                assert(*pBoneWeightCount > 0 || *pBoneWeightCount <= 4);

                // ���_�ƃC���f�b�N�X�̃��������m��
                mesh.vertices_.reserve(*pVertexCount);
                mesh.indices_.reserve(*pIndexCount);

                for (size_t j = 0; j < *pVertexCount; ++j)
                {
                    S_Vertex vertex;

                    // ���W���擾
                    for (size_t k = 0; k < 3; ++k)
                    {
                        float* pPositionElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.position_.a_[k] = *pPositionElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �@�����擾
                    for (size_t k = 0; k < 3; ++k)
                    {
                        float* pNormalElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.normal_.a_[k] = *pNormalElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �e�N�X�`�����W���擾
                    for (size_t k = 0; k < 2; ++k)
                    {
                        float* pTextureCoordElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.textureCoord_.a_[k] = *pTextureCoordElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �F���擾
                    for (size_t k = 0; k < 4; ++k)
                    {
                        float* pColorElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.color_.a_[k] = *pColorElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �ڃx�N�g�����擾
                    for (size_t k = 0; k < 4; ++k)
                    {
                        float* pTangentElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.tangent_.a_[k] = *pTangentElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �{�[���E�F�C�g�̃C���f�b�N�X���擾
                    for (size_t k = 0; k < *pBoneWeightCount; ++k)
                    {
                        uint8_t* pBoneWeightIndex = reinterpret_cast<uint8_t*>(pFileData + fileDataOffset);
                        vertex.boneWeights_.indices_[k] = *pBoneWeightIndex;
                        fileDataOffset += sizeof(uint8_t);
                    }

                    // �{�[���E�F�C�g���擾
                    for (size_t k = 0; k < *pBoneWeightCount; ++k)
                    {
                        float* pBoneWeightElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.boneWeights_.weights_.a_[k] = *pBoneWeightElement;
                        fileDataOffset += sizeof(float);
                    }

                    // ���b�V���ɒ��_��������
                    mesh.vertices_.push_back(std::move(vertex));
                }

                for (size_t j = 0; j < *pIndexCount; ++j)
                {
                    // �C���f�b�N�X���擾
                    uint16_t* pIndex = reinterpret_cast<uint16_t*>(pFileData + fileDataOffset);
                    fileDataOffset += sizeof(uint16_t);

                    // ���b�V���ɃC���f�b�N�X��������
                    mesh.indices_.push_back(*pIndex);
                }

                if (meshList_.size() < *pMeshCount)
                {
                    // ���b�V�����X�g�Ƀ��b�V����������
                    meshList_.push_back(std::move(mesh));
                }
                else
                {
                    // �e�f�[�^���R�s�[
                    meshList_[i].name_ = std::move(mesh.name_);
                    meshList_[i].parentName_ = std::move(mesh.parentName_);
                    meshList_[i].materialName_ = std::move(mesh.materialName_);
                    meshList_[i].vertices_ = std::move(mesh.vertices_);
                    meshList_[i].indices_ = std::move(mesh.indices_);
                }
            }
        }


        /*************************************************************//**
         *
         *  @brief  �t�@�C���f�[�^����}�e���A�����擾����
         *  @param  �t�@�C���f�[�^
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::GetMaterialFromFileData(char* pFileData)
        {
            // �t�@�C���f�[�^�̐擪����̃I�t�Z�b�g
            size_t fileDataOffset = 0;

            // �}�e���A�������擾
            uint32_t* pMaterialCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // �}�e���A�����X�g�̃��������m��
            materialList_.reserve(*pMaterialCount);

            for (size_t i = 0; i < *pMaterialCount; ++i)
            {
                S_Material material;

                // �}�e���A�������擾
                material.name_ = pFileData + fileDataOffset;
                fileDataOffset += sizeof(char)* 64;

                // �A���r�G���g���擾
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pAmbientElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.ambient_.a_[j] = *pAmbientElement;
                    fileDataOffset += sizeof(float);
                }

                // �f�B�t���[�Y���擾
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pDiffuseElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.diffuse_.a_[j] = *pDiffuseElement;
                    fileDataOffset += sizeof(float);
                }

                // �X�y�L�������擾
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pSpecularElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.specular_.a_[j] = *pSpecularElement;
                    fileDataOffset += sizeof(float);
                }

                // �G�~�b�V�u���擾
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pEmissiveElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.emissive_.a_[j] = *pEmissiveElement;
                    fileDataOffset += sizeof(float);
                }

                // �V���C�j�l�X�ƃ��t���N�e�B�r�e�B�̎擾
                float* pshininess = reinterpret_cast<float*>(pFileData + fileDataOffset);
                material.shininess_ = *pshininess;
                fileDataOffset += sizeof(float);

                float* pRreflectivity = reinterpret_cast<float*>(pFileData + fileDataOffset);
                material.reflectivity_ = *pRreflectivity;
                fileDataOffset += sizeof(float);

                // �e�e�N�X�`�����擾
                material.ambientTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                material.diffuseTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                material.specularTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                if (materialList_.size() < *pMaterialCount)
                {
                    // �}�e���A�����X�g�Ƀ}�e���A����ǉ�
                    materialList_.push_back(std::move(material));
                }
            }
        }


        /*************************************************************//**
         *
         *  @brief  �t�@�C���f�[�^����A�j���[�V�������擾����
         *  @param  �t�@�C���f�[�^
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoader::GetAnimationFromFileData(char* pFileData)
        {
            // �t�@�C���f�[�^�̐擪����̃I�t�Z�b�g
            size_t fileDataOffset = 0;

            // ���b�V���̐����擾
            uint32_t* pMeshCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // �I���t���[�������擾
            uint32_t* pAnimationEndFrame = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            animationEndFrame_ = *pAnimationEndFrame;
            fileDataOffset += sizeof(uint32_t);

            for (size_t i = 0; i < *pMeshCount; ++i)
            {
                S_Mesh mesh;

                // �{�[�������擾
                uint32_t* pBoneCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                // �{�[���̃��������m��
                mesh.bones_.reserve(*pBoneCount);

                for (size_t j = 0; j < *pBoneCount; ++j)
                {
                    S_Bone bone;

                    // �{�[�����Ɛe�{�[�����擾
                    bone.name_ = (pFileData + fileDataOffset);
                    fileDataOffset += sizeof(char)* 64;

                    bone.parentName_ = (pFileData + fileDataOffset);
                    fileDataOffset += sizeof(char)* 64;

                    // �{�[���̊�{�p���̋t�s����擾
                    for (size_t k = 0; k < 16; ++k)
                    {
                        float* pBoneInverseBaseposeMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        bone.inverseBaseposeMatrix_.a_[k] = *pBoneInverseBaseposeMatrixElement;
                        fileDataOffset += sizeof(float);
                    }

                    // �{�[����ǉ�
                    mesh.bones_.push_back(std::move(bone));
                }

                for (size_t j = 0; j < 16; ++j)
                {
                    // ��{�p���̋t�s����擾
                    float* pInverseBaseposeMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    mesh.inverseBaseposeMatrix_.a_[j] = *pInverseBaseposeMatrixElement;
                    fileDataOffset += sizeof(float);
                }

                // ���b�V���̊e�t�[�����̃A�j���[�V�����s��̃��������m��
                mesh.eachFrameAnimationMatrices_.reserve(*pAnimationEndFrame);

                for (size_t j = 0; j < *pAnimationEndFrame; ++j)
                {
                    for (size_t k = 0; k < *pBoneCount; ++k)
                    {
                        Matrix4x4 boneMatrix;

                        // �{�[���̊e�t�[�����̃A�j���[�V�����s��̃��������m��
                        mesh.bones_[k].eachFrameAnimationMatrices_.reserve(*pAnimationEndFrame);

                        for (size_t l = 0; l < 16; ++l)
                        {
                            // �{�[���s����擾
                            float* pBoneMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                            boneMatrix.a_[l] = *pBoneMatrixElement;
                            fileDataOffset += sizeof(float);
                        }

                        // �{�[���̊e�t�[�����̃A�j���[�V�����s���ǉ�
                        mesh.bones_[k].eachFrameAnimationMatrices_.push_back(boneMatrix);
                    }

                    Matrix4x4 meshMatrix;

                    for (size_t k = 0; k < 16; ++k)
                    {
                        float* pMeshMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        meshMatrix.a_[k] = *pMeshMatrixElement;
                        fileDataOffset += sizeof(float);
                    }

                    // ���b�V���̊e�t�[�����̃A�j���[�V�����s���ǉ�
                    mesh.eachFrameAnimationMatrices_.push_back(meshMatrix);
                }

                if (meshList_.size() < *pMeshCount)
                {
                    // ���b�V���s��̃��X�g�Ƀ��b�V���s���ǉ�
                    meshList_.push_back(std::move(mesh));
                }
                else
                {
                    // �e�f�[�^���R�s�[
                    meshList_[i].inverseBaseposeMatrix_ = mesh.inverseBaseposeMatrix_;
                    meshList_[i].eachFrameAnimationMatrices_ = std::move(mesh.eachFrameAnimationMatrices_);
                    meshList_[i].bones_ = std::move(mesh.bones_);
                }
            }
        }
    }
}