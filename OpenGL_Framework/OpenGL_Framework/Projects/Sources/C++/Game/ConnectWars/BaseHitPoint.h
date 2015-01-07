/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ベースヒットポイント
    //! @brief ヒットポイントの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseHitPoint
    {
    public:
        C_BaseHitPoint(int32_t maxValue);                       // コンストラクタ
        virtual ~C_BaseHitPoint();                              // デストラクタ
        virtual void Reset();                                   // 初期状態へリセット
        virtual void Add(int32_t value);                        // 値を足す
        virtual void Subtract(int32_t value);                   // 値を引く
        virtual bool CheckRemainValue() const;                  // 値が残っているか確認
        virtual int32_t GetValue() const;                       // 値を取得
        virtual int32_t GetMaxValue() const;                    // 最大値を取得
        virtual void SetValue(int32_t value);                   // 値を設定
        virtual void SetMaxValue(int32_t maxValue);             // 最大値を設定
    protected:
        int32_t value_ = 0;                                     ///< @brief 値
        int32_t maxValue_ = 0;                                  ///< @brief 最大値
    };
}