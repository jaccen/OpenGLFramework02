/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Key.h"
#include "../Timer/Counter/Frame/FrameCounter.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief キーフレーム
//! @brief キーフレーム関連の名前空間
//!
//-------------------------------------------------------------
namespace KeyFrame
{
    //-------------------------------------------------------------
    //!
    //! @brief キーアニメーション
    //! @brief キーフレームアニメーションを行うクラス
    //!
    //-------------------------------------------------------------
    template<typename T, typename U = float>
    class C_KeyAnimation
    {
    public:
        /* 別名 */
        using Key = S_Key<T>;                                               // Key型
        using LinearFunction = T(*)(T, T, U);                               // LinearFunction型
        using HermiteFunction = T(*)(T, T, T, T, U);                        // HermiteFunction型
        
        
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_KeyAnimation()
        {
        }


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        ~C_KeyAnimation()
        {
        }


        /*************************************************************//**
         *
         *  @brief  更新処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void Update()
        {
            if (keys_.size() == 0) return;
        
            // インデックスが最後で、かつループをする場合インデックスをリセット
            if (index_ == keys_.size() - 1)
            {
                if (loopFlag_ == true) index_ = 0;
            }

            // キーを2つ取得する。ない場合は1つ分のキーの値を設定し、終了
            if (index_ + 1 < keys_.size())
            {
                startKey = keys_[index];
                endKey = keys_[index + 1];
            }
            else
            {
                value_ = keys_[index_].value_;
                return;
            }
            
            /* 補間のタイプによって、処理を行う */
            switch (keys_[index_].interpolationType_)
            {
            case ecInterpolationType::CONSTANT:
            {
                value_ = startKey.value_;
            }
                break;
            case ecInterpolationType::LINEAR:
            {
                value_ = pLinearFunction_(startKey.value_,
                                          endKey.value_,
                                          static_cast<U>(frameCounter_.GetCount()) / static_cast<U>(endKey.frame_ - startKey.frame_);
            }
                break;
            case ecInterpolationType::HERMITE:
            {
                value_ = pHermiteFunction_(startKey.value_, 
                                           startKey.tangent_,
                                           endKey.value_,
                                           endKey.tangent_,
                                           static_cast<U>(frameCounter_.GetCount()) / static_cast<U>(endKey.frame_ - startKey.frame_);
            }
                break;
            }

            // フレーム数が次のキーまで達したら、次のキーへ進める
            frameCounter_.CountUp();
            if (endKey.frame_ == frameCounter_.GetCount()) ++index_;
        }


        /*************************************************************//**
         *
         *  @brief  キーの追加を行う
         *  @param  キー
         *  @return なし
         *
         ****************************************************************/
        void Add(const Key& rKey)
        {
            keys_.push_back(rKey);
        }


        /*************************************************************//**
         *
         *  @brief  キーを全て除去する
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void AllRemove()
        {
            keys_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ループを有効化する
         *  @param  有効か判断するフラグ
         *  @return なし
         *
         ****************************************************************/
        void EnableLoop(bool validFlag = true)
        {
            loopFlag_ = validFlag;
        }


        /*************************************************************//**
         *
         *  @brief  値を取得する
         *  @param  なし
         *  @return 値
         *
         ****************************************************************/
        T GetValue() const
        {
            return value_;
        }


        /*************************************************************//**
         *
         *  @brief  値を取得する
         *  @param  なし
         *  @return 値
         *
         ****************************************************************/
        T GetValue(uint32_t index) const
        {
            return keys_[index].value_;
        }


        /*************************************************************//**
         *
         *  @brief  キーの数を取得する
         *  @param  なし
         *  @return キーの数
         *
         ****************************************************************/
        uint32_t GetKeyCount() const
        {
            return keys_.size();
        }


        /*************************************************************//**
         *
         *  @brief  今のフレーム数を取得する
         *  @param  なし
         *  @return 今のフレーム数
         *
         ****************************************************************/
        int32_t GetNowFrame() const
        {
            return frameCounter_.GetCount();
        }
    private:
        std::deque<Key> keys_;                                              ///< @brief キー
        int32_t index_ = 0;                                                 ///< @brief インデックス
        Timer::C_FrameCounter frameCounter_;                                ///< @brief フレームカウンター
        T value_;                                                           ///< @brief 値
        bool loopFlag_ = false;                                             ///< @brief ループフラグ
        LinearFunction pLinearFunction_ = nullptr;                          ///< @brief 線形補間関数
        HermiteFunction pHermiteFunction_ = nullptr;                        ///< @brief エルミート補間関数
    };
}
