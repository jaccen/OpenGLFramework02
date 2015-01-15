/* ヘッダファイル */
#include "SmallBeamOption.h"
#include "OptionDropState.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *  @param  座標
     *
     ****************************************************************/
    C_SmallBeamOption::C_SmallBeamOption(const std::string& rId, int32_t type) : C_BaseOption(rId, type)
    {
        // ヒットポイントを生成
        upHitPoint_ = std::make_unique<C_BaseHitPoint>(10000);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SmallBeamOption::~C_SmallBeamOption()
    {
    }
}