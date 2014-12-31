/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Cell/Cell.h"
#include <vector>
#include <forward_list>
#include <deque>


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
            //! @brief リニアクアッドツリーマネージャー
            //! @brief 線形4分木空間を管理するクラス
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_CollisionListCreater
            {
            public:
                C_CollisionListCreater();                                                       // コンストラクタ
                ~C_CollisionListCreater();                                                      // デストラクタ
                void Initialize(float left,                                                     // 初期化処理
                                float top,
                                float right,
                                float bottom,
                                uint32_t level = 4);
                bool Regist(float borderLeft,                                                   // ツリーのオブジェクトの登録処理
                            float borderTop,
                            float borderRight,
                            float borderBottom,
                            S_TreeObject<T>* pTreeObject);
                bool GetCollisionList(std::deque<T*>* ppCollisionPairList,                      // 衝突判定のリストを取得
                                      uint32_t* pCollisionCount);
            private:
                std::unique_ptr<std::unique_ptr<C_Cell<T>>[]> upCells_;                         ///< @brief 線形空間
                std::vector<uint32_t> exponentialValues_;                                       ///< @brief べき乗数値配列
                uint32_t level_ = 0;                                                            ///< @brief 空間のレベル
                float width_ = 0.0f;                                                            ///< @brief 領域の幅
                float height_ = 0.0f;                                                           ///< @brief 領域の高さ
                float left_ = 0.0f;                                                             ///< @brief 領域の左端
                float top_ = 0.0f;                                                              ///< @brief 領域の上端
                float unitWidth_ = 0.0f;                                                        ///< @brief 最小レベル空間の幅
                float unitHeight_ = 0.0f;                                                       ///< @brief 最小レベル空間の高さ
                uint32_t cellNumber_ = 0;                                                       ///< @brief 空間の数

                void CalculateExponentialValue(uint32_t level);                                 // べき乗数値配列を計算
                void SetTerritory(float left,                                                   // 領域を設定
                                  float top,
                                  float right,
                                  float bottom);
                uint32_t GetMortonNumberFromAABB(float borderLeft,                              // 境界範囲からモートン番号を取得
                                                 float borderTop,
                                                 float borderRight,
                                                 float borderBottom);
                uint32_t ConvertPointToMortonNumber(float positionX, float positionY);          // 点をモートン番号へ変換
                uint32_t BitSeparate32(uint32_t value);                                         // 1bit飛びで32ビットに分割
                void CreateCell(uint32_t element);                                              // 空間を作成
                void CreateCollisionList(uint32_t cellElement,                                  // 衝突リストを作成
                                         std::deque<T*>* ppCollisionStack,
                                         std::deque<T*>* ppCollisionPairList);
            };
        }
    }
}

/* 実装 */
#include "CollisionListCreaterImpl.h"