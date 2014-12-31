/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief シングルトン
//! @brief シングルトン関連の名前空間
//!
//-------------------------------------------------------------
namespace Singleton
{
    //-------------------------------------------------------------
    //!
    //! @brief シングルトン
    //! @brief インスタンスを1つに保障するクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Singleton
    {
    public:
        static T* s_GetInstance();                                      // 唯一のインスタンスを取得
    protected:
        C_Singleton();                                                  // コンストラクタ
        virtual ~C_Singleton(); 		                                // デストラクタ
    private:
        C_Singleton(const C_Singleton& rOther) = delete;                //!< @brief コピーコンストラクタ
        C_Singleton& operator=(const C_Singleton& rOther) = delete;     //!< @brief 代入演算子のオーバーロード
    };
}


/* 実装 */
#include "SingletonImpl.h"
