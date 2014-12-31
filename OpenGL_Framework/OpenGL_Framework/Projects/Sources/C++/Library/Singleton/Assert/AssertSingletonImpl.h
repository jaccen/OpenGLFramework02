//-------------------------------------------------------------
//!
//! @brief シングルトン
//! @brief シングルトン関連の名前空間
//!
//-------------------------------------------------------------
namespace Singleton
{

#pragma region 静的メンバ変数の初期化


    /* 唯一のインスタンス */
    template<class T> T* C_AssertSingleton<T>::s_pInstance = nullptr;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<class T>
    inline C_AssertSingleton<T>::C_AssertSingleton()
    {
        assert(s_pInstance == nullptr && "[ C_AssertSingleton::C_AssertSingleton ] 同時に2つ以上のインスタンスは生成できません。");

        s_pInstance = static_cast<T*>(this);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<class T>
    inline C_AssertSingleton<T>::~C_AssertSingleton()
    {
        assert(s_pInstance && "[ C_AssertSingleton::~C_AssertSingleton ] インスタンスの二重解放です。");

        s_pInstance = nullptr;
    }


    /*************************************************************//**
     *
     *  @brief  唯一のインスタンスを取得する
     *  @param  なし
     *  @return 唯一のインスタンス
     *
     ****************************************************************/
    template<class T>
    inline T* C_AssertSingleton<T>::s_GetInstance()
    {
        return s_pInstance;
    }
}