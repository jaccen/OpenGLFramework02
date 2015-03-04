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
        using Key = S_Key<T>;                                                                   // Key型
        using LinearFunction = T(*)(const T&, const T&, U);                                     // LinearFunction型
        using HermiteFunction = T(*)(const T&, const T&, const T&, const T&, U);                // HermiteFunction型
        
        
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
                if (loopFlag_ == true)
                {
                    index_ = 0;
                    ++loopCount_;
                }
            }

            S_Key<T> startKey, endKey;

            // キーを2つ取得する。ない場合は1つ分のキーの値を設定し、終了
            if (index_ + 1 < static_cast<int32_t>(keys_.size()))
            {
                startKey = keys_[index_];
                endKey = keys_[index_ + 1];
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
                auto coefficient = static_cast<U>(frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_) - startKey.frame_) / static_cast<U>(endKey.frame_ - startKey.frame_);
                
                value_ = pLinearFunction_(startKey.value_,
                                          endKey.value_,
                                          coefficient);
            }
                break;
            case ecInterpolationType::HERMITE:
            {
                auto coefficient = static_cast<U>(frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_) - startKey.frame_) / static_cast<U>(endKey.frame_ - startKey.frame_);

                value_ = pHermiteFunction_(startKey.value_, 
                                           startKey.tangent_,
                                           endKey.value_,
                                           endKey.tangent_,
                                           coefficient);
            }
                break;
            }

            // フレーム数が次のキーまで達したら、次のキーへ進める
            if (waitFlag_ == false) frameCounter_.CountUp();
            if (endKey.frame_ == frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_)) ++index_;
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


        /*************************************************************//**
         *
         *  @brief  ループ回数を取得する
         *  @param  なし
         *  @return ループ回数
         *
         ****************************************************************/
        int32_t GetLoopCount() const
        {
            return loopCount_;
        }


        /*************************************************************//**
         *
         *  @brief  現在のフレーム数を設定する
         *  @param  フレーム数
         *  @return なし
         *
         ****************************************************************/
        void SetNowFrame(int32_t frame)
        {
            frameCounter_.SetCount(frame);
        }


        /*************************************************************//**
         *
         *  @brief  インデックスを設定する
         *  @param  インデックス
         *  @return なし
         *
         ****************************************************************/
        void SetIndex(int32_t index)
        {
            index_ = index;
        }


        /*************************************************************//**
         *
         *  @brief  線形補間関数を設定する
         *  @param  線形補間関数
         *  @return なし
         *
         ****************************************************************/
        void SetLinearFunction(LinearFunction pLinearFunction)
        {
            pLinearFunction_ = pLinearFunction;
        }


        /*************************************************************//**
         *
         *  @brief  エルミート補間関数を設定する
         *  @param  エルミート補間関数
         *  @return なし
         *
         ****************************************************************/
        void SetHermiteFunction(HermiteFunction pHermiteFunction)
        {
            pHermiteFunction_ = pHermiteFunction;
        }


        /*************************************************************//**
         *
         *  @brief  待機を有効化する
         *  @param  有効か判断するフラグ
         *  @return なし
         *
         ****************************************************************/
        void EnableWait(bool validFlag = true)
        {
            waitFlag_ = validFlag;
        }
    private:
        std::deque<Key> keys_;                                                                  ///< @brief キー
        int32_t index_ = 0;                                                                     ///< @brief インデックス
        Timer::C_FrameCounter frameCounter_;                                                    ///< @brief フレームカウンター
        T value_;                                                                               ///< @brief 値
        bool loopFlag_ = false;                                                                 ///< @brief ループフラグ
        LinearFunction pLinearFunction_ = nullptr;                                              ///< @brief 線形補間関数
        HermiteFunction pHermiteFunction_ = nullptr;                                            ///< @brief エルミート補間関数
        bool waitFlag_ = false;                                                                 ///< @brief 待機フラグ
        int32_t loopCount_ = 0;                                                                 ///< @brief ループ回数
    };
}
