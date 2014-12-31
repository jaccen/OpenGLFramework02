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
             *  @param  なし
             *
             ****************************************************************/
            template<typename T>
            C_Cell<T>::C_Cell()
            {
            }


            /*************************************************************//**
             *
             *  @brief  デストラクタ
             *  @param  なし
             *
             ****************************************************************/
            template<typename T>
            C_Cell<T>::~C_Cell()
            {
            }


            /*************************************************************//**
             *
             *  @brief  ツリーのオブジェクトをプッシュする
             *  @param  ツリーのオブジェクト
             *  @return 正常終了：true
             *  @return 異常終了：false
             *
             ****************************************************************/
            template<typename T>
            bool C_Cell<T>::Push(S_TreeObject<T>* pTreeObject)
            {
                if (pTreeObject == nullptr) return false;

                // セルが同じ場合は何もしない
                if (pTreeObject->pCell_ == this) return false;

                // ツリーオブジェクトが1つも登録されてない場合は新規登録
                if (pLastTreeObject_ == nullptr)
                {
                    pLastTreeObject_ = pTreeObject;
                }
                else
                {
                    // 最後に登録したツリーのオブジェクトを更新
                    pTreeObject->pNextObject_ = pLastTreeObject_;
                    pLastTreeObject_->pPreviousObject_ = pTreeObject;
                    pLastTreeObject_ = pTreeObject;
                }

                // セルを登録
                pTreeObject->pCell_ = this;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  最後に登録したツリーのオブジェクトをリムーブするか確認する
             *  @param  ツリーのオブジェクト
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_Cell<T>::LastRemoveCheck(S_TreeObject<T>* pTreeObject)
            {
                if (pLastTreeObject_ == pTreeObject)
                {
                    if (pLastTreeObject_) pLastTreeObject_ = pLastTreeObject_->pNextObject_;
                }
            }


            /*************************************************************//**
             *
             *  @brief  リンクを全てリセットする
             *  @param  ツリーのオブジェクト
             *  @return なし
             *
             ****************************************************************/
            template<typename T>
            void C_Cell<T>::Reset(S_TreeObject<T>* pTreeObject)
            {
                pTreeObject->pNextObject_;

                // 次がnullptrのツリーのオブジェクトまで再帰処理
                if (pTreeObject->pNextObject_) Reset(pTreeObject->pNextObject_);

                // 全てのオブジェクトをnullptrにする
                pTreeObject = nullptr;
            }


            /*************************************************************//**
             *
             *  @brief  最後に登録したツリーのオブジェクトを取得する
             *  @param  なし
             *  @return 最後に登録したツリーのオブジェクト
             *
             ****************************************************************/
            template<typename T>
            S_TreeObject<T>* C_Cell<T>::GetLastTreeObject() const
            {
                return pLastTreeObject_;
            }
        }
    }
}