/* �w�b�_�t�@�C�� */
#include "FbxLoader.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "../../../Common/CommonHelper.h"
#include "../../../Path/PathAnalizer.h"
#include <cstdint>
#include <fbxsdk.h>
#include <algorithm>
#include <unordered_map>
#include <algorithm>
#include <deque>
#include <memory>
#include <cassert>


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
        //! @brief FBX���[�_�[�C���v�������g
        //! @brief FBX���[�_�[�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_FbxLoader::C_FbxLoaderImpl
        {
        public:
            C_FbxLoaderImpl();                                                                          // �R���X�g���N�^
            ~C_FbxLoaderImpl();                                                                         // �f�X�g���N�^
            void LoadModel(const std::string& rFilePath);                                               // ���f���̃��[�h����
            void LoadAnimation(const std::string& rFilePath, int32_t stackNumber);                      // �A�j���[�V�����̃��[�h����
            void Release();                                                                             // �������

            /* �Q�b�^�[ */
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
            /** �}�l�[�W���[�̃f���[�^ */
            struct S_ManagerDeleter
            {
                void operator()(FbxManager* pManager)
                {
                    pManager->Destroy();
                }
            };

            std::unique_ptr<FbxManager, S_ManagerDeleter> upManager_;                                   ///< @brief �}�l�[�W���[
            FbxScene* pModelScene_ = nullptr;                                                           ///< @brief ���f���V�[��
            FbxScene* pAnimationScene_ = nullptr;                                                       ///< @brief �A�j���[�V�����V�[��
            std::unordered_map<std::string, int16_t> modelNodeIdDictionary_;                            ///< @brief ���f���̃m�[�hID�̎���
            std::unordered_map<std::string, int16_t> animationNodeIdDictionary_;                        ///< @brief �A�j���[�V�����̃m�[�hID�̎���
            std::unordered_map<std::string, int16_t> materialIdDictionary_;                             ///< @brief �}�e���A��ID�̎���
            std::vector<S_Mesh> meshList_;                                                              ///< @brief ���b�V�����X�g
            std::vector<S_Material> materialList_;                                                      ///< @brief �}�e���A�����X�g
            int64_t animationStartFrame_ = 0;                                                           ///< @brief �A�j���[�V�����̊J�n�t���[����
            int64_t animationEndFrame_ = 0;                                                             ///< @brief �A�j���[�V�����̏I���t���[��

            S_Mesh ParseMesh(FbxMesh* pFbxMesh);                                                        // ���b�V���̉��
            S_Material ParseMaterial(FbxSurfaceMaterial* pFbxMaterial);                                 // �}�e���A���̉��
            void SetVector3(const FbxDouble3& rFbxDouble,                                               // FbxDouble3����Vector3�ɒl��ݒ�
                            Vector3* pVector) const;
            void SetMatrix4x4(const FbxAMatrix& rFbxMatrix,                                             // FbxAMatrix����Matrix4x4�^��ݒ�
                              Matrix4x4* pMatrix) const;
            std::string GetTextureFileNameFromProperty(const FbxProperty& rProperty);                   // �v���p�e�B����e�N�X�`���t�@�C�������擾
            std::vector<int32_t> GetIndicesFromMesh(FbxMesh* pMesh);                                    // ���b�V������C���f�b�N�X���擾
            std::vector<Vector3> GetPositionsFromMesh(FbxMesh* pMesh,                                   // ���b�V��������W���擾
                                                      const std::vector<int32_t>& rIndices);
            std::vector<Vector3> GetNormalsFromMesh(FbxMesh* pMesh,                                     // ���b�V������@���x�N�g�����擾
                                                    const std::vector<int32_t>& rIndices);
            std::vector<Vector2> GetTextureCoordsFromMesh(FbxMesh* pMesh,                               // ���b�V������e�N�X�`�����W���擾
                                                          const std::vector<int32_t>& rIndices);
            std::vector<Vector4> GetColorsFromMesh(FbxMesh* pMesh,                                      // ���b�V������F���擾
                                                   const std::vector<int32_t>& rIndices);
            void GetBoneDataFromMesh(FbxMesh* pMesh,                                                    // �{�[���̏����擾
                                     const std::vector<int32_t>& rIndices,
                                     std::vector<S_BoneWeight>* pBoneWeights,
                                     std::vector<S_Bone>* pBones);
            void CalculateTangents(S_Mesh* pMesh);                                                      // �ڃx�N�g�����v�Z
        };


        /*************************************************************//**
        *
        *  @brief  �R���X�g���N�^
        *  @param  �Ȃ�
        *
        ****************************************************************/
        C_FbxLoader::C_FbxLoaderImpl::C_FbxLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_FbxLoader::C_FbxLoaderImpl::~C_FbxLoaderImpl()
        {
            if (upManager_) Release();
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̃��f���̃��[�h�������s��
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::LoadModel(const std::string& rFilePath)
        {
            // FBX�}�l�[�W���[���쐬
            upManager_.reset(FbxManager::Create());

            // IO��ݒ�
            FbxIOSettings* pIoSetting = FbxIOSettings::Create(upManager_.get(), IOSROOT);
            upManager_->SetIOSettings(pIoSetting);

            // �C���|�[�^�[���쐬���A������
            auto pImporter = Common::C_CommonHelper::s_MakeCustomUnique(FbxImporter::Create(upManager_.get(), ""),
                [](FbxImporter* pImpoter){ pImpoter->Destroy(); });

            if (pImporter->Initialize(rFilePath.c_str(), -1, upManager_->GetIOSettings()) == false)
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::LoadModel ] :�C���|�[�^�[�̏����������Ɏ��s���܂����B");
            }

            // �V�[�����쐬���A�C���|�[�g
            pModelScene_ = FbxScene::Create(upManager_.get(), "ModelScene");
            pImporter->Import(pModelScene_);

            // �|���S����S�ĎO�p�`��
            FbxGeometryConverter geometryConverter(upManager_.get());
            geometryConverter.Triangulate(pModelScene_, true);

            // �m�[�h�����擾
            int32_t nodeNumber = pModelScene_->GetNodeCount();

            // �m�[�hID�������ɓo�^
            for (int32_t i = 0; i < nodeNumber; ++i)
            {
                FbxNode* pNode = pModelScene_->GetNode(static_cast<int32_t>(i));
                modelNodeIdDictionary_.emplace(pNode->GetName(), i);
            }

            // �}�e���A�������擾
            int32_t materialCount = pModelScene_->GetMaterialCount();
            materialList_.reserve(materialCount);

            // �}�e���A������͂��A�����ƃ��X�g�ɒǉ�
            for (int32_t i = 0; i < materialCount; ++i)
            {
                FbxSurfaceMaterial* pFbxMaterial = pModelScene_->GetMaterial(i);
                S_Material material = ParseMaterial(pFbxMaterial);

                materialIdDictionary_.emplace(material.name_, i);
                materialList_.push_back(std::move(material));
            }

            // ���b�V���̐����擾
            int32_t meshCount = pModelScene_->GetMemberCount<FbxMesh>();
            meshList_.reserve(meshCount);

            // ���b�V������͂��A���X�g�ɒǉ�
            for (int32_t i = 0; i < meshCount; ++i)
            {
                FbxMesh* pFbxMesh = pModelScene_->GetMember<FbxMesh>(i);
                meshList_.push_back(ParseMesh(pFbxMesh));
            }
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̃A�j���[�V�����̃��[�h�������s��
         *  @param  �t�@�C���p�X
         *  @param  �A�j���[�V�����X�^�b�N�ԍ�
         *  @return ����I���Ftrue
         *  @return �ُ�I���Ffalse
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::LoadAnimation(const std::string& rFilePath, int32_t stackNumber)
        {
            // �C���|�[�^�[���쐬���A������
            auto pImporter = Common::C_CommonHelper::s_MakeCustomUnique(FbxImporter::Create(upManager_.get(), ""),
                                                                        [](FbxImporter* pImpoter){ pImpoter->Destroy(); });

            if (pImporter->Initialize(rFilePath.c_str(), -1, upManager_->GetIOSettings()) == false)
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::LoadAnimation ] :�C���|�[�^�[�̏����������Ɏ��s���܂����B");
            }

            // �V�[�����擾
            pAnimationScene_ = FbxScene::Create(upManager_.get(), "AnimationScene");
            pImporter->Import(pAnimationScene_);

            // �A�j���[�V�����؂�ւ�
            auto pAnimationStack = pAnimationScene_->GetSrcObject<fbxsdk_2015_1::FbxAnimStack>(stackNumber);
            pAnimationScene_->SetCurrentAnimationStack(pAnimationStack);

            // �e�C�N�����擾
            FbxTakeInfo* pTakeInfo = pImporter->GetTakeInfo(0);
            auto importOffset = pTakeInfo->mImportOffset;

            // �A�j���[�V�����t���[�������擾
            FbxTime startTime = pTakeInfo->mLocalTimeSpan.GetStart();
            FbxTime stopTime = pTakeInfo->mLocalTimeSpan.GetStop();

            animationStartFrame_ = (importOffset.Get() + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
            animationEndFrame_ = (importOffset.Get() + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);

            // �m�[�h�����擾
            int32_t nodeCount = pAnimationScene_->GetNodeCount();

            // �m�[�hID�������ɓo�^
            for (int32_t i = 0; i < nodeCount; ++i)
            {
                FbxNode* pNode = pAnimationScene_->GetNode(i);
                animationNodeIdDictionary_.emplace(pNode->GetName(), i);
            }
        }


        /*************************************************************//**
         *
         *  @brief  FBX�t�@�C���̉���������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::Release()
        {
            // �}�l�[�W���[��j��
            upManager_.reset();

            // �e���X�g�⎫�����N���A
            meshList_.clear();
            materialList_.clear();
            modelNodeIdDictionary_.clear();
            animationNodeIdDictionary_.clear();
            materialIdDictionary_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V���̐����擾����
         *  @param  �Ȃ�
         *  @return ���b�V���̐�
         *
         ****************************************************************/
        uint32_t C_FbxLoader::C_FbxLoaderImpl::GetMeshCount() const
        {
            return meshList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V�����擾����
         *  @param  �C���f�b�N�X
         *  @return ���b�V��
         *
         ****************************************************************/
        const S_Mesh& C_FbxLoader::C_FbxLoaderImpl::GetMesh(uint32_t index) const
        {
            return meshList_.at(index);
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A���̐����擾����
         *  @param  �Ȃ�
         *  @return �}�e���A���̐�
         *
         ****************************************************************/
        uint32_t C_FbxLoader::C_FbxLoaderImpl::GetMaterialCount() const
        {
            return materialList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A����ID���擾����
         *  @param  �}�e���A����
         *  @return �}�e���A����ID
         *
         ****************************************************************/
        int32_t C_FbxLoader::C_FbxLoaderImpl::GetMaterialId(const std::string& rName) const
        {
            return materialIdDictionary_.at(rName);
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A�����擾����
         *  @param  �}�e���A����ID
         *  @return �}�e���A��
         *
         ****************************************************************/
        const S_Material& C_FbxLoader::C_FbxLoaderImpl::GetMaterial(int32_t id) const
        {
            return materialList_.at(id);
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����̊J�n�t���[�������擾����
         *  @param  �Ȃ�
         *  @return �A�j���[�V�����̊J�n�t���[����
         *
         ****************************************************************/
        int64_t C_FbxLoader::C_FbxLoaderImpl::GetAnimationStartFrame() const
        {
            return animationStartFrame_;
        }


        /*************************************************************//**
         *
         *  @brief  �A�j���[�V�����̏I���t���[�������擾����
         *  @param  �Ȃ�
         *  @return �A�j���[�V�����̏I���t���[����
         *
         ****************************************************************/
        int64_t C_FbxLoader::C_FbxLoaderImpl::GetAnimationEndFrame() const
        {
            return animationEndFrame_;
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
        void C_FbxLoader::C_FbxLoaderImpl::GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const
        {
            assert(meshIndex < meshList_.size());

            // ���b�V�����擾
            const S_Mesh& rMesh = meshList_[meshIndex];

            // �A�j���[�V�����̎�������C�e���[�^���擾
            auto iterator = animationNodeIdDictionary_.find(rMesh.nodeName_);

            // �����ɂȂ��ꍇ�A�P�ʍs���Ԃ�
            if (iterator == animationNodeIdDictionary_.end())
            {
                (*pMeshMatrix) = Matrix4x4::s_IDENTITY;

                return;
            }

            // �m�[�hID���擾
            int32_t nodeId = (*iterator).second;

            // �A�j���[�V�����̃V�[������m�[�h���擾
            FbxNode* pNode = pAnimationScene_->GetNode(nodeId);

            // �t���[�������玞�Ԃ��擾
            FbxTime time;
            time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

            // ���̎��Ԃ̍s����擾���A��{�p���̋t�s�����Z�������̂����b�V���̍s��Ƃ��Đݒ�
            FbxAMatrix& rFbxMatrix = pNode->EvaluateGlobalTransform(time);
            SetMatrix4x4(rFbxMatrix, pMeshMatrix);

            *pMeshMatrix = rMesh.inverseBaseposeMatrix_ * (*pMeshMatrix);
        }


        /*************************************************************//**
         *
         *  @brief  �{�[���̍s����擾����
         *  @param  �t���[����
         *  @param  ���b�V���̃C���f�b�N�X
         *  @param  �{�[���̍s��
         *  @param  �{�[���̍s��̍ő吔
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::GetBoneMatrix(int64_t frame,
                                                         uint32_t meshIndex,
                                                         Matrix4x4* pBoneMatrixList,
                                                         int32_t maxBoneMatrixCount) const
        {
            assert(meshIndex < meshList_.size());

            // ���b�V�����擾
            const S_Mesh& rMesh = meshList_[meshIndex];

            // �{�[�����Ȃ��ꍇ�A�_�~�[�̂��߂�0�Ԗڂ̍s��ɒP�ʍs���ݒ肵�ĕԂ�
            if (rMesh.bones_.size() == 0)
            {
                pBoneMatrixList[0] = Matrix4x4::s_IDENTITY;

                return;
            }

            assert(maxBoneMatrixCount > static_cast<int32_t>(rMesh.bones_.size()));

            // �t���[�������玞�Ԃ��擾
            FbxTime time;
            time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

            for (size_t i = 0, boneSize = rMesh.bones_.size(); i < boneSize; ++i)
            {
                // �m�[�h������m�[�hID���擾���A�m�[�hID����m�[�h���擾
                const std::string& rNodeName = rMesh.bones_[i].nodeName_;
                int32_t meshNodeId = animationNodeIdDictionary_.at(rNodeName);
                FbxNode* pNode = pAnimationScene_->GetNode(meshNodeId);

                // ���̎��Ԃ̍s����擾���A��{�p���̋t�s�����Z�������̂��{�[���̍s��Ƃ��Đݒ�
                FbxAMatrix& rFbxBoneMatrix = pNode->EvaluateGlobalTransform(time);
                Matrix4x4& rBoneMatrix = pBoneMatrixList[i];
                SetMatrix4x4(rFbxBoneMatrix, &rBoneMatrix);

                rBoneMatrix = rBoneMatrix * rMesh.bones_[i].inverseBaseposeMatrix_;
            }
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V���̉�͂��s��
         *  @param  FBX�̃��b�V��
         *  @return �Ǝ��̃��b�V��
         *
         ****************************************************************/
        S_Mesh C_FbxLoader::C_FbxLoaderImpl::ParseMesh(FbxMesh* pFbxMesh)
        {
            assert(pFbxMesh);

            // ���b�V��
            S_Mesh mesh;

            // �m�[�h���擾
            FbxNode* pNode = pFbxMesh->GetNode();
            assert(pNode->GetMaterialCount() == 1);

            // �m�[�h���ƃ}�e���A�������擾
            mesh.nodeName_ = pNode->GetName();
            mesh.parentNodeName_ = pNode->GetParent()->GetName();
            mesh.materialName_ = pNode->GetMaterial(0)->GetName();

            // ��{�p���̋t�s����擾
            FbxAMatrix inverseBaseposeMatrix = pNode->EvaluateGlobalTransform().Inverse();
            SetMatrix4x4(inverseBaseposeMatrix, &mesh.inverseBaseposeMatrix_);

            // �C���f�b�N�X���擾
            std::vector<int32_t> indices = GetIndicesFromMesh(pFbxMesh);

            // ���W�E�@���x�N�g���E�e�N�X�`�����W�E�F���擾
            std::vector<Vector3> positions = GetPositionsFromMesh(pFbxMesh, indices);
            std::vector<Vector3> normals = GetNormalsFromMesh(pFbxMesh, indices);
            std::vector<Vector2> textureCoords = GetTextureCoordsFromMesh(pFbxMesh, indices);
            std::vector<Vector4> colors = GetColorsFromMesh(pFbxMesh, indices);

            // �{�[���̃E�F�C�g
            std::vector<S_BoneWeight> boneWeights;

            // �{�[���̏����擾
            GetBoneDataFromMesh(pFbxMesh, indices, &boneWeights, &mesh.bones_);

            // �f�[�^���L�������f����t���O
            bool enableTextureCoordFlag = (indices.size() == textureCoords.size()) ? true : false;
            bool enableColorFlag = (indices.size() == colors.size()) ? true : false;

            assert(indices.size() == positions.size());
            assert(indices.size() == normals.size());
            assert(enableTextureCoordFlag == true || textureCoords.size() == 0);
            assert(enableColorFlag || colors.size() == 0);
            assert(indices.size() == boneWeights.size() || boneWeights.size() == 0);

            // ���_�̃��������m��
            std::vector<S_Vertex> vertices;
            vertices.reserve(indices.size());

            for (size_t i = 0, indexSize = indices.size(); i < indexSize; ++i)
            {
                S_Vertex vertex;

                // ���_�ɍ��W�E�@���x�N�g���E�e�N�X�`�����W�E�F��ݒ�
                vertex.position_ = positions[i];
                vertex.normal_ = normals[i];
                if (enableTextureCoordFlag == true) vertex.textureCoord_ = textureCoords[i];
                if (enableColorFlag == true) vertex.color_ = colors[i];

                // ���_�ɃE�F�C�g��ݒ�
                if (boneWeights.size() > 0)
                {
                    for (size_t j = 0; j < 4; ++j) vertex.boneWeights_.indices_[j] = boneWeights[i].indices_[j];
                    vertex.boneWeights_.weights_ = boneWeights[i].weights_;
                }
                else
                {
                    for (size_t j = 0; j < 4; ++j) vertex.boneWeights_.indices_[j] = 0;
                    vertex.boneWeights_.weights_ = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
                }

                // ���_��ێ�
                vertices.push_back(vertex);
            }

            assert(vertices.size() == indices.size());

            // ���b�V���̒��_���C���f�b�N�X���擾
            auto& rMeshVertices = mesh.vertices_;
            rMeshVertices.reserve(vertices.size());

            auto& rMeshIndices = mesh.indices_;
            rMeshIndices.reserve(indices.size());

            for (auto& rVertex : vertices)
            {
                // �d�����Ă��钸�_���������A�������ʂɂ�蒸�_�ƃC���f�b�N�X������U��
                auto iterator = std::find(rMeshVertices.begin(), rMeshVertices.end(), rVertex);

                /* �d�����Ă��Ȃ� */
                if (iterator == rMeshVertices.end())
                {
                    rMeshIndices.push_back(rMeshVertices.size());
                    rMeshVertices.push_back(rVertex);
                }
                /* �d�����Ă��� */
                else
                {
                    size_t index = std::distance(rMeshVertices.begin(), iterator);
                    rMeshIndices.push_back(index);
                }
            }

            // ���_�̗]���ȃ������̈���Ȃ���
            rMeshVertices.shrink_to_fit();

            // �ڃx�N�g�����v�Z
            if (enableTextureCoordFlag == true) CalculateTangents(&mesh);

            return mesh;
        }


        /*************************************************************//**
         *
         *  @brief  �}�e���A���̉�͂��s��
         *  @param  FBX�̃}�e���A��
         *  @return �Ǝ��̃}�e���A��
         *
         ****************************************************************/
        S_Material C_FbxLoader::C_FbxLoaderImpl::ParseMaterial(FbxSurfaceMaterial* pFbxMaterial)
        {
            assert(pFbxMaterial);

            // �}�e���A��
            S_Material material;

            // ���O���擾
            material.name_ = pFbxMaterial->GetName();

            // �}�e���A���̃f�[�^��ێ�������ϐ�
            FbxPropertyT<FbxDouble> materialData;
            FbxPropertyT<FbxDouble3> materialData3;

            // Phong�}�e���A���̏ꍇ
            if (pFbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
            {
                // �A���r�G���g���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Ambient;
                SetVector3(materialData3.Get(), &(material.ambient_));

                // �f�B�t���[�Y���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Diffuse;
                SetVector3(materialData3.Get(), &(material.diffuse_));

                // �X�y�L�������擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Specular;
                SetVector3(materialData3.Get(), &(material.specular_));

                // �G�~�b�V�u���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Emissive;
                SetVector3(materialData3.Get(), &(material.emissive_));

                // �s�����x���擾
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->TransparencyFactor;
                material.opacity_ = 1.0f - static_cast<float>(materialData.Get());

                // ������擾
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Shininess;
                material.shininess_ = static_cast<float>(materialData.Get());

                // ���˗����擾
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->ReflectionFactor;
                material.reflectivity_ = static_cast<float>(materialData.Get());
            }
            // Lambert�}�e���A���̏ꍇ
            else if (pFbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
            {
                // �A���r�G���g���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Ambient;
                SetVector3(materialData3.Get(), &(material.ambient_));

                // �f�B�t���[�Y���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Diffuse;
                SetVector3(materialData3.Get(), &(material.diffuse_));

                // �G�~�b�V�u���擾
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Emissive;
                SetVector3(materialData3.Get(), &(material.emissive_));

                // �s�����x���擾
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->TransparencyFactor;
                material.opacity_ = 1.0f - static_cast<float>(materialData.Get());
            }

            // �}�e���A���̃v���p�e�B
            FbxProperty materialProperty;

            // �A���r�G���g�e�N�X�`���̃v���p�e�B���擾���A�e�N�X�`�������擾
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sAmbient);
            material.ambientTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            // �f�B�t���[�Y�e�N�X�`���̃v���p�e�B���擾���A�e�N�X�`�������擾
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
            material.diffuseTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            // �X�y�L�����e�N�X�`���̃v���p�e�B���擾���A�e�N�X�`�������擾
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
            material.specularTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            return material;
        }


        /*************************************************************//**
         *
         *  @brief  FbxDouble3����Vecotr3�ɒl��ݒ肷��
         *  @param  FBX��Double3
         *  @param  3D�x�N�g��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::SetVector3(const FbxDouble3& rFbxDouble,
                                                      Vector3* pVector) const
        {
            pVector->x_ = static_cast<float>(rFbxDouble.mData[0]);
            pVector->y_ = static_cast<float>(rFbxDouble.mData[1]);
            pVector->z_ = static_cast<float>(rFbxDouble.mData[2]);
        }


        /*************************************************************//**
         *
         *  @brief  FbxAMatrix����Matrix4x4�ɒl��ݒ肷��
         *  @param  FBX��AMatrix
         *  @param  4 * 4�̍s��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::SetMatrix4x4(const FbxAMatrix& rFbxMatrix,
                                                        Matrix4x4* pMatrix) const
        {
            for (size_t i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    (*pMatrix).a4x4_[i][j] = static_cast<float>(rFbxMatrix.mData[i].mData[j]);
                }
            }
        }


        /*************************************************************//**
         *
         *  @brief  �v���p�e�B����e�N�X�`���t�@�C�������擾����
         *  @param  �v���p�e�B
         *  @return �e�N�X�`���t�@�C����
         *
         ****************************************************************/
        std::string C_FbxLoader::C_FbxLoaderImpl::GetTextureFileNameFromProperty(const FbxProperty& rProperty)
        {
            if (rProperty.IsValid() == false) return std::string();

            // �e�N�X�`���̐����擾
            auto layeredTextureCount = rProperty.GetSrcObjectCount<FbxLayeredTexture>();

            for (int32_t i = 0; i < layeredTextureCount; ++i)
            {
                // ���C���[�e�N�X�`�����擾
                FbxLayeredTexture* pLayeredTexture = rProperty.GetSrcObject<FbxLayeredTexture>(i);

                if (pLayeredTexture)
                {
                    // ���C���[�e�N�X�`���̐����擾
                    int32_t layeredTextureCount = pLayeredTexture->GetSrcObjectCount<FbxTexture>();

                    for (int32_t j = 0; j < layeredTextureCount; ++j)
                    {
                        // �e�N�X�`�����擾
                        FbxTexture* pTexture = pLayeredTexture->GetSrcObject<FbxTexture>(j);

                        if (pTexture)
                        {
                            // �t�@�C���e�N�X�`�����擾
                            FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>(pTexture);

                            // �t�@�C���p�X���擾���A�t�@�C�����̂ݕԂ�
                            return Path::C_PathAnalizer::s_GetFileName(pFileTexture->GetFileName());
                        }
                    }
                }
                else
                {
                    // �e�N�X�`�����擾
                    FbxTexture* pTexture = rProperty.GetSrcObject<FbxTexture>(i);

                    if (pTexture)
                    {
                        // �t�@�C���e�N�X�`�����擾
                        FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>(pTexture);

                        // �t�@�C���p�X���擾���A�t�@�C�����̂ݕԂ�
                        return Path::C_PathAnalizer::s_GetFileName(pFileTexture->GetFileName());
                    }
                }
            }

            return std::string();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V������C���f�b�N�X���擾����
         *  @param  ���b�V��
         *  @return �C���f�b�N�X
         *
         ****************************************************************/
        std::vector<int32_t> C_FbxLoader::C_FbxLoaderImpl::GetIndicesFromMesh(FbxMesh* pMesh)
        {
            // �|���S�������擾
            int32_t polygonCount = pMesh->GetPolygonCount();

            // �C���f�b�N�X�̃��������m��
            std::vector<int32_t> indices;
            indices.reserve(polygonCount * 3);

            // �C���f�b�N�X���擾
            for (int32_t i = 0; i < polygonCount; ++i)
            {
                indices.push_back(pMesh->GetPolygonVertex(i, 0));
                indices.push_back(pMesh->GetPolygonVertex(i, 1));
                indices.push_back(pMesh->GetPolygonVertex(i, 2));
            }

            return indices;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V��������W���擾����
         *  @param  ���b�V��
         *  @param  �C���f�b�N�X
         *  @return ���W
         *
         ****************************************************************/
        std::vector<Vector3> C_FbxLoader::C_FbxLoaderImpl::GetPositionsFromMesh(FbxMesh* pMesh,
                                                                                const std::vector<int32_t>& rIndices)
        {
            // ���W�̃��������m��
            std::vector<Vector3> positions;
            positions.reserve(rIndices.size());

            // ���W���擾
            for (auto index : rIndices)
            {
                FbxVector4 controlPoint = pMesh->GetControlPointAt(index);
                // assert(controlPoint[3] == 0.0);

                positions.emplace_back(static_cast<float>(controlPoint[0]),
                                       static_cast<float>(controlPoint[1]),
                                       static_cast<float>(controlPoint[2]));
            }

            return positions;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V������@���x�N�g�����擾����
         *  @param  ���b�V��
         *  @param  �C���f�b�N�X
         *  @return �@���x�N�g��
         *
         ****************************************************************/
        std::vector<Vector3> C_FbxLoader::C_FbxLoaderImpl::GetNormalsFromMesh(FbxMesh* pMesh,
                                                                              const std::vector<int32_t>& rIndices)
        {
            // �@���x�N�g���̗v�f�̐����擾
            int32_t elementNormalCount = pMesh->GetElementNormalCount();
            assert(elementNormalCount == 1);

            // �@���x�N�g���̗v�f���擾
            auto pElementNormal = pMesh->GetElementNormal();

            // �}�b�s���O���[�h�ƃ��t�@�����X���[�h���擾
            auto mappingMode = pElementNormal->GetMappingMode();
            auto referenceMode = pElementNormal->GetReferenceMode();

            // �C���f�b�N�X�Ɩ@���x�N�g���̔z����擾
            auto& rIndexArray = pElementNormal->GetIndexArray();
            auto& rDirectArray = pElementNormal->GetDirectArray();

            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // �@���x�N�g��
            std::vector<Vector3> normals;
            normals.reserve(rIndices.size());

            /* �R���g���[���|�C���g�Ń}�b�s���O */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // �@���x�N�g���̃C���f�b�N�X���擾
                    int32_t normalIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // �@���x�N�g�����擾
                    FbxVector4 fbxNormal = rDirectArray.GetAt(normalIndex);
                    // assert(fbxNormal[3] == 1.0);

                    normals.emplace_back(static_cast<float>(fbxNormal[0]),
                                         static_cast<float>(fbxNormal[1]),
                                         static_cast<float>(fbxNormal[2]));
                }
            }
            /* �|���S���o�[�e�b�N�X�Ń}�b�s���O */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // �|���S���o�[�e�b�N�X�̃C���f�b�N�X
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // �@���x�N�g���̃C���f�b�N�X���擾
                    int32_t normalIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // �@���x�N�g�����擾
                    FbxVector4 fbxNormal = rDirectArray.GetAt(normalIndex);
                    // assert(fbxNormal[3] == 1.0);

                    normals.emplace_back(static_cast<float>(fbxNormal[0]),
                                         static_cast<float>(fbxNormal[1]),
                                         static_cast<float>(fbxNormal[2]));

                    ++indexByPolygonVertex;
                }
            }
            else
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::GetNormalsFromMesh ] : �Ή����Ă��Ȃ��}�b�s���O���[�h�ł��B");
            }

            return normals;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V������e�N�X�`�����W���擾����
         *  @param  ���b�V��
         *  @param  �C���f�b�N�X
         *  @return �e�N�X�`�����W
         *
         ****************************************************************/
        std::vector<Vector2> C_FbxLoader::C_FbxLoaderImpl::GetTextureCoordsFromMesh(FbxMesh* pMesh,
                                                                                    const std::vector<int32_t>& rIndices)
        {
            // �e�N�X�`�����W
            std::vector<Vector2> textureCoords;

            // �e�N�X�`�����W�̗v�f�̐����擾
            int32_t elementTextureCoordCount = pMesh->GetElementUVCount();
            if (elementTextureCoordCount < 1) return textureCoords;

            // �e�N�X�`�����W�̗v�f���擾
            auto pElementTextureCoord = pMesh->GetElementUV(0);

            // �}�b�s���O���[�h�ƃ��t�@�����X���[�h���擾
            auto mappingMode = pElementTextureCoord->GetMappingMode();
            auto referenceMode = pElementTextureCoord->GetReferenceMode();

            // �C���f�b�N�X�ƃe�N�X�`�����W�̔z����擾
            auto& rIndexArray = pElementTextureCoord->GetIndexArray();
            auto& rDirectArray = pElementTextureCoord->GetDirectArray();

            // eDirct��eIndexDirect�̂ݑΉ�
            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // �e�N�X�`�����W�̃��������m��
            textureCoords.reserve(rIndices.size());

            /* �R���g���[���|�C���g�Ń}�b�s���O */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // �e�N�X�`�����W�̃C���f�b�N�X���擾
                    int32_t textureCoordIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // �e�N�X�`�����W���擾
                    FbxVector2 fbxTextureCoord = rDirectArray.GetAt(textureCoordIndex);
                    textureCoords.emplace_back(static_cast<float>(fbxTextureCoord[0]),
                                               static_cast<float>(fbxTextureCoord[1]));
                }
            }
            /* �|���S���o�[�e�b�N�X�Ń}�b�s���O */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // �|���S���o�[�e�b�N�X�̃C���f�b�N�X
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // �e�N�X�`�����W�̃C���f�b�N�X���擾
                    int32_t textureCoordIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // �e�N�X�`�����W���擾
                    FbxVector2 fbxTextureCoord = rDirectArray.GetAt(textureCoordIndex);

                    textureCoords.emplace_back(static_cast<float>(fbxTextureCoord[0]),
                                               static_cast<float>(fbxTextureCoord[1]));

                    ++indexByPolygonVertex;
                }
            }
            else
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::GetTextureCoordsFromMesh ] : �Ή����Ă��Ȃ��}�b�s���O���[�h�ł��B");
            }

            return textureCoords;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V������F���擾����
         *  @param  ���b�V��
         *  @param  �C���f�b�N�X
         *  @return �F
         *
         ****************************************************************/
        std::vector<Vector4> C_FbxLoader::C_FbxLoaderImpl::GetColorsFromMesh(FbxMesh* pMesh,
                                                                             const std::vector<int32_t>& rIndices)
        {
            // �F
            std::vector<Vector4> colors;

            // �F�̗v�f�̐����擾
            int32_t elementColorCount = pMesh->GetElementVertexColorCount();
            if (elementColorCount < 1) return colors;

            // �F�̗v�f���擾
            auto pElementColor = pMesh->GetElementVertexColor(0);

            // �}�b�s���O���[�h�ƃ��t�@�����X���[�h���擾
            auto mappingMode = pElementColor->GetMappingMode();
            auto referenceMode = pElementColor->GetReferenceMode();

            // �C���f�b�N�X�ƃe�N�X�`�����W�̔z����擾
            auto& rIndexArray = pElementColor->GetIndexArray();
            auto& rDirectArray = pElementColor->GetDirectArray();

            // eDirct��eIndexDirect�̂ݑΉ�
            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // �F�̃��������m��
            colors.reserve(rIndices.size());

            /* �R���g���[���|�C���g�Ń}�b�s���O */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // �F�̃C���f�b�N�X���擾
                    int32_t colorIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // �F���擾
                    FbxColor fbxColor = rDirectArray.GetAt(colorIndex);
                    colors.emplace_back(static_cast<float>(fbxColor.mRed),
                                        static_cast<float>(fbxColor.mGreen),
                                        static_cast<float>(fbxColor.mBlue),
                                        static_cast<float>(fbxColor.mAlpha));
                }
            }
            /* �|���S���o�[�e�b�N�X�Ń}�b�s���O */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // �|���S���o�[�e�b�N�X�̃C���f�b�N�X
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // �F�̃C���f�b�N�X���擾
                    int32_t colorIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // �F���擾
                    FbxColor fbxColor = rDirectArray.GetAt(colorIndex);
                    colors.emplace_back(static_cast<float>(fbxColor.mRed),
                                        static_cast<float>(fbxColor.mGreen),
                                        static_cast<float>(fbxColor.mBlue),
                                        static_cast<float>(fbxColor.mAlpha));

                    ++indexByPolygonVertex;
                }
            }
            else
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::GetColorsFromMesh ] : �Ή����Ă��Ȃ��}�b�s���O���[�h�ł��B");
            }

            return colors;
        }


        /*************************************************************//**
         *
         *  @brief  ���b�V������{�[���̏����擾����
         *  @param  ���b�V��
         *  @param  �C���f�b�N�X
         *  @param  �{�[���̃E�F�C�g
         *  @param  �{�[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::GetBoneDataFromMesh(FbxMesh* pMesh,
                                                               const std::vector<int32_t>& rIndices,
                                                               std::vector<S_BoneWeight>* pBoneWeights,
                                                               std::vector<S_Bone>* pBones)
        {
            // �X�L���̐����擾
            int32_t skinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);

            if (skinCount == 0) return;
            assert(skinCount == 1);

            // �R���g���[���|�C���g�̐����擾
            int32_t controlPointsCount = pMesh->GetControlPointsCount();

            // ���̃E�F�C�g
            using TemporaryWeight = std::pair<int32_t, float>;
            std::vector<std::deque<TemporaryWeight>> tempBoneWeights(controlPointsCount);

            // �X�L�����擾
            FbxSkin* pSkin = static_cast<FbxSkin*>(pMesh->GetDeformer(0, FbxDeformer::eSkin));

            // �N���X�^�[�����擾���A�{�[���̃��������m��
            int32_t clusterCount = pSkin->GetClusterCount();
            (*pBones).reserve(clusterCount);

            for (int32_t i = 0; i < clusterCount; ++i)
            {
                // �N���X�^�[( �{�[�� )���擾
                FbxCluster* pCluster = pSkin->GetCluster(i);
                assert(pCluster->GetLinkMode() == FbxCluster::eNormalize);

                // ���̃{�[��
                S_Bone tempBone;

                // �{�[���̃m�[�h���Ɛe�m�[�h�����擾
                FbxNode* pNode = pCluster->GetLink();
                tempBone.nodeName_ = pNode->GetName();
                tempBone.parentNodeName_ = pNode->GetParent()->GetName();

                // �R���g���[���|�C���g�̃C���f�b�N�X�̐��ƃC���f�b�N�X���擾
                int32_t controlPointIndicesCount = pCluster->GetControlPointIndicesCount();
                int32_t* pControlPointIndices = pCluster->GetControlPointIndices();

                // �R���g���[���|�C���g�̃E�F�C�g���擾
                double* pControlPointWeights = pCluster->GetControlPointWeights();

                // �e�R���g���[���|�C���g�̃E�F�C�g�����ׂĎ擾
                for (int32_t j = 0; j < controlPointIndicesCount; ++j)
                {
                    int32_t controlPointIndex = pControlPointIndices[j];
                    tempBoneWeights[controlPointIndex].emplace_back(i, static_cast<float>(pControlPointWeights[j]));
                }

                // ��{�p���̋t�s����擾����
                auto inverseBaseposeMatrix = pCluster->GetLink()->EvaluateGlobalTransform().Inverse();
                SetMatrix4x4(inverseBaseposeMatrix, &tempBone.inverseBaseposeMatrix_);

                // �{�[����ێ�
                (*pBones).push_back(tempBone);
            }

            // �R���g���[���|�C���g�ɑΉ������E�F�C�g�̃��������m��
            std::vector<S_BoneWeight> boneWeightsControlPoints;
            boneWeightsControlPoints.reserve(controlPointsCount);

            for (auto& tempBoneWeight : tempBoneWeights)
            {
                // �E�F�C�g���\�[�g
                std::sort(tempBoneWeight.begin(),
                          tempBoneWeight.end(),
                          [](const TemporaryWeight& rWeight, const TemporaryWeight& rAnotherWeight){ return rWeight.second > rAnotherWeight.second; });

                // 4�𒴉߂��Ă���ꍇ�A4�ɂȂ�悤�ɃE�F�C�g�̒Ⴂ���̂�r��
                while (tempBoneWeight.size() > 4) tempBoneWeight.pop_back();

                // 4�����̏ꍇ�A4�ɂȂ�悤�Ƀ_�~�[��ǉ�
                while (tempBoneWeight.size() < 4) tempBoneWeight.emplace_back(0, 0.0f);

                // �C���f�b�N�X�Ɛ��K�������E�F�C�g��ێ�
                S_BoneWeight weight;
                float totalWeight = 0.0f;

                for (size_t i = 0; i < 4; ++i)
                {
                    weight.indices_[i] = tempBoneWeight[i].first;
                    totalWeight += tempBoneWeight[i].second;
                }

                weight.weights_.x_ = tempBoneWeight[0].second / totalWeight;
                weight.weights_.y_ = tempBoneWeight[1].second / totalWeight;
                weight.weights_.z_ = tempBoneWeight[2].second / totalWeight;
                weight.weights_.w_ = tempBoneWeight[3].second / totalWeight;

                boneWeightsControlPoints.push_back(weight);
            }

            // �E�F�C�g�̃��������m��
            (*pBoneWeights).reserve(rIndices.size());

            // �C���f�b�N�X�ŃE�F�C�g���擾
            for (auto index : rIndices) (*pBoneWeights).push_back(boneWeightsControlPoints[index]);
        }


        /*************************************************************//**
         *
         *  @brief  �ڃx�N�g�����v�Z����
         *  @param  ���b�V��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::CalculateTangents(S_Mesh* pMesh)
        {
            auto& rMeshVertices = pMesh->vertices_;
            auto& rMeshIndices = pMesh->indices_;

            size_t vertexCount = rMeshVertices.size();

            // �ڃx�N�g���Ə]�@���x�N�g�������߂�
            std::vector<Vector3> tangents(vertexCount);
            std::vector<Vector3> binormals(vertexCount);

            for (size_t i = 0, polygonSize = rMeshIndices.size() / 3; i < polygonSize; ++i)
            {
                size_t index = i * 3;
                int32_t index0 = rMeshIndices[index];
                int32_t index1 = rMeshIndices[index + 1];
                int32_t index2 = rMeshIndices[index + 2];

                auto tangetnAndBinormal = Vector3::s_CreateTangentAndBinormal(rMeshVertices[index0].position_,
                                                                              rMeshVertices[index0].textureCoord_,
                                                                              rMeshVertices[index1].position_,
                                                                              rMeshVertices[index1].textureCoord_,
                                                                              rMeshVertices[index2].position_,
                                                                              rMeshVertices[index2].textureCoord_);

                auto& rTangent = std::get<0>(tangetnAndBinormal);
                auto& rBinormal = std::get<1>(tangetnAndBinormal);

                tangents[index0] += rTangent;
                tangents[index1] += rTangent;
                tangents[index2] += rTangent;
                binormals[index0] += rBinormal;
                binormals[index1] += rBinormal;
                binormals[index2] += rBinormal;
            }

            for (size_t i = 0; i < vertexCount; ++i)
            {
                auto& rNormal = rMeshVertices[i].normal_;
                auto& rTangent = tangents[i];
                auto& rBinormal = binormals[i];

                // �O�����E�V���~�b�g�̒��s���@�Őڃx�N�g�����擾
                rMeshVertices[i].tangent_.xyz_ = (rTangent - (Vector3::s_DotProduct(rNormal, rTangent) * rNormal)).GetNormalize();

                // �ڋ�Ԃ̏��������߂�
                rMeshVertices[i].tangent_.w_ = (Vector3::s_DotProduct(Vector3::s_CrossProduct(rNormal, rTangent), rBinormal) < 0.0f) ? -1.0f : 1.0f;
            }
        }
    }
}