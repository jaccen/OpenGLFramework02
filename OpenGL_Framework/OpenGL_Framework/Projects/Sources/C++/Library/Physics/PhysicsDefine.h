/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /* 別名 */
    using Vector3 = btVector3;                                                  // Vector3型
    using Vector4 = btVector4;                                                  // Vector4型
    using Matrix3x3 = btMatrix3x3;                                              // Matrix3x3型
    using Quaternion = btQuaternion;                                            // Quaternion型
    using Transform = btTransform;                                              // Transform型
    using SoftBodyInfo = btSoftBodyWorldInfo;                                   // SoftBodyInfo型
    using CollisionCallbackFunction = ContactProcessedCallback;                 // CollisionCallbackFanction型
    using SimulationSubstepCallbackFunction = btInternalTickCallback;           // SimulationSubstepCallbackFunction型
    

    namespace
    {
        /* 形状の種類 */
        namespace ShapeType
        {
            const int32_t s_BOX = BOX_SHAPE_PROXYTYPE;                          ///< @brief ボックス形状
            const int32_t s_SPHERE = SPHERE_SHAPE_PROXYTYPE;                    ///< @brief 球形状
            const int32_t s_CAPSULE = CAPSULE_SHAPE_PROXYTYPE;                  ///< @brief カプセル形状
            const int32_t s_COMPOUND = COMPOUND_SHAPE_PROXYTYPE;                ///< @brief 複合形状

        }

        /* アクティベーションステート */
        namespace ActivationState
        {
            const int32_t s_ACTIVE_TAG = ACTIVE_TAG;                            ///< @brief 通常の状態
            const int32_t s_DISABLE_DEACTIVATION = DISABLE_DEACTIVATION;        ///< @brief 非活動化の無効化状態
            const int32_t s_DISABLE_SIMULATION = DISABLE_SIMULATION;            ///< @brief シミュレーションの無効化状態
        }
    }
    
    /** 向き */
    enum class ecDirection
    {
        X,
        Y,
        Z
    };


    /*************************************************************//**
     *
     *  @brief  ソフトボディ情報を作成する
     *  @param  なし
     *
     ****************************************************************/
    inline SoftBodyInfo* CreateSoftBodyInfo()
    {
        return new(_aligned_malloc(sizeof(SoftBodyInfo), __alignof(SoftBodyInfo))) SoftBodyInfo;
    }


    //-------------------------------------------------------------
    //!
    //! @brief ソフトボディインフォーデリータ―
    //! @brief ソフトボディ情報のデリータ
    //!
    //-------------------------------------------------------------
    class C_SoftBodyInfoDeleter
    {
    public:
        /* 関数呼び出し演算子のオーバーロード */
        void operator ()(SoftBodyInfo* pSoftBodyInfo)
        {
            // セルのメモリを解放
            pSoftBodyInfo->m_sparsesdf.Reset();

            // デストラクタを明示的に呼び出し、メモリを解放
            pSoftBodyInfo->~btSoftBodyWorldInfo();
            ::_aligned_free(pSoftBodyInfo);
        }
    };
}