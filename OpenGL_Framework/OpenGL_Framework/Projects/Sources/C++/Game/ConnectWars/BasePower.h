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
    //! @brief ベースパワー
    //! @brief パワーの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BasePower
    {
    public:
        C_BasePower(int32_t power);                             // コンストラクタ
        virtual ~C_BasePower();                                 // デストラクタ
        virtual void Add(int32_t power);                        // 値を足す
        virtual void Subtract(int32_t power);                   // 値を引く
        virtual int32_t GetValue() const;                       // 値を取得
        virtual void SetValue(int32_t power);                   // 値を設定
    protected:
        int32_t value_ = 0;                                     ///< @brief 値
    };
}