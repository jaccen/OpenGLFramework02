/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../OpenGlDefine.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* 前方宣言 */
    class C_PrimitiveBuffer;

    
    using PrimitiveBufferPtr = std::shared_ptr<C_PrimitiveBuffer>;                                  // PrimitiveBufferPtr型


    //-------------------------------------------------------------
    //!
    //! @brief プリミティブバッファ
    //! @brief プリミティブ描画に用いるバッファを表すクラス
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBuffer
    {
    public:
        /* 生成情報 */
        template<typename T, typename U>
        struct S_CreateData
        {
            T* pVertices_ = nullptr;                                                                ///< @brief 頂点
            uint32_t vertexCount_ = 0;                                                              ///< @brief 頂点数
            uint32_t vertexAttributeCount_ = 0;                                                     ///< @brief 頂点の属性数
            uint32_t* vertexAttributeElementCountList_ = nullptr;                                   ///< @brief 頂点の属性の要素数リスト
            DataEnum* vertexAttributeDataTypeList_ = nullptr;                                       ///< @brief 頂点の属性のデータ型リスト
            ModifyEnum vertexModifyType_ = 0;                                                       ///< @brief 頂点の修正の種類
            U* pIndices_ = nullptr;                                                                 ///< @brief インデックス
            uint32_t indexCount_ = 0;                                                               ///< @brief インデックス数
            ModifyEnum indexModifyType_ = Modify::s_STATIC;                                         ///< @brief インデックスの修正の種類
        };

        template<typename T, typename U = uint16_t>
        C_PrimitiveBuffer(T* pVertices,                                                             // コンストラクタ
                          uint32_t vertexCount,
                          uint32_t vertexAttributeCount,
                          uint32_t vertexAttributeElementCountList[],
                          DataEnum vertexAttributeDataTypeList[],
                          ModifyEnum vertexModifyType,
                          U* pIndices = nullptr,
                          uint32_t indexCount = 0,
                          ModifyEnum indexModifyType = Modify::s_STATIC);
        template<typename T, typename U = uint16_t>
        C_PrimitiveBuffer(const S_CreateData<T, U>& rCreateData);                                   // コンストラクタ
        virtual ~C_PrimitiveBuffer();                                                               // デストラクタ
        VertexArrayObjectHandle GetVertexArrayObjectHandle() const;                                 // 頂点配列オブジェクトハンドルを取得
        IndexBufferObjenctHandle GetIndexBufferObjectHandle() const;                                // インデックスバッファオブジェクトハンドルを取得
        uint32_t GetVertexCount() const;                                                            // 頂点数を取得
        uint32_t GetIndexCount() const;                                                             // インデックス数を取得
        template<typename T>
        void RewriteVertices(T vertices[],                                                          // 頂点の書き換え
                             int32_t rewriteVertexCount,
                             int32_t firstVertexNumber = 0);   
        template<typename T>
        void RewriteIndices(T indices[],                                                            // インデックスの書き換え
                            int32_t rewriteIndexCount,
                            int32_t firstIndexNumber = 0);
        template<typename T, typename U = uint16_t>
        static PrimitiveBufferPtr s_Create(T* pVertices,                                            // 生成処理
                                           uint32_t vertexCount,
                                           uint32_t vertexAttributeCount,
                                           uint32_t vertexAttributeElementCountList[],
                                           DataEnum vertexAttributeDataTypeList[],
                                           ModifyEnum vertexModifyType,
                                           U* pIndices = nullptr,
                                           uint32_t indexCount = 0,
                                           ModifyEnum indexModifyType = Modify::s_STATIC);
        template<typename T, typename U = uint16_t>
        static PrimitiveBufferPtr s_Create(const S_CreateData<T, U>& rCreateData);                  // 生成処理
    private:
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                       ///< @brief 頂点配列オブジェクトハンドル
        VertexBufferObjectHandle vertexBufferObjectHandle_ = 0;                                     ///< @brief 頂点バッファオブジェクトハンドル
        IndexBufferObjenctHandle indexBufferObjectHandle_ = 0;                                      ///< @brief インデックスバッファオブジェクトハンドル
        uint32_t vertexCount_ = 0;                                                                  ///< @brief 頂点数
        uint32_t indexCount_ = 0;                                                                   ///< @brief インデックス数
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  頂点
     *  @param  頂点数
     *  @param  頂点の属性数
     *  @param  頂点の属性の要素数のリスト
     *  @param  頂点の属性の型のリスト
     *  @param  頂点の修正の種類
     *  @param  インデックス
     *  @param  インデックス数
     *  @param  インデックスの修正の種類
     *
     ****************************************************************/
    template<typename T, typename U>
    C_PrimitiveBuffer::C_PrimitiveBuffer(T* pVertices,
                                         uint32_t vertexCount,
                                         uint32_t vertexAttributeCount,
                                         uint32_t vertexAttributeElementCountList[],
                                         DataEnum vertexAttributeDataTypeList[],
                                         ModifyEnum vertexModifyType,
                                         U* pIndices,
                                         uint32_t indexCount,
                                         ModifyEnum indexModifyType) :

        // 頂点とインデックス数
        vertexCount_(vertexCount),
        indexCount_(indexCount)

    {
        // 頂点バッファオブジェクトとインデックスバッファオブジェクトを作成
        glGenBuffers(1, &vertexBufferObjectHandle_);
        glGenBuffers(1, &indexBufferObjectHandle_);

        // 頂点バッファをバインドし、全てのデータを転送
        glBindBuffer(Buffer::s_VERTEX, vertexBufferObjectHandle_);
        glBufferData(Buffer::s_VERTEX, vertexCount * sizeof(T), pVertices, vertexModifyType);

        // 頂点配列オブジェクトを作成とバインド
        glGenVertexArrays(1, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);

        // バイトオフセット
        int32_t byteOffset = 0;

        for (size_t i = 0; i < vertexAttributeCount; ++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, vertexAttributeElementCountList[i], vertexAttributeDataTypeList[i], GL_FALSE, sizeof(T), reinterpret_cast<GLubyte*>(byteOffset));

            if (DataType::s_DOUBLE == vertexAttributeDataTypeList[i])
            {
                byteOffset += vertexAttributeElementCountList[i] * 8;
            }
            else if (DataType::s_BOOL == vertexAttributeDataTypeList[i])
            {
                byteOffset += vertexAttributeElementCountList[i] * 1;
            }
            else
            {
                byteOffset += vertexAttributeElementCountList[i] * 4;
            }
        }

        if (pIndices)
        {
            // インデックスバッファオブジェクトをバインドしデータを転送
            glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle_);
            glBufferData(Buffer::s_INDEX, indexCount * sizeof(U), pIndices, indexModifyType);
        }

        // 各バッファをアンバインド
        glBindBuffer(Buffer::s_VERTEX, 0);
        glBindBuffer(Buffer::s_VERTEX, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  生成情報
     *
     ****************************************************************/
    template<typename T, typename U>
    C_PrimitiveBuffer::C_PrimitiveBuffer(const S_CreateData<T, U>& rCreateData) : C_PrimitiveBuffer(rCreateData.pVertices_,
                                                                                                    rCreateData.vertexCount_,
                                                                                                    rCreateData.vertexAttributeCount_,
                                                                                                    rCreateData.vertexAttributeElementCountList_,
                                                                                                    rCreateData.vertexAttributeDataTypeList_,
                                                                                                    rCreateData.vertexModifyType_,
                                                                                                    rCreateData.pIndices_,
                                                                                                    rCreateData.indexCount_,
                                                                                                    rCreateData.indexModifyType_)
    {
    }


    /*************************************************************//**
     *
     *  @brief  頂点の書き換えを行う
     *  @param  頂点
     *  @param  書き換える頂点数
     *  @param  先頭の頂点番号
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_PrimitiveBuffer::RewriteVertices(T vertices[],
                                            int32_t rewriteVertexCount,
                                            int32_t firstVertexNumber)
    {
        // 頂点バッファをバインド
        glBindBuffer(Buffer::s_VERTEX, vertexBufferObjectHandle_);

        // 頂点バッファをマップ
        T* pVertices = reinterpret_cast<T*>(glMapBuffer(Buffer::s_VERTEX, GL_WRITE_ONLY));
        assert(pVertices);

        // 頂点バッファのデータを書き換え
        int32_t loopTotalCount = firstVertexNumber + rewriteVertexCount;
        int32_t indexOfArgumentVertex = 0;

        for (int32_t i = firstVertexNumber; i < loopTotalCount; ++i)
        {
            pVertices[i] = vertices[indexOfArgumentVertex];
            ++indexOfArgumentVertex;
        }

        // 頂点バッファをアンマップ
        glUnmapBuffer(Buffer::s_VERTEX);

        // 頂点バッファをアンバインド
        glBindBuffer(Buffer::s_VERTEX, 0);
    }


    /*************************************************************//**
     *
     *  @brief  インデックスの書き換えを行う
     *  @param  インデックス
     *  @param  書き換えるインデックス数
     *  @param  先頭のインデックス番号
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void C_PrimitiveBuffer::RewriteIndices(T indices[],
                                           int32_t rewriteIndexCount,
                                           int32_t firstIndexNumber)
    {
        // インデックスバッファをバインド
        glBindBuffer(Buffer::s_INDEX, vertexBufferObjectHandle_);

        // インデックスバッファをマップ
        T* pIndices = reinterpret_cast<T*>(glMapBuffer(Buffer::s_INDEX, GL_WRITE_ONLY));
        assert(pVertices);

        // インデックスバッファのデータを書き換え
        int32_t loopTotalCount = firstVertexNumber + rewriteVertexCount;
        int32_t indexOfArgumentIndex = 0;

        for (int32_t i = firstIndexNumber; i < loopTotalCount; ++i)
        {
            pIndices[i] = indices[indexOfArgumentIndex];
            ++indexOfArgumentIndex;
        }

        // インデックスバッファをアンマップ
        glUnmapBuffer(Buffer::s_INDEX);

        // インデックスバッファをアンバインド
        glBindBuffer(Buffer::s_INDEX, 0);
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  頂点
     *  @param  頂点数
     *  @param  頂点の属性数
     *  @param  頂点の属性の要素数のリスト
     *  @param  頂点の属性の型のリスト
     *  @param  頂点の修正の種類
     *  @param  インデックス
     *  @param  インデックス数
     *  @param  インデックスの修正の種類
     *  @return ポリゴンバッファ
     *
     ****************************************************************/
    template<typename T, typename U>
    PrimitiveBufferPtr C_PrimitiveBuffer::s_Create(T* pVertices,
                                                   uint32_t vertexCount,
                                                   uint32_t vertexAttributeCount,
                                                   uint32_t vertexAttributeElementCountList[],
                                                   DataEnum vertexAttributeDataTypeList[],
                                                   ModifyEnum vertexModifyType,
                                                   U* pIndices,
                                                   uint32_t indexCount,
                                                   ModifyEnum indexModifyType)
    {
        return std::make_shared<C_PrimitiveBuffer>(pVertices,
                                                   vertexCount,
                                                   vertexAttributeCount,
                                                   vertexAttributeElementCountList,
                                                   vertexAttributeDataTypeList,
                                                   vertexModifyType,
                                                   pIndices,
                                                   indexCount,
                                                   indexModifyType);
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  生成情報
     *  @return ポリゴンバッファ
     *
     ****************************************************************/
    template<typename T, typename U>
    PrimitiveBufferPtr C_PrimitiveBuffer::s_Create(const S_CreateData<T, U>& rCreateData)
    {
        return s_Create(rCreateData.pVertices_,
                        rCreateData.vertexCount_,
                        rCreateData.vertexAttributeCount_,
                        rCreateData.vertexAttributeElementCountList_,
                        rCreateData.vertexAttributeDataTypeList_,
                        rCreateData.vertexModifyType_,
                        rCreateData.pIndices_,
                        rCreateData.indexCount_,
                        rCreateData.indexModifyType_);
    }
}
