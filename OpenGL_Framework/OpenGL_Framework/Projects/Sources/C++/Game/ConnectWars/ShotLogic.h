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
    //! @brief ショットロジック
    //! @brief 射撃のロジックのインターフェース
    //!
    //-------------------------------------------------------------
    class C_ShotLogic
    {
    public:
        C_ShotLogic(int32_t shotInterval);                  // コンストラクタ
        virtual ~C_ShotLogic();                             // デストラクタ
        bool Process();                                     // 処理
        void SetShotInterval(int32_t shotInterval);         // 射撃の間隔を設定
    protected:
        int32_t shotInterval_ = 1;                          ///< @brief 射撃の間隔
    private:
        virtual bool DoProcess() = 0;                       // 非公開の処理
    };
}