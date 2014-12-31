/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../FbxDefine.h"


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
        //! @brief FBXローダー
        //! @brief FBXファイルのロードを行うクラス
        //!
        //-------------------------------------------------------------
        class C_FbxLoader
        {
        public:
            C_FbxLoader();                                                                              // コンストラクタ
            ~C_FbxLoader();                                                                             // デストラクタ
            void LoadModel(const std::string& rFilePath);                                               // モデルのロード処理
            void LoadAnimation(const std::string& rFilePath, int32_t animationStackNumber = 0);         // アニメーションのロード処理
            void Release();                                                                             // 解放処理
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
            /* 前方宣言 */
            class C_FbxLoaderImpl;

            std::unique_ptr<C_FbxLoaderImpl> upImpl_;                                                   ///< @brief 実装情報
        };
    }
}