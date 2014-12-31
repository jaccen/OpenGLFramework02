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
            /*************************************************************//**
             *
             *  @brief  コンストラクタ
             *  @param  衝突オブジェクトの見積もり数
             *
             ****************************************************************/
            template<typename T>
            C_QuadtreeManager<T>::C_QuadtreeManager(uint32_t collisionObjectEstimateCount) :

                // ツリーオブジェクト
                treeObjects_(collisionObjectEstimateCount)

            {
            }


            /*************************************************************//**
             *
             *  @brief  デストラクタ
             *  @param  なし
             *
             ****************************************************************/
            template<typename T>
            C_QuadtreeManager<T>::~C_QuadtreeManager()
            {
            }


            /*************************************************************//**
             *
             *  @brief  初期化処理を行う
             *  @param  左端座標
             *  @param  上端座標
             *  @param  右端座標
             *  @param  下端座標
             *  @param  衝突処理を行う関数
             *  @param  レベル
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::Initialize(float leftPosition,
                                                  float topPosition,
                                                  float rightPosition,
                                                  float bottomPosition,
                                                  const CollisionFunction& rCollisionFunction,
                                                  uint32_t level)
            {
                collisionListCreater_.Initialize(leftPosition, topPosition, rightPosition, bottomPosition, level);
            }


            /*************************************************************//**
             *
             *  @brief  衝突オブジェクトを全て除去する
             *  @param  衝突オブジェクト
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::AllRemmove()
            {
                for (size_t i = 0; i < treeObjectCount_; ++i) treeObjects_[i].Remove();
                treeObjectCount_ = 0;
            }


            /*************************************************************//**
             *
             *  @brief  衝突オブジェクトを登録する
             *  @param  境界範囲の左端座標
             *  @param  境界範囲の上端座標
             *  @param  境界範囲の右端座標
             *  @param  境界範囲の下端座標
             *  @param  衝突オブジェクト
             *  @return 正常終了：true
             *  @return 異常終了：false
             *
             ****************************************************************/
            template<typename T>
            bool C_QuadtreeManager<T>::Regist(float borderLeftPosition,
                                              float borderTopPosition,
                                              float borderRightPosition,
                                              float borderBottomPosition,
                                              T* pCollisionObject)
            {
                if (treeObjectCount_ >= treeObjects_.size()) treeObjects_.emplace_back();

                // 衝突リスト生成機に登録
                treeObjects_[treeObjectCount_].pObject_ = pCollisionObject;
                if (collisionListCreater_.Regist(borderLeftPosition,
                                                 borderTopPosition,
                                                 borderRightPosition,
                                                 borderBottomPosition,
                                                 &treeObjects_[treeObjectCount_]) == false)
                {
                    return false;
                }

                ++treeObjectCount_;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  更新処理を行う
             *  @param  なし
             *  @return 正常終了：true
             *  @return 異常終了：false
             *
             ****************************************************************/
            template<typename T>
            bool C_QuadtreeManager<T>::Update()
            {
                uint32_t collisionCount = 0;

                // 衝突リストを取得
                pCollisionList_.clear();
                if (liner4TreeManager_.GetCollisionList(&pCollisionList_, &collisionCount) == false) return false;

                // 衝突処理を行う
                for (size_t i = 0; i < collisionCount; ++i)
                {
                    collisionFunction_(pCollisionList_[i * 2], pCollisionList_[i * 2 + 1]);
                }
            }


            /*************************************************************//**
             *
             *  @brief  衝突処理を行う関数を設定
             *  @param  衝突処理を行う関数
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::SetCollisionFunction(const CollisionFunction& rCollisionFunction)
            {
                collisionFunction_ = rCollisionFunction;
            }
        }
    }
}