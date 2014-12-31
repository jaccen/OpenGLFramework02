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
    //! @brief アサートシングルトン
    //! @brief アサートによりインスタンスを1つに保障するクラス
    //!
    //-------------------------------------------------------------
    template<class T>
    class C_AssertSingleton
    {
    public:
        C_AssertSingleton();                                                            // コンストラクタ
        virtual ~C_AssertSingleton();                                                   // デストラクタ
        static T* s_GetInstance();                                                      // インスタンスを取得
    private:
        static T* s_pInstance;                                                          ///< @brief 唯一のインスタンス

        C_AssertSingleton(const C_AssertSingleton& rOther) = delete;                    //!< @brief コピーコンストラクタ
        C_AssertSingleton& operator=(const C_AssertSingleton& rOther) = delete;         //!< @brief 代入演算子のオーバーロード
    };
}


/* 実装 */
#include "AssertSingletonImpl.h"
