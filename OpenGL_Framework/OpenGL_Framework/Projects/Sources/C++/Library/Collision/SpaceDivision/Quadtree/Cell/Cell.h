/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Object/TreeObject.h"


//-------------------------------------------------------------
//!
//! @brief コリジョン
//! @brief 衝突関連の名前空間
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief スペースディビジョン
    //! @brief 空間分割関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SpaceDivision
    {
        //-------------------------------------------------------------
        //!
        //! @brief クアッドツリー
        //! @brief 4分木関連の名前空間
        //!
        //-------------------------------------------------------------
        namespace Quadtree
        {
            //-------------------------------------------------------------
            //!
            //! @brief セル
            //! @brief 空間を表すクラス
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_Cell
            {
            public:
                C_Cell();                                                   // コンストラクタ
                ~C_Cell();                                                  // デストラクタ
                bool Push(S_TreeObject<T>* pTreeObject);                    // ツリーのオブジェクトをプッシュ
                void LastRemoveCheck(S_TreeObject<T>* pTreeObject);         // 最後に登録したツリーのオブジェクトをリムーブするか確認
                void Reset(S_TreeObject<T>* pTreeObject);                   // リンクを全てリセット
                S_TreeObject<T>* GetLastTreeObject() const;                 // 最後に登録したツリーのオブジェクトを取得
            private:
                S_TreeObject<T>* pLastTreeObject_ = nullptr;                ///< @brief 最後に登録したツリーのオブジェクト
            };
        }
    }
}


/* 実装 */
#include "CellImpl.h"