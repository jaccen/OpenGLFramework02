/* 二重インクルード防止 */
#pragma once


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
            /* 前方宣言 */
            template<typename T>
            class C_Cell;


            //-------------------------------------------------------------
            //!
            //! @brief ツリーオブジェクト
            //! @brief ツリーのオブジェクトを表す構造体
            //!
            //-------------------------------------------------------------
            template<typename T>
            struct S_TreeObject
            {
                C_Cell<T>* pCell_ = nullptr;                        ///< @brief 登録空間
                T* pObject_ = nullptr;                              ///< @brief オブジェクト
                S_TreeObject<T>* pPreviousObject_ = nullptr;        ///< @brief 前のオブジェクト
                S_TreeObject<T>* pNextObject_ = nullptr;            ///< @brief 次のオブジェクト

                /*************************************************************//**
                 *
                 *  @brief  リストから自身をリムーブする
                 *  @param  なし
                 *  @return 正常終了：true
                 *  @return 異常終了：false
                 *
                 ****************************************************************/
                bool Remove()
                {
                    if (pCell_ == nullptr) return false;

                    // 最後のツリーのオブジェクトか確認
                    pCell_->LastRemoveCheck(this);

                    // 前後のオブジェクトを繋ぎかえる
                    if (pPreviousObject_) pPreviousObject_->pNextObject_ = pNextObject_;
                    if (pNextObject_) pNextObject_->pPreviousObject_ = pNextObject_;

                    pPreviousObject_ = nullptr;
                    pNextObject_ = nullptr;
                    pCell_ = nullptr;

                    return true;
                }
            };
        }
    }
}