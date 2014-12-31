/* ヘッダファイル */
#include "FbxLoaderImpl.h"


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
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_FbxLoader::C_FbxLoader() :

            // 実装情報
            upImpl_(std::make_unique<C_FbxLoaderImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_FbxLoader::~C_FbxLoader()
        {
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルのモデルのロード処理を行う
         *  @param  ファイルパス
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::LoadModel(const std::string& rFilePath)
        {
            upImpl_->LoadModel(rFilePath);
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルのアニメーションのロード処理を行う
         *  @param  ファイルパス
         *  @param  アニメーションスタック番号
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::LoadAnimation(const std::string& rFilePath, int32_t animationStackNumber)
        {
            upImpl_->LoadAnimation(rFilePath, animationStackNumber);
        }


        /*************************************************************//**
         *
         *  @brief  FBXファイルの解放処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_FbxLoader::Release()
        {
            upImpl_->Release();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュの数を取得する
         *  @param  なし
         *  @return メッシュの数
         *
         ****************************************************************/
        uint32_t C_FbxLoader::GetMeshCount() const
        {
            return upImpl_->GetMeshCount();
        }


        /*************************************************************//**
         *
         *  @brief  メッシュを取得する
         *  @param  インデックス
         *  @return メッシュ
         *
         ****************************************************************/
        const S_Mesh& C_FbxLoader::GetMesh(uint32_t index) const
        {
            return upImpl_->GetMesh(index);
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルの数を取得する
         *  @param  なし
         *  @return マテリアルの数
         *
         ****************************************************************/
        uint32_t C_FbxLoader::GetMaterialCount() const
        {
            return upImpl_->GetMaterialCount();
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルのIDを取得する
         *  @param  マテリアル名
         *  @return マテリアルのID
         *
         ****************************************************************/
        int32_t C_FbxLoader::GetMaterialId(const std::string& rName) const
        {
            return upImpl_->GetMaterialId(rName);
        }


        /*************************************************************//**
         *
         *  @brief  マテリアルを取得する
         *  @param  マテリアルのID
         *  @return マテリアル
         *
         ****************************************************************/
        const S_Material& C_FbxLoader::GetMaterial(int32_t materialId) const
        {
            return upImpl_->GetMaterial(materialId);
        }


        /*************************************************************//**
         *
         *  @brief  アニメーションの開始フレーム数を取得する
         *  @param  なし
         *  @return アニメーションの開始フレーム数
         *
         ****************************************************************/
        int64_t C_FbxLoader::GetAnimationStartFrame() const
        {
            return upImpl_->GetAnimationStartFrame();
        }


        /*************************************************************//**
         *
         *  @brief  アニメーションの終了フレーム数を取得する
         *  @param  なし
         *  @return アニメーションの終了フレーム数
         *
         ****************************************************************/
        int64_t C_FbxLoader::GetAnimationEndFrame() const
        {
            return upImpl_->GetAnimationEndFrame();
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
        void C_FbxLoader::GetMeshMatrix(int64_t frame, uint32_t meshIndex, Matrix4x4* pMeshMatrix) const
        {
            upImpl_->GetMeshMatrix(frame, meshIndex, pMeshMatrix);
        }


        /*************************************************************//**
         *
         *  @brief  ボーンの行列を取得する
         *  @param  フレーム数
         *  @param  メッシュのインデックス
         *  @param  ボーン
         *  @return なし
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