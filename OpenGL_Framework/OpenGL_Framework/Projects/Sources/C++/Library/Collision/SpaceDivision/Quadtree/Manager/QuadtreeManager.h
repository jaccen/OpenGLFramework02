/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Object/TreeObject.h"
#include "../Creater/CollisionListCreater.h"
#include <functional>


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
            /* 別名 */
            template <typename T>
            using CollisionFunction = std::function<void(T*, T*)>;                  // CollisionFunction型


            //-------------------------------------------------------------
            //!
            //! @brief クアッドツリーマネージャー
            //! @brief 4分木の管理を行うクラス
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_QuadtreeManager
            {
            public:
                /* 別名 */
                using CollisionFunction = CollisionFunction<T>;                                 // CollisionFunction型を省略


                explicit C_QuadtreeManager(uint32_t collisionObjectEstimateCount = 1000);       // コンストラクタ
                virtual ~C_QuadtreeManager();                                                   // デストラクタ
                void Initialize(float leftPosition,                                             // 初期化処理
                                float topPosition,
                                float rightPosition,
                                float bottomPosition,
                                const CollisionFunction& rCollisionFunction,
                                uint32_t level = 4);
                void AllRemove();                                                               // 衝突オブジェクトを全て除去
                bool Regist(float borderLeftPosition,                                           // 衝突オブジェクトの登録処理
                            float borderTopPosition,
                            float borderRightPosition,
                            float borderBottomPosition,
                            T* pCollisionObject);
                bool Update();                                                                  // 更新処理
                void SetCollisionFunction(const CollisionFunction& rCollisionFunction);         // 衝突処理を行う関数を設定
            private:
                std::vector<S_TreeObject<T>> treeObjects_;                                      ///< @brief 4分木に登録するオブジェクト
                uint32_t treeObjectCount_ = 0;                                                  ///< @biref 4分木に登録するオブジェクトの数
                std::deque<T*> pCollisionList_;                                                 ///< @brief 衝突判定を行うオブジェクトのリスト
                C_CollisionListCreater<T> collisionListCreater_;                                ///< @brief 衝突リスト作成機
                CollisionFunction collisionFunction_;                                           ///< @brief 衝突処理を行う関数
            };
        }
    }
}


/* 実装 */
#include "QuadtreeManagerImpl.h"