/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"


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
    //! @brief ムーブロジック( インターフェース )
    //! @brief 移動のロジックのインターフェースクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class IC_MoveLogic
    {
    public:
        IC_MoveLogic() = default;                           //!< @brief コンストラクタ
        virtual ~IC_MoveLogic() = default;                  //!< @brief デストラクタ
        virtual void Process(T* pSomething) = 0;            //!< @brief 処理
    };
}