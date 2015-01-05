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
        C_BaseHitPoint(int32_t maxHitPoint);                        // コンストラクタ
        virtual ~C_BaseHitPoint();                                  // デストラクタ
        virtual void Reset();                                       // 初期状態へリセット
        virtual void Add(int32_t hitPoint);                         // ヒットポイントを加える
        virtual bool CheckRemainHitPoint() const;                   // ヒットポイントが残っているか確認
        virtual int32_t GetHitPoint() const;                        // ヒットポイントを取得
        virtual int32_t GetMaxHitPoint() const;                     // 最大ヒットポイントを取得
        virtual void SetHitPoint(int32_t hitPoint);                 // ヒットポイントを設定
        virtual void SetMaxHitPoint(int32_t maxHitPoint);           // 最大ヒットポイントを設定
    protected:
        int32_t hitPoint_ = 0;                                      ///< @brief ヒットポイント
        int32_t maxHitPoint_ = 0;                                   ///< @brief 最大ヒットポイント
    };
}