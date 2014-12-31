/* ヘッダファイル */
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
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief FBX
    //! @brief FBX関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace FBX
    {
        //-------------------------------------------------------------
        //!
        //! @brief FBXローダーインプリメント
        //! @brief FBXローダーのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_FbxLoader::C_FbxLoaderImpl
        {
        public:
            C_FbxLoaderImpl();                                                                          // コンストラクタ
            ~C_FbxLoaderImpl();                                                                         // デストラクタ
            void LoadModel(const std::string& rFilePath);                                               // モデルのロード処理
            void LoadAnimation(const std::string& rFilePath, int32_t stackNumber);                      // アニメーションのロード処理
            void Release();                                                                             // 解放処理

            /* ゲッター */
            uint32_t GetMeshCount() const;                                                              // メッシュ数を取得
            const S_Mesh& GetMesh(uint32_t index) const;                                                // メッシュを取得
            uint32_t GetMaterialCount() const;                                                          // マテリアル数を取得
            int32_t GetMaterialId(const std::string& rName) const;                                      // マテリアルのIDを取得
            const S_Material& GetMaterial(int32_t id) const;                                            // マテリアルを取得
            int64_t GetAnimationStartFrame() const;                                                     // アニメーションの開始フレーム数を取得
            int64_t GetAnimationEndFrame() const;                                                       // アニメーションの終了フレーム数を取得
            void GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const;        // メッシュの行列を取得
            void GetBoneMatrix(int64_t frame,                                                           // ボーンの行列を取得
                               uint32_t meshIndex,
                               Matrix4x4* pBoneMatrixList,
                               int32_t maxBoneMatrixCount) const;
        private:
            /** マネージャーのデリータ */
            struct S_ManagerDeleter
            {
                void operator()(FbxManager* pManager)
                {
                    pManager->Destroy();
                }
            };

            std::unique_ptr<FbxManager, S_ManagerDeleter> upManager_;                                   ///< @brief マネージャー
            FbxScene* pModelScene_ = nullptr;                                                           ///< @brief モデルシーン
            FbxScene* pAnimationScene_ = nullptr;                                                       ///< @brief アニメーションシーン
            std::unordered_map<std::string, int16_t> modelNodeIdDictionary_;                            ///< @brief モデルのノードIDの辞書
            std::unordered_map<std::string, int16_t> animationNodeIdDictionary_;                        ///< @brief アニメーションのノードIDの辞書
            std::unordered_map<std::string, int16_t> materialIdDictionary_;                             ///< @brief マテリアルIDの辞書
            std::vector<S_Mesh> meshList_;                                                              ///< @brief メッシュリスト
            std::vector<S_Material> materialList_;                                                      ///< @brief マテリアルリスト
            int64_t animationStartFrame_ = 0;                                                           ///< @brief アニメーションの開始フレーム数
            int64_t animationEndFrame_ = 0;                                                             ///< @brief アニメーションの終了フレーム

            S_Mesh ParseMesh(FbxMesh* pFbxMesh);                                                        // メッシュの解析
            S_Material ParseMaterial(FbxSurfaceMaterial* pFbxMaterial);                                 // マテリアルの解析
            void SetVector3(const FbxDouble3& rFbxDouble,                                               // FbxDouble3からVector3に値を設定
                            Vector3* pVector) const;
            void SetMatrix4x4(const FbxAMatrix& rFbxMatrix,                                             // FbxAMatrixからMatrix4x4型を設定
                              Matrix4x4* pMatrix) const;
            std::string GetTextureFileNameFromProperty(const FbxProperty& rProperty);                   // プロパティからテクスチャファイル名を取得
            std::vector<int32_t> GetIndicesFromMesh(FbxMesh* pMesh);                                    // メッシュからインデックスを取得
            std::vector<Vector3> GetPositionsFromMesh(FbxMesh* pMesh,                                   // メッシュから座標を取得
                                                      const std::vector<int32_t>& rIndices);
            std::vector<Vector3> GetNormalsFromMesh(FbxMesh* pMesh,                                     // メッシュから法線ベクトルを取得
                                                    const std::vector<int32_t>& rIndices);
            std::vector<Vector2> GetTextureCoordsFromMesh(FbxMesh* pMesh,                               // メッシュからテクスチャ座標を取得
                                                          const std::vector<int32_t>& rIndices);
            std::vector<Vector4> GetColorsFromMesh(FbxMesh* pMesh,                                      // メッシュから色を取得
                                                   const std::vector<int32_t>& rIndices);
            void GetBoneDataFromMesh(FbxMesh* pMesh,                                                    // ボーンの情報を取得
                                     const std::vector<int32_t>& rIndices,
                                     std::vector<S_BoneWeight>* pBoneWeights,
                                     std::vector<S_Bone>* pBones);
            void CalculateTangents(S_Mesh* pMesh);                                                      // 接ベクトルを計算
        };


        /*************************************************************//**
        *
        *  @brief  コンストラクタ
        *  @param  なし
        *
        ****************************************************************/
        C_FbxLoader::C_FbxLoaderImpl::C_FbxLoaderImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_FbxLoader::C_FbxLoaderImpl::~C_FbxLoaderImpl()
        {
            if (upManager_) Release();
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルのモデルのロード処理を行う
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::LoadModel(const std::string& rFilePath)
        {
            // FBXマネージャーを作成
            upManager_.reset(FbxManager::Create());

            // IOを設定
            FbxIOSettings* pIoSetting = FbxIOSettings::Create(upManager_.get(), IOSROOT);
            upManager_->SetIOSettings(pIoSetting);

            // インポーターを作成し、初期化
            auto pImporter = Common::C_CommonHelper::s_MakeCustomUnique(FbxImporter::Create(upManager_.get(), ""),
                [](FbxImporter* pImpoter){ pImpoter->Destroy(); });

            if (pImporter->Initialize(rFilePath.c_str(), -1, upManager_->GetIOSettings()) == false)
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::LoadModel ] :インポーターの初期化処理に失敗しました。");
            }

            // シーンを作成し、インポート
            pModelScene_ = FbxScene::Create(upManager_.get(), "ModelScene");
            pImporter->Import(pModelScene_);

            // ポリゴンを全て三角形化
            FbxGeometryConverter geometryConverter(upManager_.get());
            geometryConverter.Triangulate(pModelScene_, true);

            // ノード数を取得
            int32_t nodeNumber = pModelScene_->GetNodeCount();

            // ノードIDを辞書に登録
            for (int32_t i = 0; i < nodeNumber; ++i)
            {
                FbxNode* pNode = pModelScene_->GetNode(static_cast<int32_t>(i));
                modelNodeIdDictionary_.emplace(pNode->GetName(), i);
            }

            // マテリアル数を取得
            int32_t materialCount = pModelScene_->GetMaterialCount();
            materialList_.reserve(materialCount);

            // マテリアルを解析し、辞書とリストに追加
            for (int32_t i = 0; i < materialCount; ++i)
            {
                FbxSurfaceMaterial* pFbxMaterial = pModelScene_->GetMaterial(i);
                S_Material material = ParseMaterial(pFbxMaterial);

                materialIdDictionary_.emplace(material.name_, i);
                materialList_.push_back(std::move(material));
            }

            // メッシュの数を取得
            int32_t meshCount = pModelScene_->GetMemberCount<FbxMesh>();
            meshList_.reserve(meshCount);

            // メッシュを解析し、リストに追加
            for (int32_t i = 0; i < meshCount; ++i)
            {
                FbxMesh* pFbxMesh = pModelScene_->GetMember<FbxMesh>(i);
                meshList_.push_back(ParseMesh(pFbxMesh));
            }
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルのアニメーションのロード処理を行う
         *  @param  ファイルパス
         *  @param  アニメーションスタック番号
         *  @return 正常終了：true
         *  @return 異常終了：false
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::LoadAnimation(const std::string& rFilePath, int32_t stackNumber)
        {
            // インポーターを作成し、初期化
            auto pImporter = Common::C_CommonHelper::s_MakeCustomUnique(FbxImporter::Create(upManager_.get(), ""),
                                                                        [](FbxImporter* pImpoter){ pImpoter->Destroy(); });

            if (pImporter->Initialize(rFilePath.c_str(), -1, upManager_->GetIOSettings()) == false)
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::LoadAnimation ] :インポーターの初期化処理に失敗しました。");
            }

            // シーンを取得
            pAnimationScene_ = FbxScene::Create(upManager_.get(), "AnimationScene");
            pImporter->Import(pAnimationScene_);

            // アニメーション切り替え
            auto pAnimationStack = pAnimationScene_->GetSrcObject<fbxsdk_2015_1::FbxAnimStack>(stackNumber);
            pAnimationScene_->SetCurrentAnimationStack(pAnimationStack);

            // テイク情報を取得
            FbxTakeInfo* pTakeInfo = pImporter->GetTakeInfo(0);
            auto importOffset = pTakeInfo->mImportOffset;

            // アニメーションフレーム数を取得
            FbxTime startTime = pTakeInfo->mLocalTimeSpan.GetStart();
            FbxTime stopTime = pTakeInfo->mLocalTimeSpan.GetStop();

            animationStartFrame_ = (importOffset.Get() + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
            animationEndFrame_ = (importOffset.Get() + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);

            // ノード数を取得
            int32_t nodeCount = pAnimationScene_->GetNodeCount();

            // ノードIDを辞書に登録
            for (int32_t i = 0; i < nodeCount; ++i)
            {
                FbxNode* pNode = pAnimationScene_->GetNode(i);
                animationNodeIdDictionary_.emplace(pNode->GetName(), i);
            }
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルの解放処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::Release()
        {
            // マネージャーを破棄
            upManager_.reset();

            // 各リストや辞書をクリア
            meshList_.clear();
            materialList_.clear();
            modelNodeIdDictionary_.clear();
            animationNodeIdDictionary_.clear();
            materialIdDictionary_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュの数を取得する
         *  @param  なし
         *  @return メッシュの数
         *
         ****************************************************************/
        uint32_t C_FbxLoader::C_FbxLoaderImpl::GetMeshCount() const
        {
            return meshList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュを取得する
         *  @param  インデックス
         *  @return メッシュ
         *
         ****************************************************************/
        const S_Mesh& C_FbxLoader::C_FbxLoaderImpl::GetMesh(uint32_t index) const
        {
            return meshList_.at(index);
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルの数を取得する
         *  @param  なし
         *  @return マテリアルの数
         *
         ****************************************************************/
        uint32_t C_FbxLoader::C_FbxLoaderImpl::GetMaterialCount() const
        {
            return materialList_.size();
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルのIDを取得する
         *  @param  マテリアル名
         *  @return マテリアルのID
         *
         ****************************************************************/
        int32_t C_FbxLoader::C_FbxLoaderImpl::GetMaterialId(const std::string& rName) const
        {
            return materialIdDictionary_.at(rName);
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルを取得する
         *  @param  マテリアルのID
         *  @return マテリアル
         *
         ****************************************************************/
        const S_Material& C_FbxLoader::C_FbxLoaderImpl::GetMaterial(int32_t id) const
        {
            return materialList_.at(id);
        }


        /*************************************************************//**
         *
         *  @brief  アニメーションの開始フレーム数を取得する
         *  @param  なし
         *  @return アニメーションの開始フレーム数
         *
         ****************************************************************/
        int64_t C_FbxLoader::C_FbxLoaderImpl::GetAnimationStartFrame() const
        {
            return animationStartFrame_;
        }


        /*************************************************************//**
         *
         *  @brief  アニメーションの終了フレーム数を取得する
         *  @param  なし
         *  @return アニメーションの終了フレーム数
         *
         ****************************************************************/
        int64_t C_FbxLoader::C_FbxLoaderImpl::GetAnimationEndFrame() const
        {
            return animationEndFrame_;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュの行列を取得する
         *  @param  フレーム数
         *  @param  メッシュのインデックス
         *  @param  メッシュの行列
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const
        {
            assert(meshIndex < meshList_.size());

            // メッシュを取得
            const S_Mesh& rMesh = meshList_[meshIndex];

            // アニメーションの辞書からイテレータを取得
            auto iterator = animationNodeIdDictionary_.find(rMesh.nodeName_);

            // 辞書にない場合、単位行列を返す
            if (iterator == animationNodeIdDictionary_.end())
            {
                (*pMeshMatrix) = Matrix4x4::s_IDENTITY;

                return;
            }

            // ノードIDを取得
            int32_t nodeId = (*iterator).second;

            // アニメーションのシーンからノードを取得
            FbxNode* pNode = pAnimationScene_->GetNode(nodeId);

            // フレーム数から時間を取得
            FbxTime time;
            time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

            // その時間の行列を取得し、基本姿勢の逆行列を乗算したものをメッシュの行列として設定
            FbxAMatrix& rFbxMatrix = pNode->EvaluateGlobalTransform(time);
            SetMatrix4x4(rFbxMatrix, pMeshMatrix);

            *pMeshMatrix = rMesh.inverseBaseposeMatrix_ * (*pMeshMatrix);
        }


        /*************************************************************//**
         *
         *  @brief  ボーンの行列を取得する
         *  @param  フレーム数
         *  @param  メッシュのインデックス
         *  @param  ボーンの行列
         *  @param  ボーンの行列の最大数
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::GetBoneMatrix(int64_t frame,
                                                         uint32_t meshIndex,
                                                         Matrix4x4* pBoneMatrixList,
                                                         int32_t maxBoneMatrixCount) const
        {
            assert(meshIndex < meshList_.size());

            // メッシュを取得
            const S_Mesh& rMesh = meshList_[meshIndex];

            // ボーンがない場合、ダミーのために0番目の行列に単位行列を設定して返す
            if (rMesh.bones_.size() == 0)
            {
                pBoneMatrixList[0] = Matrix4x4::s_IDENTITY;

                return;
            }

            assert(maxBoneMatrixCount > static_cast<int32_t>(rMesh.bones_.size()));

            // フレーム数から時間を取得
            FbxTime time;
            time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

            for (size_t i = 0, boneSize = rMesh.bones_.size(); i < boneSize; ++i)
            {
                // ノード名からノードIDを取得し、ノードIDからノードを取得
                const std::string& rNodeName = rMesh.bones_[i].nodeName_;
                int32_t meshNodeId = animationNodeIdDictionary_.at(rNodeName);
                FbxNode* pNode = pAnimationScene_->GetNode(meshNodeId);

                // その時間の行列を取得し、基本姿勢の逆行列を乗算したものをボーンの行列として設定
                FbxAMatrix& rFbxBoneMatrix = pNode->EvaluateGlobalTransform(time);
                Matrix4x4& rBoneMatrix = pBoneMatrixList[i];
                SetMatrix4x4(rFbxBoneMatrix, &rBoneMatrix);

                rBoneMatrix = rBoneMatrix * rMesh.bones_[i].inverseBaseposeMatrix_;
            }
        }


        /*************************************************************//**
         *
         *  @brief  メッシュの解析を行う
         *  @param  FBXのメッシュ
         *  @return 独自のメッシュ
         *
         ****************************************************************/
        S_Mesh C_FbxLoader::C_FbxLoaderImpl::ParseMesh(FbxMesh* pFbxMesh)
        {
            assert(pFbxMesh);

            // メッシュ
            S_Mesh mesh;

            // ノードを取得
            FbxNode* pNode = pFbxMesh->GetNode();
            assert(pNode->GetMaterialCount() == 1);

            // ノード名とマテリアル名を取得
            mesh.nodeName_ = pNode->GetName();
            mesh.parentNodeName_ = pNode->GetParent()->GetName();
            mesh.materialName_ = pNode->GetMaterial(0)->GetName();

            // 基本姿勢の逆行列を取得
            FbxAMatrix inverseBaseposeMatrix = pNode->EvaluateGlobalTransform().Inverse();
            SetMatrix4x4(inverseBaseposeMatrix, &mesh.inverseBaseposeMatrix_);

            // インデックスを取得
            std::vector<int32_t> indices = GetIndicesFromMesh(pFbxMesh);

            // 座標・法線ベクトル・テクスチャ座標・色を取得
            std::vector<Vector3> positions = GetPositionsFromMesh(pFbxMesh, indices);
            std::vector<Vector3> normals = GetNormalsFromMesh(pFbxMesh, indices);
            std::vector<Vector2> textureCoords = GetTextureCoordsFromMesh(pFbxMesh, indices);
            std::vector<Vector4> colors = GetColorsFromMesh(pFbxMesh, indices);

            // ボーンのウェイト
            std::vector<S_BoneWeight> boneWeights;

            // ボーンの情報を取得
            GetBoneDataFromMesh(pFbxMesh, indices, &boneWeights, &mesh.bones_);

            // データが有効か判断するフラグ
            bool enableTextureCoordFlag = (indices.size() == textureCoords.size()) ? true : false;
            bool enableColorFlag = (indices.size() == colors.size()) ? true : false;

            assert(indices.size() == positions.size());
            assert(indices.size() == normals.size());
            assert(enableTextureCoordFlag == true || textureCoords.size() == 0);
            assert(enableColorFlag || colors.size() == 0);
            assert(indices.size() == boneWeights.size() || boneWeights.size() == 0);

            // 頂点のメモリを確保
            std::vector<S_Vertex> vertices;
            vertices.reserve(indices.size());

            for (size_t i = 0, indexSize = indices.size(); i < indexSize; ++i)
            {
                S_Vertex vertex;

                // 頂点に座標・法線ベクトル・テクスチャ座標・色を設定
                vertex.position_ = positions[i];
                vertex.normal_ = normals[i];
                if (enableTextureCoordFlag == true) vertex.textureCoord_ = textureCoords[i];
                if (enableColorFlag == true) vertex.color_ = colors[i];

                // 頂点にウェイトを設定
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

                // 頂点を保持
                vertices.push_back(vertex);
            }

            assert(vertices.size() == indices.size());

            // メッシュの頂点をインデックスを取得
            auto& rMeshVertices = mesh.vertices_;
            rMeshVertices.reserve(vertices.size());

            auto& rMeshIndices = mesh.indices_;
            rMeshIndices.reserve(indices.size());

            for (auto& rVertex : vertices)
            {
                // 重複している頂点を検索し、検索結果により頂点とインデックスを割り振る
                auto iterator = std::find(rMeshVertices.begin(), rMeshVertices.end(), rVertex);

                /* 重複していない */
                if (iterator == rMeshVertices.end())
                {
                    rMeshIndices.push_back(rMeshVertices.size());
                    rMeshVertices.push_back(rVertex);
                }
                /* 重複している */
                else
                {
                    size_t index = std::distance(rMeshVertices.begin(), iterator);
                    rMeshIndices.push_back(index);
                }
            }

            // 頂点の余分なメモリ領域をなくす
            rMeshVertices.shrink_to_fit();

            // 接ベクトルを計算
            if (enableTextureCoordFlag == true) CalculateTangents(&mesh);

            return mesh;
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルの解析を行う
         *  @param  FBXのマテリアル
         *  @return 独自のマテリアル
         *
         ****************************************************************/
        S_Material C_FbxLoader::C_FbxLoaderImpl::ParseMaterial(FbxSurfaceMaterial* pFbxMaterial)
        {
            assert(pFbxMaterial);

            // マテリアル
            S_Material material;

            // 名前を取得
            material.name_ = pFbxMaterial->GetName();

            // マテリアルのデータを保持させる変数
            FbxPropertyT<FbxDouble> materialData;
            FbxPropertyT<FbxDouble3> materialData3;

            // Phongマテリアルの場合
            if (pFbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
            {
                // アンビエントを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Ambient;
                SetVector3(materialData3.Get(), &(material.ambient_));

                // ディフューズを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Diffuse;
                SetVector3(materialData3.Get(), &(material.diffuse_));

                // スペキュラを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Specular;
                SetVector3(materialData3.Get(), &(material.specular_));

                // エミッシブを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Emissive;
                SetVector3(materialData3.Get(), &(material.emissive_));

                // 不透明度を取得
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->TransparencyFactor;
                material.opacity_ = 1.0f - static_cast<float>(materialData.Get());

                // 光沢を取得
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Shininess;
                material.shininess_ = static_cast<float>(materialData.Get());

                // 反射率を取得
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->ReflectionFactor;
                material.reflectivity_ = static_cast<float>(materialData.Get());
            }
            // Lambertマテリアルの場合
            else if (pFbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
            {
                // アンビエントを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Ambient;
                SetVector3(materialData3.Get(), &(material.ambient_));

                // ディフューズを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Diffuse;
                SetVector3(materialData3.Get(), &(material.diffuse_));

                // エミッシブを取得
                materialData3 = static_cast<FbxSurfacePhong*>(pFbxMaterial)->Emissive;
                SetVector3(materialData3.Get(), &(material.emissive_));

                // 不透明度を取得
                materialData = static_cast<FbxSurfacePhong*>(pFbxMaterial)->TransparencyFactor;
                material.opacity_ = 1.0f - static_cast<float>(materialData.Get());
            }

            // マテリアルのプロパティ
            FbxProperty materialProperty;

            // アンビエントテクスチャのプロパティを取得し、テクスチャ名を取得
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sAmbient);
            material.ambientTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            // ディフューズテクスチャのプロパティを取得し、テクスチャ名を取得
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
            material.diffuseTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            // スペキュラテクスチャのプロパティを取得し、テクスチャ名を取得
            materialProperty = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
            material.specularTextureFileName_ = GetTextureFileNameFromProperty(materialProperty);

            return material;
        }


        /*************************************************************//**
         *
         *  @brief  FbxDouble3からVecotr3に値を設定する
         *  @param  FBXのDouble3
         *  @param  3Dベクトル
         *  @return なし
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
         *  @brief  FbxAMatrixからMatrix4x4に値を設定する
         *  @param  FBXのAMatrix
         *  @param  4 * 4の行列
         *  @return なし
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
         *  @brief  プロパティからテクスチャファイル名を取得する
         *  @param  プロパティ
         *  @return テクスチャファイル名
         *
         ****************************************************************/
        std::string C_FbxLoader::C_FbxLoaderImpl::GetTextureFileNameFromProperty(const FbxProperty& rProperty)
        {
            if (rProperty.IsValid() == false) return std::string();

            // テクスチャの数を取得
            auto layeredTextureCount = rProperty.GetSrcObjectCount<FbxLayeredTexture>();

            for (int32_t i = 0; i < layeredTextureCount; ++i)
            {
                // レイヤーテクスチャを取得
                FbxLayeredTexture* pLayeredTexture = rProperty.GetSrcObject<FbxLayeredTexture>(i);

                if (pLayeredTexture)
                {
                    // レイヤーテクスチャの数を取得
                    int32_t layeredTextureCount = pLayeredTexture->GetSrcObjectCount<FbxTexture>();

                    for (int32_t j = 0; j < layeredTextureCount; ++j)
                    {
                        // テクスチャを取得
                        FbxTexture* pTexture = pLayeredTexture->GetSrcObject<FbxTexture>(j);

                        if (pTexture)
                        {
                            // ファイルテクスチャを取得
                            FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>(pTexture);

                            // ファイルパスを取得し、ファイル名のみ返す
                            return Path::C_PathAnalizer::s_GetFileName(pFileTexture->GetFileName());
                        }
                    }
                }
                else
                {
                    // テクスチャを取得
                    FbxTexture* pTexture = rProperty.GetSrcObject<FbxTexture>(i);

                    if (pTexture)
                    {
                        // ファイルテクスチャを取得
                        FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>(pTexture);

                        // ファイルパスを取得し、ファイル名のみ返す
                        return Path::C_PathAnalizer::s_GetFileName(pFileTexture->GetFileName());
                    }
                }
            }

            return std::string();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュからインデックスを取得する
         *  @param  メッシュ
         *  @return インデックス
         *
         ****************************************************************/
        std::vector<int32_t> C_FbxLoader::C_FbxLoaderImpl::GetIndicesFromMesh(FbxMesh* pMesh)
        {
            // ポリゴン数を取得
            int32_t polygonCount = pMesh->GetPolygonCount();

            // インデックスのメモリを確保
            std::vector<int32_t> indices;
            indices.reserve(polygonCount * 3);

            // インデックスを取得
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
         *  @brief  メッシュから座標を取得する
         *  @param  メッシュ
         *  @param  インデックス
         *  @return 座標
         *
         ****************************************************************/
        std::vector<Vector3> C_FbxLoader::C_FbxLoaderImpl::GetPositionsFromMesh(FbxMesh* pMesh,
                                                                                const std::vector<int32_t>& rIndices)
        {
            // 座標のメモリを確保
            std::vector<Vector3> positions;
            positions.reserve(rIndices.size());

            // 座標を取得
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
         *  @brief  メッシュから法線ベクトルを取得する
         *  @param  メッシュ
         *  @param  インデックス
         *  @return 法線ベクトル
         *
         ****************************************************************/
        std::vector<Vector3> C_FbxLoader::C_FbxLoaderImpl::GetNormalsFromMesh(FbxMesh* pMesh,
                                                                              const std::vector<int32_t>& rIndices)
        {
            // 法線ベクトルの要素の数を取得
            int32_t elementNormalCount = pMesh->GetElementNormalCount();
            assert(elementNormalCount == 1);

            // 法線ベクトルの要素を取得
            auto pElementNormal = pMesh->GetElementNormal();

            // マッピングモードとリファレンスモードを取得
            auto mappingMode = pElementNormal->GetMappingMode();
            auto referenceMode = pElementNormal->GetReferenceMode();

            // インデックスと法線ベクトルの配列を取得
            auto& rIndexArray = pElementNormal->GetIndexArray();
            auto& rDirectArray = pElementNormal->GetDirectArray();

            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // 法線ベクトル
            std::vector<Vector3> normals;
            normals.reserve(rIndices.size());

            /* コントロールポイントでマッピング */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // 法線ベクトルのインデックスを取得
                    int32_t normalIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // 法線ベクトルを取得
                    FbxVector4 fbxNormal = rDirectArray.GetAt(normalIndex);
                    // assert(fbxNormal[3] == 1.0);

                    normals.emplace_back(static_cast<float>(fbxNormal[0]),
                                         static_cast<float>(fbxNormal[1]),
                                         static_cast<float>(fbxNormal[2]));
                }
            }
            /* ポリゴンバーテックスでマッピング */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // ポリゴンバーテックスのインデックス
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // 法線ベクトルのインデックスを取得
                    int32_t normalIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // 法線ベクトルを取得
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
                throw std::runtime_error("[ C_FbxLoaderImpl::GetNormalsFromMesh ] : 対応していないマッピングモードです。");
            }

            return normals;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュからテクスチャ座標を取得する
         *  @param  メッシュ
         *  @param  インデックス
         *  @return テクスチャ座標
         *
         ****************************************************************/
        std::vector<Vector2> C_FbxLoader::C_FbxLoaderImpl::GetTextureCoordsFromMesh(FbxMesh* pMesh,
                                                                                    const std::vector<int32_t>& rIndices)
        {
            // テクスチャ座標
            std::vector<Vector2> textureCoords;

            // テクスチャ座標の要素の数を取得
            int32_t elementTextureCoordCount = pMesh->GetElementUVCount();
            if (elementTextureCoordCount < 1) return textureCoords;

            // テクスチャ座標の要素を取得
            auto pElementTextureCoord = pMesh->GetElementUV(0);

            // マッピングモードとリファレンスモードを取得
            auto mappingMode = pElementTextureCoord->GetMappingMode();
            auto referenceMode = pElementTextureCoord->GetReferenceMode();

            // インデックスとテクスチャ座標の配列を取得
            auto& rIndexArray = pElementTextureCoord->GetIndexArray();
            auto& rDirectArray = pElementTextureCoord->GetDirectArray();

            // eDirctかeIndexDirectのみ対応
            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // テクスチャ座標のメモリを確保
            textureCoords.reserve(rIndices.size());

            /* コントロールポイントでマッピング */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // テクスチャ座標のインデックスを取得
                    int32_t textureCoordIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // テクスチャ座標を取得
                    FbxVector2 fbxTextureCoord = rDirectArray.GetAt(textureCoordIndex);
                    textureCoords.emplace_back(static_cast<float>(fbxTextureCoord[0]),
                                               static_cast<float>(fbxTextureCoord[1]));
                }
            }
            /* ポリゴンバーテックスでマッピング */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // ポリゴンバーテックスのインデックス
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // テクスチャ座標のインデックスを取得
                    int32_t textureCoordIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // テクスチャ座標を取得
                    FbxVector2 fbxTextureCoord = rDirectArray.GetAt(textureCoordIndex);

                    textureCoords.emplace_back(static_cast<float>(fbxTextureCoord[0]),
                                               static_cast<float>(fbxTextureCoord[1]));

                    ++indexByPolygonVertex;
                }
            }
            else
            {
                throw std::runtime_error("[ C_FbxLoaderImpl::GetTextureCoordsFromMesh ] : 対応していないマッピングモードです。");
            }

            return textureCoords;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュから色を取得する
         *  @param  メッシュ
         *  @param  インデックス
         *  @return 色
         *
         ****************************************************************/
        std::vector<Vector4> C_FbxLoader::C_FbxLoaderImpl::GetColorsFromMesh(FbxMesh* pMesh,
                                                                             const std::vector<int32_t>& rIndices)
        {
            // 色
            std::vector<Vector4> colors;

            // 色の要素の数を取得
            int32_t elementColorCount = pMesh->GetElementVertexColorCount();
            if (elementColorCount < 1) return colors;

            // 色の要素を取得
            auto pElementColor = pMesh->GetElementVertexColor(0);

            // マッピングモードとリファレンスモードを取得
            auto mappingMode = pElementColor->GetMappingMode();
            auto referenceMode = pElementColor->GetReferenceMode();

            // インデックスとテクスチャ座標の配列を取得
            auto& rIndexArray = pElementColor->GetIndexArray();
            auto& rDirectArray = pElementColor->GetDirectArray();

            // eDirctかeIndexDirectのみ対応
            assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

            // 色のメモリを確保
            colors.reserve(rIndices.size());

            /* コントロールポイントでマッピング */
            if (mappingMode == FbxGeometryElement::eByControlPoint)
            {
                for (auto index : rIndices)
                {
                    // 色のインデックスを取得
                    int32_t colorIndex = (referenceMode == FbxGeometryElement::eDirect) ? index : rIndexArray.GetAt(index);

                    // 色を取得
                    FbxColor fbxColor = rDirectArray.GetAt(colorIndex);
                    colors.emplace_back(static_cast<float>(fbxColor.mRed),
                                        static_cast<float>(fbxColor.mGreen),
                                        static_cast<float>(fbxColor.mBlue),
                                        static_cast<float>(fbxColor.mAlpha));
                }
            }
            /* ポリゴンバーテックスでマッピング */
            else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
            {
                // ポリゴンバーテックスのインデックス
                int32_t indexByPolygonVertex = 0;

                for (size_t i = 0, indexSize = rIndices.size(); i < indexSize; ++i)
                {
                    // 色のインデックスを取得
                    int32_t colorIndex = (referenceMode == FbxGeometryElement::eDirect) ? indexByPolygonVertex : rIndexArray.GetAt(indexByPolygonVertex);

                    // 色を取得
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
                throw std::runtime_error("[ C_FbxLoaderImpl::GetColorsFromMesh ] : 対応していないマッピングモードです。");
            }

            return colors;
        }


        /*************************************************************//**
         *
         *  @brief  メッシュからボーンの情報を取得する
         *  @param  メッシュ
         *  @param  インデックス
         *  @param  ボーンのウェイト
         *  @param  ボーン
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::GetBoneDataFromMesh(FbxMesh* pMesh,
                                                               const std::vector<int32_t>& rIndices,
                                                               std::vector<S_BoneWeight>* pBoneWeights,
                                                               std::vector<S_Bone>* pBones)
        {
            // スキンの数を取得
            int32_t skinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);

            if (skinCount == 0) return;
            assert(skinCount == 1);

            // コントロールポイントの数を取得
            int32_t controlPointsCount = pMesh->GetControlPointsCount();

            // 仮のウェイト
            using TemporaryWeight = std::pair<int32_t, float>;
            std::vector<std::deque<TemporaryWeight>> tempBoneWeights(controlPointsCount);

            // スキンを取得
            FbxSkin* pSkin = static_cast<FbxSkin*>(pMesh->GetDeformer(0, FbxDeformer::eSkin));

            // クラスター数を取得し、ボーンのメモリを確保
            int32_t clusterCount = pSkin->GetClusterCount();
            (*pBones).reserve(clusterCount);

            for (int32_t i = 0; i < clusterCount; ++i)
            {
                // クラスター( ボーン )を取得
                FbxCluster* pCluster = pSkin->GetCluster(i);
                assert(pCluster->GetLinkMode() == FbxCluster::eNormalize);

                // 仮のボーン
                S_Bone tempBone;

                // ボーンのノード名と親ノード名を取得
                FbxNode* pNode = pCluster->GetLink();
                tempBone.nodeName_ = pNode->GetName();
                tempBone.parentNodeName_ = pNode->GetParent()->GetName();

                // コントロールポイントのインデックスの数とインデックスを取得
                int32_t controlPointIndicesCount = pCluster->GetControlPointIndicesCount();
                int32_t* pControlPointIndices = pCluster->GetControlPointIndices();

                // コントロールポイントのウェイトを取得
                double* pControlPointWeights = pCluster->GetControlPointWeights();

                // 各コントロールポイントのウェイトをすべて取得
                for (int32_t j = 0; j < controlPointIndicesCount; ++j)
                {
                    int32_t controlPointIndex = pControlPointIndices[j];
                    tempBoneWeights[controlPointIndex].emplace_back(i, static_cast<float>(pControlPointWeights[j]));
                }

                // 基本姿勢の逆行列を取得する
                auto inverseBaseposeMatrix = pCluster->GetLink()->EvaluateGlobalTransform().Inverse();
                SetMatrix4x4(inverseBaseposeMatrix, &tempBone.inverseBaseposeMatrix_);

                // ボーンを保持
                (*pBones).push_back(tempBone);
            }

            // コントロールポイントに対応したウェイトのメモリを確保
            std::vector<S_BoneWeight> boneWeightsControlPoints;
            boneWeightsControlPoints.reserve(controlPointsCount);

            for (auto& tempBoneWeight : tempBoneWeights)
            {
                // ウェイトをソート
                std::sort(tempBoneWeight.begin(),
                          tempBoneWeight.end(),
                          [](const TemporaryWeight& rWeight, const TemporaryWeight& rAnotherWeight){ return rWeight.second > rAnotherWeight.second; });

                // 4つを超過している場合、4つになるようにウェイトの低いものを排除
                while (tempBoneWeight.size() > 4) tempBoneWeight.pop_back();

                // 4つ未満の場合、4つになるようにダミーを追加
                while (tempBoneWeight.size() < 4) tempBoneWeight.emplace_back(0, 0.0f);

                // インデックスと正規化したウェイトを保持
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

            // ウェイトのメモリを確保
            (*pBoneWeights).reserve(rIndices.size());

            // インデックスでウェイトを取得
            for (auto index : rIndices) (*pBoneWeights).push_back(boneWeightsControlPoints[index]);
        }


        /*************************************************************//**
         *
         *  @brief  接ベクトルを計算する
         *  @param  メッシュ
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::C_FbxLoaderImpl::CalculateTangents(S_Mesh* pMesh)
        {
            auto& rMeshVertices = pMesh->vertices_;
            auto& rMeshIndices = pMesh->indices_;

            size_t vertexCount = rMeshVertices.size();

            // 接ベクトルと従法線ベクトルを求める
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

                // グラム・シュミットの直行化法で接ベクトルを取得
                rMeshVertices[i].tangent_.xyz_ = (rTangent - (Vector3::s_DotProduct(rNormal, rTangent) * rNormal)).GetNormalize();

                // 接空間の掌性を求める
                rMeshVertices[i].tangent_.w_ = (Vector3::s_DotProduct(Vector3::s_CrossProduct(rNormal, rTangent), rBinormal) < 0.0f) ? -1.0f : 1.0f;
            }
        }
    }
}