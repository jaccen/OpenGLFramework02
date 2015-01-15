/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../ModelDefine.h"
#include <vector>


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
        /* 前方宣言 */
        class C_ModelLoader;


        /* 別名 */
        using ModelLoaderPtr = std::shared_ptr<C_ModelLoader>;                                          // ModelLoaderPtr型


        //-------------------------------------------------------------
        //!
        //! @brief モデルローダー
        //! @brief 自作フォーマットのモデルファイルのロードを行うクラス
        //!
        //-------------------------------------------------------------
        class C_ModelLoader
        {
        public:
            C_ModelLoader();                                                                            // コンストラクタ
            virtual ~C_ModelLoader();                                                                   // デストラクタ
            void LoadModel(const std::string& rModelFilePath);                                          // モデルのロード処理
            void LoadMaterial(const std::string& rMaterialFilePath);                                    // マテリアルのロード処理
            void LoadAnimation(const std::string& rAnimationFilePath);                                  // アニメーションのロード処理
            void Release();                                                                             // 解放処理
            uint32_t GetMeshCount() const;                                                              // メッシュ数を取得
            uint32_t GetBoneCount(uint32_t meshIndex) const;                                            // ボーン数を取得
            uint32_t GetMaterialCount() const;                                                          // マテリアル数を取得
            const S_Mesh& GetMesh(uint32_t index) const;                                                // メッシュを取得
            const S_Material& GetMaterial(uint32_t index) const;                                        // マテリアルを取得
            uint32_t GetAnimationEndFrame() const;                                                      // アニメーションの終了フレーム数を取得
            const Matrix4x4& GetMeshAnimationMatrix(uint32_t frame, uint32_t meshIndex) const;          // メッシュのアニメーション行列を取得
            const Matrix4x4& GetBoneAnimationMatrix(uint32_t frame,                                     // ボーンのアニメーション行列を取得
                                                    uint32_t meshIndex,
                                                    uint32_t boneIndex) const;

            static ModelLoaderPtr s_Create();                                                           // 生成処理
        private:
            std::vector<S_Mesh> meshList_;                                                              ///< @brief メッシュリスト
            std::vector<S_Material> materialList_;                                                      ///< @brief マテリアルリスト
            uint32_t animationEndFrame_ = 0;                                                            ///< @brief アニメーション終了フレーム数

            void GetModelFromFileData(char* pFileData);                                                 ///< @brief ファイルデータからモデルを取得
            void GetMaterialFromFileData(char* pFileData);                                              ///< @brief ファイルデータからマテリアルを取得
            void GetAnimationFromFileData(char* pFileData);                                             ///< @brief ファイルデータからアニメーションを取得
        };
    }
}