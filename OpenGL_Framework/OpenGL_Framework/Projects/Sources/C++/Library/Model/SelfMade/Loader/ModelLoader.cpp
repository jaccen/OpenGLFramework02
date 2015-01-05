/* ヘッダファイル */
#include "ModelLoader.h"
#include "../../../Common/CommonHelper.h"
#include <fstream>


//-------------------------------------------------------------
//!
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief 自作関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoader::C_ModelLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoader::~C_ModelLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  モデルのロード処理を行う
         *  @param  モデルファイルのパス
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::LoadModel(const std::string& rModelFilePath)
        {
            std::ifstream inFile(rModelFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadModel ] : 入力ファイルを開くのに失敗しました。");
            }

            // ファイルサイズを取得
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // ファイルデータのメモリを確保し、ファイルからデータを全て読み込む
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // ファイルデータからモデルを取得
            GetModelFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルのロード処理を行う
         *  @param  マテリアルファイルのパス
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::LoadMaterial(const std::string& rMaterialFilePath)
        {
            std::ifstream inFile(rMaterialFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadMaterial ] : 入力ファイルを開くのに失敗しました。");
            }

            // ファイルサイズを取得
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // ファイルデータのメモリを確保し、ファイルからデータを全て読み込む
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // マテリアルをファイルデータから取得
            GetMaterialFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  アニメーションのロード処理を行う
         *  @param  アニメーションファイルのパス
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::LoadAnimation(const std::string& rAnimationFilePath)
        {
            std::ifstream inFile(rAnimationFilePath, std::ios::in | std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_ModelLoader::LoadMaterial ] : 入力ファイルを開くのに失敗しました。");
            }

            // ファイルサイズを取得
            uint32_t fileSize = Common::C_CommonHelper::s_GetFileSize(&inFile);

            // ファイルデータのメモリを確保し、ファイルからデータを全て読み込む
            std::unique_ptr<char[]> fileData = std::make_unique<char[]>(fileSize);
            inFile.read(fileData.get(), fileSize);

            // アニメーションをファイルデータから取得
            GetAnimationFromFileData(fileData.get());
        }


        /*************************************************************//**
         *
         *  @brief  解放処理を行う
         *  @param  なし
         *  @return なし
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
         *  @brief  メッシュ数を取得する
         *  @param  なし
         *  @return メッシュ数
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetMeshCount() const
        {
            return meshList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  ボーン数を取得する
         *  @param  メッシュのインデックス
         *  @return ボーン数
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetBoneCount(uint32_t meshIndex) const
        {
            return meshList_[meshIndex].bones_.size();
        }


        /*************************************************************//**
         *
         *  @brief  マテリアル数を取得する
         *  @param  なし
         *  @return マテリアル数
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetMaterialCount() const
        {
            return materialList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュを取得する
         *  @param  インデックス
         *  @return メッシュ
         *
         ****************************************************************/
        const S_Mesh& C_ModelLoader::GetMesh(uint32_t index) const
        {
            assert(index < meshList_.size());
            return meshList_[index];
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルを取得する
         *  @param  インデックス
         *  @return マテリアル
         *
         ****************************************************************/
        const S_Material& C_ModelLoader::GetMaterial(uint32_t index) const
        {
            assert(index < materialList_.size());
            return materialList_[index];
        }


        /*************************************************************//**
         *
         *  @brief  アニメーション終了フレーム数を取得する
         *  @param  なし
         *  @return メッシュリスト
         *
         ****************************************************************/
        uint32_t C_ModelLoader::GetAnimationEndFrame() const
        {
            return animationEndFrame_;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュのアニメーション行列を取得する
         *  @param  フレーム数
         *  @param  メッシュのインデックス
         *  @return メッシュのアニメーション行列
         *
         ****************************************************************/
        const Matrix4x4& C_ModelLoader::GetMeshAnimationMatrix(uint32_t frame, uint32_t meshIndex) const
        {
            return meshList_[meshIndex].eachFrameAnimationMatrices_[frame];
        }


        /*************************************************************//**
         *
         *  @brief  ボーンのアニメーション行列を取得する
         *  @param  フレーム数
         *  @param  メッシュのインデックス
         *  @param  ボーンのインデックス
         *  @return ボーンのアニメーション行列
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
         *  @brief  ファイルデータからモデルを取得する
         *  @param  ファイルデータ
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::GetModelFromFileData(char* pFileData)
        {
            // ファイルデータの先頭からのオフセット
            size_t fileDataOffset = 0;

            // メッシュ数を取得
            uint32_t* pMeshCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // メッシュリストのメモリを確保
            meshList_.reserve(*pMeshCount);

            for (size_t i = 0; i < *pMeshCount; ++i)
            {
                S_Mesh mesh;

                // 名前と親の名前とマテリアル名を取得
                mesh.name_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                mesh.parentName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                mesh.materialName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                // 頂点数とインデックス数とボーン数を取得
                uint32_t* pVertexCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                uint32_t* pIndexCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                uint8_t* pBoneWeightCount = reinterpret_cast<uint8_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint8_t);
                assert(*pBoneWeightCount > 0 || *pBoneWeightCount <= 4);

                // 頂点とインデックスのメモリを確保
                mesh.vertices_.reserve(*pVertexCount);
                mesh.indices_.reserve(*pIndexCount);

                for (size_t j = 0; j < *pVertexCount; ++j)
                {
                    S_Vertex vertex;

                    // 座標を取得
                    for (size_t k = 0; k < 3; ++k)
                    {
                        float* pPositionElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.position_.a_[k] = *pPositionElement;
                        fileDataOffset += sizeof(float);
                    }

                    // 法線を取得
                    for (size_t k = 0; k < 3; ++k)
                    {
                        float* pNormalElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.normal_.a_[k] = *pNormalElement;
                        fileDataOffset += sizeof(float);
                    }

                    // テクスチャ座標を取得
                    for (size_t k = 0; k < 2; ++k)
                    {
                        float* pTextureCoordElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.textureCoord_.a_[k] = *pTextureCoordElement;
                        fileDataOffset += sizeof(float);
                    }

                    // 色を取得
                    for (size_t k = 0; k < 4; ++k)
                    {
                        float* pColorElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.color_.a_[k] = *pColorElement;
                        fileDataOffset += sizeof(float);
                    }

                    // 接ベクトルを取得
                    for (size_t k = 0; k < 4; ++k)
                    {
                        float* pTangentElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.tangent_.a_[k] = *pTangentElement;
                        fileDataOffset += sizeof(float);
                    }

                    // ボーンウェイトのインデックスを取得
                    for (size_t k = 0; k < *pBoneWeightCount; ++k)
                    {
                        uint8_t* pBoneWeightIndex = reinterpret_cast<uint8_t*>(pFileData + fileDataOffset);
                        vertex.boneWeights_.indices_[k] = *pBoneWeightIndex;
                        fileDataOffset += sizeof(uint8_t);
                    }

                    // ボーンウェイトを取得
                    for (size_t k = 0; k < *pBoneWeightCount; ++k)
                    {
                        float* pBoneWeightElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        vertex.boneWeights_.weights_.a_[k] = *pBoneWeightElement;
                        fileDataOffset += sizeof(float);
                    }

                    // メッシュに頂点を加える
                    mesh.vertices_.push_back(std::move(vertex));
                }

                for (size_t j = 0; j < *pIndexCount; ++j)
                {
                    // インデックスを取得
                    uint16_t* pIndex = reinterpret_cast<uint16_t*>(pFileData + fileDataOffset);
                    fileDataOffset += sizeof(uint16_t);

                    // メッシュにインデックスを加える
                    mesh.indices_.push_back(*pIndex);
                }

                if (meshList_.size() < *pMeshCount)
                {
                    // メッシュリストにメッシュを加える
                    meshList_.push_back(std::move(mesh));
                }
                else
                {
                    // 各データをコピー
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
         *  @brief  ファイルデータからマテリアルを取得する
         *  @param  ファイルデータ
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::GetMaterialFromFileData(char* pFileData)
        {
            // ファイルデータの先頭からのオフセット
            size_t fileDataOffset = 0;

            // マテリアル数を取得
            uint32_t* pMaterialCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // マテリアルリストのメモリを確保
            materialList_.reserve(*pMaterialCount);

            for (size_t i = 0; i < *pMaterialCount; ++i)
            {
                S_Material material;

                // マテリアル名を取得
                material.name_ = pFileData + fileDataOffset;
                fileDataOffset += sizeof(char)* 64;

                // アンビエントを取得
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pAmbientElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.ambient_.a_[j] = *pAmbientElement;
                    fileDataOffset += sizeof(float);
                }

                // ディフューズを取得
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pDiffuseElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.diffuse_.a_[j] = *pDiffuseElement;
                    fileDataOffset += sizeof(float);
                }

                // スペキュラを取得
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pSpecularElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.specular_.a_[j] = *pSpecularElement;
                    fileDataOffset += sizeof(float);
                }

                // エミッシブを取得
                for (size_t j = 0; j < 3; ++j)
                {
                    float* pEmissiveElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    material.emissive_.a_[j] = *pEmissiveElement;
                    fileDataOffset += sizeof(float);
                }

                // シャイニネスとリフレクティビティの取得
                float* pshininess = reinterpret_cast<float*>(pFileData + fileDataOffset);
                material.shininess_ = *pshininess;
                fileDataOffset += sizeof(float);

                float* pRreflectivity = reinterpret_cast<float*>(pFileData + fileDataOffset);
                material.reflectivity_ = *pRreflectivity;
                fileDataOffset += sizeof(float);

                // 各テクスチャを取得
                material.ambientTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                material.diffuseTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                material.specularTextureFileName_ = (pFileData + fileDataOffset);
                fileDataOffset += sizeof(char)* 64;

                if (materialList_.size() < *pMaterialCount)
                {
                    // マテリアルリストにマテリアルを追加
                    materialList_.push_back(std::move(material));
                }
            }
        }


        /*************************************************************//**
         *
         *  @brief  ファイルデータからアニメーションを取得する
         *  @param  ファイルデータ
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoader::GetAnimationFromFileData(char* pFileData)
        {
            // ファイルデータの先頭からのオフセット
            size_t fileDataOffset = 0;

            // メッシュの数を取得
            uint32_t* pMeshCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            fileDataOffset += sizeof(uint32_t);

            // 終了フレーム数を取得
            uint32_t* pAnimationEndFrame = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
            animationEndFrame_ = *pAnimationEndFrame;
            fileDataOffset += sizeof(uint32_t);

            for (size_t i = 0; i < *pMeshCount; ++i)
            {
                S_Mesh mesh;

                // ボーン数を取得
                uint32_t* pBoneCount = reinterpret_cast<uint32_t*>(pFileData + fileDataOffset);
                fileDataOffset += sizeof(uint32_t);

                // ボーンのメモリを確保
                mesh.bones_.reserve(*pBoneCount);

                for (size_t j = 0; j < *pBoneCount; ++j)
                {
                    S_Bone bone;

                    // ボーン名と親ボーン名取得
                    bone.name_ = (pFileData + fileDataOffset);
                    fileDataOffset += sizeof(char)* 64;

                    bone.parentName_ = (pFileData + fileDataOffset);
                    fileDataOffset += sizeof(char)* 64;

                    // ボーンの基本姿勢の逆行列を取得
                    for (size_t k = 0; k < 16; ++k)
                    {
                        float* pBoneInverseBaseposeMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        bone.inverseBaseposeMatrix_.a_[k] = *pBoneInverseBaseposeMatrixElement;
                        fileDataOffset += sizeof(float);
                    }

                    // ボーンを追加
                    mesh.bones_.push_back(std::move(bone));
                }

                for (size_t j = 0; j < 16; ++j)
                {
                    // 基本姿勢の逆行列を取得
                    float* pInverseBaseposeMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                    mesh.inverseBaseposeMatrix_.a_[j] = *pInverseBaseposeMatrixElement;
                    fileDataOffset += sizeof(float);
                }

                // メッシュの各フーレムのアニメーション行列のメモリを確保
                mesh.eachFrameAnimationMatrices_.reserve(*pAnimationEndFrame);

                for (size_t j = 0; j < *pAnimationEndFrame; ++j)
                {
                    for (size_t k = 0; k < *pBoneCount; ++k)
                    {
                        Matrix4x4 boneMatrix;

                        // ボーンの各フーレムのアニメーション行列のメモリを確保
                        mesh.bones_[k].eachFrameAnimationMatrices_.reserve(*pAnimationEndFrame);

                        for (size_t l = 0; l < 16; ++l)
                        {
                            // ボーン行列を取得
                            float* pBoneMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                            boneMatrix.a_[l] = *pBoneMatrixElement;
                            fileDataOffset += sizeof(float);
                        }

                        // ボーンの各フーレムのアニメーション行列を追加
                        mesh.bones_[k].eachFrameAnimationMatrices_.push_back(boneMatrix);
                    }

                    Matrix4x4 meshMatrix;

                    for (size_t k = 0; k < 16; ++k)
                    {
                        float* pMeshMatrixElement = reinterpret_cast<float*>(pFileData + fileDataOffset);
                        meshMatrix.a_[k] = *pMeshMatrixElement;
                        fileDataOffset += sizeof(float);
                    }

                    // メッシュの各フーレムのアニメーション行列を追加
                    mesh.eachFrameAnimationMatrices_.push_back(meshMatrix);
                }

                if (meshList_.size() < *pMeshCount)
                {
                    // メッシュ行列のリストにメッシュ行列を追加
                    meshList_.push_back(std::move(mesh));
                }
                else
                {
                    // 各データをコピー
                    meshList_[i].inverseBaseposeMatrix_ = mesh.inverseBaseposeMatrix_;
                    meshList_[i].eachFrameAnimationMatrices_ = std::move(mesh.eachFrameAnimationMatrices_);
                    meshList_[i].bones_ = std::move(mesh.bones_);
                }
            }
        }
    }
}