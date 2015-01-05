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
        virtual void Add(int32_t power);                        // パワーを加える
        virtual int32_t GetPower() const;                       // パワーを取得
        virtual void SetPower(int32_t power);                   // パワーを設定
    protected:
        int32_t power_ = 0;                                     ///< @brief パワー
    };
}