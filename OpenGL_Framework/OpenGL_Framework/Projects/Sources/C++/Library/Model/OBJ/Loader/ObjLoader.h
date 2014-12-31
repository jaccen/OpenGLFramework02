/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../ObjDefine.h"


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
    //! @brief OBJ
    //! @brief OBJ関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        //-------------------------------------------------------------
        //!
        //! @brief OBJローダー
        //! @brief OBJファイルのパースを行うクラス
        //!
        //-------------------------------------------------------------
        class C_ObjLoader
        {
        public:
            C_ObjLoader();                                                                              // コンストラクタ
            ~C_ObjLoader();                                                                             // デストラクタ
            void Load(const std::string& rFilePath);                                                    // ロード処理
            void Release();                                                                             // 解放処理
            const S_Mesh& GetMesh() const;                                                              // メッシュを取得
            uint32_t GetMaterialCount() const;                                                          // マテリアル数を取得
            int32_t GetMaterialIndex(const std::string& rName) const;                                   // マテリアルインデックスを取得
            const S_Material& GetMaterial(int32_t index) const;                                         // マテリアルを取得
            const S_Material& GetMaterial(const std::string& rName) const;                              // マテリアルを取得
        private:
            /* 前方宣言 */
            class C_ObjLoaderImpl;

            std::unique_ptr<C_ObjLoaderImpl> upImpl_;                                                   ///< @brief 実装情報
        };
    }
}